#pragma once

#include "finiteAutomaton.h"
#include <fstream>

FiniteAutomaton::FiniteAutomaton(string filename) {
	this->filename = filename;
	this->readFiniteAutomaton();
}

void FiniteAutomaton::readFiniteAutomaton() {
	ifstream fin(this->filename);
	string line;
	getline(fin, line);
	this->readStates(line);
	getline(fin, line);
	this->readAlphabet(line);
	getline(fin, line);
	this->readInitialState(line);
	getline(fin, line);
	this->readFinalStates(line);
	while (getline(fin, line)) 
		this->readTransition(line);
}

void FiniteAutomaton::readStates(string line) {
	string state;
	for (int i = 0; i < line.size(); ++i) {
		if (line[i] == ' ') {
			this->states.push_back(state);
			state.clear();
		}
		else 
			state += line[i];
	}
	this->states.push_back(state);
}

void FiniteAutomaton::readAlphabet(string line) {
	string letter;
	for (int i = 0; i < line.size(); ++i) {
		if (line[i] == ' ') {
			this->alphabet.push_back(letter);
			letter.clear();
		}
		else
			letter += line[i];
	}
	this->alphabet.push_back(letter);
}

void FiniteAutomaton::readInitialState(string line) {
	this->initialState = line;
}

void FiniteAutomaton::readFinalStates(string line) {
	string finalState;
	for (int i = 0; i < line.size(); ++i) {
		if (line[i] == ' ') {
			this->finalStates.push_back(finalState);
			finalState.clear();
		}
		else
			finalState += line[i];
	}
	this->finalStates.push_back(finalState);
}

void FiniteAutomaton::readTransition(string line) {
	string beginState;
	int index = 0;
	while (true) {
		if (line[index] == ' ')
			break;
		beginState += line[index];
		++index;
	}
	string letter;
	++index;
	while (true) {
		if (line[index] == ' ')
			break;
		letter += line[index];
		++index;
	}
	vector<string> vectorOfNextStates;
	string state;
	for (index = index + 1; index < line.size(); ++index) {
		if (line[index] == ' ') {
			vectorOfNextStates.push_back(state);
			state.clear();
		}
		else
			state += line[index];
	}
	vectorOfNextStates.push_back(state);
	pair<string, string> myPair;
	myPair.first = beginState;
	myPair.second = letter;
	this->transitions.insert(pair<pair<string, string>, vector<string>>(myPair, vectorOfNextStates));
}

void FiniteAutomaton::printStates() {
	cout << "States are: ";
	for (int i = 0; i < this->states.size() - 1; ++i)
		cout << this->states[i] << ", ";
	cout << this->alphabet[this->alphabet.size() - 1] << "\n";
}

void FiniteAutomaton::printAlphabet() {
	cout << "The alphabet is: ";
	for (int i = 0; i < this->alphabet.size() - 1; ++i)
		cout << this->alphabet[i] << ", ";
	cout << this->alphabet[this->alphabet.size() - 1] << "\n";
}

void FiniteAutomaton::printFinalStates() {
	cout << "Final states are: ";
	for (int i = 0; i < this->finalStates.size() - 1; ++i)
		cout << this->finalStates[i] << ", ";
	cout << this->finalStates[this->finalStates.size() - 1] << "\n";
}

void FiniteAutomaton::printTransitions() {
	cout << "Transitions are: \n";
	map<pair<string, string>, vector<string>>::iterator it;
	for (it = this->transitions.begin(); it != this->transitions.end(); it++) {
		cout << it->first.first << " " << it->first.second << " --> ";
		vector<string> vectorOfNextStates = it->second;
		for (int i = 0; i < vectorOfNextStates.size() - 1; ++i)
			cout << vectorOfNextStates[i] << ", ";
		cout << vectorOfNextStates[vectorOfNextStates.size() - 1] << "\n";
	}
}

bool FiniteAutomaton::isDFA() {
	map<pair<string, string>, vector<string>>::iterator it;
	for (it = this->transitions.begin(); it != this->transitions.end(); it++) 
		if (it->second.size() > 1)
			return false;
	return true;
}

bool FiniteAutomaton::acceptsSequence(string sequence) {
	if (this->isDFA()) {
		string currentState = this->initialState;
		for (int i = 0; i < sequence.size(); ++i) {
			string currentChar;
			currentChar += sequence[i];
			pair<string, string> myPair;
			myPair.first = currentState;
			myPair.second = currentChar;
			if (this->transitions.count(myPair))
				currentState = this->transitions.at(myPair)[0];
			else
				return false;
		}
		for (int i = 0; i < this->finalStates.size(); ++i)
			if (this->finalStates[i] == currentState)
				return true;
		return false;
	}
	else
		cout << "This isn't a DFA! \n";
}

vector <string> FiniteAutomaton::getStates() {
	return this->states;
}

vector <string> FiniteAutomaton::getAlphabet() {
	return this->alphabet;
}

vector <string> FiniteAutomaton::getFinalStates() {
	return this->finalStates;
}