#include "parser.h"
#include "lexer.h"
#include <fstream>
#include "globals.h"

using namespace std;

Token token;
int ruleNum;
string s;

//fstream coutfile(outputFile, std::ios_base::app);
//ofstream coutfile;

void Parser(Token word) {
    token = word;
    Rat18S(token);
}

void Error() {
    cout << "Syntax Error!" << endl;
}

//R1: <Rat18S> → <Opt Function Definitions> %% <Opt Declaration List> <Statement List>
void Rat18S(Token token) {
    OptFunctionDefinitions();
    if (lexer(s).value == "%%") {
        OptDeclarationList();
        StatementList();
        PrintRule(1);
    }
    else Error();
    if (token.value != "$") Error();
}

//R2: <Opt Function Definitions> → <Function Definitions> | <Empty>
void OptFunctionDefinitions() {
    if (token.type == "NotToken" || token.type == "COMMENT") {
        Empty();
    }
    else {
        FunctionDefinitions();
    }
    PrintRule(2);
}

//R3: <Function Definitions> → <Function> <Function Definitions’>
void FunctionDefinitions() {
    Function();
    FunctionDefinitionsP();
    PrintRule(3);
}

//R4: <Function Definitions’> → <Function Definitions> |  𝜀
void FunctionDefinitionsP() {
    if (token.type == "NotToken" || token.type == "COMMENT") {
        Empty();
    }
    else {
        FunctionDefinitions();
    }
    PrintRule(4);
}

//R5: <Function> → function <Identifier> [<Opt Parameter List>] <Opt Declaration List> <Body>
void Function() {
    //int rule = 5;
    if (token.value == "function") {
        Identifier();
        if (lexer(s).value == "[") {
            OptParameterList();
            if (lexer(s).value == "]") {
                OptDeclarationList();
                Body();
                PrintRule(5);
            }
            else Error();
        }
        else Error();
    }
    else Error();
}

//R6: <Opt Parameter List> → <Parameter List> | <Empty>
void OptParameterList() {
    if (token.type == "NotToken" || token.type == "COMMENT") {
        Empty();
    }
    else {
        ParameterList();
    }
    PrintRule(6);
}

//R7: <Parameter List> → <Parameter> <Parameter List’>
void ParameterList() {
    Parameter();
    ParameterListP();
    PrintRule(7);
}

//R8: <Parameter List’> → , <Parameter List> |  𝜀
void ParameterListP() {
    if (token.type == "NotToken" || token.type == "COMMENT") {
        Empty();
        PrintRule(8);
    }
    else {
        if (token.value == ",") {
            ParameterList();
            PrintRule(8);
        }
        else Error();
    }
}

//R9: <Parameter> → <IDs> : <Qualifier>
void Parameter() {
    IDs();
    if (lexer(s).value == ":") {
        Qualifier();
        PrintRule(9);
    }
    else Error();
}

//R10: <Qualifier> → int | boolean | real
void Qualifier() {
    if(token.value == "int" || token.value == "boolean" || token.value == "real"){
        PrintRule(10);
    }
    else Error();
}

//R11: <Body> → { <Statement List> }
void Body() {
    if (token.value == "{") {
        StatementList();
        if (lexer(s).value == "}") {
            PrintRule(11);
        }
        else Error();
    }
    else Error();
}

//R12: <Opt Declaration List> → <Declaration List> | <Empty>
void OptDeclarationList() {
    if (token.type == "NotToken" || token.type == "COMMENT") {
        Empty();
    }
    else {
        DeclarationList();
    }
    PrintRule(12);
}

//R13: <Declaration List> → <Declaration> ; <Declaration List’>
void DeclarationList(){
    Declaration();
    if (lexer(s).value == ";"){
        DeclarationListP();
        PrintRule(13);
    }
    else
        Error();
}

//R14: <Declaration List’> → <Declaration List> | <Empty>
void DeclarationListP()
{
    if (token.type == "NotToken" || token.type == "COMMENT")
    {
        Empty();
        PrintRule(14);
    }
    else
    {
        DeclarationList();
    }
}

//R15: <Declaration> → <Qualifier> <IDs>
void Declaration(){
    Qualifier();
    IDs();
    PrintRule(15);
}

//R16: <IDs> → <Identifier> <IDs’>
void IDs(){
    Identifier();
    IDsP();
    PrintRule(16);
}

//R17: <IDs’> → , <IDs> | <Empty>
void IDsP(){
    if (token.type == "NotToken" || token.type == "COMMENT") {
        Empty();
        PrintRule(17);
    }
    else {
        if (token.value == ",") {
            IDs();
            PrintRule(17);
        }
        else
            Error();
    }
}

//R18: <Statement List> → <Statement> <Statement List’>
void StatementList(){
    Statement();
    StatementListP();
    PrintRule(18);
}

//R19: <Statement List’> → <Statement List> | <Empty>
void StatementListP(){
    if (token.type == "NotToken" || token.type == "COMMENT") {
        Empty();
    }
    else {
        StatementList();
    }
    PrintRule(19);
}

//R20: <Statement> → <Compound> | <Assign> | <If> | <Return> | <Print> | <Scan> | <While>
void Statement(){
    // Check if <Compound>
    if (token.value == "{") {
        Compound();
    }
    
    // Check if <Assign>
    if (token.type == "identifier"){
        if (lexer(s).value == ":") {
            Assign();
        }
    }
    
    // Check <If>
    if (token.type == "keyword" && token.value == "if"){
        if (lexer(s).value =="("){
            If();
        }
    }
    
    // Check <Return>
    if (token.type == "keyword" && token.value == "return"){
        Return();
    }
    
    // Check <Print>
    if (token.type == "keyword" && token.value == "Print"){
        Print();
    }
    
    // Check <Scan>
    if (token.type == "keyword" && token.value == "get"){
        Scan();
    }
    
    // Check <While>
    if (token.type == "keyword" && token.value == "while"){
        While();
    }
    
    else Error();
    
}

//R21: <Compound> → { <Statement List> }
void Compound(){
    Body();
}

//R22: <Assign> → <Identifier> = <Expressions> ;
void Assign(){
    Identifier();
    if (lexer(s).value == "="){
        Expression();
    }
    else
        Error();
}

//R23: <If> → if ( <Condition> ) <Statement> <If’> endif
void If(){
    Condition();
    if (lexer(s).value == ")"){
        Statement();
        IfP();
        if(lexer(s).value == "endif")
            PrintRule(23);
        else
            Error();
    }
}

//R24: <If’> → else <Statement> | <Empty>
void IfP(){
    if (token.type == "NotToken" || token.type == "COMMENT") {
        Empty();
        PrintRule(24);
    }
    else{
        if (lexer(s).value == "else"){
            Statement();
            PrintRule(24);
        }
        else
            Error();
    }
}

//R25: <Return> → return <Return’> ;
void Return() {
    if (token.value == "return") {
        ReturnP();
        if (lexer(s).value == ";") {
            PrintRule(25);
        }
        else
            Error();
    }
    else Error();
}

//R26: <Return’> → <Expression> | 𝜀
void ReturnP() {
    if (token.type == "Not Token" || token.type == "COMMENT") {
        Empty();
    }
    else {
        Expression();
    }
    PrintRule(26);
}

//R27: <Print> → put (<Expression>);
void Print() {
    if (token.value == "put") {
        if (lexer(s).value == "(") {
            Expression();
            if (lexer(s).value == ")") {
                if (lexer(s).value == ";") {
                    PrintRule(27);
                }
                else Error();
            }
            else Error();
        }
        else Error();
    }
    else Error();
}

//R28: <Scan> → get(<IDs>);
void Scan() {
    if (token.value == "get") {
        if (lexer(s).value == "(") {
            IDs();
            if (lexer(s).value == ")") {
                if (lexer(s).value == ";") {
                    PrintRule(28);
                }
                else Error();
            }
            else Error();
        }
        else Error();
    }
    else Error();
}

//R29: <While> → while (<Condition>) <Statement>
void While() {
    if (token.value == "while") {
        if (lexer(s).value == "(") {
            Condition();
            if (lexer(s).value == ")") {
                Statement();
                PrintRule(29);
            }
            else Error();
        }
        else Error();
    }
    else Error();
}

//R30: <Condition> → <Expression> <Relop> <Expression>
void Condition() {
    Expression();
    Relop();
    Expression();
    
    PrintRule(30);
}

//R31: <Relop> → == | ^= | > | < | => | =<
void Relop() {
    if (token.value == "==" || token.value == "^=" || token.value == ">" || token.value == "<" || token.value == "=>" || token.value == "=<") {
        PrintRule(31);
    }
    else Error();
}

//R32: <Expression> → <Term> <Expression’>
void Expression() {
    Term();
    ExpressionP();
    PrintRule(32);
}

//R33: <Expression’> → + <Term> <Expression’> | - <Term> <Expression’> | 𝜀
void ExpressionP() {
    if (token.type == "Not Token" || token.type == "COMMENT") {
        Empty();
        PrintRule(33);
    }
    else if (token.value == "+" || token.value == "-") {
        Term();
        ExpressionP();
        PrintRule(33);
    }
    else Error();
}

//R34: <Term> → <Factor> <Term’>
void Term() {
    Factor();
    TermP();
    PrintRule(34);
}

//R35: <Term’> → * <Factor> <Term’> | / <Factor> <Term’> | 𝜀
void TermP() {
    if (token.type == "Not Token" || token.type == "COMMENT") {
        Empty();
        PrintRule(35);
    }
    else if (token.value == "*" || token.value == "/") {
        Factor();
        TermP();
        PrintRule(35);
    }
    else Error();
}

//R36: <Factor> → - <Primary> | <Primary>
void Factor() {
    if (token.value == "-") {
        Primary();
        PrintRule(36);
    }
    else {
        Primary();
        PrintRule(36);
    }
}

//R37: <Primary> → <Identifier> | <Integer> | <Identifier> (<IDs>) | (<Expression>) | <Real> | true | false
void Primary() {
    if (token.type == "identifier") {
        Identifier();
        if (token.value == "(") {
            IDs();
        }
        PrintRule(37);
    }
    else if (token.value == "integer") {
        Integer();
        PrintRule(37);
    }
    else if (token.value == "(") {
        Expression();
        PrintRule(37);
    }
    else if (token.type == "real") {
        Real();
        PrintRule(37);
    }
    else if (token.value == "true" || token.value == "false")
        PrintRule(37);
    else Error();
}

//R38: <Empty> → 𝜀
void Empty(){}

void PrintRule(int ruleNum) {
    fstream coutfile(outputFile, ios_base::app);
    switch (ruleNum) {
        case 1:
            coutfile << "<Rat18S> → <Opt Function Definitions> %% <Opt Declaration List> <Statement List>" << endl;
            break;
        case 2:
            coutfile << "<Opt Function Definitions> → <Function Definitions> | <Empty>" << endl;
            break;
        case 3:
            coutfile << "<Function Definitions> → <Function> <Function Definitions’>" << endl;
            break;
        case 4:
            coutfile << "<Function Definitions’> → <Function Definitions> |  𝜀" << endl;
            break;
        case 5:
            coutfile << "<Function> → function <Identifier> [<Opt Parameter List>] <Opt Declaration List> <Body>" << endl;
            break;
        case 6:
            coutfile << "<Opt Parameter List> → <Parameter List> | <Empty>" << endl;
            break;
        case 7:
            coutfile << "<Parameter List> → <Parameter> <Parameter List’>" << endl;
            break;
        case 8:
            coutfile << "<Parameter List’> → , <Parameter List> |  𝜀" << endl;
            break;
        case 9:
            coutfile << "<Parameter> → <IDs> : <Qualifier>" << endl;
            break;
        case 10:
            coutfile << "<Qualifier> → int | boolean | real" << endl;
            break;
        case 11:
            coutfile << "<Body> → { <Statement List> }" << endl;
            break;
        case 12:
            coutfile << "<Opt Declaration List> → <Declaration List> | <Empty>" << endl;
            break;
        case 13:
            coutfile << "<Declaration List> → <Declaration> ; <Declaration List’>" << endl;
            break;
        case 14:
            coutfile << "<Declaration List’> → <Declaration List> | 𝜀" << endl;
            break;
        case 15:
            coutfile << "<Declaration> → <Qualifier> <IDs>" << endl;
            break;
        case 16:
            coutfile << "<IDs> → <Identifier> <IDs’>" << endl;
            break;
        case 17:
            coutfile << "<IDs’> → , <IDs> | 𝜀" << endl;
            break;
        case 18:
            coutfile << "<Statement List> → <Statement> <Statement List’>" << endl;
            break;
        case 19:
            coutfile << "<Statement List’> → <Statement List> | 𝜀" << endl;
            break;
        case 20:
            coutfile << "<Statement> → <Compound> | <Assign> | <If> | <Return> | <Print> | <Scan> | <While>" << endl;
            break;
        case 21:
            coutfile << "<Compound> → { <Statement List> }" << endl;
            break;
        case 22:
            coutfile << "<Assign> → <Identifier> = <Expressions> ;" << endl;
            break;
        case 23:
            coutfile << "<If> →  if ( <Condition> ) <Statement> <If’> endif" << endl;
            break;
        case 24:
            coutfile << "<If’> → else <Statement> | 𝜀" << endl;
            break;
        case 25:
            coutfile << "<Return> → return <Return’> ;" << endl;
            break;
        case 26:
            coutfile << "<Return’> → <Expression> | 𝜀" << endl;
            break;
        case 27:
            coutfile << "<Print> → put (<Expression>);" << endl;
            break;
        case 28:
            coutfile << "<Scan> → get(<IDs>);" << endl;
            break;
        case 29:
            coutfile << "<While> → while (<Condition>) <Statement>" << endl;
            break;
        case 30:
            coutfile << "<Condition> → <Expression> <Relop> <Expression>" << endl;
            break;
        case 31:
            coutfile << "<Relop> → == | ^= | > | < | => | =<" << endl;
            break;
        case 32:
            coutfile << "<Expression> → <Term> <Expression’>" << endl;
            break;
        case 33:
            coutfile << "<Expression’> → + <Term> <Expression’> | - <Term> <Expression’> | 𝜀" << endl;
            break;
        case 34:
            coutfile << "<Term> → <Factor> <Term’>" << endl;
            break;
        case 35:
            coutfile << "<Term’> → * <Factor> <Term’> | / <Factor> <Term’> | 𝜀" << endl;
            break;
        case 36:
            coutfile << "<Factor> → - <Primary> | <Primary>" << endl;
            break;
        case 37:
            coutfile << "<Primary> → <Identifier> | <Integer> | <Identifier> (<IDs>) | (<Expression>) | <Real> | true | false" << endl;
            break;
        default:
            coutfile << "Syntax Error" << endl;
            break;
    }
    coutfile.close();
}

//void PrintRule(int ruleNum) {
//    ofstream coutfile;
//    coutfile.open(outputFile, std::ios_base::app);
//
//    switch (ruleNum) {
//        case 1:
//            coutfile << "<Rat18S> → <Opt Function Definitions> %% <Opt Declaration List> <Statement List>" << endl;
//            coutfile.close();
//            break;
//        case 2:
//            coutfile << "<Opt Function Definitions> → <Function Definitions> | <Empty>" << endl;
//            coutfile.close();
//            break;
//        case 3:
//            coutfile << "<Function Definitions> → <Function> <Function Definitions’>" << endl;
//            coutfile.close();
//            break;
//        case 4:
//            coutfile << "<Function Definitions’> → <Function Definitions> |  𝜀" << endl;
//            coutfile.close();
//            break;
//        case 5:
//            coutfile << "<Function> → function <Identifier> [<Opt Parameter List>] <Opt Declaration List> <Body>" << endl;
//            coutfile.close();
//            break;
//        case 6:
//            coutfile << "<Opt Parameter List> → <Parameter List> | <Empty>" << endl;
//            coutfile.close();
//            break;
//        case 7:
//            coutfile << "<Parameter List> → <Parameter> <Parameter List’>" << endl;
//            coutfile.close();
//            break;
//        case 8:
//            coutfile << "<Parameter List’> → , <Parameter List> |  𝜀" << endl;
//            coutfile.close();
//            break;
//        case 9:
//            coutfile << "<Parameter> → <IDs> : <Qualifier>" << endl;
//            coutfile.close();
//            break;
//        case 10:
//            coutfile << "<Qualifier> → int | boolean | real" << endl;
//            coutfile.close();
//            break;
//        case 11:
//            coutfile << "<Body> → { <Statement List> }" << endl;
//            coutfile.close();
//            break;
//        case 12:
//            coutfile << "<Opt Declaration List> → <Declaration List> | <Empty>" << endl;
//            coutfile.close();
//            break;
//        case 13:
//            coutfile << "<Declaration List> → <Declaration> ; <Declaration List’>" << endl;
//            coutfile.close();
//            break;
//        case 14:
//            coutfile << "<Declaration List’> → <Declaration List> | 𝜀" << endl;
//            coutfile.close();
//            break;
//        case 15:
//            coutfile << "<Declaration> → <Qualifier> <IDs>" << endl;
//            coutfile.close();
//            break;
//        case 16:
//            coutfile << "<IDs> → <Identifier> <IDs’>" << endl;
//            coutfile.close();
//            break;
//        case 17:
//            coutfile << "<IDs’> → , <IDs> | 𝜀" << endl;
//            coutfile.close();
//            break;
//        case 18:
//            coutfile << "<Statement List> → <Statement> <Statement List’>" << endl;
//            coutfile.close();
//            break;
//        case 19:
//            coutfile << "<Statement List’> → <Statement List> | 𝜀" << endl;
//            coutfile.close();
//            break;
//        case 20:
//            coutfile << "<Statement> → <Compound> | <Assign> | <If> | <Return> | <Print> | <Scan> | <While>" << endl;
//            coutfile.close();
//            break;
//        case 21:
//            coutfile << "<Compound> → { <Statement List> }" << endl;
//            coutfile.close();
//            break;
//        case 22:
//            coutfile << "<Assign> → <Identifier> = <Expressions> ;" << endl;
//            coutfile.close();
//            break;
//        case 23:
//            coutfile << "<If> →  if ( <Condition> ) <Statement> <If’> endif" << endl;
//            coutfile.close();
//            break;
//        case 24:
//            coutfile << "<If’> → else <Statement> | 𝜀" << endl;
//            coutfile.close();
//            break;
//        case 25:
//            coutfile << "<Return> → return <Return’> ;" << endl;
//            coutfile.close();
//            break;
//        case 26:
//            coutfile << "<Return’> → <Expression> | 𝜀" << endl;
//            coutfile.close();
//            break;
//        case 27:
//            coutfile << "<Print> → put (<Expression>);" << endl;
//            coutfile.close();
//            break;
//        case 28:
//            coutfile << "<Scan> → get(<IDs>);" << endl;
//            coutfile.close();
//            break;
//        case 29:
//            coutfile << "<While> → while (<Condition>) <Statement>" << endl;
//            coutfile.close();
//            break;
//        case 30:
//            coutfile << "<Condition> → <Expression> <Relop> <Expression>" << endl;
//            coutfile.close();
//            break;
//        case 31:
//            coutfile << "<Relop> → == | ^= | > | < | => | =<" << endl;
//            coutfile.close();
//            break;
//        case 32:
//            coutfile << "<Expression> → <Term> <Expression’>" << endl;
//            coutfile.close();
//            break;
//        case 33:
//            coutfile << "<Expression’> → + <Term> <Expression’> | - <Term> <Expression’> | 𝜀" << endl;
//            coutfile.close();
//            break;
//        case 34:
//            coutfile << "<Term> → <Factor> <Term’>" << endl;
//            coutfile.close();
//            break;
//        case 35:
//            coutfile << "<Term’> → * <Factor> <Term’> | / <Factor> <Term’> | 𝜀" << endl;
//            coutfile.close();
//            break;
//        case 36:
//            coutfile << "<Factor> → - <Primary> | <Primary>" << endl;
//            coutfile.close();
//            break;
//        case 37:
//            coutfile << "<Primary> → <Identifier> | <Integer> | <Identifier> (<IDs>) | (<Expression>) | <Real> | true | false" << endl;
//            coutfile.close();
//            break;
//        default:
//            coutfile << "Syntax Error" << endl;
//            coutfile.close();
//            break;
//    }
//
//}

void Identifier(){
    if(token.type == "identifier"){
    }
    else
        Error();
}

void Real(){
    if(token.type == "real"){
    }
    else
        Error();
}

void Integer(){
    if(token.type == "integer"){
    }
    else
        Error();
}


