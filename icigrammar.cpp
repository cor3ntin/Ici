// This file was generated by qlalr - DO NOT EDIT!
#include "icigrammar_p.h"

const char *const ICIGrammar::spell [] = {
  "end of file", 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 
#ifndef QLALR_NO_ICIGRAMMAR_DEBUG_INFO
"Source", "StatementList", "Statement", "StatementBlock", "Assignement", "IfStatement", 
  "IncludeStatement", "UnsetStatement", "FunctionCall", "Identifier", "LogicalExpression", "Expression", "StoredIdent", "ListParameters", "AssignementOperator", "List", 
  "IdentifierPart", "$accept"
#endif // QLALR_NO_ICIGRAMMAR_DEBUG_INFO
};

const short ICIGrammar::lhs [] = {
  24, 25, 25, 27, 27, 26, 26, 26, 26, 26, 
  30, 31, 29, 29, 34, 34, 34, 34, 34, 35, 
  32, 32, 38, 38, 38, 28, 35, 39, 39, 37, 
  37, 35, 33, 40, 40, 36, 35, 35, 35, 35, 
  35, 41};

const short ICIGrammar::rhs [] = {
  1, 2, 1, 3, 2, 1, 1, 1, 1, 1, 
  2, 2, 4, 2, 3, 3, 3, 2, 1, 1, 
  3, 4, 1, 1, 1, 3, 1, 2, 3, 1, 
  3, 1, 1, 3, 1, 1, 1, 1, 1, 1, 
  1, 2};


#ifndef QLALR_NO_ICIGRAMMAR_DEBUG_INFO
const int ICIGrammar::rule_info [] = {
    24, 25
  , 25, 25, 26
  , 25, 26
  , 27, 13, 25, 14
  , 27, 13, 14
  , 26, 28
  , 26, 29
  , 26, 30
  , 26, 31
  , 26, 32
  , 30, 22, 1
  , 31, 23, 33
  , 29, 34, 27, 21, 27
  , 29, 34, 27
  , 34, 11, 35, 12
  , 34, 35, 18, 34
  , 34, 35, 19, 34
  , 34, 20, 35
  , 34, 35
  , 35, 32
  , 32, 36, 11, 12
  , 32, 36, 11, 37, 12
  , 38, 8
  , 38, 9
  , 38, 10
  , 28, 33, 38, 35
  , 35, 39
  , 39, 15, 16
  , 39, 15, 37, 16
  , 37, 35
  , 37, 37, 17, 35
  , 35, 33
  , 33, 40
  , 40, 40, 7, 36
  , 40, 36
  , 36, 3
  , 35, 2
  , 35, 1
  , 35, 4
  , 35, 5
  , 35, 6
  , 41, 24, 0};

const int ICIGrammar::rule_index [] = {
  0, 2, 5, 7, 11, 14, 16, 18, 20, 22, 
  24, 27, 30, 35, 38, 42, 46, 50, 53, 55, 
  57, 61, 66, 68, 70, 72, 76, 78, 81, 85, 
  87, 91, 93, 95, 99, 101, 103, 105, 107, 109, 
  111, 113};
#endif // QLALR_NO_ICIGRAMMAR_DEBUG_INFO

const short ICIGrammar::action_default [] = {
  0, 6, 37, 19, 41, 10, 36, 0, 32, 33, 
  7, 8, 0, 0, 27, 0, 0, 39, 38, 0, 
  3, 1, 35, 40, 0, 9, 0, 0, 20, 32, 
  16, 35, 0, 30, 0, 21, 0, 22, 31, 17, 
  11, 0, 23, 25, 24, 26, 0, 34, 0, 15, 
  0, 28, 29, 0, 14, 5, 0, 4, 2, 0, 
  13, 18, 42, 12, 35};

const short ICIGrammar::goto_default [] = {
  19, 21, 20, 54, 1, 10, 11, 25, 28, 29, 
  15, 3, 31, 50, 41, 14, 9, 0};

const short ICIGrammar::action_index [] = {
  112, -24, -24, -9, -24, 6, -24, -1, 8, -4, 
  -24, -24, 43, 66, -24, -7, 43, -24, -24, 7, 
  -24, 112, 0, -24, 20, -24, 89, 89, -24, -24, 
  -24, -6, 25, -24, 3, -24, 43, -24, -24, -24, 
  -24, 43, -24, -24, -24, -24, -2, -24, -10, -24, 
  -3, -24, -24, 135, -17, -24, 158, -24, -24, -5, 
  -24, -24, -24, -24, -24, 

  15, -18, -18, -18, -18, -18, -18, -18, -18, -18, 
  -18, -18, -10, -5, -18, -18, -6, -18, -18, -18, 
  -18, 10, -18, -18, 1, -18, 5, -8, -18, -18, 
  -18, -18, -2, -18, -18, -18, -7, -18, -18, -18, 
  -18, -4, -18, -18, -18, -18, -9, -18, -18, -18, 
  -18, -18, -18, 32, -18, -18, 23, -18, -18, -3, 
  -18, -18, -18, -18, -18};

const short ICIGrammar::action_info [] = {
  40, 6, 49, 46, 59, 32, 53, 62, 53, 26, 
  27, 32, 0, 52, 36, 37, 42, 44, 43, -20, 
  36, 0, 0, 6, -20, -20, 18, 2, 6, 17, 
  23, 4, 0, 0, 0, 0, 0, 35, 0, 0, 
  13, 0, 0, 0, 18, 2, 6, 17, 23, 4, 
  0, 0, 0, 0, 0, 0, 0, 0, 13, 0, 
  0, 0, 0, 0, 0, 0, 0, 18, 2, 6, 
  17, 23, 4, 0, 0, 0, 0, 0, 0, 0, 
  0, 13, 51, 0, 0, 0, 0, 0, 0, 0, 
  18, 2, 6, 17, 23, 4, 0, 0, 0, 0, 
  12, 0, 0, 0, 13, 0, 0, 0, 0, 16, 
  0, 0, 0, 18, 2, 6, 17, 23, 4, 0, 
  0, 0, 0, 12, 0, 0, 0, 13, 0, 0, 
  0, 0, 16, 0, 7, 24, 18, 2, 6, 17, 
  23, 4, 0, 0, 0, 0, 12, 0, 0, 55, 
  13, 0, 0, 0, 0, 16, 0, 7, 24, 18, 
  2, 6, 17, 23, 4, 0, 0, 0, 0, 12, 
  0, 0, 57, 13, 0, 0, 0, 0, 16, 0, 
  7, 24, 

  60, 48, 39, 47, 38, 61, 33, 45, 0, 33, 
  63, 34, 58, 64, 0, 30, 0, 0, 5, 8, 
  0, 0, 22, 5, 8, 58, 0, 22, 0, 0, 
  0, 5, 8, 56, 0, 22, 0, 0, 0, 0, 
  5, 8, 0, 0, 22, 0, 0, 0, 0, 0};

const short ICIGrammar::action_check [] = {
  1, 3, 12, 7, 21, 11, 13, 0, 13, 18, 
  19, 11, -1, 16, 17, 12, 8, 9, 10, 13, 
  17, -1, -1, 3, 18, 19, 1, 2, 3, 4, 
  5, 6, -1, -1, -1, -1, -1, 12, -1, -1, 
  15, -1, -1, -1, 1, 2, 3, 4, 5, 6, 
  -1, -1, -1, -1, -1, -1, -1, -1, 15, -1, 
  -1, -1, -1, -1, -1, -1, -1, 1, 2, 3, 
  4, 5, 6, -1, -1, -1, -1, -1, -1, -1, 
  -1, 15, 16, -1, -1, -1, -1, -1, -1, -1, 
  1, 2, 3, 4, 5, 6, -1, -1, -1, -1, 
  11, -1, -1, -1, 15, -1, -1, -1, -1, 20, 
  -1, -1, -1, 1, 2, 3, 4, 5, 6, -1, 
  -1, -1, -1, 11, -1, -1, -1, 15, -1, -1, 
  -1, -1, 20, -1, 22, 23, 1, 2, 3, 4, 
  5, 6, -1, -1, -1, -1, 11, -1, -1, 14, 
  15, -1, -1, -1, -1, 20, -1, 22, 23, 1, 
  2, 3, 4, 5, 6, -1, -1, -1, -1, 11, 
  -1, -1, 14, 15, -1, -1, -1, -1, 20, -1, 
  22, 23, 

  3, 11, 10, 12, 11, 11, 11, 11, -1, 11, 
  9, 13, 2, 12, -1, 10, -1, -1, 8, 9, 
  -1, -1, 12, 8, 9, 2, -1, 12, -1, -1, 
  -1, 8, 9, 1, -1, 12, -1, -1, -1, -1, 
  8, 9, -1, -1, 12, -1, -1, -1, -1, -1};

