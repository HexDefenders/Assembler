# assembler
## Introduction and Overview
This assembler can be used to take in a file of simplified CR16 code, and output the machine code into a seperate file. The machine code output is in four hexadecimal characters, and arranged in little-endian format; this means that the two leftmost hexadecimal characters correspond to the rightmost eight instruction bits, and vice-versa. Each hexadecimal machine code instruction is printed onto it's own line. The designated input file is a file with the name "input.txt", and the output is appended to a file titled "test.dat". (Both file names can be switched in the main.c file.)

The assembler makes two passes of the given assembly code: the first pass finds label declarations, and houses them in an array of structs that contain the label name, and the program counter where the label declaration resides. The second pass then progresses through the code and translates it into machine code, substituting the label call with either the direct address (in the case of Jump instructions), or the 2's complement value of the distance between the label call and the label declaration (for branch instructions).

The assembler is built in C, Flex, and Bison. Make sure that the computer utilizing the compiler has support for the three languages.

## User Manual
The assembler requires five files to be compiled: parser.y, main.c, lexer.l, helpers.h, and helpers.c. These five files must all be in the same folder for the assembler to compile correctly. Currently, there is also an "input.txt" file that is required for the assembler to run, and must also be in the same file. Additionally, the output will be *appended* to an output file, which means that if the assembler is run twice in a row, the output file will have both run's output inside the same file. Because of this, it is important to ensure that the output file is empty before each run, or that the output file is deleted before each run.

For ease of use, a Makefile has been included. To fully compile and run the assembler, one simply has to use two commands:
```
make all
./parser
```
The first command compiles all the files, and the second runs the fully compiled assembler. There is no output to the command line that shows a successful run, so be sure to check that the output file has been instantiated or filled.

Without use of the Makefile, the assembler can be compiled by using the following commands:
```
flex lexer.l
bison parser.y
gcc main.c helpers.c parser.c lexer.c -o [NAME]
```
with [NAME] substituted with any name of the user's choosing. Just be sure that when calling the assembler you use **./[NAME]** instead of the original **./parser**. There has also been a **make clean** command included in the Makefile, which will remove all files except the original five and Makefile.

## Programmer's Manual
The assembler can take instructions that start with an Opcode, followed by one or two arguments seperated by a comma, and terminated by a semicolon. For example:
```
ADDI R1, R2;
CMP $2, R4;
JEQ L1;
```
Currently, all Opcodes must be fully upper-case. Register values may either have an upper- or lower-case 'R', and hexadecimal codes may have either an upper- or lower-case x. Immediate values - such as those used in ADDI or CMPI - can either be in hexadecimal format, or as a signed integer followed by the '$' character. Per the ECE3710 ISA, hexadecimal numbers may only be two bytes long, and immediate values must stay between positive and negative 127.

### Labels
As stated in the Introduction, Label support is included. Labels may contain any mix of numbers or letters, so long as the label begins with a letter. When declaring a label, the label name must terminate with a colon ':'. For example:
```
L1: ADDI 0x2a, R2;   %L1: as a label declaration
    SUB R2, R4;
    JLE L1;          %L1 as a label call
```
Label declarations can also be on their own line, with the associated operation encoding beginning on the line below. Label addresses can be up to four bytes long. In this case, the full value of the address will be contained in the register R1 to be read. Any value previously inside R1 will be over-written.

## The Files
### lexer.l
The lexer file is written in Flex, and is used to declare what patterns of input correspond to what 'tokens'. These tokens will be passed to the parser as a way to build patterns of grammer. For the lexer, anything included between square brackets - [] - is included in the rule. These correspond to ASCII table values, and can thus be given a range of inputs. For example,
```
[A-Z]    searches for any character between A and Z, only upper-case
[a-z]    searches for any character between a and z, only lower-case
[A-z]    searches for all characters between A and z. In the ASCII table, this includes [, \, ] , ^, _, and ` as well
```
The asterisk \* can be used after a bracketed group to denote that zero or more of the range can be matched, while the plus sign + can be used to denote that one or more of the range can be matched. The caret ^ can be used inside the square brackets to tell the lexer to match all characters *except* those in the square brackets, so [^\n], for example, will match everything but the newline character. The period . can be used to mean *all other characters*. 

These rules can be mixed to find specific inputs. For example, the rule for label declarations in the lexer.l file is
```
[A-Za-z][0-9A-Za-z]*":"       {/*C code contained here*/ return TOKEN_NAME;}
```
which means match a pattern that starts with capital or lower-case letter [A-Za-z], then hase zero or more of any number or letter [0-9A-Za-z]\*, then ends with a colon ":".

The lexer usually begins in the state INITIAL, or 0. However, in our code we want to start in an alternative state, <FIRST_PASS>, which only registers label patterns. To do this, we have this code in the lexer.l file:
```
%{
if(first_enter)
   BEGIN(FIRST_PASS);
%}
```
This code forces the lexer to start in state FIRST_PASS when the integer first_enter is not zero. The lexer than follows the rules contained in the FIRST_PASS secion of the lexer, until it reaches the end of input. The token <<EOF>> is the lexer's given token for the end of file. Usually, this is not a rule that is altered, but in FIRST_PASS, since it is not the 'main' lexer section, we use this token to pass control back to the INITIAL state, which contains the rules for parsing everything except the Label declarations.
  
  ### parser.y
  The parser is written in Bison. This file contains a set of grammer 'rules' to match the order in which tokens are passed in from the lexer. The tokens that have values attached (from the lexer) must have the value type declared in a union to be held. The token must also be declared with this type:
  ```
  %union {
  char *op;
  int num;
}

%token <op> OPCODE          OPCODE has a char* value associated with the OPCODE token
%token EOP                  EOP does not have any variable value attached, so doesn't need a <type> declaration
%type <num> lab;            The grammer type lab returns a <num> value
```
Grammer rules that return a value must also be declared to have a type, as seen in the last line of the above code. Grammer rules can be recursive when matching multiple lines of similar structures, and can call other grammer rules. For example,
```
instr: OPCODE arg SEMI       {$$ = $2}  //instr returns what is returned by arg
;
arg: HEXVAL   {$$ = $1} //This is the default rule. returns the value assigned to HEXVAL in the lexer.
| REGISTER;
```
instr will search for an OPCODE, then either a HEXVAL or REGISTER, before returning to instr and search for a SEMI. Once this pattern is satisfied, it will return to whatever called instr.

As stated previously, rules can have return values. These return values are denoted by $$. Unless stated otherwise, the return value is set to $$ = $1, where $1 is the first token in the line. This can be a called rule's returned value, or a defined token. The grammer rule will be returned to it's called rule after the last token of the line is matched. The only rule that doesn't follow this is the starting rule, which will only terminate when the end of the input is reached.

### helpers.c, helpers.h
Contained in this file are the C helper functions for the parser. toHex(char*,int,int) returns the hex value of a line as a string, and toLE(char*) prints it in little-endian format. holdLabel(char*, int) is used when defining labels on the first pass, keeping an array of struts that hold the label's name and program counter number. needLabel(char*) is used when calling a label, and searches through the array of structs to find it's matching label declaration, and returns the program counter value of the declared label.

helpers.h is the header file for the helper functions, and declares extern variables used across all the files (like the program counter integer).

### main.c
The main file. This is where yyparse (the call that stars the parser and lexer) is called, and where the name of the input and output files is declared. Also where output is rerounted from the terminal to the output file. Finally, main.c is where we fill the rest of the output file with zeros, so ensure the processer can correctly run the code.
