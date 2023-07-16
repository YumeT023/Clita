#ifndef CLITA_PARSER_H
#define CLITA_PARSER_H

#include "lexer.h"

typedef enum {
    SymbolDeclaration,
    SymbolLiteral,
    NumericLiteral,
} NodeType;

typedef struct {
    NodeType type;
    char *name;
} SymbolLiteralNode;


typedef struct {
    NodeType type;
    int value;
} NumericLiteralNode;

typedef union {
    SymbolLiteralNode symbolLiteralNode;
    NumericLiteralNode numericLiteralNode;
} Expression;

typedef struct {
    NodeType type;
    SymbolLiteralNode *identifier;
    NumericLiteralNode *initialValue;
} SymbolDeclarationNode;

typedef struct {
    Token *tokens;
    size_t tokens_len;
    size_t pos;
} Parser;

Parser create_parser(size_t initial_capacity);

Token *consume(Parser *p);
Token *p_peek(Parser *p);

SymbolDeclarationNode *parse_symbol_declaration(Parser *p);
SymbolLiteralNode *parse_symbol_literal(Parser *p);
NumericLiteralNode *parse_numeric_literal(Parser *p);

#endif//CLITA_PARSER_H
