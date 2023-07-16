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

SymbolAssignmentNode *parse_symbol_assignment(Parser *p) {
    assert(consume(p)->kind == Raiso);
    SymbolLiteralNode *symbol = parse_symbol_literal(p);

    assert(consume(p)->kind == Kasoloy);
    NumericLiteralNode *numeric = parse_numeric_literal(p);

    SymbolAssignmentNode *node = malloc(sizeof(SymbolAssignmentNode));
    assert(node != NULL);

    node->type = SymbolDeclaration;
    node->identifier = symbol;
    node->value = numeric;
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

BinaryExprNode *parse_binary_expr(Parser *p) {
    NumericLiteralNode *left = parse_numeric_literal(p);

    Token *op = consume(p);
    TokenKind kind = op->kind;
    assert(kind == Plus || kind == Minus || kind == Times || kind == Division || kind == Gt || kind == Gte || kind == Lt || kind == Lte);// -, +, *, /, >, >=, <, <=

    NumericLiteralNode *right = parse_numeric_literal(p);

    BinaryExprNode *node = malloc(sizeof(BinaryExprNode));
    node->type = BinaryExpr;
    node->left = left;
    node->right = right;
    node->op = op->text;
    return node;
}

UnaryExprNode *parse_unary_expr(Parser *p) {
    assert(consume(p)->kind == Minus);
    NumericLiteralNode *numeric = parse_numeric_literal(p);

    UnaryExprNode *node = malloc(sizeof(UnaryExprNode));
    node->type = UnaryExpr;
    node->expr = numeric;
    node->op = '-';
    return node;
}
