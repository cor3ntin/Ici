// This file was generated by qlalr - DO NOT EDIT!
#include "icigrammar_p.h"

const char *const ICIGrammar::spell [] = {
  "end of file", 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 
#ifndef QLALR_NO_ICIGRAMMAR_DEBUG_INFO
"Source", "StatementList", "Statement", 
  "StatementBlock", "Assignement", "IfStatement", "IncludeStatement", "UnsetStatement", "FunctionCall", "Identifier", "LogicalExpression", "Expression", "StoredIdent", 
  "ListParameters", "AssignementOperator", "List", "Map", "MapParameters", "IdentifierPart", "$accept"
#endif // QLALR_NO_ICIGRAMMAR_DEBUG_INFO
};

const short ICIGrammar::lhs [] = {
  27, 28, 28, 30, 30, 30, 29, 29, 29, 29, 
  29, 33, 34, 32, 32, 38, 37, 37, 37, 37, 
  38, 35, 35, 41, 41, 41, 41, 31, 38, 42, 
  42, 42, 40, 40, 38, 43, 43, 43, 44, 44, 
  38, 36, 45, 45, 45, 45, 45, 39, 38, 38, 
  38, 38, 38, 46};

const short ICIGrammar::rhs [] = {
  1, 2, 1, 3, 2, 1, 1, 1, 1, 1, 
  1, 2, 2, 5, 3, 3, 3, 3, 2, 1, 
  1, 3, 4, 1, 1, 1, 1, 3, 1, 2, 
  3, 4, 1, 3, 1, 2, 3, 4, 3, 5, 
  1, 1, 3, 3, 3, 1, 2, 1, 1, 1, 
  1, 1, 1, 2};


#ifndef QLALR_NO_ICIGRAMMAR_DEBUG_INFO
const int ICIGrammar::rule_info [] = {
    27, 28
  , 28, 28, 29
  , 28, 29
  , 30, 14, 28, 15
  , 30, 14, 15
  , 30, 29
  , 29, 31
  , 29, 32
  , 29, 33
  , 29, 34
  , 29, 35
  , 33, 25, 1
  , 34, 26, 36
  , 32, 23, 37, 30, 24, 30
  , 32, 23, 37, 30
  , 38, 12, 38, 13
  , 37, 38, 20, 37
  , 37, 38, 21, 37
  , 37, 22, 38
  , 37, 38
  , 38, 35
  , 35, 39, 12, 13
  , 35, 39, 12, 40, 13
  , 41, 8
  , 41, 9
  , 41, 10
  , 41, 11
  , 31, 36, 41, 38
  , 38, 42
  , 42, 16, 17
  , 42, 16, 40, 17
  , 42, 16, 40, 18, 17
  , 40, 38
  , 40, 40, 18, 38
  , 38, 43
  , 43, 14, 15
  , 43, 14, 44, 15
  , 43, 14, 44, 18, 15
  , 44, 36, 19, 38
  , 44, 44, 18, 36, 19, 38
  , 38, 36
  , 36, 45
  , 45, 45, 7, 39
  , 45, 45, 7, 1
  , 45, 45, 7, 2
  , 45, 39
  , 45, 7, 1
  , 39, 3
  , 38, 2
  , 38, 1
  , 38, 4
  , 38, 5
  , 38, 6
  , 46, 27, 0};

const int ICIGrammar::rule_index [] = {
  0, 2, 5, 7, 11, 14, 16, 18, 20, 22, 
  24, 26, 29, 32, 38, 42, 46, 50, 54, 57, 
  59, 61, 65, 70, 72, 74, 76, 78, 82, 84, 
  87, 91, 96, 98, 102, 104, 107, 111, 116, 120, 
  126, 128, 130, 134, 138, 142, 144, 147, 149, 151, 
  153, 155, 157, 159};
#endif // QLALR_NO_ICIGRAMMAR_DEBUG_INFO

const short ICIGrammar::action_default [] = {
  0, 7, 0, 11, 48, 0, 0, 0, 42, 8, 
  9, 0, 3, 1, 46, 0, 10, 47, 49, 20, 
  53, 21, 41, 0, 0, 0, 29, 0, 35, 0, 
  51, 50, 46, 52, 0, 0, 17, 18, 0, 0, 
  36, 46, 0, 39, 0, 37, 0, 38, 0, 40, 
  0, 16, 33, 0, 30, 0, 31, 34, 32, 0, 
  6, 15, 5, 0, 4, 2, 0, 14, 19, 0, 
  0, 22, 0, 23, 12, 0, 24, 26, 25, 27, 
  28, 0, 45, 44, 43, 54, 13};

const short ICIGrammar::goto_default [] = {
  11, 13, 12, 61, 1, 9, 10, 16, 21, 22, 
  27, 19, 32, 53, 75, 26, 28, 39, 8, 0};

const short ICIGrammar::action_index [] = {
  22, -27, 26, -27, -27, 128, 5, 25, -2, -27, 
  -27, 0, -27, 34, -11, 6, -27, -27, -27, 1, 
  -27, -27, -27, 16, 102, 154, -27, 49, -27, 102, 
  -27, -27, -8, -27, 128, 128, -27, -27, -16, -4, 
  -27, -27, 102, -27, 17, -27, -12, -27, 102, -27, 
  -5, -27, -27, -1, -27, 206, -27, -27, -27, 43, 
  -27, -22, -27, 76, -27, -27, 64, -27, -27, 180, 
  -3, -27, 102, -27, -27, 102, -27, -27, -27, -27, 
  -27, 52, -27, -27, -27, -27, -27, 

  19, -20, -20, -20, -20, -20, -20, -20, -20, -20, 
  -20, -20, -20, 56, -20, 4, -20, -20, -20, -20, 
  -20, -20, -20, 2, -5, 7, -20, 32, -20, -2, 
  -20, -20, -20, -20, -8, -3, -20, -20, -20, -20, 
  -20, -20, -7, -20, 3, -20, -20, -20, -11, -20, 
  -20, -20, -20, -20, -20, -1, -20, -20, -20, 38, 
  -20, -20, -20, 21, -20, -20, 40, -20, -20, 6, 
  -20, -20, -6, -20, -20, -10, -20, -20, -20, -20, 
  -20, -9, -20, -20, -20, -20, -20};

const short ICIGrammar::action_info [] = {
  85, 69, 66, 42, 69, 81, 74, 48, 51, 4, 
  73, 45, 0, 2, 44, 72, 56, 55, 0, 4, 
  4, 34, 35, 2, 2, 4, 0, 17, 0, 2, 
  0, 40, 47, 76, 78, 77, 79, 4, 0, 0, 
  0, 2, 0, 0, 0, 5, 4, 6, 15, 0, 
  2, 0, 4, 83, 82, 4, 2, 5, 62, 6, 
  15, 0, 0, 59, 0, 0, 5, 4, 6, 15, 
  0, 2, 5, 0, 6, 15, 0, 0, 59, 4, 
  0, 0, 0, 2, 0, 0, 0, 5, 0, 6, 
  15, 64, 0, 0, 0, 0, 0, 0, 0, 5, 
  0, 6, 15, 31, 18, 4, 30, 33, 20, 2, 
  0, 0, 0, 0, 24, 0, 23, 0, 25, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 31, 
  18, 4, 30, 33, 20, 2, 0, 0, 0, 0, 
  24, 0, 23, 0, 25, 0, 0, 0, 0, 0, 
  29, 0, 0, 0, 0, 31, 18, 4, 30, 33, 
  20, 2, 0, 0, 0, 0, 24, 0, 23, 0, 
  25, 54, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 31, 18, 4, 30, 33, 20, 2, 0, 0, 
  0, 0, 24, 71, 23, 0, 25, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 31, 18, 4, 
  30, 33, 20, 2, 0, 0, 0, 0, 24, 0, 
  23, 0, 25, 58, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 

  49, 80, 36, 84, 43, 57, 50, 37, 0, 68, 
  57, 38, 46, 86, 41, 41, 41, 52, 52, 70, 
  0, 0, 0, 65, 0, 0, 0, 3, 7, 3, 
  7, 14, 0, 14, 60, 0, 0, 0, 0, 63, 
  3, 7, 60, 67, 14, 0, 3, 7, 3, 7, 
  14, 0, 14, 0, 0, 0, 0, 0, 65, 0, 
  0, 0, 0, 0, 3, 7, 0, 0, 14, 0, 
  0, 0, 0, 0, 0, 0};

const short ICIGrammar::action_check [] = {
  0, 12, 24, 19, 12, 7, 1, 19, 13, 3, 
  13, 15, -1, 7, 18, 18, 17, 18, -1, 3, 
  3, 20, 21, 7, 7, 3, -1, 1, -1, 7, 
  -1, 15, 15, 8, 9, 10, 11, 3, -1, -1, 
  -1, 7, -1, -1, -1, 23, 3, 25, 26, -1, 
  7, -1, 3, 1, 2, 3, 7, 23, 15, 25, 
  26, -1, -1, 14, -1, -1, 23, 3, 25, 26, 
  -1, 7, 23, -1, 25, 26, -1, -1, 14, 3, 
  -1, -1, -1, 7, -1, -1, -1, 23, -1, 25, 
  26, 15, -1, -1, -1, -1, -1, -1, -1, 23, 
  -1, 25, 26, 1, 2, 3, 4, 5, 6, 7, 
  -1, -1, -1, -1, 12, -1, 14, -1, 16, -1, 
  -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 
  2, 3, 4, 5, 6, 7, -1, -1, -1, -1, 
  12, -1, 14, -1, 16, -1, -1, -1, -1, -1, 
  22, -1, -1, -1, -1, 1, 2, 3, 4, 5, 
  6, 7, -1, -1, -1, -1, 12, -1, 14, -1, 
  16, 17, -1, -1, -1, -1, -1, -1, -1, -1, 
  -1, 1, 2, 3, 4, 5, 6, 7, -1, -1, 
  -1, -1, 12, 13, 14, -1, 16, -1, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, 1, 2, 3, 
  4, 5, 6, 7, -1, -1, -1, -1, 12, -1, 
  14, -1, 16, 17, -1, -1, -1, -1, -1, -1, 
  -1, -1, -1, 

  11, 11, 10, 12, 11, 11, 11, 10, -1, 11, 
  11, 9, 9, 9, 12, 12, 12, 11, 11, 13, 
  -1, -1, -1, 2, -1, -1, -1, 8, 9, 8, 
  9, 12, -1, 12, 2, -1, -1, -1, -1, 1, 
  8, 9, 2, 3, 12, -1, 8, 9, 8, 9, 
  12, -1, 12, -1, -1, -1, -1, -1, 2, -1, 
  -1, -1, -1, -1, 8, 9, -1, -1, 12, -1, 
  -1, -1, -1, -1, -1, -1};

