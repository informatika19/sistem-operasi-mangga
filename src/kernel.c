// ------- Kernel -------
// BCC notes
// - Variable declaration must be put on top of code
// - First defined function is starting function
// - Pointer declaration syntax is <type> *<varname>;

// Configuration
#define V_MEM 0xB000
#define V_OFFSET 0x8000

#include "kernel.h"
#include "std.h"

int main() {
    // Declaration
    char stringBuffer[1024];

    // Setup
    clear(stringBuffer, 1024);
    makeInterrupt21();

    // Initial screen
    clearScreen();
    setCursorPos(1,1);
    drawBootLogo();

    // Other
    interrupt(0x21, 0x1, stringBuffer, 0, 0);
    interrupt(0x21, 0x0, stringBuffer, 0, 0);
    while (1);
}

void handleInterrupt21(int AX, int BX, int CX, int DX){
    switch (AX) {
        case 0x0:
            printString(BX);
            break;
        case 0x1:
            readString(BX);
            break;
        default:
            printString("Invalid interrupt");
    }
}

void videoMemoryWrite(int offset, char character) {
    putInMemory(V_MEM, V_OFFSET + offset, character);
}

void printString(char *string) {
    // Direct video memory writing
    // int i = 0;
    // while (string[i] != '\0') {
    //     videoMemoryWrite(2*i, string[i]);
    //     videoMemoryWrite(1 + 2*i, 0xD);
    //     i++;
    // }
    int i = 0, temp = 0;
    while (string[i] != '\0') {
        temp = 0x900 + string[i];
        interrupt(0x10, temp, 0x000D, 0x1, 0);
        i++;
    }

    // interrupt(0x10,0x1301,0x010D,strlen(string),0);
}

void readString(char *string) {
    char c = interrupt(0x16, 0x00, 0, 0, 0);
    int i = 1;
    string[0] = c;
    while (c != 0xD) {
        // Note : ASCII 0xD -> Carriage Return
        c = interrupt(0x16, 0x00, 0, 0, 0);
        if (c != 0xD) {
            string[i] = c;
            i++;
        }
        // TODO : Add backspace, 0x8
    }
    string[i] = '\0';
}

void clear(char *string, int length) {
    int i = 0;
    while (i < length) {
        string[i] = '\0';
        i++;
    }
}

void clearScreen() {
    int i = 0;
    while (i < 4096) {
        videoMemoryWrite(2*i, ' ');
        videoMemoryWrite(1 + 2*i, 0x0);
        i++;
    }
}

void setCursorPos(int r, int c) {
    int temp = 0x100*r + c;
    interrupt(0x10, 0x0200, 0x1, 0, temp);
}

void drawBootLogo() {
    // TODO : Extra, ASCII / Graphical
}
