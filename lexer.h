#ifndef CLITA_LEXER_H
#define CLITA_LEXER_H

#include <stdbool.h>
#include <stddef.h>

typedef enum {
    Eof = 0,
    // literal
    Numeric,
    Symbol,
    Marina,
    Diso,

    // punctuation
    Colon,
    Dot,
    BracketLeft,
    BracketRight,
    Backtick,
    Underscore,
    Quote,
    DoubleQuote,

    // logical & op
    Gt,
    Lt,
    Gte,
    Lte,
    Equals,

    Plus,
    Minus,
    Division,
    Times,

    // keywords
    Forony,
    Ataovy,
    Baiko,
    Raha,
    Raiso,
    Kasoloy,
    Rambola,
    Ho,
} TokenKind;

typedef struct {
    const char *source;
    size_t pos;
    size_t line;
    size_t end;
    size_t count;
} Lexer;

typedef struct {
    char *text;
    TokenKind kind;
    size_t pos;
    size_t end;
} Token;

Lexer create_lexer(const char *source);
Token *token(TokenKind kind);

Token *lex(Lexer *l);
Token *lex_next(Lexer *l);

Token *scan_symbol(Lexer *l);
Token *scan_numeric(Lexer *l);
Token *scan_punctuation(Lexer *l);

void set_range_pos(Token *t, size_t pos);
void set_range_end(Token *t, size_t end);
void set_range_pos_end(Token *t, size_t pos, size_t end);

// predicates
bool is_symbol_start(char c);
bool is_symbol_part(char c);

// get the current char
char peek(Lexer *l);

bool is_eof(Lexer *l);

// skip whitespace
void trim_left(Lexer *l);

// move the cursor
void advance(Lexer *l);

// beauty print token
void print_token(Token *t);

// beauty token kind
char *kind_str(TokenKind kind);

#endif//CLITA_LEXER_H
