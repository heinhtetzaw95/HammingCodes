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

		//define maximum number of inputs that this program can handle (10 is enough for this case)
#define max 10

using namespace std;

void header(ofstream&);
void footer(ofstream&);
string getMessage(int);

int main() {
			//set up input file and output files
	ifstream infile("data2.txt", ios::in);
	ofstream outfile("output.txt", ios::out);

			//print out the header file before anything
	header(outfile);

			//set up arrays for memory in and out strings
	string temp, bit[max][2];

			//get the very first line of input file
	infile >> temp;

			//read the given data file into arrays
	int counter = 0;
	while (temp.compare("-1") != 0) {

				//read two lines as one input
		for (int i = 0; i < 2; i++) {

					//put in the memory in for the first line
			if (i%2 == 0) {
				bit[counter][0] = temp;
				infile >> temp;
			}

					//put in the memory out for the second line
			else {
				bit[counter][1] = temp;
				infile >> temp;
			}
		}
				//increament input counter
		counter++;
	}

//this is for testing *********************************************************
	for (int i = 0; i < counter; i++) {
		outfile << i << ":\n" << bit[i][0] << endl << bit[i][1] << endl;
	}
//*****************************************************************************

//	cin.get();

			//print out footer after everything is finished
	footer(outfile);

	return 0;
}
//*****************************************************************************************************
string getMessage(int caseNumber, int x, int y) {

			// Receives – case number of the message
			// Task - determines the message for given case number
			// Returns - message string for the input case

	string temp;
	int yInv = 0;

	if (y < 0) {
		goto pass;
	}
	else if (y == 0) {
		yInv = 1;
	}
	else if (y == 1) {
		yInv = 0;
	}

	pass: switch (caseNumber) {
	case 1:
		temp = "A comparison of the syndrome words indicates that ";
		temp += "the word read from memory is correct.";
		return temp;

	case 2:
		temp = "The syndrome word indicates that the bit in position "+ to_string(x) +" of the ";
		temp += "word read from memory is in error.It was read as a "+ to_string(y) +" and must ";
		temp += "be inverted to a "+ to_string(yInv) +".";
		return temp;

	case 3:
		temp = "The syndrome word indicates that a check bit is in error. ";
		temp += "No correction to the data is necessary.";
		return temp;

	case 4:
		temp = "The value of the syndrome word indicates that the error ";
		temp += "cannot be corrected.Output data is unreliable.";
		return temp;
	}
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
