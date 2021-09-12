#include <stdio.h>
#include <stdlib.h>

signed char c;
unsigned char mem[65536];
unsigned char * ptr = mem;
unsigned char * startPtr = mem;
FILE * file;

void block() {
    long int blockPos = ftell(file);

    while (!feof(file))
    {   
        c = fgetc(file);

        switch (c) {
            case '[':
                block();
                break;
            case ']':
                if (*ptr) fseek(file, blockPos, SEEK_SET);
                else return;
                break;
            case '+':
                ++(*ptr);
                break;
            case '-':
                if ((*ptr) > 0) --(*ptr);
                break;
            case '>':
                ++ptr;
                break;
            case '<':
                if (startPtr < ptr) --ptr;
                break;
            case ',': 
                scanf("%c", ptr);
                if (*ptr == '\n') *ptr = 0;
                break;
            case '.':
                printf("%c", *ptr);
        }
    }
}

int main(int argc, char ** argv) {
    if (argv[1] == NULL) {
        printf("File name was not specified\n");
        return 0;
    } 

    file = fopen(argv[1], "rb+");

    if (file == NULL) {
        printf("No such file named '%s' \n", argv[1]);
        return 0;
    }

    block(file);
    fclose(file);
    printf("\n");

    return 0;
} 