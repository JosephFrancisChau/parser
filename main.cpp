#include "lexer.h"
#include "parser.hpp"
#include <fstream>
#include <iomanip>


using namespace std;

ofstream coutfile;
void readFile(const string& filename);
void printSourceCode(const string& filename);

int main(int argc, const char * argv[]) {
    string sourceFile, outputFile, start;
    
    //test sample source code
    cout << "Enter test file name(format: filename.txt): ";
    cin >> sourceFile;
    
    cout << "Enter test output file name(format: filename.txt): ";
    cin >> outputFile;
    
    coutfile.open(outputFile);
    //readFile(sourceFile);
    
    // Opening File to get 1st character to input into 
    
    
    
    coutfile.close();
    
    
    
    
    return 0;
}

void readFile(const string& filename){
    ifstream file(filename);
    string word;
    
    if (file.is_open()) {
        while (file >> word) {
            vector<string> vec = splitWord(word);
            Token token = lexer(word);
//            for (unsigned i = 0; i < vec.size(); ++i) {
//                token = lexer(vec.at(i));
//                if (!(token.type == "NotToken" || token.type == "COMMENT")) {
//                    cout << left << setw(10) << token.type << "\t\t" << token.value << endl;
//                    coutfile << left << setw(10) << token.type << "\t\t" << token.value << endl;
//                }
//            }
        }
    }
    else {
        cout << "Can't open the file: " << filename << endl;
    }
    
    file.close();
    file.clear();
    return;
}
