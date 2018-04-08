#include "lexer.h"
#include "globals.h"
#include "parser.hpp"
#include <fstream>
#include <iomanip>

using namespace std;

ofstream coutfile;
//void readFile(const string& filename);
//void printSourceCode(const string& filename);

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
    coutfile.close();
    
    return 0;
}
//
//void readFile(const string& filename){
//    ifstream file(filename);
//    string word;
//
//    if (file.is_open()) {
//        while (file >> word) {
//            vector<string> vec = splitWord(word);
//            Token token = lexer(word);
////            for (unsigned i = 0; i < vec.size(); ++i) {
////                token = lexer(vec.at(i));
////                if (!(token.type == "NotToken" || token.type == "COMMENT")) {
////                    cout << left << setw(10) << token.type << "\t\t" << token.value << endl;
////                    coutfile << left << setw(10) << token.type << "\t\t" << token.value << endl;
////                }
////            }
//        }
//    }
//    else {
//        cout << "Can't open the file: " << filename << endl;
//    }
//
//    file.close();
//    file.clear();
//    return;
//}
