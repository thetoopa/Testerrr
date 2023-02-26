#include "program1.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool invalidGrammar = true;
int currTokenIndex = 0;

vector<string> tokens; // Global vector to hold the tokens

bool ParseS();
bool ParseNonTerminals();
bool ParseIDs();
bool ParseID();
bool ParseRule();
bool ParseRules();
bool ParseRightSide();
bool ParseArrow();

// Loads the grammar.
void LoadGrammar(char* grammarFileName) {
    // Declare a variable to hold the file stream
    ifstream grammarFile;

    // Open the file
    grammarFile.open(grammarFileName);

    // Check if the file was opened successfully
    if (!grammarFile.is_open()) {
        // If the file was not opened successfully, print an error message and return
        cout << "Error: Unable to open file: " << grammarFileName << endl;
        return;
    }

    // Declare a vector to hold the lines of the file
    vector<string> lines;

    // Declare a string to hold each line of the file as it is read in
    string line;

    // Loop through each line in the file
    while (getline(grammarFile, line)) {
        // Add the line to the vector
        lines.push_back(line);
    }

    // Close the file
    grammarFile.close();

    // Print the lines that were read in (this is just for debugging purposes)
    for (string s : lines) {
        cout << s << endl;
    }
}

// Parses the grammar file.
void ParseGrammar(vector<string>& lines) {
    // Parse S
    if (!ParseS()) {
        cerr << "Error parsing S" << endl;
        return;
    }

    // Parse NonTerminals
    if (!ParseNonTerminals()) {
        cerr << "Error parsing NonTerminals" << endl;
        return;
    }

    // Parse Rules
    while (currTokenIndex < tokens.size()) {
        if (!ParseRule()) {
            cerr << "Error parsing Rule" << endl;
            return;
        }
    }

    // The grammar has been parsed successfully
    invalidGrammar = false;
}

// Parses S
bool ParseS() {
    if (tokens.empty()) {
        cerr << "Error: no tokens available" << endl;
        return false;
    }

    if (tokens[currTokenIndex] != "S") {
        cerr << "Error parsing S" << endl;
        return false;
    }

    currTokenIndex++;
    return true;
}

// Parses NonTerminals
bool ParseNonTerminals() {
    if (tokens.empty() || currTokenIndex >= tokens.size()) {
        cerr << "Error: no tokens available" << endl;
        return false;
    }

    if (tokens[currTokenIndex] != "NonTerminals") {
        cerr << "Error parsing NonTerminals" << endl;
        return false;
    }

    currTokenIndex++;
    if (!ParseIDs()) {
        cerr << "Error parsing IDs" << endl;
        return false;
    }

    if (tokens[currTokenIndex] != "@") {
        cerr << "Error: missing @" << endl;
        return false;
    }

    currTokenIndex++;
    return true;
}

// Parses IDs
bool ParseIDs() {
    if (tokens.empty() || currTokenIndex >= tokens.size()) {
        cerr << "Error: no tokens available" << endl;
        return false;
    }

    if (tokens[currTokenIndex] != "ID") {
        cerr << "Error parsing IDs" << endl;
        return false;
    }

    currTokenIndex++;
    while (tokens[currTokenIndex] == "ID") {
        currTokenIndex++;
    }

    return true;
}

// Parses a rule
bool ParseRule() {
    if (tokens.empty() || currTokenIndex >= tokens.size()) {
        cerr << "Error: no tokens available" << endl;
        return false;
    }

    if (tokens[currTokenIndex] != "ID") {
        cerr << "Error parsing Rule" << endl;
        return false;
    }

    currTokenIndex++;
    if (tokens[currTokenIndex] != "->") {
        cerr << "Error: missing ->" << endl;
        return false;
    }

    currTokenIndex++;
    if (!ParseRightSide()) {
        cerr << "Error parsing RightSide" << endl;
        return false;
    }

    if (tokens[currTokenIndex] != "@") {
        cerr << "Error: missing @" << endl;
        return false;
    }

    currTokenIndex++;
    return true;
}

// Parses the right side of a rule
bool ParseRightSide() {
    if (tokens.empty() || currTokenIndex >= tokens.size()) {
        cerr << "Error: no tokens available" << endl;
        return false;
    }

    if (tokens[currTokenIndex] == "#") {
        currTokenIndex++;
        return true;
	}
}

// Returns a string with some statistics for the grammar.
char* GetStats() {
	return "";
}

// Returns the first sets of all nonterminals.
char* GetFirstSets() {
	return "";
}

// Returns the first set of the specified nonterminal.
char* GetFirstSet(char *nonTerminal) {
	return "";
}

// Returns the follow sets of all nonterminals.
char* GetFollowSets() {
	return "";
}

// Returns the follow set of the specified nonterminal.
char* GetFollowSet(char *nonTerminal) {
	return "";
}

int main() {
    LoadGrammar("/Users/cooperheisler/Desktop/Assignment1/my_grammar.txt");
    //std::cout << GetStats() << std::endl;
    //std::cout << GetFirstSets() << std::endl;
    //std::cout << GetFollowSets() << std::endl;
    return 0;
}