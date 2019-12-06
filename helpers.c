#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.h"

int j = 0;
int n = 0;

struct Label heldLoc[100];
struct Label dataHold[50];

void checkJump(char *op){
  //printf("GOTHERE, PC = %d, Opcode = %s | ", pc, op);
  if(op[0] == 'j' || op[0] == 'J') {
    pc = pc + 2;
}
 //printf("NEW PC = %d\n", pc);
}

int getaddr(char *lab){
  //printf("GOTHERE, PC = %d, Opcode = %s \n ", pc, lab);
  int k;
  int ret = 14;
  for(k = 0; k < n; k++){
    if(strcmp(lab, dataHold[k].name) == 0){
      //printf("AND HERE: %s, %d\n", dataHold[k].name, dataHold[k].location);
      int place = dataHold[k].location;
      unsigned int lower = place & 0xff;
      unsigned int upper = (place >> 8) & 0xff;
      toLE(toHex("MOVI", lower, 14));
      toLE(toHex("LUI", upper, 14));
      pc = pc + 2;
      return ret;
    }
  }
  return 0;
}

void setdata(char *lab, int loc){
  struct Label label;
  label.name = lab;
  label.location = loc;
  dataHold[n] = label;
  //printf("SETDATA: %s, LOCATION: %d \n", lab, loc);
  n++;
}

int needLabel(char *op){
  int len = strlen(op);
  char *check = malloc(len+2);
  strcpy(check, op);
  check[len] = ':';
  check[len+1] = '\0';
  int k;
  for(k = 0; k < j; k++){
    if(strcmp(check, heldLoc[k].name) == 0){
      free(check);
      return heldLoc[k].location;
    }
  }
  free(check);
  return 0;
}

void holdLabel(char *op, int line){
  struct Label lab;
  lab.name = op;
  lab.location = line;
  heldLoc[j] = lab;
  //printf("LABEL: %s, ROW: %d\n", lab.name, lab.location);
  j++;
}

void toLE(char *hexCode){
  printf("%c%c%c%c\n", hexCode[0], hexCode[1], hexCode[2], hexCode[3]);
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

char* toHex(char *inOp, int src, int dest){
  char imm[20];
  
  //allows for upper or lowercase op codes
  int a = strlen(inOp);
  int i;
  char *op;
  op = (char*)malloc(a);
  strcpy(op, inOp);
  for(i = 0; i < a; i++)
    op[i] = toupper((unsigned char)op[i]);
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
      int a = strlen(imm)-1;
      immHi = imm[a-1];
      immLo = imm[a];
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
      int a = strlen(imm)-1;
      immHi = imm[a-1];
      immLo = imm[a];
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
      int a = strlen(imm)-1;
      immHi = imm[a-1];
      immLo = imm[a];
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
    if(src < 16 && src >= 0){
      immHi = '0';
      immLo = iToC(src);
    } else {
      sprintf(imm, "%x", src);
      int a = strlen(imm)-1;
      immHi = imm[a-1];
      immLo = imm[a];
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
    if(src < 16 && src >= 0){
      immHi = '0';
      immLo = iToC(src);
    } else {
      sprintf(imm, "%x", src);
      int a = strlen(imm)-1;
      immHi = imm[a-1];
      immLo = imm[a];
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
    if(src < 16 && src >= 0){
      immHi = '0';
      immLo = iToC(src);
    } else {
      sprintf(imm, "%x", src);
      int a = strlen(imm)-1;
      immHi = imm[a-1];
      immLo = imm[a];
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
    if(src < 16 && src >= 0){
      immHi = '0';
      immLo = iToC(src);
    } else {
      sprintf(imm, "%x", src);
      int a = strlen(imm)-1;
      immHi = imm[a-1];
      immLo = imm[a];
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
    if(src >= 0){
      immHi = '0';
      immLo = iToC(src);
    } else {
      immHi = '1';
      immLo = iToC(-src);
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
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
    }
  }
  else if(strcmp(op, "LOAD") == 0) {
    opcode = '4';
    rDest = iToC(src);
    immHi = '0';
    immLo = iToC(dest);
  }
  else if(strcmp(op, "STOR") == 0) {
    opcode = '4';
    rDest = iToC(src);
    immHi = '4';
    immLo = iToC(dest);
  }
  else if(strcmp(op, "BEQ") == 0) {
    opcode = 'c';
    rDest = '0';
    if(!trigger){
      if(dest < 16 && dest >= 0){
        immHi = '0';
        immLo = iToC(dest);
      } else {
        sprintf(imm, "%x", dest);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
    } else {
      int PCtoDisp = src - pc;
      if(PCtoDisp < 16 && PCtoDisp >= 0){
        immHi = '0';
        immLo = iToC(PCtoDisp);
      } else {
        sprintf(imm, "%x", PCtoDisp);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
      trigger = 0;
    }      
  }
  else if(strcmp(op, "BNE") == 0) {
    opcode = 'c';
    rDest = '1';
    if(!trigger){
      if(dest < 16 && dest >= 0){
        immHi = '0';
        immLo = iToC(dest);
      } else {
        sprintf(imm, "%x", dest);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
    } else {
      int PCtoDisp = src - pc;
      if(PCtoDisp < 16 && PCtoDisp >= 0){
        immHi = '0';
        immLo = iToC(PCtoDisp);
      } else {
        sprintf(imm, "%x", PCtoDisp);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
      trigger = 0;
    }
  }
  else if(strcmp(op, "BGE") == 0) {
    opcode = 'c';
    rDest = 'd';
    if(!trigger){
      if(dest < 16 && dest >= 0){
        immHi = '0';
        immLo = iToC(dest);
      } else {
        sprintf(imm, "%x", dest);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
    } else {
      int PCtoDisp = src - pc;
      if(PCtoDisp < 16 && PCtoDisp >= 0){
        immHi = '0';
        immLo = iToC(PCtoDisp);
      } else {
        sprintf(imm, "%x", PCtoDisp);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
      trigger = 0;
    }
  }
  else if(strcmp(op, "BCS") == 0) {
    opcode = 'c';
    rDest = '2';
    if(!trigger){
      if(dest < 16 && dest >= 0){
        immHi = '0';
        immLo = iToC(dest);
      } else {
        sprintf(imm, "%x", dest);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
    } else {
      int PCtoDisp = src - pc;
      if(PCtoDisp < 16 && PCtoDisp >= 0){
        immHi = '0';
        immLo = iToC(PCtoDisp);
      } else {
        sprintf(imm, "%x", PCtoDisp);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
      trigger = 0;
    }
  }
  else if(strcmp(op, "BCC") == 0) {
    opcode = 'c';
    rDest = '3';
    if(!trigger){
      if(dest < 16 && dest >= 0){
        immHi = '0';
        immLo = iToC(dest);
      } else {
        sprintf(imm, "%x", dest);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
    } else {
      int PCtoDisp = src - pc;
      if(PCtoDisp < 16 && PCtoDisp >= 0){
        immHi = '0';
        immLo = iToC(PCtoDisp);
      } else {
        sprintf(imm, "%x", PCtoDisp);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
      trigger = 0;
    }
  }
  else if(strcmp(op, "BHI") == 0) {
    opcode = 'c';
    rDest = '4';
    if(!trigger){
      if(dest < 16 && dest >= 0){
        immHi = '0';
        immLo = iToC(dest);
      } else {
        sprintf(imm, "%x", dest);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
    } else {
      int PCtoDisp = src - pc;
      if(PCtoDisp < 16 && PCtoDisp >= 0){
        immHi = '0';
        immLo = iToC(PCtoDisp);
      } else {
        sprintf(imm, "%x", PCtoDisp);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
      trigger = 0;
    }
  }
  else if(strcmp(op, "BLS") == 0) {
    opcode = 'c';
    rDest = '5';
    if(!trigger){
      if(dest < 16 && dest >= 0){
        immHi = '0';
        immLo = iToC(dest);
      } else {
        sprintf(imm, "%x", dest);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
    } else {
      int PCtoDisp = src - pc;
      if(PCtoDisp < 16 && PCtoDisp >= 0){
        immHi = '0';
        immLo = iToC(PCtoDisp);
      } else {
        sprintf(imm, "%x", PCtoDisp);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
      trigger = 0;
    }
  }
  else if(strcmp(op, "BLO") == 0) {
    opcode = 'c';
    rDest = 'a';
    if(!trigger){
      if(dest < 16 && dest >= 0){
        immHi = '0';
        immLo = iToC(dest);
      } else {
        sprintf(imm, "%x", dest);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
    } else {
      int PCtoDisp = src - pc;
      if(PCtoDisp < 16 && PCtoDisp >= 0){
        immHi = '0';
        immLo = iToC(PCtoDisp);
      } else {
        sprintf(imm, "%x", PCtoDisp);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
      trigger = 0;
    }
  }
  else if(strcmp(op, "BHS") == 0) {
    opcode = 'c';
    rDest = 'b';
    if(!trigger){
      if(dest < 16 && dest >= 0){
        immHi = '0';
        immLo = iToC(dest);
      } else {
        sprintf(imm, "%x", dest);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
    } else {
      int PCtoDisp = src - pc;
      if(PCtoDisp < 16 && PCtoDisp >= 0){
        immHi = '0';
        immLo = iToC(PCtoDisp);
      } else {
        sprintf(imm, "%x", PCtoDisp);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
      trigger = 0;
    }
  }
  else if(strcmp(op, "BGT") == 0) {
    opcode = 'c';
    rDest = '6';
    if(!trigger){
      if(dest < 16 && dest >= 0){
        immHi = '0';
        immLo = iToC(dest);
      } else {
        sprintf(imm, "%x", dest);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
    } else {
      int PCtoDisp = src - pc;
      if(PCtoDisp < 16 && PCtoDisp >= 0){
        immHi = '0';
        immLo = iToC(PCtoDisp);
      } else {
        sprintf(imm, "%x", PCtoDisp);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
      trigger = 0;
    }
  }
  else if(strcmp(op, "BLE") == 0) {
    opcode = 'c';
    rDest = '7';
    if(!trigger){
      if(dest < 16 && dest >= 0){
        immHi = '0';
        immLo = iToC(dest);
      } else {
        sprintf(imm, "%x", dest);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
    } else {
      int PCtoDisp = src - pc;
      if(PCtoDisp < 16 && PCtoDisp >= 0){
        immHi = '0';
        immLo = iToC(PCtoDisp);
      } else {
        sprintf(imm, "%x", PCtoDisp);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
      trigger = 0;
    }
  }
  else if(strcmp(op, "BFS") == 0) {
    opcode = 'c';
    rDest = '8';
    if(!trigger){
      if(dest < 16 && dest >= 0){
        immHi = '0';
        immLo = iToC(dest);
      } else {
        sprintf(imm, "%x", dest);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
    } else {
      int PCtoDisp = src - pc;
      if(PCtoDisp < 16 && PCtoDisp >= 0){
        immHi = '0';
        immLo = iToC(PCtoDisp);
      } else {
        sprintf(imm, "%x", PCtoDisp);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
      trigger = 0;
    }
  }
  else if(strcmp(op, "BFC") == 0) {
    opcode = 'c';
    rDest = '9';
    if(!trigger){
      if(dest < 16 && dest >= 0){
        immHi = '0';
        immLo = iToC(dest);
      } else {
        sprintf(imm, "%x", dest);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
    } else {
      int PCtoDisp = src - pc;
      if(PCtoDisp < 16 && PCtoDisp >= 0){
        immHi = '0';
        immLo = iToC(PCtoDisp);
      } else {
        sprintf(imm, "%x", PCtoDisp);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
      trigger = 0;
    }
  }
  else if(strcmp(op, "BLT") == 0) {
    opcode = 'c';
    rDest = 'c';
    if(!trigger){
      if(dest < 16 && dest >= 0){
        immHi = '0';
        immLo = iToC(dest);
      } else {
        sprintf(imm, "%x", dest);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
    } else {
      int PCtoDisp = src - pc;
      if(PCtoDisp < 16 && PCtoDisp >= 0){
        immHi = '0';
        immLo = iToC(PCtoDisp);
      } else {
        sprintf(imm, "%x", PCtoDisp);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
      trigger = 0;
    }
  }
  else if(strcmp(op, "BUC") == 0) {
    opcode = 'c';
    rDest = 'e';
    if(!trigger){
      if(dest < 16 && dest >= 0){
        immHi = '0';
        immLo = iToC(dest);
      } else {
        sprintf(imm, "%x", dest);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
    } else {
      int PCtoDisp = src - pc;
      if(PCtoDisp < 16 && PCtoDisp >= 0){
        immHi = '0';
        immLo = iToC(PCtoDisp);
      } else {
        sprintf(imm, "%x", PCtoDisp);
        int a = strlen(imm)-1;
        immHi = imm[a-1];
        immLo = imm[a];
      }
      trigger = 0;
    }
  }
  else if(strcmp(op, "JEQ") == 0) {
    opcode = '4';
    immHi = 'c';
    if (!trigger)
      immLo = iToC(dest);
    else {
      unsigned int lower = src & 0xff;
      unsigned int upper = (src >> 8) & 0xff;
      toLE(toHex("MOVI", lower, 1));
      toLE(toHex("LUI", upper, 1));
      pc = pc + 2;
      immLo = '1';
      trigger = 0;
    }
    rDest = '0';
  }
  else if(strcmp(op, "JNE") == 0) {
    opcode = '4';
    immHi = 'c';
    if (!trigger)
      immLo = iToC(dest);
    else {
      unsigned int lower = src & 0xff;
      unsigned int upper = (src >> 8) & 0xff;
      toLE(toHex("MOVI", lower, 1));
      toLE(toHex("LUI", upper, 1));
      pc = pc + 2;
      immLo = '1';
      trigger = 0;
    }
    rDest = '1';
  }
  else if(strcmp(op, "JGE") == 0) {
    opcode = '4';
    immHi = 'c';
    if (!trigger)
      immLo = iToC(dest);
    else {
      unsigned int lower = src & 0xff;
      unsigned int upper = (src >> 8) & 0xff;
      toLE(toHex("MOVI", lower, 1));
      toLE(toHex("LUI", upper, 1));
      pc = pc + 2;
      immLo = '1';
      trigger = 0;
    }
    rDest = 'd';
  }
  else if(strcmp(op, "JCS") == 0) {
    opcode = '4';
    immHi = 'c';
    if (!trigger)
      immLo = iToC(dest);
    else {
      unsigned int lower = src & 0xff;
      unsigned int upper = (src >> 8) & 0xff;
      toLE(toHex("MOVI", lower, 1));
      toLE(toHex("LUI", upper, 1));
      pc = pc + 2;
      immLo = '1';
      trigger = 0;
    }
    rDest = '2';
  }
  else if(strcmp(op, "JCC") == 0) {
    opcode = '4';
    immHi = 'c';
    if (!trigger)
      immLo = iToC(dest);
    else {
      unsigned int lower = src & 0xff;
      unsigned int upper = (src >> 8) & 0xff;
      toLE(toHex("MOVI", lower, 1));
      toLE(toHex("LUI", upper, 1));
      pc = pc + 2;
      immLo = '1';
      trigger = 0;
    }
    rDest = '3';
  }
  else if(strcmp(op, "JHI") == 0) {
    opcode = '4';
    immHi = 'c';
    if (!trigger)
      immLo = iToC(dest);
    else {
      unsigned int lower = src & 0xff;
      unsigned int upper = (src >> 8) & 0xff;
      toLE(toHex("MOVI", lower, 1));
      toLE(toHex("LUI", upper, 1));
      pc = pc + 2;
      immLo = '1';
      trigger = 0;
    }
    rDest = '4';
  }
  else if(strcmp(op, "JLS") == 0) {
    opcode = '4';
    immHi = 'c';
    if (!trigger)
      immLo = iToC(dest);
    else {
      unsigned int lower = src & 0xff;
      unsigned int upper = (src >> 8) & 0xff;
      toLE(toHex("MOVI", lower, 1));
      toLE(toHex("LUI", upper, 1));
      pc = pc + 2;
      immLo = '1';
      trigger = 0;
    }
    rDest = '5';
  }
  else if(strcmp(op, "JLO") == 0) {
    opcode = '4';
    immHi = 'c';
    if (!trigger)
      immLo = iToC(dest);
    else {
      unsigned int lower = src & 0xff;
      unsigned int upper = (src >> 8) & 0xff;
      toLE(toHex("MOVI", lower, 1));
      toLE(toHex("LUI", upper, 1));
      pc = pc + 2;
      immLo = '1';
      trigger = 0;
    }
    rDest = 'a';
  }
  else if(strcmp(op, "JHS") == 0) {
    opcode = '4';
    immHi = 'c';
    if (!trigger)
      immLo = iToC(dest);
    else {
      unsigned int lower = src & 0xff;
      unsigned int upper = (src >> 8) & 0xff;
      toLE(toHex("MOVI", lower, 1));
      toLE(toHex("LUI", upper, 1));
      pc = pc + 2;
      immLo = '1';
      trigger = 0;
    }
    rDest = 'b';
  }
  else if(strcmp(op, "JGT") == 0) {
    opcode = '4';
    immHi = 'c';
    if (!trigger)
      immLo = iToC(dest);
    else {
      unsigned int lower = src & 0xff;
      unsigned int upper = (src >> 8) & 0xff;
      toLE(toHex("MOVI", lower, 1));
      toLE(toHex("LUI", upper, 1));
      immLo = '1';
      trigger = 0;
    }
    rDest = '6';
  }
  else if(strcmp(op, "JLE") == 0) {
    opcode = '4';
    immHi = 'c';
    if (!trigger)
      immLo = iToC(dest);
    else {
      unsigned int lower = src & 0xff;
      unsigned int upper = (src >> 8) & 0xff;
      toLE(toHex("MOVI", lower, 1));
      toLE(toHex("LUI", upper, 1));
      pc = pc + 2;
      immLo = '1';
      trigger = 0;
    }
    rDest = '7';
  }
  else if(strcmp(op, "JFS") == 0) {
    opcode = '4';
    immHi = 'c';
    if (!trigger)
      immLo = iToC(dest);
    else {
      unsigned int lower = src & 0xff;
      unsigned int upper = (src >> 8) & 0xff;
      toLE(toHex("MOVI", lower, 1));
      toLE(toHex("LUI", upper, 1));
      immLo = '1';
      trigger = 0;
    }
    rDest = '8';
  }
  else if(strcmp(op, "JFC") == 0) {
    opcode = '4';
    immHi = 'c';
    if (!trigger)
      immLo = iToC(dest);
    else {
      unsigned int lower = src & 0xff;
      unsigned int upper = (src >> 8) & 0xff;
      toLE(toHex("MOVI", lower, 1));
      toLE(toHex("LUI", upper, 1));
      pc = pc + 2;
      immLo = '1';
      trigger = 0;
    }
    rDest = '9';
  }
  else if(strcmp(op, "JLT") == 0) {
    opcode = '4';
    immHi = 'c';
    if (!trigger)
      immLo = iToC(dest);
    else {
      unsigned int lower = src & 0xff;
      unsigned int upper = (src >> 8) & 0xff;
      toLE(toHex("MOVI", lower, 1));
      toLE(toHex("LUI", upper, 1));
      pc = pc + 2;
      immLo = '1';
      trigger = 0;
    }
    rDest = 'c';
  }
  else if(strcmp(op, "JUC") == 0) {
    opcode = '4';
    immHi = 'c';
    if (!trigger)
      immLo = iToC(dest);
    else {
      unsigned int lower = src & 0xff;
      unsigned int upper = (src >> 8) & 0xff;
      toLE(toHex("MOVI", lower, 1));
      toLE(toHex("LUI", upper, 1));
      pc = pc + 2;
      immLo = '1';
      trigger = 0;
    }
    rDest = 'e';
  }
  else if(strcmp(op, "JAL") == 0) {
    opcode = '4';
    rDest = iToC(src);
    immHi = '8';
    if(trigger){
      unsigned int lower = dest & 0xff;
      unsigned int upper = (dest >> 8) & 0xff;
      toLE(toHex("MOVI", lower, 1));
      toLE(toHex("LUI", upper, 1));
      pc = pc + 2;
      immLo = '1';
      trigger = 0;
    } else
      immLo = iToC(dest);
  }

  char hexCode[4];
  hexCode[0] = opcode;
  hexCode[1] = rDest;
  hexCode[2] = immHi;
  hexCode[3] = immLo;
  char *cp = hexCode;
  free(op);
  return cp;
}
