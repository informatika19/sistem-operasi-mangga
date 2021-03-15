// 13519214 - Standard function header

// ---------------- Standard Macro ----------------
#define NULL 0x00



// ---------------- Standard string operation ----------------
int strlen(char *string);
// Standard string length

int mod(int a, int n);
// Standard modulo function

void strcpy(char *dest, char *src);
// Standard strcpy without returning

void strcpybounded(char *dest, char *src, int n);
// strcpy only first n characters

void rawstrcpy(char *dest, char *src);
// strcpy without copying null terminator

void rawstrcpybounded(char *dest, char *src, int n);
// strcpy only first n characters and without null terminator

char strcmp(char *s1, char *s2);
// Standard strcmp function

void strrev(char *string);
// Reversing string at pointed location

void strapp(char *string1, char* string2);
// WARNING : No bound checking
// Append string 1 with string 2

void inttostr(char *buffer, int n);
// WARNING : Naive implementation, no bound checking
// Converting integer n to string pointed at buffer

char isCharInString(char c, char *string);
// Finding whether char c is in string

void clear(char *buffer, int length);
// Clearing string buffer

// ---------------- Standard I/O ----------------
void print(char *string, char color);
// Simple printing with color

void gets(char *string);
// Simple keyboard input, ye olde gets()

void putchar(char a);
// Standard 1 char output

int getFullKey();
// Getting 1 keypress, blocking, no echo

void showKeyboardCursor();
// Showing keyboard cursor to screen

void hideKeyboardCursor();
// Disable keyboard cursor



// --- File I/O ---
void getDirectoryTable(char *buffer); // TODO : Move this from std
// WARNING : No bound checking
// Get all directory table, put in buffer

void write(char *buffer, char *path, int *returncode, char parentIndex);
// Write "buffer" with name "path" at "parentIndex" folder

void read(char *buffer, char *path, int *returncode, char parentIndex);
// Read file with name "path" at "parentIndex" folder and write to "buffer"
