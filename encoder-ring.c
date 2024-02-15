/**
 * COSC 3250 - Project 1
 * This program takes characters from the standard input and encodes them using an algorithm
 * based on the value of the character (A/a = 1, B/b = 2, Z/z = 27, and non alpha characters = 0),
 * the value of the previous character (Starting with zero for the first one), and a key which is 
 * given as a command line argument. it excludes the '\n' character from decoding and then prints
 * the encoded message to standard output. it will keep encoding until EOF is entered
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

// encodes the character based on the previous character, the value of the current character,
// and the key value
// mods by 27 to allow the encoding to wrap around back to zero if it overflows
int encode(int ch, int prevch, int key) {
    int ret = (convertChar(ch) + prevch + key) % 27;
    
    return ret;  
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
    int ch;                                     // character input  
    int xch;                                    // encoded character
    int key = 0;
    if (argc > 1)                               // set key if a value is passed otherwise use 0
        key = atoi(argv[1]);                    // key passed as cmd line argument
    int prevch = 0;                             // previous character starts as zero
    while ((ch = getchar()) != EOF) {           // while EOF is not entered
        if (ch != '\n') {                       // skip over '\n'
            xch = encode(ch, prevch, key);      // get encoded version of character
            prevch = xch;                       // use encoding as previous character
            xch = convertCharBack(xch);         // convert encoded character back into ascii form
            putchar(xch);                       // print out encoded ascii character
        }
        else {
            putchar('\n');
        }
        
    } 
    return 0;
}