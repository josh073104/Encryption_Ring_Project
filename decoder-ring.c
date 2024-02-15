/**
 * COSC 3250 - Project 1
 * This program takes characters from the standard input and decodes them using an algorithm
 * based on the value of the character (A/a = 1, B/b = 2, Z/z = 27, and non alpha characters = 0),
 * the value of the previous character (Starting with zero for the first one), and a key which is 
 * given as a command line argument. it excludes the '\n' character from decoding and then prints
 * the decoded message to standard output. it will keep decoding until EOF is entered
 * @author Josh Wild
 */

#include <stdio.h>
#include <stdlib.h>

// converts a character to the numerical form of the ring
// A/a = 1, Z/z = 27, non alpha characters = 0
// subtract 'A' or 'a' to get the proper numerical value and return the new character as an int
int convertChar(int ch) {
    if (ch >= 'A' && ch <= 'Z') {
        ch = (ch - 'A') + 1;
    }
    else if (ch >= 'a' && ch <= 'z') {
        ch = (ch - 'a') + 1;
    }
    else {
        ch = 0;
    }
    return ch;
}

int decode(int ch, int prevch, int key) {
    int val = convertChar(ch);                      // value of input character on ring
    int subtract = prevch + key;                    // value to shift input character backwards on ring 
    int i;                                          // placeholder for how far to shift back

    for (i = 0; i < subtract; i ++) {               // while loop up until the value being subtracted
        val -= 1;                                   // subtract 1 each time
        if (val < 0)                                // if the value is less than zero, set value to 26 (take care of mod)
            val = 26;
    }
    return val;  
}

// takes a character in the converted numberical form of the ring and converts it back into the
// proper ascii form to be used as a char by the program
// always converts it to an upper case letter 
// edge case where the return value is 64 instead of 65 ('A') happens when the character is a non
// alphabetical character in which case the character should just become a space
int convertCharBack(int ch) {
    int ret;
    ret = ch + 'A' - 1;
    if (ret < 'A')
        ret = ' ';
    return ret;
}

int main(int argc, char * argv[]) {
    int ch;                                         // character input
    int xch;                                        // decoded character
    int key = 0;                                    // start key as zero
    if (argc > 1)                                   // if a value is entered for a key, use it
        key = atoi(argv[1]);                        // key entered on command line
    int prevch = 0;                                 // previous character value (starts at 0)
    while ((ch = getchar()) != EOF) {               // while EOF has not been entered
        if (ch != '\n') {                           // skip over decoding '\n' if one is entered
            xch = decode(ch, prevch, key);          // decode ch and save it to xch
            prevch = convertChar(ch);               // set prevch as encoded version of ch (convert it to ring numbers)
            xch = convertCharBack(xch);             // convert decoded version back to ascii format   
            putchar(xch);                           // print ascii value to standard output
        } 
        else {
            putchar('\n');                         
        }
    } 

    return 0;
}