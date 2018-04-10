#pragma once
#pragma once
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "lexer.h"
#include "globals.h"

void Parser(Token token, unsigned tokenIndex);

void Error();

//R1: <Rat18S> → <Opt Function Definitions> %% <Opt Declaration List> <Statement List>
void Rat18S(Token token, unsigned tokenIndex);

//R2: <Opt Function Definitions> → <Function Definitions> | <Empty>
void OptFunctionDefinitions();

//R3: <Function Definitions> → <Function> <Function Definitions’>
void FunctionDefinitions();

//R4: <Function Definitions’> → <Function Definitions> |  𝜀
void FunctionDefinitionsP(Token t);

//R5: <Function> → function <Identifier> [<Opt Parameter List>] <Opt Declaration List> <Body>
void Function();
//R6: <Opt Parameter List> → <Parameter List> | <Empty>
void OptParameterList(Token t);

//R7: <Parameter List> → <Parameter> <Parameter List’>
void ParameterList(Token t);

//R8: <Parameter List’> → , <Parameter List> |  𝜀
void ParameterListP(Token t);

//R9: <Parameter> → <IDs> : <Qualifier>
void Parameter(Token t);

//R10: <Qualifier> → int | boolean | real
void Qualifier(Token t);

//R11:    <Body> → { <Statement List> }
void Body(Token t);

//R12: <Opt Declaration List> → <Declaration List> | <Empty>
void OptDeclarationList(Token t);

//R13: <Declaration List> → <Declaration> ; <Declaration List’>
void DeclarationList();

//R14: <Declaration List’> → <Declaration List> | <Empty>
void DeclarationListP(Token t);

//R15: <Declaration> → <Qualifier> <IDs>
void Declaration();

//R16: <IDs> → <Identifier> <IDs’>
void IDs(Token t);

//R17: <IDs’> → , <IDs> | <Empty>
void IDsP(Token t);

//R18: <Statement List> → <Statement> <Statement List’>
void StatementList(Token t);

//R19: <Statement List’> → <Statement List> | <Empty>
void StatementListP(Token t);
//R20: <Statement> → <Compound> | <Assign> | <If> | <Return> | <Print> | <Scan> | <While>
void Statement(Token t);

//R21: <Compound> → { <Statement List> }
void Compound();

//R22: <Assign> → <Identifier> = <Expressions> ;
void Assign();

//R23: <If> → if ( <Condition> ) <Statement> <If’> endif
void If();

//R24: <If’> → else <Statement> | <Empty>
void IfP(Token t);

//R25: <Return> → return <Return’> ;
void Return();

//R26: <Return’> → <Expression> | 𝜀
void ReturnP(Token t);

//R27: <Print> → put (<Expression>);
void Print();
//R28: <Scan> → get(<IDs>);
void Scan();

//R29: <While> → while (<Condition>) <Statement>
void While();

//R30: <Condition> → <Expression> <Relop> <Expression>
void Condition(Token t);

//R31: <Relop> → == | ^= | > | < | => | =<
void Relop(Token t);

//R32: <Expression> → <Term> <Expression’>
void Expression(Token t);

//R33: <Expression’> → + <Term> <Expression’> | - <Term> <Expression’> | 𝜀
void ExpressionP(Token t);
//R34: <Term> → <Factor> <Term’>
void Term(Token t);

//R35: <Term’> → * <Factor> <Term’> | / <Factor> <Term’> | 𝜀
void TermP(Token t);

//R36: <Factor> → - <Primary> | <Primary>
void Factor(Token t);

//R37: <Primary> → <Identifier> | <Integer> | <Identifier> (<IDs>) | (<Expression>) | <Real> | true | false
void Primary(Token t);
//R38: <Empty> → 𝜀
void Empty();

void PrintRule(int ruleNum);

void Identifier(Token temp);

void Integer();

void Real();


//#endif /* parser_h */
