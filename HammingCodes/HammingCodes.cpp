//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME: HammingCodes.cpp               ASSIGNMENT #2              Grade: _________   *
//*                                                                                                   *
//*   PROGRAM AUTHOR:     _________________________________________                                   *
//*                                    Hein Htet Zaw                                                  *
//*                                                                                                   *
//*   COURSE #:  CSC 40300 11                                           DUE DATE: November 16, 2016   *
//*                                                                                                   *
//*****************************************************************************************************
//*****************************************************************************************************
//*                                                                                                   *
//* Program description:This program is to implement the error-correcting codes known as Hamming codes*
//*                     developed by Richard Hamming at Bell Laboratories. The program first computes *
//*                     the positions of the check bits for the word stored in memory. Then it takes  *
//*                     the first input word and compute the first K-bit code word that is stored in  *
//*                     memory. Then it computes the second K-bit code word from the word as it is    *
//*                     read from memory (the second input line in the data). Then it takes the two   *
//*                     K - bit words and compute the syndrome word. The value of the syndrome word   *
//*                     determines the program output.                                                *
//*                                                                                                   *
//*****************************************************************************************************

#include <stdio.h>
#include <string>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <math.h>

		//define maximum number of cases that this program can handle (10 is enough for this project)
#define max 10

using namespace std;

void header(ofstream&);
void footer(ofstream&);
void calcSyndromes(string[][2], string[][2], int);
void getCodeWords(string [][2], string [][2], string[][2], int);
void printMessage(ofstream&, string, string, string, string, string, string, string);
int compareSyndromes(string, string, string&, int&, int&);
string getMessage(int, int, int);
int binToDec(string);

int main() {
			//set up input file and output files
	ifstream infile("testdata.txt", ios::in);
	ofstream outfile("output.txt", ios::out);

			//print out the header file before anything
	header(outfile);

			//set up arrays in and out strings, syndrome words, and syndrome codes
	string temp, original[max][2], codeWord[max][2], syndromes[max][2], finalSyndrome;
	int cases[max], x = -1, y = -1;

			//get the very first line of input file
	infile >> temp;

			//read the given data file into arrays
	int counter = 0;
	while (temp.compare("-1") != 0) {

				//read two lines as one input
		for (int i = 0; i < 2; i++) {

					//put in the memory in for the first line
			if (i%2 == 0) {
				original[counter][0] = temp;
				infile >> temp;
			}

					//put in the memory out for the second line
			else {
				original[counter][1] = temp;
				infile >> temp;
			}
		}
				//increament input counter
		counter++;
	}

			//calculate syndrome words for both input and output messages
	calcSyndromes(original, syndromes, counter);

			//get code words from original input and output messages and syndrome words
	getCodeWords(original, codeWord, syndromes, counter);

			//process error cases and message outputs
	for (int i = 0; i < counter; i++) {
		outfile << "Record # " << i + 1;

				//calculate case number based on the syndrome words
		cases[i] = compareSyndromes(syndromes[i][0], syndromes[i][1], finalSyndrome, x, y);

				//print out for case 1
		if (cases[i] == 1) {

					//get message string for case 1
			temp = getMessage(1, x, y);
			printMessage(outfile, original[i][0], original[i][1], codeWord[i][0],
				syndromes[i][0], syndromes[i][1], finalSyndrome, temp);
		}
				//print out for case 2
		else if (cases[i] == 2) {
					
					//pick the vaule of y from position x
			y = codeWord[i][1][21-x] - '0';

					//get message string for case 2
			temp = getMessage(2, x, y);

					//print out the information
			printMessage(outfile, original[i][0], original[i][1], codeWord[i][0],
				syndromes[i][0], syndromes[i][1], finalSyndrome, temp);
		}
				//print out for case 3
		else if (cases[i] == 3) {

					//get message string for case 3
			temp = getMessage(3, x, y);

					//print out the information
			printMessage(outfile, original[i][0], original[i][1], codeWord[i][0],
				syndromes[i][0], syndromes[i][1], finalSyndrome, temp);
		}
				//print out for case 4
		else if (cases[i] == 4) {

					//get message string for case 4
			temp = getMessage(4, x, y);
				
					//print out the information
			printMessage(outfile, original[i][0], original[i][1], codeWord[i][0],
				syndromes[i][0], syndromes[i][1], finalSyndrome, temp);
		}

				//reset x and y to default values for the next record
		x = -1; y = -1;
	}

			//print out footer after everything is finished
	footer(outfile);

	return 0;
}

//*****************************************************************************************************
void calcSyndromes(string original[][2], string syndromes[][2], int counter) {

			// Receives – array of original input and output strings
			// Task - calculate two syndrome words
			// Returns - array of strings of code words

	for (int i = 0; i < counter; i++) {
				//make room for 16 data bits and 5 parity bits
		int temp[2][21];		
		int code[2][5];

				//turn the string of 16 characters into integer type
		for (int j = 0; j < 16; j++) {

					//turn the characters into integers to work
			temp[0][j] = original[i][0][j] - '0';
			temp[1][j] = original[i][1][j] - '0';
		}

				//calculate for position 1
				//calculate for input data
		temp[0][16] = temp[0][15] + temp[0][14] + temp[0][12] + temp[0][11] + temp[0][9]
					+ temp[0][7] + temp[0][5] + temp[0][4] + temp[0][2] + temp[0][0];
		code[0][4] = temp[0][16] % 2;

				//calculate for output data
		temp[1][16] = temp[1][15] + temp[1][14] + temp[1][12] + temp[1][11] + temp[1][9]
			+ temp[1][7] + temp[1][5] + temp[1][4] + temp[1][2] + temp[1][0];
		code[1][4] = temp[1][16] % 2;

				//calculate for position 2
				//calculate for input data
		temp[0][17] = temp[0][15] + temp[0][13] + temp[0][12] + temp[0][10] 
					+ temp[0][9] + temp[0][6] + temp[0][5] + temp[0][3] + temp[0][2];
		code[0][3] = temp[0][17] % 2;

				//calculate for output data
		temp[1][17] = temp[1][15] + temp[1][13] + temp[1][12] + temp[1][10]
			+ temp[1][9] + temp[1][6] + temp[1][5] + temp[1][3] + temp[1][2];
		code[1][3] = temp[1][17] % 2;
		
				//calculate for position 4
				//calculate for input data
		temp[0][18] = temp[0][14] + temp[0][13] + temp[0][12] + temp[0][8] 
					+ temp[0][7] + temp[0][6] + temp[0][5] + temp[0][1] + temp[0][0];
		code[0][2] = temp[0][18] % 2;

				//calculate for output data
		temp[1][18] = temp[1][14] + temp[1][13] + temp[1][12] + temp[1][8]
			+ temp[1][7] + temp[1][6] + temp[1][5] + temp[1][1] + temp[1][0];
		code[1][2] = temp[1][18] % 2;
		
				//calculate for position 8
				//calculate for input data
		temp[0][19] = temp[0][11] + temp[0][10] + temp[0][9] 
					+ temp[0][8] + temp[0][7] + temp[0][6] + temp[0][5];
		code[0][1] = temp[0][19] % 2;

				//calculate for output data
		temp[1][19] = temp[1][11] + temp[1][10] + temp[1][9]
			+ temp[1][8] + temp[1][7] + temp[1][6] + temp[1][5];
		code[1][1] = temp[1][19] % 2;

				//calculate for position 16
				//calculate for input data
		temp[0][20] = temp[0][4] + temp[0][3] + temp[0][2] + temp[0][1] + temp[0][0];
		code[0][0] = temp[0][20] % 2;

				//calculate for output data
		temp[1][20] = temp[1][4] + temp[1][3] + temp[1][2] + temp[1][1] + temp[1][0];
		code[1][0] = temp[1][20] % 2;

				//turn array of syndrome codes into strings syndrome words
		for (int k = 0; k < 5; k++) {
					
					//turn the integers into characters
			syndromes[i][0] += code[0][k] + '0';
			syndromes[i][1] += code[1][k] + '0';
		}
	}

}

//*****************************************************************************************************
void getCodeWords(string original[][2], string codeWord[][2], string syndromes[][2], int counter) {

			// Receives – array of original input and output strings
			// Task - add parity bits to the original string
			// Returns - array of strings of code words

	for (int i = 0; i < counter; i++) {

				//add five more bits to original bits to allow adding 5 parity bits on codeWord
		codeWord[i][0] = original[i][0] + "00000";
		codeWord[i][1] = original[i][1] + "00000";

		for (int j = 0; j<21; j++) {

					//reposition the data bits for both input and output data strings
			if (j < 5) {
				codeWord[i][0][j] = original[i][0][j];
				codeWord[i][1][j] = original[i][1][j];
			}
			else if (j > 5 && j < 13) {
				codeWord[i][0][j] = original[i][0][j - 1];
				codeWord[i][1][j] = original[i][1][j - 1];
			}
			else if (j > 13 && j < 17) {
				codeWord[i][0][j] = original[i][0][j - 2];
				codeWord[i][1][j] = original[i][1][j - 2];
			}
			else if (j == 18) {
				codeWord[i][0][j] = original[i][0][j - 3];
				codeWord[i][1][j] = original[i][1][j - 3];
			}
					//place the parity bits at their appropiate positions in both data strings
					//place C5 in position 16
			else if (j == 5) {
				codeWord[i][0][j] = syndromes[i][0][4];
				codeWord[i][1][j] = syndromes[i][1][4];
			}
					//place C4 in position 8
			else if (j == 13) {
				codeWord[i][0][j] = syndromes[i][0][3];
				codeWord[i][1][j] = syndromes[i][1][3];
			}
					//place C3 in position 4
			else if (j == 17) {
				codeWord[i][0][j] = syndromes[i][0][2];
				codeWord[i][1][j] = syndromes[i][1][2];
			}
					//place C2 in position 2
			else if (j == 19) {
				codeWord[i][0][j] = syndromes[i][0][1];
				codeWord[i][1][j] = syndromes[i][1][1];
			}
					//place C1 in position 1
			else if (j == 20) {
				codeWord[i][0][j] = syndromes[i][0][0];
				codeWord[i][1][j] = syndromes[i][1][0];
			}
		}
	}
}

//*****************************************************************************************************
int compareSyndromes(string input, string output, string &syndrome, int &x, int &y) {

			// Receives – syndrome word of input and output strings
			// Task - calculates a final syndrome word from input and output syndromes
			// Returns - comparison result, final syndrome word

			//initiate Final syndrome word
	syndrome = "00000";

			//calculate final syndrome word
	for (int i = 0; i < 5; i++) {
		if (input[i] != output[i]) {
			syndrome[i] = '1';
		}
	}
			//turn the binary word into calculatable decimal
	int temp = binToDec(syndrome);

			//return case 1 if error location is at 0 (no error)
	if (temp == 0) return 1;

			//return case 4 if error location is larger than 21
	else if (temp > 21) return 4;

			//return case 3 iferror location is at check bit positions
	else if (temp == 1 || temp == 2 || temp == 4 || temp == 8 || temp == 16) return 3;

			//return case 2 if syndrome is at data bit positions
	else {
				//set x to error location
		x = temp;
		return 2;
	}
	
}

//*****************************************************************************************************
int binToDec(string bin) {

			// Receives – string of binary digits
			// Task - convert the string of binary digits into a decimal number
			// Returns - converted decimal value

			//get length of the binary string
	int length = bin.length();

			//set the initial value to 0
	int value = 0;

			//calculate the decimal value of given binary string
	for (int i = length-1; i >= 0; i--) {
		if (bin[i] == '1') {
			value += (int) pow(2, (4-i));
		}
	}

			//return calculated decimal value
	return value;
}

//*****************************************************************************************************
string getMessage(int caseNumber, int x, int y) {

			// Receives – case number of the message
			// Task - determines the message for given case number
			// Returns - message string for the input case

			//get a temporary string holder
	string temp;

			//calculate y prime
	int yInv = 0;
	if (y == 0) yInv = 1;

			//make sure the case number is valid
	if (caseNumber > 0 && caseNumber < 5) {
		switch (caseNumber) {

					//return no error message for case 1
		case 1:
			temp = "A comparison of the syndrome words indicates that ";
			temp += "the word read from memory is correct.";
			return temp;

					//return message for error on data bit position for case 2
		case 2:
			temp = "The syndrome word indicates that the bit in position " + to_string(x) + " of the ";
			temp += "word read from memory is in error. It was read as a " + to_string(y) + " and must ";
			temp += "be inverted to a " + to_string(yInv) + ".";
			return temp;

					//return message for error on check bit position for case 3
		case 3:
			temp = "The syndrome word indicates that a check bit is in error. ";
			temp += "No correction to the data is necessary.";
			return temp;

					//return message for uncorrectable error
		case 4:
			temp = "The value of the syndrome word indicates that the error ";
			temp += "cannot be corrected. Output data is unreliable.";
			return temp;
		}
	}

			//throw an error if the given case number are not in range
	else return "Case code Error!";
}

//*****************************************************************************************************
void printMessage(ofstream &outfile, string input1, string input2, string stored, 
				string syndrome1, string syndrome2, string fSyndrome, string message) {

			// Receives – information needed to print out each record
			// Task - Prints the output the formatted record
			// Returns - Nothing

	outfile << endl << message << endl;
}
//*****************************************************************************************************
void header(ofstream &outfile) {

			// Receives – the output file
			// Task - Prints the output preamble
			// Returns - Nothing

	outfile << setw(33) << "Hein Htet Zaw";
	outfile << setw(15) << "CSC 40300";
	outfile << setw(15) << "Section 11" << endl;
	outfile << setw(37) << "Fall 2016";
	outfile << setw(20) << "Assignment #2" << endl;
	outfile << setw(38) << "-------------------------------------------";
	outfile << setw(38) << "------------------------------------------\n\n";

	return;
}

//*****************************************************************************************************
void footer(ofstream &outfile) {

			// Receives – the output file
			// Task - Prints the output salutation
			// Returns - Nothing

	outfile << endl;
	outfile << setw(35) << "----------------------------------" << endl;
	outfile << setw(35) << "|      END OF PROGRAM OUTPUT     |" << endl;
	outfile << setw(35) << "----------------------------------" << endl;

	return;
}

//*****************************************************************************************************
