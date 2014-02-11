// This file was generated by qlalr - DO NOT EDIT!
#ifndef ICIGRAMMAR_P_H
#define ICIGRAMMAR_P_H

class ICIGrammar
{
public:
  enum VariousConstants {
    EOF_SYMBOL = 0,
    TOKEN_AND = 20,
    TOKEN_COLON = 19,
    TOKEN_COMMA = 18,
    TOKEN_DIGIT = 2,
    TOKEN_DOT = 7,
    TOKEN_ELSE = 24,
    TOKEN_EQUAL = 8,
    TOKEN_FALSE = 6,
    TOKEN_IDENT = 3,
    TOKEN_IF = 23,
    TOKEN_INCLUDE = 25,
    TOKEN_LBRACKET = 14,
    TOKEN_LPAREN = 12,
    TOKEN_LSQUARE_BRACKET = 16,
    TOKEN_MINUS_EQUAL = 10,
    TOKEN_NOT = 22,
    TOKEN_NULL = 4,
    TOKEN_OR = 21,
    TOKEN_PLUS_EQUAL = 9,
    TOKEN_RBRACKET = 15,
    TOKEN_RPAREN = 13,
    TOKEN_RSQUARE_BRACKET = 17,
    TOKEN_STAR_EQUAL = 11,
    TOKEN_STRING = 1,
    TOKEN_TRUE = 5,
    TOKEN_UNSET = 26,

    ACCEPT_STATE = 84,
    RULE_COUNT = 53,
    STATE_COUNT = 86,
    TERMINAL_COUNT = 27,
    NON_TERMINAL_COUNT = 20,

    GOTO_INDEX_OFFSET = 86,
    GOTO_INFO_OFFSET = 227,
    GOTO_CHECK_OFFSET = 227
  };

  static const char  *const    spell [];
  static const short             lhs [];
  static const short             rhs [];

#ifndef QLALR_NO_ICIGRAMMAR_DEBUG_INFO
  static const int     rule_index [];
  static const int      rule_info [];
#endif // QLALR_NO_ICIGRAMMAR_DEBUG_INFO

  static const short    goto_default [];
  static const short  action_default [];
  static const short    action_index [];
  static const short     action_info [];
  static const short    action_check [];

  static inline int nt_action (int state, int nt)
  {
    const int yyn = action_index [GOTO_INDEX_OFFSET + state] + nt;
    if (yyn < 0 || action_check [GOTO_CHECK_OFFSET + yyn] != nt)
      return goto_default [nt];

    return action_info [GOTO_INFO_OFFSET + yyn];
  }

  static inline int t_action (int state, int token)
  {
    const int yyn = action_index [state] + token;

    if (yyn < 0 || action_check [yyn] != token)
      return - action_default [state];

    return action_info [yyn];
  }
};


#endif // ICIGRAMMAR_P_H

