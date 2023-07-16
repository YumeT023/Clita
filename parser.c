#include "parser.h"
#include "lexer.h"
#include <assert.h>
#include <stdlib.h>

Parser create_parser(size_t initial_capacity) {
    Parser p;
    p.tokens = malloc(initial_capacity * sizeof(Token));
    assert(p.tokens != NULL);
    p.tokens_len = 0;
    return p;
}

Token *p_peek(Parser *p) {
    return &p->tokens[p->pos];
}

Token *consume(Parser *p) {
    Token *t = p_peek(p);
    p->pos++;
    return t;
}

SymbolDeclarationNode *parse_symbol_declaration(Parser *p) {
    assert(consume(p)->kind == Forony);
    SymbolLiteralNode *symbol = parse_symbol_literal(p);

    assert(consume(p)->kind == Ho);
    NumericLiteralNode *numeric = parse_numeric_literal(p);

    SymbolDeclarationNode *node = malloc(sizeof(SymbolDeclarationNode));
    assert(node != NULL);

    node->type = SymbolDeclaration;
    node->identifier = symbol;
    node->initialValue = numeric;
    return node;
}

SymbolLiteralNode *parse_symbol_literal(Parser *p) {
    Token *t = consume(p);

    assert(t->kind == Symbol);
    SymbolLiteralNode *node = malloc(sizeof(SymbolLiteralNode));
    assert(node != NULL);

    node->type = SymbolLiteral;
    node->name = t->text;
    return node;
}

NumericLiteralNode *parse_numeric_literal(Parser *p) {
    Token *t = consume(p);

    assert(t->kind == Numeric);
    NumericLiteralNode *node = malloc(sizeof(NumericLiteralNode));
    assert(node != NULL);

    node->type = NumericLiteral;
    node->value = strtol(t->text, NULL, 10);
    return node;
}
