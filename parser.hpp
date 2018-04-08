//
//  parser.hpp
//  parser
//
//
#ifndef parser_hpp
#define parser_hpp
#include "lexer.cpp"
#include <stdio.h>

//#include "stdafx.h"
#include <iostream>
#include "lexer.h"

void Parser(Token token);
void Error();

//R1: <Rat18S> → <Opt Function Definitions> %% <Opt Declaration List> <Statement List>
void Rat18S(Token token);

//R2: <Opt Function Definitions> → <Function Definitions> | <Empty>
void OptFunctionDefinitions();

//R3: <Function Definitions> → <Function> <Function Definitions’>
void FunctionDefinitions();

//R4: <Function Definitions’> → <Function Definitions> |  𝜀
void FunctionDefinitionsP();

//R5: <Function> → function <Identifier> [<Opt Parameter List>] <Opt Declaration List> <Body>
void Function();
//R6: <Opt Parameter List> → <Parameter List> | <Empty>
void OptParameterList();

//R7: <Parameter List> → <Parameter> <Parameter List’>
void ParameterList();

//R8: <Parameter List’> → , <Parameter List> |  𝜀
void ParameterListP();

//R9: <Parameter> → <IDs> : <Qualifier>
void Parameter();

//R10: <Qualifier> → int | boolean | real
void Qualifier();

//R11:    <Body> → { <Statement List> }
void Body();

//R12: <Opt Declaration List> → <Declaration List> | <Empty>
void OptDeclarationList();

//R13: <Declaration List> → <Declaration> ; <Declaration List’>
void DeclarationList();

//R14: <Declaration List’> → <Declaration List> | <Empty>
void DeclarationListP();

//R15: <Declaration> → <Qualifier> <IDs>
void Declaration();

//R16: <IDs> → <Identifier> <IDs’>
void IDs();

//R17: <IDs’> → , <IDs> | <Empty>
void IDsP();

//R18: <Statement List> → <Statement> <Statement List’>
void StatementList();

//R19: <Statement List’> → <Statement List> | <Empty>
void StatementListP();
//R20: <Statement> → <Compound> | <Assign> | <If> | <Return> | <Print> | <Scan> | <While>
void Statement();

//R21: <Compound> → { <Statement List> }
void Compound();

//R22: <Assign> → <Identifier> = <Expressions> ;
void Assign();

//R23: <If> → if ( <Condition> ) <Statement> <If’> endif
void If();

//R24: <If’> → else <Statement> | <Empty>
void IfP();

//R25: <Return> → return <Return’> ;
void Return();

//R26: <Return’> → <Expression> | 𝜀
void ReturnP();

//R27: <Print> → put (<Expression>);
void Print();
//R28: <Scan> → get(<IDs>);
void Scan();

//R29: <While> → while (<Condition>) <Statement>
void While();

//R30: <Condition> → <Expression> <Relop> <Expression>
void Condition();

//R31: <Relop> → == | ^= | > | < | => | =<
void Relop();

//R32: <Expression> → <Term> <Expression’>
void Expression();

//R33: <Expression’> → + <Term> <Expression’> | - <Term> <Expression’> | 𝜀
void ExpressionP();
//R34: <Term> → <Factor> <Term’>
void Term();

//R35: <Term’> → * <Factor> <Term’> | / <Factor> <Term’> | 𝜀
void TermP();

//R36: <Factor> → - <Primary> | <Primary>
void Factor();

//R37: <Primary> → <Identifier> | <Integer> | <Identifier> (<IDs>) | (<Expression>) | <Real> | true | false
void Primary();
//R38: <Empty> → 𝜀
void Empty();

void PrintRule(int ruleNum);




#endif /* parser_hpp */
