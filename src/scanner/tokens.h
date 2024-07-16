#ifndef TOKENS_H
#define TOKENS_H

#define TOKEN_NULL            0x00

/* Keyword Tokens */
#define TOKEN_KW_RETURN       0x01
#define TOKEN_KW_IF           0x02
#define TOKEN_KW_ELSE_IF      0x03
#define TOKEN_KW_ELSE         0x04
#define TOKEN_KW_WHILE        0x05
#define TOKEN_KW_FOR          0x06
#define TOKEN_KW_SWITCH       0x07
#define TOKEN_KW_CASE         0x08
#define TOKEN_KW_BREAK        0x09
#define TOKEN_KW_CONTINUE     0x10
#define TOKEN_KW_FUNCTION     0x11
#define TOKEN_KW_CONST        0x12 
#define TOKEN_KW_DEF          0x13
#define TOKEN_KW_END          0x14
#define TOKEN_KW_COMMENT      0x15

/* Arithmetical Operators */
#define TOKEN_OP_ADD          0xA0
#define TOKEN_OP_SUS          0xA1
#define TOKEN_OP_MUL          0xA2
#define TOKEN_OP_DIV          0xA3
#define TOKEN_OP_LEFT_SHIFT   0xA4
#define TOKEN_OP_RIGHT_SHIFT  0xA5

/* Logic Gates */
#define TOKEN_GATE_OR         0xB0
#define TOKEN_GATE_AND        0xB1
#define TOKEN_GATE_NOT        0xB2

/* Definitions */
#define TOKEN_IDENTIFIER      0xC0
#define TOKEN_EQUAL           0xC1
#define TOKEN_NOT_EQUAL       0xC2

#define TOKEN_VALUE_DEF       "DEF"
#define TOKEN_VALUE_END       "END"
#define TOKEN_VALUE_COMMENT   "..."
#define TOKEN_VALUE_IF        "IF"

#endif
