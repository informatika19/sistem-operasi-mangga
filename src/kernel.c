// ------- Kernel -------


// Configuration
#define V_MEM 0xB000
#define V_OFFSET 0x8000


// Implemented in assembly
extern void putInMemory(int segment, int address, char character);
extern void makeInterrupt21();
extern int interrupt(int number, int AX, int BX, int CX, int DX);

void handleInterrupt21 (int AX, int BX, int CX, int DX);
void printString(char *string);
void readString(char *string);
void clear(char *buffer, int length); //Fungsi untuk mengisi buffer dengan 0


int main() {
    // TODO : Extra, ASCII
    printString("av\0");
    makeInterrupt21();

    while (1);
}

void handleInterrupt21(int AX, int BX, int CX, int DX){
    switch (AX) {
        case 0x0:
            printString(BX);
            break;
        case 0x1:
            // readString(BX);
            break;
        default:
            printString("Invalid interrupt");
    }
}

int strlen(char* string) {
    int length = 0;
    while (*(string+length) != '\0')
        length++;
    return length;
}

void printString(char *string) {
    // Self-note : pt[i] operator not translate to *(pt+i) in bcc
    int i = 0;
    while (*(string+i) != '\0') {
        putInMemory(V_MEM, V_OFFSET + 2*i, string[i]);
        putInMemory(V_MEM, V_OFFSET + 1 + 2*i, 0xD);
        i++;
    }

    // interrupt(0x10,0x1301,0x010D,strlen(string),0);
}





// void readString(char *string);
// void clear(char *buffer, int length); //Fungsi untuk mengisi buffer dengan 0
