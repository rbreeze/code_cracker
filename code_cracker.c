/************************************************
*       copyright 2013 Remington Breeze         *
*                  cracker                      *
*              beta version 0.5                 *
************************************************/

//include libraries
#include "cs50.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>

//define colors
#define RED "\033[0;31m"
#define BLUE "\033[0;34m"
#define YELLOW "\033[0;33m"
#define GREEN "\033[0;32m"
#define CYAN "\033[0;36m"
#define RESET "\033[0m"

//define a struct to remember the most frequent letter
struct {
    float value;
    int letter;
}
biggest;

//define the variable that input will be stored in
char* input;

//prototypes
int decrypt(int x, int k);
int eval(int x, float u);
void printstats(float w, int j, int l);

int main(int argc, char* argv[]) {
    //declare the input variable
    //if the 'file' flag is detected
    if (strcmp(argv[1], "-f") == 0){
        //open the specified file
        char* fname = argv[2];
        FILE* file = fopen(fname, "r");
        //check that it isn't null
        if (file == NULL){
            printf("There was an error opening the file.\n");
            return 6;
        }
        //check the file's size
        struct stat filesize;
        if (stat(fname, &filesize) < 0 ){
            printf("There was an error while finding the size of your file.\n");
            return 7;
        }
        stat(fname, &filesize);
        //put the file's contents into 'input'
        input = malloc(filesize.st_size + 1);
        fread(input, filesize.st_size, sizeof(char), file); 
        //close the file
        fclose(file);    
    }
    //if the 'input' flag is detected
    else if (strcmp(argv[1], "-i") == 0) {
        //get the user's input
        printf("input cyphertext:\n\n");
        input = GetString();
    }
    //if no flag is detected
    else {
        printf("Improper usage.\n");
        return 8;
    }
        //find out how long the input is
        int l = strlen(input);
        //declare a variable that will store how many letters there are
        float w = 0;
        //declare an int that will keep track of how many times a letter occurs
        int b;
        //find out how many letters there are
        for (int z = 0; z < l; z++) {
            if (isupper(input[z]) != 0 || islower(input[z]) != 0)
            	w++;
        }
        //warn the user if there might not be enough data
        if (w < 30)
            printf("\n"RED"WARNING: You may have too few characters for the decipherment to have been very accurate.\n"RESET"");
        //declare a float
        float u;
        //cycle through the alphabet
        for (int x = 0; x < 26; x++) {
            //set b to zero
            b = 0;
            //cycle through the cyphertext
            for (int y = 0; y < l; y++) {
                if(isupper(input[y]) != 0) {
		            	if (input[y] == x + 65 ) {
		                	b++;
		            	}
                }
                else if (islower(input[y]) != 0) {
		            	if (input[y] == x + 97 ) {
		                	b++;
		            	}
                }
            }
            //find the frequency of the letter
            u = 100 * (b / w);
            //if the frequency is over 7 percent, see if it is the most frequent letter
            if (u > 7.00){ 
                eval(x, u);
            }
        }
        //find what the caesar shift is likely to be, based on the letter e
        int shift = biggest.letter - 4;
        printf("\nThe caesar shift is likely to be "YELLOW"%d"RESET".\n", shift);
        printf("\ndecrypting...\n\n");
        //decrypt the message based on the caesar shift
        int k = 26 - shift;
        for (int i = 0; i < l; i++) {
            int plainchar = decrypt(input[i], k);         
            printf("%c", plainchar);
        }
        printf("\n\ndone!\n\n");
        printf("Possibly useful stats for cryptanalysts:\n\n");
        //print out statistics of the letter frequencies/ number of letters
        printf(""YELLOW"%.0f letters\n\n"RESET"", w);
        for(int j = 0; j < 26; j++)
            printstats(w, j, l);
        printf("\n");
        //finished!
        return 0;
}

//decrypts a message based on what the caesar shift is
int decrypt(int x, int k) {
    if (isalpha(x)) {
        int i;
        if (islower(x) != 0)
            i = 97;
        else if (isupper(x) != 0)
            i = 65;
        int z = x - i;
        int y = (z + k) % 26;
        int r;
        r = y + i; 
        return r;
    }
    else
        return x;
}

//prints out statistics
void printstats(float w, int j, int l) {
    int p = 0;
    int b = 0;
    for (int inc = 0; inc < l; inc++){
            if (input[inc] == j + 97 ) 
                b++;
            else if (input[inc] == j + 65 ) 
                b++;
        }
        p = j + 97;
            float u = 100 * (b / w); 
            //make sure everything is aligned
            if (b > 9)
        		printf("%c: %d -->  ", p, b);
            else
            	printf("%c: %d  -->  ", p, b);
            //display frequently occuring letters in red
            if (u > 7.00){ 
                printf(""RED"%.2f%%"RESET"", u);
            }
            else 
                printf("%.2f%%", u);
            printf("\n");
}

//resets and checks the current biggest value
int eval(int x, float u) {
    if (u > biggest.value){
        biggest.value = u;
        biggest.letter = x;
    }
    return 0;
}

