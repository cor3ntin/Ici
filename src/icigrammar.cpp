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
  38, 36, 45, 45, 39, 38, 38, 38, 38, 38, 
  46};

const short ICIGrammar::rhs [] = {
  1, 2, 1, 3, 2, 1, 1, 1, 1, 1, 
  1, 2, 2, 5, 3, 3, 3, 3, 2, 1, 
  1, 3, 4, 1, 1, 1, 1, 3, 1, 2, 
  3, 4, 1, 3, 1, 2, 3, 4, 3, 5, 
  1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 
  2};


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
  , 45, 39
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
  126, 128, 130, 134, 136, 138, 140, 142, 144, 146, 
  148};
#endif // QLALR_NO_ICIGRAMMAR_DEBUG_INFO

const short ICIGrammar::action_default [] = {
  0, 7, 11, 45, 0, 0, 0, 42, 8, 9, 
  0, 3, 1, 44, 0, 10, 46, 20, 50, 21, 
  41, 0, 0, 0, 29, 0, 35, 0, 48, 47, 
  44, 49, 0, 0, 17, 18, 0, 0, 36, 44, 
  0, 39, 0, 37, 0, 38, 0, 40, 0, 16, 
  33, 0, 30, 0, 31, 34, 32, 0, 6, 15, 
  5, 0, 4, 2, 0, 14, 19, 0, 0, 22, 
  0, 23, 12, 0, 24, 26, 25, 27, 28, 0, 
  43, 51, 13};

const short ICIGrammar::goto_default [] = {
  10, 12, 11, 59, 1, 8, 9, 15, 19, 20, 
  25, 17, 30, 51, 73, 24, 26, 37, 7, 0};

const short ICIGrammar::action_index [] = {
  50, -27, -27, -27, 126, 26, 12, -6, -27, -27, 
  2, -27, 23, -8, 0, -27, -27, -2, -27, -27, 
  -27, 10, 100, 77, -27, 29, -27, 100, -27, -27, 
  -7, -27, 126, 126, -27, -27, -10, -4, -27, -27, 
  100, -27, 9, -27, -12, -27, 100, -27, -5, -27, 
  -27, -1, -27, 178, -27, -27, -27, 41, -27, -24, 
  -27, 35, -27, -27, 74, -27, -27, 152, -3, -27, 
  100, -27, -27, 100, -27, -27, -27, -27, -27, 3, 
  -27, -27, -27, 

  12, -20, -20, -20, -20, -20, -20, -20, -20, -20, 
  -20, -20, 36, -20, 18, -20, -20, -20, -20, -20, 
  -20, 10, 7, -3, -20, 54, -20, -6, -20, -20, 
  -20, -20, -8, -4, -20, -20, -20, -20, -20, -20, 
  -2, -20, 2, -20, -20, -20, -7, -20, -20, -20, 
  -20, -20, -20, -1, -20, -20, -20, 24, -20, -20, 
  -20, 36, -20, -20, 38, -20, -20, 4, -20, -20, 
  -11, -20, -20, -10, -20, -20, -20, -20, -20, -9, 
  -20, -20, -20};

const short ICIGrammar::action_info [] = {
  64, 79, 81, 3, 67, 67, 3, 46, 49, 40, 
  71, 43, 3, 3, 42, 70, 54, 53, 32, 33, 
  74, 76, 75, 77, 45, 38, 3, 72, 0, 0, 
  0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 
  0, 0, 0, 57, 3, 0, 4, 0, 5, 14, 
  62, 0, 4, 3, 5, 14, 60, 0, 4, 0, 
  5, 14, 0, 0, 4, 0, 5, 14, 0, 0, 
  0, 0, 0, 4, 0, 5, 14, 3, 29, 16, 
  3, 28, 31, 18, 0, 0, 0, 0, 57, 22, 
  0, 21, 0, 23, 52, 0, 0, 4, 0, 5, 
  14, 29, 16, 3, 28, 31, 18, 0, 0, 0, 
  0, 0, 22, 0, 21, 0, 23, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 29, 16, 3, 
  28, 31, 18, 0, 0, 0, 0, 0, 22, 0, 
  21, 0, 23, 0, 0, 0, 0, 0, 27, 0, 
  0, 0, 0, 29, 16, 3, 28, 31, 18, 0, 
  0, 0, 0, 0, 22, 69, 21, 0, 23, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 29, 
  16, 3, 28, 31, 18, 0, 0, 0, 0, 0, 
  22, 0, 21, 0, 23, 56, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 

  55, 78, 34, 80, 47, 66, 35, 0, 50, 41, 
  55, 44, 0, 0, 39, 50, 0, 68, 48, 36, 
  2, 6, 39, 0, 13, 61, 0, 82, 0, 0, 
  39, 0, 2, 6, 0, 0, 13, 0, 63, 0, 
  58, 65, 0, 0, 2, 6, 2, 6, 13, 0, 
  13, 0, 0, 0, 0, 0, 58, 0, 0, 0, 
  0, 0, 2, 6, 0, 0, 13, 0, 0, 0, 
  0, 0, 0, 0};

const short ICIGrammar::action_check [] = {
  24, 7, 0, 3, 12, 12, 3, 19, 13, 19, 
  13, 15, 3, 3, 18, 18, 17, 18, 20, 21, 
  8, 9, 10, 11, 15, 15, 3, 1, -1, -1, 
  -1, -1, 3, -1, -1, -1, -1, -1, 3, -1, 
  -1, -1, -1, 14, 3, -1, 23, -1, 25, 26, 
  15, -1, 23, 3, 25, 26, 15, -1, 23, -1, 
  25, 26, -1, -1, 23, -1, 25, 26, -1, -1, 
  -1, -1, -1, 23, -1, 25, 26, 3, 1, 2, 
  3, 4, 5, 6, -1, -1, -1, -1, 14, 12, 
  -1, 14, -1, 16, 17, -1, -1, 23, -1, 25, 
  26, 1, 2, 3, 4, 5, 6, -1, -1, -1, 
  -1, -1, 12, -1, 14, -1, 16, -1, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, 1, 2, 3, 
  4, 5, 6, -1, -1, -1, -1, -1, 12, -1, 
  14, -1, 16, -1, -1, -1, -1, -1, 22, -1, 
  -1, -1, -1, 1, 2, 3, 4, 5, 6, -1, 
  -1, -1, -1, -1, 12, 13, 14, -1, 16, -1, 
  -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 
  2, 3, 4, 5, 6, -1, -1, -1, -1, -1, 
  12, -1, 14, -1, 16, 17, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, 

  11, 11, 10, 12, 11, 11, 10, -1, 11, 11, 
  11, 9, -1, -1, 12, 11, -1, 13, 11, 9, 
  8, 9, 12, -1, 12, 1, -1, 9, -1, -1, 
  12, -1, 8, 9, -1, -1, 12, -1, 2, -1, 
  2, 3, -1, -1, 8, 9, 8, 9, 12, -1, 
  12, -1, -1, -1, -1, -1, 2, -1, -1, -1, 
  -1, -1, 8, 9, -1, -1, 12, -1, -1, -1, 
  -1, -1, -1, -1};
