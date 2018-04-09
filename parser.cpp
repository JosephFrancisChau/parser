#include "parser.h"
#include "lexer.h"
#include <fstream>
#include "globals.h"
using namespace std;

vector<string> allWords;
Token token;
int ruleNum;
string s;

//fstream coutfile(outputFile, std::ios_base::app);
//ofstream coutfile;

void Parser(Token word, unsigned index) {
	token = word;
	Rat18S(token, index);
}

void Error() {
	cout << "Syntax Error!" << endl;
	return;
}

//R1: <Rat18S> → <Opt Function Definitions> %% <Opt Declaration List> <Statement List>
void Rat18S(Token token, unsigned index) {
	PrintRule(1);
	OptFunctionDefinitions();
	Token temp = lexer(allWords.at(++index));
	if (temp.value == "%%") {
		OptDeclarationList();
		StatementList();
	}
	else Error();
	if (token.value != "$") Error();
}

//R2: <Opt Function Definitions> → <Function Definitions> | <Empty>
void OptFunctionDefinitions() {
	PrintRule(2);
	if (token.type == "NotToken" || token.type == "COMMENT") {
		Empty();
	}
	else {
		FunctionDefinitions();
	}
}

//R3: <Function Definitions> → <Function> <Function Definitions’>
void FunctionDefinitions() {
	PrintRule(3);
	Function();
	FunctionDefinitionsP();
}

//R4: <Function Definitions’> → <Function Definitions> |  𝜀
void FunctionDefinitionsP() {
	PrintRule(4);
	if (token.type == "NotToken" || token.type == "COMMENT") {
		Empty();
	}
	else {
		FunctionDefinitions();
	}
}

//R5: <Function> → function <Identifier> [<Opt Parameter List>] <Opt Declaration List> <Body>
void Function() {
	PrintRule(5);
	if (token.value == "function") {
		Identifier();
		Token temp1 = lexer(allWords.at(++index));
		if (temp1.value == "[") {
			OptParameterList();
			Token temp2 = lexer(allWords.at(++index));
			if (temp2.value == "]") {
				OptDeclarationList();
				Body();
			}
			else Error();
		}
		else Error();
	}
	else Error();
}

//R6: <Opt Parameter List> → <Parameter List> | <Empty>
void OptParameterList() {
	PrintRule(6);
	if (token.type == "NotToken" || token.type == "COMMENT") {
		Empty();
	}
	else {
		ParameterList();
	}
}

//R7: <Parameter List> → <Parameter> <Parameter List’>
void ParameterList() {
	PrintRule(7);
	Parameter();
	ParameterListP();
}

//R8: <Parameter List’> → , <Parameter List> |  𝜀
void ParameterListP() {
	PrintRule(8);
	if (token.type == "NotToken" || token.type == "COMMENT") {
		Empty();
	}
	else if (token.value == ",") {
		ParameterList();
	}
	else Error();
}

//R9: <Parameter> → <IDs> : <Qualifier>
void Parameter() {
	PrintRule(9);
	IDs();
	Token temp=lexer(allWords.at(++index));
	if (temp.value == ":") {
		Qualifier();
	}
	else Error();
}

//R10: <Qualifier> → int | boolean | real
void Qualifier() {
	PrintRule(10);
	if (token.value == "int" || token.value == "boolean" || token.value == "real") {	}
	else Error();
}

//R11: <Body> → { <Statement List> }
void Body() {
	PrintRule(11);
	if (token.value == "{") {
		StatementList();
		Token temp = lexer(allWords.at(++index));
		if (temp.value == "}") {}
		else Error();
	}
	else Error();
}

//R12: <Opt Declaration List> → <Declaration List> | <Empty>
void OptDeclarationList() {
	PrintRule(12);
	if (token.type == "NotToken" || token.type == "COMMENT") {
		Empty();
	}
	else {
		DeclarationList();
	}
}

//R13: <Declaration List> → <Declaration> ; <Declaration List’>
void DeclarationList() {
	PrintRule(13);
	Declaration();
	Token temp = lexer(allWords.at(++index));
	if (temp.value == ";") {
		DeclarationListP();
	}
	else
		Error();
}

//R14: <Declaration List’> → <Declaration List> | <Empty>
void DeclarationListP(){
	PrintRule(14);
	if (token.type == "NotToken" || token.type == "COMMENT")	{
		Empty();
	}
	else	{
		DeclarationList();
	}
}

//R15: <Declaration> → <Qualifier> <IDs>
void Declaration() {
	PrintRule(15);
	Qualifier();
	IDs();
}

//R16: <IDs> → <Identifier> <IDs’>
void IDs() {
	PrintRule(16);
	Identifier();
	IDsP();	
}

//R17: <IDs’> → , <IDs> | <Empty>
void IDsP() {
	PrintRule(17);
	if (token.type == "NotToken" || token.type == "COMMENT") {
		Empty();
	}
	else if (token.value == ",") {
		IDs();
	}
	else	Error();
}

//R18: <Statement List> → <Statement> <Statement List’>
void StatementList() {
	PrintRule(18);
	Statement();
	StatementListP();
}

//R19: <Statement List’> → <Statement List> | <Empty>
void StatementListP() {
	PrintRule(19);
	if (token.type == "NotToken" || token.type == "COMMENT") {
		Empty();
	}
	else {
		StatementList();
	}	
}

//R20: <Statement> → <Compound> | <Assign> | <If> | <Return> | <Print> | <Scan> | <While>
void Statement() {
	PrintRule(20);
	Token temp = lexer(allWords.at(++index));

	// Check if <Compound>
	if (token.value == "{") {
		Compound();
	}

	// Check if <Assign>
	else if (temp.type == "identifier") {
		Assign();
	}

	// Check <If>
	else if (token.type == "keyword" && token.value == "if") {
		If();
	}

	// Check <Return>
	else if (token.type == "keyword" && token.value == "return") {
		Return();
	}

	// Check <Print>
	else if (token.type == "keyword" && token.value =="put") {
		Print();
	}

	// Check <Scan>
	else if (token.type == "keyword" && token.value == "get") {
		Scan();
	}

	// Check <While>
	else if (token.type == "keyword" && token.value == "while") {
		While();
	}

	else Error();
}

//R21: <Compound> → { <Statement List> }
void Compound() {
	PrintRule(21);
	if (token.value == "{") {
		StatementList();
		Token temp = lexer(allWords.at(++index));
		if (temp.value == "}") {}
		else Error();
	}
	else Error();
}

//R22: <Assign> → <Identifier> = <Expressions> ;
void Assign() {
	PrintRule(22);
	Identifier();
	Token temp = lexer(allWords.at(++index));
	if (temp.value == "=") {
		Expression();
	}
	else
		Error();
}

//R23: <If> → if ( <Condition> ) <Statement> <If’> endif
void If() {
	PrintRule(23);
	if (token.value == "if") {
		Token temp1 = lexer(allWords.at(++index));
		if (temp1.value == "(") {
			Condition();
			Token temp2 = lexer(allWords.at(++index));
			if (temp2.value == ")") {
				Statement();
				IfP();
				Token temp3 = lexer(allWords.at(++index));
				if (temp3.value == "endif") {}
				else
					Error();
			}
		}
	}
	else Error();
}

//R24: <If’> → else <Statement> | <Empty>
void IfP() {
	PrintRule(24);
	if (token.type == "NotToken" || token.type == "COMMENT") {
		Empty();
	}
	else {
		if (token.value == "else") {
			Statement();
		}
		else
			Error();
	}
}

//R25: <Return> → return <Return’> ;
void Return() {
	PrintRule(25);
	if (token.value == "return") {
		ReturnP();
		Token temp = lexer(allWords.at(++index));
		if (temp.value == ";") {}
		else
			Error();
	}
	else Error();
}

//R26: <Return’> → <Expression> | 𝜀
void ReturnP() {
	PrintRule(26);
	if (token.type == "Not Token" || token.type == "COMMENT") {
		Empty();
	}
	else {
		Expression();
	}
	
}

//R27: <Print> → put (<Expression>);
void Print() {
	PrintRule(27);
	if (token.value == "put") {
		Token temp1 = lexer(allWords.at(++index));
		if (temp1.value == "(") {
			Expression();
			Token temp2 = lexer(allWords.at(++index));
			if (temp2.value == ")") {
				Token temp3 = lexer(allWords.at(++index));
				if (temp3.value == ";") {}
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
	PrintRule(28);
	if (token.value == "get") {
		Token temp1 = lexer(allWords.at(++index));
		if (temp1.value == "(") {
			IDs();
			Token temp2 = lexer(allWords.at(++index));
			if (temp2.value == ")") {
				Token temp3 = lexer(allWords.at(++index));
				if (temp3.value == ";") {}
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
	PrintRule(29);
	if (token.value == "while") {
		Token temp1 = lexer(allWords.at(++index));
		if (temp1.value == "(") {
			Condition();
			Token temp2 = lexer(allWords.at(++index));
			if (temp2.value == ")") {
				Statement();
			}
			else Error();
		}
		else Error();
	}
	else Error();
}

//R30: <Condition> → <Expression> <Relop> <Expression>
void Condition() {
	PrintRule(30);
	Expression();
	Relop();
	Expression();
}

//R31: <Relop> → == | ^= | > | < | => | =<
void Relop() {
	PrintRule(31);
	if (token.value == "==" || token.value == "^=" || token.value == ">" ||
		token.value == "<" || token.value == "=>" || token.value == "=<") {}
	else Error();
}

//R32: <Expression> → <Term> <Expression’>
void Expression() {
	PrintRule(32);
	Term();
	ExpressionP();
}

//R33: <Expression’> → + <Term> <Expression’> | - <Term> <Expression’> | 𝜀
void ExpressionP() {
	PrintRule(33);
	if (token.type == "Not Token" || token.type == "COMMENT") {
		Empty();
	}
	else if (token.value == "+" || token.value == "-") {
		Term();
		ExpressionP();
	}
	else Error();
}

//R34: <Term> → <Factor> <Term’>
void Term() {
	PrintRule(34);
	Factor();
	TermP();
}

//R35: <Term’> → * <Factor> <Term’> | / <Factor> <Term’> | 𝜀
void TermP() {
	PrintRule(35);
	if (token.type == "Not Token" || token.type == "COMMENT") {
		Empty();
	}
	else if (token.value == "*" || token.value == "/") {
		Factor();
		TermP();
	}
	else Error();
}

//R36: <Factor> → - <Primary> | <Primary>
void Factor() {
	PrintRule(36);
	if (token.value == "-") {
		Primary();
	}
	else {
		Primary();
	}
}

//R37: <Primary> → <Identifier> | <Integer> | <Identifier> (<IDs>) | (<Expression>) | <Real> | true | false
void Primary() {
	PrintRule(37);
	Token temp1 = lexer(allWords.at(++index));
	if (token.type == "identifier" && temp1.value == "(") {
		IDs();
		Token temp2 = lexer(allWords.at(++index));
		if (temp2.value == ")") {}
		else Error();
	}
	else if (token.type == "identifier") {
		Identifier();
	}
	else if (token.type == "integer") {
		Integer();
	}
	else if (token.value == "(") {
		Expression();
		Token temp = lexer(allWords.at(++index));
		if (temp.value == ")") {}
		else Error();
	}
	else if (token.type == "real") {
		Real();
	}
	else if (token.value == "true" || token.value == "false") {}
	else Error();
}

//R38: <Empty> → 𝜀
void Empty() {
	PrintRule(38);
}

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
		coutfile << "<Function Definitions’> → <Function Definitions> |  e" << endl;
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
		coutfile << "<Parameter List’> → , <Parameter List> |  e" << endl;
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
		coutfile << "<Declaration List’> → <Declaration List> | e" << endl;
		break;
	case 15:
		coutfile << "<Declaration> → <Qualifier> <IDs>" << endl;
		break;
	case 16:
		coutfile << "<IDs> → <Identifier> <IDs’>" << endl;
		break;
	case 17:
		coutfile << "<IDs’> → , <IDs> | e" << endl;
		break;
	case 18:
		coutfile << "<Statement List> → <Statement> <Statement List’>" << endl;
		break;
	case 19:
		coutfile << "<Statement List’> → <Statement List> | e" << endl;
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
		coutfile << "<If’> → else <Statement> | e" << endl;
		break;
	case 25:
		coutfile << "<Return> → return <Return’> ;" << endl;
		break;
	case 26:
		coutfile << "<Return’> → <Expression> | e" << endl;
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
		coutfile << "<Expression’> → + <Term> <Expression’> | - <Term> <Expression’> | e" << endl;
		break;
	case 34:
		coutfile << "<Term> → <Factor> <Term’>" << endl;
		break;
	case 35:
		coutfile << "<Term’> → * <Factor> <Term’> | / <Factor> <Term’> | e" << endl;
		break;
	case 36:
		coutfile << "<Factor> → - <Primary> | <Primary>" << endl;
		break;
	case 37:
		coutfile << "<Primary> → <Identifier> | <Integer> | <Identifier> (<IDs>) | (<Expression>) | <Real> | true | false" << endl;
		break;
	case 38:
		coutfile << "<Empty> → e" << endl;
		break;
	default:
		coutfile << "Syntax Error" << endl;
		break;
	}
	coutfile.close();
}

void Identifier() {
	if (token.type == "identifier") {
	}
	else
		Error();
}

void Real() {
	if (token.type == "real") {
	}
	else
		Error();
}

void Integer() {
	if (token.type == "integer") {
	}
	else
		Error();
}
