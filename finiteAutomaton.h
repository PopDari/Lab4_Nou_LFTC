#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>

using namespace std;

class FiniteAutomaton {

private:

	string filename;

	vector<string> states;

	vector<string> alphabet;

	map<pair<string, string>, vector<string>> transitions;

	string initialState;

	vector<string> finalStates;

public:

	FiniteAutomaton(string filename);

	void readFiniteAutomaton();

	void readStates(string line);

	void readAlphabet(string line);

	void readInitialState(string line);

	void readFinalStates(string line);

	void readTransition(string line);

	void printStates();

	void printAlphabet();

	void printFinalStates();

	void printTransitions();

	bool isDFA();

	bool acceptsSequence(string sequence);

	vector <string> getStates();

	vector <string> getAlphabet();

	vector <string> getFinalStates();

};