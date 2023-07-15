#include "lexer.h"
#include "util.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Token punctuation_tokens[] = {
        {.kind = Colon, .text = ":"},
        {.kind = Dot, .text = "."},
        {.kind = BracketLeft, .text = "["},
        {.kind = BracketRight, .text = "]"},
        {.kind = Backtick, .text = "`"},
        {.kind = Underscore, .text = "_"},
        {.kind = Gt, .text = ">"},
        {.kind = Lt, .text = "<"},
        {.kind = Plus, .text = "+"},
        {.kind = Minus, .text = "-"},
        {.kind = Times, .text = "*"},
        {.kind = Division, .text = "/"},
        {.kind = Quote, .text = "'"},
        {.kind = DoubleQuote, .text = "\""},
        {.kind = Equals, .text = "="},
};

#define PUNCTUATION_LEN sizeof(punctuation_tokens) / sizeof(*punctuation_tokens)

Lexer create_lexer(const char *source) {
    Lexer l = {
            .source = source,
            .pos = 0,
            .line = 0,
            .end = strlen(source)};
    return l;
}

Token *token(TokenKind kind) {
    Token *t = malloc(sizeof(Token));
    t->text = NULL;
    t->kind = kind;
    return t;
}


void set_range_pos(Token *t, size_t pos) {
    t->pos = pos;
}

void set_range_end(Token *t, size_t end) {
    t->end = end;
}

void set_range_pos_end(Token *t, size_t pos, size_t end) {
    t->pos = pos;
    t->end = end;
}

Token *lex(Lexer *l) {
    trim_left(l);
    char c = peek(l);

    if (ispunct(c)) {
        return scan_punctuation(l);
    }

    if (isdigit(c)) {
        return scan_numeric(l);
    }

    if (is_symbol_start(c)) {
        return scan_symbol(l);
    }

    Token *t = token(EOF);
    set_range_pos_end(t, l->pos, l->pos);
    return t;
}

Token *scan_symbol(Lexer *l) {
    Token *t = token(Symbol);
    size_t begin = l->pos;
    while (!is_eof(l) && is_symbol_part(peek(l))) {
        advance(l);
    }
    set_range_pos_end(t, begin, l->pos);
    t->text = cut(l->source, begin, t->end - begin);
    return t;
}

Token *scan_numeric(Lexer *l) {
    Token *t = token(Numeric);
    size_t begin = l->pos;
    while (!is_eof(l) && isdigit(peek(l))) {
        advance(l);
    }
    set_range_pos_end(t, begin, l->pos);
    t->text = cut(l->source, begin, t->pos - begin);
    return t;
}

Token *scan_punctuation(Lexer *l) {
    char c = peek(l);

    for (int i = 0; i < PUNCTUATION_LEN; ++i) {
        char *text = punctuation_tokens[i].text;
        if (*text == c) {
            Token *t = token(punctuation_tokens[i].kind);
            set_range_pos_end(t, l->pos, l->pos + 1);

            advance(l);
            char c_next = peek(l);

            if ((t->kind == Gt || t->kind == Lt) && c_next == '=') {
                advance(l);
                char *sym = malloc(3);
                strcpy(sym, text);
                strncat(sym, &c_next, 1);

                set_range_end(t, l->pos);
                t->kind = t->kind == Gt ? Gte : Lte;
                t->text = sym;
                return t;
            }
            // fallback
            t->text = text;
            t->kind = t->kind;
            return t;
        }
    }
    printf("Unknown character: %c \n", c);
    exit(1);
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

void advance(Lexer *l) {
    l->pos++;
}

void trim_left(Lexer *l) {
    while (!is_eof(l) && isspace(peek(l))) {
        advance(l);
    }
}

void print_token(Token *t) {
    printf("%s = (%s) [%zu, %zu]\n", t->text, kind_str(t->kind), t->pos, t->end);
}

static char *kind_str(TokenKind kind) {
    switch (kind) {
        case Eof:
            return "End of file";
        case Numeric:
            return "Numeric";
        case Symbol:
            return "Symbol";
        case Keyword:
            return "Keyword";
        // punctuation
        case Colon:
            return "Colon";
        case Dot:
            return "Dot";
        case BracketLeft:
            return "Bracket left";
        case BracketRight:
            return "Bracket right";
        case Backtick:
            return "Backtick";
        case Underscore:
            return "Underscore";
        case Quote:
            return "Quote";
        case DoubleQuote:
            return "Double quote";
        // logical & op
        case Gt:
            return "Greater than";
        case Lt:
            return "Lesser than";
        case Gte:
            return "Greater than or Equal";
        case Lte:
            return "Lesser than or Equal";
        case Equals:
            return "Equals";
        case Plus:
            return "Plus";
        case Minus:
            return "Minus";
        case Division:
            return "Division";
        case Times:
            return "Times";
        default:
            printf("Unexpected kind: %d", kind);
            exit(1);
    }
}
