#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// prototype function
void shiftstring(int shift_num, char* input);

int main (int argc, char** argv) {
    if (argc != 3) {
        printf("Invalid arguments. Please input a number and a string/n");
        return -1;
    }
    int shift_num = atoi(argv[1]);
    /** when we receive input as string from the argument, it's by default to 
     * store as string in char*. Therefore, the string stored in input will be 
     * end with \0. For this reason, when we strcpy the input to a temp char[]
     * we need to have one more space for \0
     */
    char* input = argv[2]; 
    
    shiftstring(shift_num, input);

    return 0;
}

void shiftstring(int shift_num, char* input) {
    int size = strlen(input); // noting strlen not count the \0
    if (size == 0) {
        printf("\"\" ===> \"\"/n");
        return;
    }
    // obtain the mode of shift_num to avoid too many shifts
    if (shift_num < 0) {
        shift_num = (shift_num % size) + size;
    } else {
        shift_num %= size;
    }

    /** here I used char temp[size + 1] but not char* temp to initialize.
     * char temp[] will allocate space on stack, no need to manage the mem by 
     * myself. char* temp is accompanied by malloc, spaced to be allocated on heap
     * and I need to manage the allocated by myself. 
     */
    char temp[size + 1];
    int i, tidx;
    // 1, hello -> ohell. copy o (at idx 4) first, then left 0 to 3
    /* the algo is copy the str in input starting at size-shift_num, to end. 
    not include \0
    then copy start of input to char before size-shift_num. 
    finally add \0 to temp, so that temp will be a string not a char[]*/
    for (i = size - shift_num, tidx = 0; i < size; i++, tidx++) {
        temp[tidx] = input[i];
    }

    for (i = 0; tidx < size; i++, tidx++) {
        temp[tidx] = input[i];
    }

    temp[tidx] = '\0'; //end of the string
    printf("\"%s\" ===> \"%s\"/n", input, temp);
}