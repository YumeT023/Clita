#include "lexer.h"
#include "util.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Token punctuation_tokens[] = {
        {.kind = TOKEN_COLON, .text = ":"},
        {.kind = TOKEN_DOT, .text = "."},
        {.kind = TOKEN_BRACKET_LEFT, .text = "["},
        {.kind = TOKEN_BRACKET_RIGHT, .text = "]"},
        {.kind = TOKEN_BACKTICK, .text = "`"},
        {.kind = TOKEN_UNDERSCORE, .text = "_"},
        {.kind = TOKEN_GT, .text = ">"},
        {.kind = TOKEN_LT, .text = "<"},
        {.kind = TOKEN_PLUS, .text = "+"},
        {.kind = TOKEN_MINUS, .text = "-"},
        {.kind = TOKEN_TIMES, .text = "*"},
        {.kind = TOKEN_DIVISION, .text = "/"},
        {.kind = TOKEN_QUOTE, .text = "'"},
        {.kind = TOKEN_DBL_QUOTE, .text = "\""},
        {.kind = TOKEN_EQUALS, .text = "="},
};

#define PUNCTUATION_TOKEN_LEN sizeof(punctuation_tokens) / sizeof(*punctuation_tokens)

Lexer *create_lexer(const char *source) {
    Lexer *l = malloc(sizeof(Lexer));
    l->source = source;
    l->pos = 0;
    l->line = 0;
    l->end = strlen(source);
    return l;
}

Token *token(Token_Kind kind) {
    Token *t = malloc(sizeof(Token));
    t->text = NULL;
    t->kind = kind;
    return t;
}

Token *lex(Lexer *l) {
    trim_left(l);

    Token *t = token(TOKEN_EOF);
    char c = peek(l);

    if (ispunct(c)) {
        size_t begin = l->pos;
        for (int i = 0; i < PUNCTUATION_TOKEN_LEN; ++i) {
            char *text = punctuation_tokens[i].text;
            if (*text == c) {
                advance(l);
                t->kind = punctuation_tokens[i].kind;
                t->text = text;
                t->pos = begin;
                t->end = l->pos;
                return t;
            }
        }
        printf("Unknown character: %c \n", c);
        exit(1);
    }

    if (isdigit(c)) {
        size_t begin = l->pos;
        while (!is_eof(l) && isdigit(peek(l))) {
            advance(l);
        }
        t->kind = TOKEN_NUMERIC;
        t->text = cut(l->source, begin, l->pos - begin);
        t->end = l->pos;
        return t;
    }

    if (is_symbol_start(c)) {
        size_t begin = l->pos;
        while (!is_eof(l) && is_symbol_part(peek(l))) {
            advance(l);
        }
        t->kind = TOKEN_SYMBOl;
        t->text = cut(l->source, begin, l->pos - begin);
        t->end = l->pos;
        return t;
    }

    return t;
}

bool is_symbol_start(char c) {
    return isalpha(c) || c == '_';
}

bool is_symbol_part(char c) {
    return isalnum(c) || c == '_';
}

bool is_eof(Lexer *l) {
    return l->pos >= l->end;
}

char peek(Lexer *l) {
    if (!is_eof(l)) {
        return l->source[l->pos];
    }
    return 0;
}

char consume(Lexer *l) {
    char c = peek(l);
    advance(l);
    return c;
}

void advance(Lexer *l) {
    l->pos++;
}

void trim_left(Lexer *l) {
    while (!is_eof(l) && isspace(peek(l))) {
        advance(l);
    }
}

void print_token(Token *t) {
    printf("%s = (%s)\n", t->text, kind_str(t->kind));
}

// beauty token kind
static char *kind_str(Token_Kind kind) {
    switch (kind) {
        case TOKEN_EOF:
            return "End of file";
        case TOKEN_NUMERIC:
            return "Numeric";
        case TOKEN_SYMBOl:
            return "Symbol";
        case TOKEN_KEYWORD:
            return "Keyword";
        // punctuations
        case TOKEN_GT:
            return "Greater than";
        case TOKEN_LT:
            return "Lesser than";
        case TOKEN_COLON:
            return "Colon";
        case TOKEN_UNDERSCORE:
            return "Underscore";
        case TOKEN_DOT:
            return "Dot";
        case TOKEN_BRACKET_LEFT:
            return "Bracket left";
        case TOKEN_BRACKET_RIGHT:
            return "Bracket right";
        case TOKEN_BACKTICK:
            return "Backtick";
        case TOKEN_PLUS:
            return "Plus";
        case TOKEN_MINUS:
            return "Minus";
        case TOKEN_DIVISION:
            return "Division";
        case TOKEN_TIMES:
            return "Times";
        case TOKEN_QUOTE:
            return "Quote";
        case TOKEN_DBL_QUOTE:
            return "Double quote";
        case TOKEN_EQUALS:
            return "Equals";
        default:
            printf("Unexpected kind: %d", kind);
            exit(1);
    }
}
