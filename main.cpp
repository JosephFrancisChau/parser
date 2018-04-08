#include "lexer.h"
#include "globals.h"
#include "parser.h"

using namespace std;

string outputFile;

int main(int argc, const char * argv[]) {
    string inputFile, word, ofile;
    ifstream sourceFile;
    Token start;
    
    //test sample source code
    cout << "Enter test file name(format: filename.txt): ";
    cin >> inputFile;
    
    cout << "Enter test output file name(format: filename.txt): ";
    cin >> outputFile;
    //readFile(sourceFile);
    
    if (sourceFile.is_open()){
        while (sourceFile >> word){
            vector<string> vec = splitWord(word);
            start = lexer(word);
        }
    }
    Parser(start);
    return 0;
}

