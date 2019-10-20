#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void toLE(char *hexCode){
  
  printf("%c%c\n%c%c\n", hexCode[0], hexCode[1], hexCode[2], hexCode[3]);
}

char iToC(int num){
  switch(num){
  case 0: return '0';
  case 1: return '1';
  case 2: return '2';
  case 3: return '3';
  case 4: return '4';
  case 5: return '5';
  case 6: return '6';
  case 7: return '7';
  case 8: return '8';
  case 9: return '9';
  case 10: return 'a';
  case 11: return 'b';
  case 12: return 'c';
  case 13: return 'd';
  case 14: return 'e';
  case 15: return 'f';
  }
  return '0';
}

char* toHex(char *op, int src, int dest){
  char imm[2];
  char opcode;
  char rDest;
  char immHi;
  char immLo;
  
  if(strcmp(op, "ADDI") == 0) {
    opcode = '5';
    rDest = iToC(dest);
    if(src < 16 && src >= 0){
      immHi = '0';
      immLo = iToC(src);
    } else {
      sprintf(imm, "%x", src);
      immHi = imm[0];
      immLo = imm[1];
    }
  }
  else if(strcmp(op, "ADD") == 0) {
    opcode = '0';
    rDest = iToC(dest);
    immHi = '5';
    immLo = iToC(src);
  }
  else if(strcmp(op, "SUBI") == 0) {
    opcode = '9';
    rDest = iToC(dest);
    if(src < 16 && src >= 0){
      immHi = '0';
      immLo = iToC(src);
    } else {
      sprintf(imm, "%x", src);
      immHi = imm[0];
      immLo = imm[1];
    }
  }
  else if(strcmp(op, "SUB") == 0) {
    opcode = '0';
    rDest = iToC(dest);
    immHi = '9';
    immLo = iToC(src);
  }
  else if(strcmp(op, "CMPI") == 0) {
    opcode = 'b';
    rDest = iToC(dest);
    if(src < 16 && src >= 0){
      immHi = '0';
      immLo = iToC(src);
    } else {
      sprintf(imm, "%x", src);
      immHi = imm[0];
      immLo = imm[1];
    }
  }
  else if(strcmp(op, "CMP") == 0) {
    opcode = '0';
    rDest = iToC(dest);
    immHi = 'b';
    immLo = iToC(src);
  }
  else if(strcmp(op, "ANDI") == 0) {
    opcode = '1';
    rDest = iToC(dest);
    if(src < 16){
      immHi = '0';
      immLo = iToC(src);
    } else {
      sprintf(imm, "%x", src);
      immHi = imm[0];
      immLo = imm[1];
    }
  }
  else if(strcmp(op, "AND") == 0) {
    opcode = '0';
    rDest = iToC(dest);
    immHi = '1';
    immLo = iToC(src);
  }
  else if(strcmp(op, "ORI") == 0) {
    opcode = '2';
    rDest = iToC(dest);
    if(src < 16){
      immHi = '0';
      immLo = iToC(src);
    } else {
      sprintf(imm, "%x", src);
      immHi = imm[0];
      immLo = imm[1];
    }
  }
  else if(strcmp(op, "OR") == 0) {
    opcode = '0';
    rDest = iToC(dest);
    immHi = '2';
    immLo = iToC(src);
  }
  else if(strcmp(op, "XORI") == 0) {
    opcode = '3';
    rDest = iToC(dest);
    if(src < 16){
      immHi = '0';
      immLo = iToC(src);
    } else {
      sprintf(imm, "%x", src);
      immHi = imm[0];
      immLo = imm[1];
    }
  }
  else if(strcmp(op, "XOR") == 0) {
    opcode = '0';
    rDest = iToC(dest);
    immHi = '3';
    immLo = iToC(src);
  }
  else if(strcmp(op, "MOVI") == 0) {
    opcode = 'd';
    rDest = iToC(dest);
    if(src < 16){
      immHi = '0';
      immLo = iToC(src);
    } else {
      sprintf(imm, "%x", src);
      immHi = imm[0];
      immLo = imm[1];
    }
  }
  else if(strcmp(op, "MOV") == 0) {
    opcode = '0';
    rDest = iToC(dest);
    immHi = 'd';
    immLo = iToC(src);
  }
  else if(strcmp(op, "LSHI") == 0) {
    opcode = '8';
    rDest = iToC(dest);
    immLo = iToC(src);
    if(src >= 0){
      immHi = 0;
    } else {
      immHi = 1;
    }
  }
  else if(strcmp(op, "LSH") == 0) {
    opcode = '8';
    rDest = iToC(dest);
    immHi = '4';
    immLo = iToC(src);
  }
  else if(strcmp(op, "LUI") == 0) {
    opcode = 'f';
    rDest = iToC(dest);
    if(src < 16 && src >= 0){
      immHi = '0';
      immLo = iToC(src);
    } else {
      sprintf(imm, "%x", src);
      immHi = imm[0];
      immLo = imm[1];
    }
  }
  else if(strcmp(op, "LOAD") == 0) {
    opcode = '4';
    rDest = iToC(dest);
    immHi = '0';
    immLo = iToC(src);
  }
  else if(strcmp(op, "STOR") == 0) {
    opcode = '4';
    rDest = iToC(dest);
    immHi = '4';
    immLo = iToC(src);
  }
  else if(strcmp(op, "BEQ") == 0) {
    opcode = 'c';
    rDest = '0';
    if(src < 16 && src >= 0){
      immHi = '0';
      immLo = iToC(src);
    } else {
      sprintf(imm, "%x", src);
      immHi = imm[0];
      immLo = imm[1];    
    }
  }
  else if(strcmp(op, "BNE") == 0) {
    opcode = 'c';
    rDest = '1';
    if(src < 16 && src >= 0){
      immHi = '0';
      immLo = iToC(src);
    } else {
      sprintf(imm, "%x", src);
      immHi = imm[0];
      immLo = imm[1];  
    }
  }
  else if(strcmp(op, "BGE") == 0) {
    opcode = 'c';
    rDest = 'd';
    if(src < 16 && src >= 0){
      immHi = '0';
      immLo = iToC(src);
    } else {
      sprintf(imm, "%x", src);
      immHi = imm[0];
      immLo = imm[1];    
    }
  }
  else if(strcmp(op, "BCS") == 0) {
    opcode = 'c';
    rDest = '2';
    if(src < 16 && src >= 0){
      immHi = '0';
      immLo = iToC(src);
    } else {
      sprintf(imm, "%x", src);
      immHi = imm[0];
      immLo = imm[1];   
    }
  }
  else if(strcmp(op, "BCC") == 0) {
    opcode = 'c';
    rDest = '3';
    if(src < 16 && src >= 0){
      immHi = '0';
      immLo = iToC(src);
    } else {
      sprintf(imm, "%x", src);
      immHi = imm[0];
      immLo = imm[1];    
    }
  }
  else if(strcmp(op, "BHI") == 0) {
    opcode = 'c';
    rDest = '4';
    if(src < 16 && src >= 0){
      immHi = '0';
      immLo = iToC(src);
    } else {
      sprintf(imm, "%x", src);
      immHi = imm[0];
      immLo = imm[1];   
    }
  }
  else if(strcmp(op, "BLS") == 0) {
    opcode = 'c';
    rDest = '5';
    if(src < 16 && src >= 0){
      immHi = '0';
      immLo = iToC(src);
    } else {
      sprintf(imm, "%x", src);
      immHi = imm[0];
      immLo = imm[1];  
    }
  }
  else if(strcmp(op, "BLO") == 0) {
    opcode = 'c';
    rDest = 'a';
    if(src < 16 && src >= 0){
      immHi = '0';
      immLo = iToC(src);
    } else {
      sprintf(imm, "%x", src);
      immHi = imm[0];
      immLo = imm[1];  
    }
  }
  else if(strcmp(op, "BHS") == 0) {
    opcode = 'c';
    rDest = 'b';
    if(src < 16 && src >= 0){
      immHi = '0';
      immLo = iToC(src);
    } else {
      sprintf(imm, "%x", src);
      immHi = imm[0];
      immLo = imm[1];    
    }
  }
  else if(strcmp(op, "BGT") == 0) {
    opcode = 'c';
    rDest = '6';
    if(src < 16 && src >= 0){
      immHi = '0';
      immLo = iToC(src);
    } else {
      sprintf(imm, "%x", src);
      immHi = imm[0];
      immLo = imm[1];    
    }
  }
  else if(strcmp(op, "BLE") == 0) {
    opcode = 'c';
    rDest = '7';
    if(src < 16 && src >= 0){
      immHi = '0';
      immLo = iToC(src);
    } else {
      sprintf(imm, "%x", src);
      immHi = imm[0];
      immLo = imm[1];    
    }
  }
  else if(strcmp(op, "BFS") == 0) {
    opcode = 'c';
    rDest = '8';
    if(src < 16 && src >= 0){
      immHi = '0';
      immLo = iToC(src);
    } else {
      sprintf(imm, "%x", src);
      immHi = imm[0];
      immLo = imm[1];  
    }
  }
  else if(strcmp(op, "BFC") == 0) {
    opcode = 'c';
    rDest = '9';
    if(src < 16 && src >= 0){
      immHi = '0';
      immLo = iToC(src);
    } else {
      sprintf(imm, "%x", src);
      immHi = imm[0];
      immLo = imm[1];   
    }
  }
  else if(strcmp(op, "BLT") == 0) {
    opcode = 'c';
    rDest = 'c';
    if(src < 16 && src >= 0){
      immHi = '0';
      immLo = iToC(src);
    } else {
      sprintf(imm, "%x", src);
      immHi = imm[0];
      immLo = imm[1];
    }
  }
  else if(strcmp(op, "BUC") == 0) {
    opcode = 'c';
    rDest = 'e';
    if(src < 16 && src >= 0){
      immHi = '0';
      immLo = iToC(src);
    } else {
      sprintf(imm, "%x", src);
      immHi = imm[0];
      immLo = imm[1];
    }
  }
  else if(strcmp(op, "JEQ") == 0) {
    opcode = '4';
    immHi = 'c';
    immLo = iToC(dest);
    rDest = '0';    
  }
  else if(strcmp(op, "JNE") == 0) {
    opcode = '4';
    immHi = 'c';
    immLo = iToC(dest);
    rDest = '1';   
  }
  else if(strcmp(op, "JGE") == 0) {
    opcode = '4';
    immHi = 'c';
    immLo = iToC(dest);
    rDest = 'd';   
  }
  else if(strcmp(op, "JCS") == 0) {
    opcode = '4';
    immHi = 'c';
    immLo = iToC(dest);
    rDest = '2';   
  }
  else if(strcmp(op, "JCC") == 0) {
    opcode = '4';
    immHi = 'c';
    immLo = iToC(dest);
    rDest = '3';   
  }
  else if(strcmp(op, "JHI") == 0) {
    opcode = '4';
    immHi = 'c';
    immLo = iToC(dest);
    rDest = '4';  
  }
  else if(strcmp(op, "JLS") == 0) {
    opcode = '4';
    immHi = 'c';
    immLo = iToC(dest);
    rDest = '5';   
  }
  else if(strcmp(op, "JLO") == 0) {
    opcode = '4';
    immHi = 'c';
    immLo = iToC(dest);
    rDest = 'a';   
  }
  else if(strcmp(op, "JHS") == 0) {
    opcode = '4';
    immHi = 'c';
    immLo = iToC(dest);
    rDest = 'b';   
  }
  else if(strcmp(op, "JGT") == 0) {
    opcode = '4';
    immHi = 'c';
    immLo = iToC(dest);
    rDest = '6';   
  }
  else if(strcmp(op, "JLE") == 0) {
    opcode = '4';
    immHi = 'c';
    immLo = iToC(dest);
    rDest = '7';   
  }
  else if(strcmp(op, "JFS") == 0) {
    opcode = '4';
    immHi = 'c';
    immLo = iToC(dest);
    rDest = '8';   
  }
  else if(strcmp(op, "JFC") == 0) {
    opcode = '4';
    immHi = 'c';
    immLo = iToC(dest);
    rDest = '9';   
  }
  else if(strcmp(op, "JLT") == 0) {
    opcode = '4';
    immHi = 'c';
    immLo = iToC(dest);
    rDest = 'c';   
  }
  else if(strcmp(op, "JUC") == 0) {
    opcode = '4';
    immHi = 'c';
    immLo = iToC(dest);
    rDest = 'e';   
  }
  else if(strcmp(op, "JAL") == 0) {
    opcode = '4';
    rDest = iToC(dest);
    immHi = '8';
    immLo = iToC(src);
  }
  
  char hexCode[4];
  hexCode[0] = opcode;
  hexCode[1] = rDest;
  hexCode[2] = immHi;
  hexCode[3] = immLo;
  char *cp = hexCode;
  
  return cp;
}

int main(){
  char *cp;
  char *op = "ADDI";

  cp = toHex(op,1,1);
  toLE(cp);

  return 0;
}
