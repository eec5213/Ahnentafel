/*
File: ahnentafel.c

The main goal of this project is to process command line arguments, handle user input, process strings,
convert binary to decimal and vice versa, as well as implement basic algorithms

Ahnentafel numbers are used in genealogy to determine the relationship between an individual and an ancestor of theirs.

updated: Feb 26, 2020
author @ Eve Cho
email: eec5213@g.rit.edu
*/

// header files included in this program
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// a function explicitly defining pow() so that I don't have to link it while compiling
// @param base	the base value for the exponent
// 	  exp	the value of the exponent
// returns the complete exponent 
int power(int base, int exp) {
        int ret = 1;
        for (int i = 0; i< exp; i++){
                ret = ret*base;
        }
        return ret;
}

// a function that prints the menu for the ahnentafel program
// returns none
void menu() {
	printf("\n1) description\n"
		"2) ahnentafel number (base 10)\n"
                "3) ahnentafel number (base 2)\n"
                "4) relation (e.g. mother's mother's father)\n"
                "5) exit\n"
                "\n>  ");
}

// decimal to binary conversion function
// @param decimal	the decimal value to be converted into binary
// returns the initial decimal value converted into binary form
int dec2bi(int decimal) {
	int binary = 0;
	int remainder, decFactor = 1;
	while (decimal != 0) {
		remainder = decimal % 2;
		decimal /= 2;
		binary += remainder * decFactor;
		decFactor *= 10;
	}
	return binary;
}

// binary to decimal conversion function
// @param binary	the binary value to be converted into binary
// returns the initial binary value converted into decimal form
int bi2dec(int binary) {
	int decimal = 0, factor = 0, remainder;
	while (binary != 0) {
		remainder = binary % 10;
		binary /= 10;
		decimal += remainder * power(2,factor);
		factor++;
	}
	return decimal;
}

// a function that both gets the relation from the ahnentafel individual and the starting inidividual, as well as the number of generations back it goes
// @param binary	the binary value used to calculate the relation to the starting individual
// returns the number of generations back it goes
int relation(int binary) {
	// finding the length of the binary number to create a int array
	int pos = 0;
	int init = binary;
	while (init != 0) {
		init /= 10;
		pos++;
	}
	int bi[pos];
	int len = pos;
	pos = 0;
	init = binary;

	// filling the int array with the corresponding binary values; NOTE that the indexes are REVERSED from the initial binary int
	while (init != 0) {
    		bi[pos] = init % 10;
    		init /= 10;
    		pos++;
	}

	char self[] = "self";
	int gen = 0;

	// in the case that the binary value corresponds to the initial individual 
	if (binary == 1) {
		printf("Family relation: %s\n", self);
		return gen;
	}
	// in the case that the binary value represents an ancestor and not the initial individual
	else {
		printf("Family relation: ");
		for (int i = len-2; i >= 0; i--) {
			if (i == 0) {
				if (bi[i] == 1) {
					printf("mother");
				}
				else if (bi[i] == 0) {
				printf("father");
				}	
			}	
			else if (bi[i] == 1) {
				printf("mother's ");
			}
			else if (bi[i] == 0) {
				printf("father's ");
			}
		gen++;
		}
	}
	printf("\n");
	return gen;	
}

// a function that takes an string of relations and converts the relation to the individual into a binary and decimal value, and also calculate how many generations back the relation goes
// @param ancestor	a character array that contains the relationship between the individual and the ancestor in question
// returns 0 if successful and 1 if otherwise
int relateToInt(char ancestor[]) {
	// gets rid of any trailing newline which was happening in the menu option for some reason
	int len = strlen(ancestor);
	if (ancestor[len-1] == '\n') {
		ancestor[len-1] = 0;
	}


	int gen = 0;
	if (strcmp(ancestor, "self") == 0) {
		int base10 = 1;
		int base2 = dec2bi(base10);
		printf("Ahnentafel number in binary: %d\n", base2);
		printf("Ahnentafel number in decimal: %d\n", base10);
	       	printf("Generations back: %d\n", gen);	
	}
	else if (strcmp(ancestor, "self") != 0) {
		char *point;
		int binary = 1;
		point = strtok(ancestor, " ,.\n");
		while (point != NULL) {
			if (strcmp(point, "mother") == 0 || strcmp(point, "mother's") == 0) {
				binary = (binary * 10) + 1;
			}
			else if (strcmp(point, "father") == 0 || strcmp(point, "father's") == 0) {
				binary = (binary * 10);
			}
			// this is checking if the string is in a valid format
			// there will be an error message if it is not mother, mother's, father, father's, or self
			else {
				fprintf(stderr, "Invalid String Format!\n");
				return 1;
			}
			gen++;
			point = strtok(NULL, " ,.\\");
		}
		int decimal;
		decimal = bi2dec(binary);
		printf("Ahnentafel number in binary: %d\n", binary);
		printf("Ahnentafel number in decimal: %d\n", decimal);
		printf("Generations back: %d\n", gen);
		
	}
	return 0;
}

// a function that checks if the string entered is a string of binary digits or not
// @param biCheck	the character array to be checked
// 	  arr_len	the length of character array biCheck
// returns 0 if the string is a valid binary value and 1 otherwise
int bi2check(char biCheck[], int arr_len) {
	int len = arr_len;
	for (int n = 0; n < len; n++) {
		if(biCheck[n] != '1' && biCheck[n] != '0') {
			return 1;
		}
	}
	return 0;
}

// a function that provides a description of ahnentafel numbers
// returns none
void item1() {
    	printf("The ahnentafel number is used to determine the relation between an individual and each of his/her direct ancestors.\n");
}

// a function that allows the user to enter a number in base 10, and prints out the binary conversion as well as the relation to the individual and the number of generations back
// returns none
void item2() {	        
	int base10;
	// prompts the user to enter a decimal value
	printf("Enter the ahnentafel number in base-10: ");
	scanf("%d", &base10);

	// converts the decimal into a binary and prints out the value as well as generations
        int base2 = dec2bi(base10);
        printf("ahnentafel number in binary: %d\n", base2);
	int gen = relation(base2);
	printf("Generations back: %d\n", gen);
}

// a function that allows the user to enter a number in binary, and prints out the decimal conversion as well as the relation to the individual and the number of generations back
// returns none
void item3() {
    	int base2;
	// prompts the user to enter a binary value
        printf("Enter the ahnentafel number in binary: ");
        scanf("%d", &base2);
        
	// converts the binary into a decimal and prints out the value as well as generations
        int base10 = bi2dec(base2);
        printf("Decimal value: %d\n", base10);
	int gen = relation(base2);
	printf("Generations back: %d\n", gen);
}

// a function that allows the user to enter the relation to the individual and prints out the ahnentafel number in binary, in decimal, and the number of generations back
// returns none
void item4() {
	// character array to store the relations
	char input[350];

	// prompts the user to enter a family relation
    	printf("Enter the family relation (e.g.) \"father's mother\": ");
	getchar(); 	// getchar() is here to clear the newline before fgets() retrieves the actual user input
	fgets(input, 350, stdin);
	relateToInt(input);
}

// a function that prints \"Goodbye.\" and terminates the program
// returns none
void item5() {
    	printf("\nGoodbye.\n");
}

// a function that proceeds with an operation of the user's choosing
// @param n	an int that represents one of the options on the menu
// returns none
void selection(int n) {
	switch(n) {
		case 1:
			item1();
			break;
		case 2:
			item2();
			break;
		case 3:
			item3();
			break;
		case 4:
			item4();
			break;
		case 5:
			item5();
			break;
		default:
			fprintf(stderr, "Unknown Operation!\n");
	}
}

// the main function that runs the entire ahnentafel program and it's functions
// @param argc	the number of command line arguments
// 	  argv	the command line arguments represented as a string
int main(int argc, char *argv[]) {
	
	// this is in the case that the program is run without command line arguments, and continues to run until it is explicitly cancelled by the user
	if (argc < 2) {
		int select = 0;
	    	while(select != 5) {
			menu();       	 		
			scanf("%d", &select);
    			selection(select);	     
	    	}
		if(select == 5) {
			return EXIT_SUCCESS;
		}
    	}

	// this is in the case that the program is run with command line arguments; the program only runs once, does not display the menu, and then exits
	if (argc > 1) {
		char item[350];
		strcpy(item, argv[1]);
		int length = strlen(item);
		int decimal;
		int binary;
		int gen;
		char *ptr;

		// case if command line argument is a binary number
		if (item[length-1] == 'b') {
			item[length-1] = 0;
			length = strlen(item);
			if (bi2check(item, length) == 0) {
				binary = strtol(item, &ptr, 10);
				decimal = bi2dec(binary);
				printf("Ahnentafel number in decimal: %d\n", decimal);
				gen = relation(binary);
				printf("Generations back: %d\n", gen);
				return EXIT_SUCCESS;
			}
			else {
				fprintf(stderr, "Invalid string!\n");
				return EXIT_FAILURE;
			}
		}
		// case if command line argument is a decimal; the else if statement itself checks if it is an integer or not
		else if (strtol(item, &ptr, 10) != 0) {
			decimal = strtol(item, &ptr, 10);
			binary = dec2bi(decimal);
			printf("Ahnentafel number in binary: %d\n", binary);
			gen = relation(binary);
			printf("Generations back: %d\n", gen);
			return EXIT_SUCCESS;
		}

		else {
			// case if command line argument is meant to be a relation
			//int totLen = 0;

			// figuring out the length of all the arguments combined to set a character array size
			/*for (int x = 1; x < argc; x++) {
				totLen += strlen(argv[x]);
				
				if (x != argc-1) {
					totLen++;
				}
				// adding +1 to buffer for spaces to be added between each relation element
			}
			*/
			// character array where all the arguments are going to go
			char relations[350];
			strcpy(relations, "");
			// adding all the arguments to relations
			for (int a = 1; a < argc; a++) {
				strcat(relations, argv[a]);

				//adds spaces between elements except at the very end so that strtok() in relateToInt() recognizes and separates the elements by the identified token
				if (a != argc-1) {
					strcat(relations, " ");
				}
			}
			int pass = relateToInt(relations);
			if (pass == 1) {
				return EXIT_FAILURE;
			}
			else if (pass == 0) {
				return EXIT_SUCCESS;
			}
		}

	}

    	return EXIT_SUCCESS;
}

// end of program
