struct Label {
  char *name;
  int location;
};

extern int trigger;
extern struct Label heldLoc[];
extern int pc;
extern int first_enter;

void checkJump(char *);
void toLE(char *);
char iToC(int);
char* toHex(char *, int, int);
int needLabel(char*);
void holdLabel(char*, int );
