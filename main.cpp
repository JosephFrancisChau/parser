#include "lexer.h"
#include "globals.h"
#include "parser.h"

using namespace std;

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
                while (sourceFile >> word) {
                    vector<string> vec = splitWord(word);
                    Token start = lexer(word);
                    for (unsigned i = 0; i < vec.size(); ++i) {
                        start = lexer(vec.at(i));
                        Parser(start);
                    }
                }
            }
    else {
        cout << "Can't open the file: " << inputFile << endl;
    }
    
    sourceFile.close();
    
    
    return 0;
}

