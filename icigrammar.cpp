// This file was generated by qlalr - DO NOT EDIT!
#include "icigrammar_p.h"

const char *const ICIGrammar::spell [] = {
  "end of file", 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 
#ifndef QLALR_NO_ICIGRAMMAR_DEBUG_INFO
"Source", "StatementList", "Statement", "StatementBlock", "Assignement", "IfStatement", "FunctionCall", "LogicalExpression", 
  "Expression", "StoredIdent", "ListParameters", "AssignementOperator", "Identifier", "List", "IdentifierPart", "$accept"
#endif // QLALR_NO_ICIGRAMMAR_DEBUG_INFO
};

const short ICIGrammar::lhs [] = {
  22, 23, 23, 25, 25, 25, 24, 24, 24, 27, 
  27, 29, 29, 29, 29, 29, 30, 28, 28, 33, 
  33, 33, 26, 30, 35, 35, 32, 32, 30, 34, 
  36, 36, 31, 30, 30, 30, 30, 30, 37};

const short ICIGrammar::rhs [] = {
  1, 2, 1, 1, 3, 2, 1, 1, 1, 4, 
  2, 3, 3, 3, 2, 1, 1, 3, 4, 1, 
  1, 1, 3, 1, 2, 3, 1, 3, 1, 1, 
  3, 1, 1, 1, 1, 1, 1, 1, 2};


#ifndef QLALR_NO_ICIGRAMMAR_DEBUG_INFO
const int ICIGrammar::rule_info [] = {
    22, 23
  , 23, 23, 24
  , 23, 24
  , 25, 24
  , 25, 13, 23, 14
  , 25, 13, 14
  , 24, 26
  , 24, 27
  , 24, 28
  , 27, 29, 25, 21, 25
  , 27, 29, 25
  , 29, 11, 30, 12
  , 29, 30, 18, 29
  , 29, 30, 19, 29
  , 29, 20, 30
  , 29, 30
  , 30, 28
  , 28, 31, 11, 12
  , 28, 31, 11, 32, 12
  , 33, 8
  , 33, 9
  , 33, 10
  , 26, 34, 33, 30
  , 30, 35
  , 35, 15, 16
  , 35, 15, 32, 16
  , 32, 30
  , 32, 32, 17, 30
  , 30, 34
  , 34, 36
  , 36, 36, 7, 31
  , 36, 31
  , 31, 3
  , 30, 2
  , 30, 1
  , 30, 4
  , 30, 5
  , 30, 6
  , 37, 22, 0};

const int ICIGrammar::rule_index [] = {
  0, 2, 5, 7, 9, 13, 16, 18, 20, 22, 
  27, 30, 34, 38, 42, 45, 47, 49, 53, 58, 
  60, 62, 64, 68, 70, 73, 77, 79, 83, 85, 
  87, 91, 93, 95, 97, 99, 101, 103, 105};
#endif // QLALR_NO_ICIGRAMMAR_DEBUG_INFO

const short ICIGrammar::action_default [] = {
  0, 7, 34, 16, 38, 17, 33, 29, 30, 8, 
  0, 0, 24, 0, 0, 36, 35, 0, 3, 1, 
  32, 37, 0, 0, 17, 29, 13, 32, 0, 27, 
  0, 18, 0, 19, 28, 14, 0, 20, 22, 21, 
  23, 0, 31, 0, 12, 0, 25, 26, 0, 4, 
  11, 6, 0, 5, 2, 0, 10, 15, 39};

const short ICIGrammar::goto_default [] = {
  17, 19, 18, 50, 1, 9, 24, 13, 3, 27, 
  45, 36, 25, 12, 8, 0};

const short ICIGrammar::action_index [] = {
  82, -22, -22, -12, -22, 167, -22, 5, -6, -22, 
  40, 61, -22, 103, 40, -22, -22, 19, -22, 82, 
  -9, -22, 82, 82, -22, -22, -22, -9, 20, -22, 
  -7, -22, 40, -22, -22, -22, 40, -22, -22, -22, 
  -22, -3, -22, -8, -22, -5, -22, -22, 124, -22, 
  -18, -22, 145, -22, -22, 103, -22, -22, -22, 

  11, -16, -16, -16, -16, -16, -16, -16, -16, -16, 
  -1, -5, -16, 12, -2, -16, -16, -16, -16, 25, 
  -16, -16, -7, -3, -16, -16, -16, -16, 0, -16, 
  -16, -16, 1, -16, -16, -16, -6, -16, -16, -16, 
  -16, -8, -16, -16, -16, -16, -16, -16, 10, -16, 
  -16, -16, 25, -16, -16, 23, -16, -16, -16};

const short ICIGrammar::action_info [] = {
  6, 41, 28, 55, 44, 33, 22, 23, 0, 0, 
  32, 47, 32, 37, 39, 38, 0, 0, 0, 58, 
  0, 16, 2, 6, 15, 21, 4, 0, 0, 0, 
  0, 0, 31, 0, 0, 11, 0, 0, 0, 0, 
  0, 16, 2, 6, 15, 21, 4, 0, 0, 0, 
  0, 0, 0, 0, 0, 11, 0, 0, 0, 0, 
  0, 0, 16, 2, 6, 15, 21, 4, 0, 0, 
  0, 0, 0, 0, 0, 0, 11, 46, 0, 0, 
  0, 0, 0, 16, 2, 6, 15, 21, 4, 0, 
  0, 0, 0, 10, 0, 0, 0, 11, 0, 0, 
  0, 0, 14, 0, 16, 2, 6, 15, 21, 4, 
  0, 0, 0, 0, 10, 0, 48, 0, 11, 0, 
  0, 0, 0, 14, 0, 16, 2, 6, 15, 21, 
  4, 0, 0, 0, 0, 10, 0, 0, 51, 11, 
  0, 0, 0, 0, 14, 0, 16, 2, 6, 15, 
  21, 4, 0, 0, 0, 0, 10, 0, 0, 53, 
  11, 0, 0, 0, 0, 14, 0, -9, -9, -9, 
  -9, -9, -9, -9, 0, 0, 0, 0, -9, 0, 
  0, -9, -9, 0, 0, 0, 0, -9, -9, 

  26, 42, 40, 29, 35, 0, 57, 43, 29, 34, 
  30, 52, 0, 0, 49, 0, 5, 5, 5, 20, 
  20, 20, 7, 7, 7, 49, 56, 54, 0, 5, 
  0, 5, 20, 0, 20, 7, 0, 7, 0, 0, 
  0};

const short ICIGrammar::action_check [] = {
  3, 7, 11, 21, 12, 12, 18, 19, -1, -1, 
  17, 16, 17, 8, 9, 10, -1, -1, -1, 0, 
  -1, 1, 2, 3, 4, 5, 6, -1, -1, -1, 
  -1, -1, 12, -1, -1, 15, -1, -1, -1, -1, 
  -1, 1, 2, 3, 4, 5, 6, -1, -1, -1, 
  -1, -1, -1, -1, -1, 15, -1, -1, -1, -1, 
  -1, -1, 1, 2, 3, 4, 5, 6, -1, -1, 
  -1, -1, -1, -1, -1, -1, 15, 16, -1, -1, 
  -1, -1, -1, 1, 2, 3, 4, 5, 6, -1, 
  -1, -1, -1, 11, -1, -1, -1, 15, -1, -1, 
  -1, -1, 20, -1, 1, 2, 3, 4, 5, 6, 
  -1, -1, -1, -1, 11, -1, 13, -1, 15, -1, 
  -1, -1, -1, 20, -1, 1, 2, 3, 4, 5, 
  6, -1, -1, -1, -1, 11, -1, -1, 14, 15, 
  -1, -1, -1, -1, 20, -1, 1, 2, 3, 4, 
  5, 6, -1, -1, -1, -1, 11, -1, -1, 14, 
  15, -1, -1, -1, -1, 20, -1, 0, 1, 2, 
  3, 4, 5, 6, -1, -1, -1, -1, 11, -1, 
  -1, 14, 15, -1, -1, -1, -1, 20, 21, 

  7, 9, 8, 8, 7, -1, 8, 8, 8, 8, 
  10, 1, -1, -1, 2, -1, 6, 6, 6, 9, 
  9, 9, 12, 12, 12, 2, 3, 2, -1, 6, 
  -1, 6, 9, -1, 9, 12, -1, 12, -1, -1, 
  -1};

