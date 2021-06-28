/************************************************************************************
** Damian Valles
** EE5321 – CPP Templates
** Filename: add-values.cpp
**
** Objective:
** Add two values
**
*************************************************************************************/
#include <iostream>
using namespace std;

int main() {

	// Declare variables
 	int firstNumber, secondNumber, sumOfTwoNumbers;

	// Defining the two number variables
	firstNumber = 35;
	secondNumber = 25;

	// sum of two numbers in stored in variable sumOfTwoNumbers
 	sumOfTwoNumbers = firstNumber + secondNumber;
 
	// Prints sum
	cout << "\n 1st Number = " << firstNumber << " \n";
	cout << "\n 2nd Number = " << secondNumber << " \n";
	cout << "\n Addition = " << sumOfTwoNumbers << " \n";

	return 0;
}
