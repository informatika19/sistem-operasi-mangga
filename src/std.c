// 13519214 - Standard function

#include "std-header/std.h"
#include "std-header/boolean.h"
#include "kernel-header/config.h"

// ---------------- Standard string operation ----------------
int strlen(char *string) {
    int i = 0;
    while (string[i] != '\0')
        i++;
    return i;
}

void strcpy(char *dest, char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

void rawstrcpy(char *dest, char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
}

void strcpybounded(char *dest, char *src, int n) {
    int i = 0;
    while (src[i] != '\0' && i < n) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

void rawstrcpybounded(char *dest, char *src, int n) {
    int i = 0;
    while (src[i] != '\0' && i < n) {
        dest[i] = src[i];
        i++;
    }
}

char strcmp(char *s1, char *s2) {
    int i = 0;
    if (strlen(s1) == strlen(s2)) {
        // If string length matches, check every char
        while (s1[i] != '\0') {
            if (s1[i] != s2[i])
                return 1;
            i++;
        }

        // If both string matches
        return 0;
    }

    return 1;
}

void strapp(char *string1, char *string2) {
    int i = strlen(string1), j = 0;
    while (string2[j] != CHAR_NULL) {
        string1[i] = string2[j];
        i++;
        j++;
    }
    string1[i] = CHAR_NULL;
}

char isCharInString(char c, char *string) {
    int i = 0;
    while (string[i] != CHAR_NULL) {
        if (string[i] == c)
            return 1;
        i++;
    }
    return 0;
}

void clear(char *string, int length) {
    int i = 0;
    while (i < length) {
        string[i] = CHAR_NULL;
        i++;
    }
}

void inttostr(char *buffer, int n) {
    int i = 0;
    bool is_negative = false;
    if (n < 0) {
        n *= -1;
        is_negative = true;
    }
    while (n > 10) {
        buffer[i] = CHAR_NUMBER_0 + mod(n, 10);
        i++;
        n /= 10;
    }
    buffer[i] = CHAR_NUMBER_0 + mod(n, 10); // First digit
    i++;
    if (is_negative) {
        buffer[i] = '-';
        i++;
    }
    buffer[i] = '\0';
    strrev(buffer);
}

void strrev(char *string) {
    int i = 0, length = strlen(string);
    char temp;
    while (i < length/2) {
        temp = string[i];
        string[i] = string[length - 1 - i];
        string[length - 1 - i] = temp;
        i++;
    }
}



// ---------------- Standard I/O ----------------
void print(char *string, char color) {
    // TODO : Extra, Maybe not safe (?)
    // TODO : Extra, Including black color
    if (BIOS_BLACK < color && color <= BIOS_WHITE)
        interrupt(0x21, 0x00, string, 0x00, color);
    else
        interrupt(0x21, 0x00, string, 0x00, BIOS_GRAY);
}

void gets(char *string) {
    interrupt(0x21, 0x01, string, 0x00, 0);
}

void putchar(char a) {
    int temp;
    char tempstring[2];
    tempstring[0] = a;
    tempstring[1] = '\0';
    if (a == CHAR_BACKSPACE)
        interrupt(0x21, 0x00, 0, 0x01, 0);
    else
        interrupt(0x21, 0x00, tempstring, 0x00, BIOS_GRAY);

}

int getFullKey() {
    int key;
    interrupt(0x21, 0x01, &key, 0x01, 0);
    return key;
}

void showKeyboardCursor() {
    interrupt(0x21, 0x0001, 0, 0x4, 0);
}

void hideKeyboardCursor() {
    interrupt(0x21, 0x0001, 0, 0x5, 0);
}

void setKeyboardCursor(char r, char c) {
    int BX = (r << 8);
    BX |= c;
    interrupt(0x21, 0x01, BX, 0x02, 0);
}

int getKeyboardCursor(bool isrow) {
    int pos;
    interrupt(0x21, 0x01, &pos, 0x3, isrow);
    return pos;
}


// ---------------- File I/O ----------------
void getDirectoryTable(char *buffer) { // TODO : Move this from std
    // WARNING : Naive implementation
    interrupt(0x21, 0x0002, buffer, FILES_SECTOR, 0);
    interrupt(0x21, 0x0002, buffer + SECTOR_SIZE, FILES_SECTOR + 1, 0);
}

void write(char *buffer, char *path, int *returncode, char parentIndex) {
    int AX = parentIndex << 8;
    AX |= 0x04;
    interrupt(0x21, AX, buffer, path, returncode);
}

void read(char *buffer, char *path, int *returncode, char parentIndex) {
    int AX = parentIndex << 8;
    AX |= 0x05;
    interrupt(0x21, AX, buffer, path, returncode);
}



// TODO : getRawCursorPos() wrapper
// TODO : setCursorPos() wrapper


// TODO : Extra, printf(), Extra Extra : Color escape sequence
// TODO : Extra, simple string builder
// TODO : Extra, strtoint / atoi and inttostr
