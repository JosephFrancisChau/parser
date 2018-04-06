//#include "stdafx.h"
#include "lexer.h"
#include <iostream>
#include <iomanip>  //setw
#include <fstream>

using namespace std;

ofstream coutfile;
void readFile(const string& filename);
void printSourceCode(const string& filename);

int main() {
	string sourceFile, outputFile;	

	//test sample source code
	cout << "Enter test file name(format: filename.txt): ";
	cin >> sourceFile;

	cout << "Enter test output file name(format: filename.txt): ";
	cin >> outputFile;

	coutfile.open(outputFile);
	cout << "source Code:" << endl << endl;
	coutfile << "Source Code:" << endl << endl;
	printSourceCode(sourceFile);

	cout << "\nOutput:\n\n";
	coutfile << "\nOutput:\n\n";
	
	cout << left << setw(10) << "token" << "\t\t" << "lexeme" << endl;
	coutfile << left << setw(10) << "token" << "\t\t" << "lexeme" << endl;
	readFile(sourceFile);
	coutfile.close();
	//system("pause");
	return 0;
}

void readFile(const string& filename) {
	ifstream file(filename);
	string word;

	if (file.is_open()) {
		while (file >> word) {
			vector<string> vec = splitWord(word);
			Token token = lexer(word);
			for (unsigned i = 0; i < vec.size(); ++i) {
				token = lexer(vec.at(i));
				if (!(token.type == "NotToken" || token.type == "COMMENT")) {
					cout << left << setw(10) << token.type << "\t\t" << token.value << endl;
					coutfile << left << setw(10) << token.type << "\t\t" << token.value << endl;
				}
			}			
		}
	}
	else {
		cout << "Can't open the file: " << filename << endl;
	}

	file.close();
	file.clear();
	return;
	}

void printSourceCode(const string& filename) {
	ifstream file(filename);
	string line;

	if (file.is_open()) {
		while (!file.eof()) {
			getline(file, line);
			cout << line << endl;
			coutfile << line << endl;
		}
	}
	else
		cout << "Can't open the file: " << filename << endl;
	file.close();
	file.clear();
	cout << endl;
	coutfile << endl;
	return;
}
