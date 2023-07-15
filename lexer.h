#ifndef CLITA_LEXER_H
#define CLITA_LEXER_H

#include <stdbool.h>
#include <stddef.h>

typedef enum {
    TOKEN_EOF = 0,
    TOKEN_NUMERIC,
    TOKEN_SYMBOl,
    TOKEN_KEYWORD,

    // punctuation
    TOKEN_COLON,
    TOKEN_DOT,
    TOKEN_BRACKET_LEFT,
    TOKEN_BRACKET_RIGHT,
    TOKEN_BACKTICK,
    TOKEN_UNDERSCORE,

    // logical & op
    TOKEN_GT,
    TOKEN_LT,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_DIVISION,
    TOKEN_TIMES,
    TOKEN_QUOTE,
    TOKEN_DBL_QUOTE,
    TOKEN_EQUALS
} Token_Kind;

typedef struct {
    const char *source;
    size_t pos;
    size_t line;
    size_t end;
} Lexer;

typedef struct {
    char *text;
    Token_Kind kind;
    size_t pos;
    size_t end;
} Token;

Lexer *create_lexer(const char *source);
Token *token(Token_Kind kind);

// scan token
Token *lex(Lexer *l);

// predicates
bool is_symbol_start(char c);
bool is_symbol_part(char c);

// get the current char
char peek(Lexer *l);

bool is_eof(Lexer *l);

// get the current char and move the cursor
char consume(Lexer *l);

// skip whitespace
void trim_left(Lexer *l);

// move the cursor
void advance(Lexer *l);

// beauty print token
void print_token(Token *t);

// beauty token kind
static char *kind_str(Token_Kind kind);

#endif//CLITA_LEXER_H
