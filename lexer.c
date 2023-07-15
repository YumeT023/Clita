#include "lexer.h"
#include "util.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    if (isalpha(c)) {
        size_t begin = l->pos;
        while (!is_eof(l) && isalnum(peek(l))) {
            advance(l);
        }
        t->kind = TOKEN_SYMBOl;
        t->text = cut(l->source, begin, l->pos - begin);
        t->end = l->pos;
        return t;
    }

    return t;
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
    printf("%s: (%s)\n", t->text, kind_str(t->kind));
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
        default:
            printf("Unexpected kind: %d", kind);
            exit(1);
    }
}
