#include "lexer.h"
#include "globals.h"
#include "parser.h"

using namespace std;
vector<string> allWords;
string outputFile;
Token start;
//fstream coutfile(outputFile);

int main(int argc, const char * argv[]) {
    string inputFile, word, ofile;
    //ifstream sourceFile;
    
    
    //test sample source code
    cout << "Enter test file name(format: filename.txt): ";
    cin >> inputFile;
    
    cout << "Enter test output file name(format: filename.txt): ";
    cin >> outputFile;
    
    fstream coutfile;
    coutfile.open(outputFile, fstream::out);
    
    ifstream sourceFile(inputFile);
    
    if (sourceFile.is_open()) {
                // call splitWord can creat allWords
		while (sourceFile >> word) {
			vector<string> vec = splitWord(word);
			for (unsigned i = 0; i < vec.size(); ++i) {
				allWords.push_back(vec.at(i));
			}
		}

		//test the new code on allWords works or nor
		for (unsigned i = 0; i < allWords.size(); ++i) {
			Token token = lexer(allWords.at(i));
			cout << token.type << "\t\t" << token.value << endl;
			coutfile << token.type << "\t\t" << token.value << endl;
		}	
    }
    else {
        cout << "Can't open the file: " << inputFile << endl;
    }
    
    sourceFile.close();
    
    
    return 0;
}

