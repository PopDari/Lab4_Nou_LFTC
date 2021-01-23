#pragma once

#include <iostream>
#include "finiteAutomaton.h"

using namespace std;

int main() {
	FiniteAutomaton finiteAutomaton("FA.in");
	cout << "To print the states enter 1. \n";
	cout << "To print the alphabet enter 2. \n";
	cout << "To print the final states enter 3. \n";
	cout << "To print the transitions enter 4. \n";
	cout << "To see if i accepts a sequence enter 5 and then enter the sequence. \n";
	cout << "To exit enter 0. \n";
	cout << "________________________________________________________________\n";
	string userInput;
	cin >> userInput;
	while (userInput != "0") {
		if (userInput == "1")
			finiteAutomaton.printStates();
		else if (userInput == "2")
			finiteAutomaton.printAlphabet();
		else if (userInput == "3")
			finiteAutomaton.printFinalStates();
		else if (userInput == "4") 
			finiteAutomaton.printTransitions();
		else if (userInput == "5") {
			string sequence;
			cout << "Enter sequence: ";
			cin >> sequence;
			if (finiteAutomaton.acceptsSequence(sequence))
				cout << "Sequence is accepted! \n";
			else
				cout << "Sequence is NOT accepted! \n";
		}
		else
			cout << "Input can be only 0, 1, 2, 3 or 4! \n";
		cout << "________________________________________________________________\n";
		cin >> userInput;
	}
	return 0;
}