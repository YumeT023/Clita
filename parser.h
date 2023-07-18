#ifndef CLITA_PARSER_H
#define CLITA_PARSER_H

#include "lexer.h"

typedef enum {
    Program,
    SymbolDeclaration,
    SymbolAssignment,
    SymbolLiteral,
    NumericLiteral,
    BinaryExpr,    // kajy
    ComparisonExpr,// vina
    UnaryExpr,
    Pragma
} NodeType;

typedef struct {
    NodeType type;
    char *name;
} SymbolLiteralNode;

typedef struct {
    NodeType type;
    int value;
} NumericLiteralNode;

typedef struct Expression Expression;
typedef struct BinaryExprNode BinaryExprNode;
// TODO: should also support symbolLiteral as its operand
struct BinaryExprNode {
    NodeType type;
    NumericLiteralNode *left;
    char *op;// + , - , * , /
    Expression *right;
};

typedef struct {
    NodeType type;
    NumericLiteralNode *left;
    char *op;// <, <=, >, >=, =
    NumericLiteralNode *right;
} ComparisonExprNode;

// TODO: should support symbol_literal_node and add pre/post(increment)
typedef struct {
    NodeType type;
    char *op;// '-', '--', '++'
    NumericLiteralNode *expr;
} UnaryExprNode;

typedef struct {
    NodeType type;
    SymbolLiteralNode *identifier;
    NumericLiteralNode *initialValue;
} SymbolDeclarationNode;

typedef struct {
    NodeType type;
    SymbolLiteralNode *identifier;
    NumericLiteralNode *value;
} SymbolAssignmentNode;

typedef struct {
    NodeType type;
    char *name;
    NumericLiteralNode *argument;
} PragmaNode;

struct Expression {
    NodeType type;
    union {
        SymbolLiteralNode symbolLiteral;
        NumericLiteralNode numericLiteral;
        BinaryExprNode binaryExpr;
        UnaryExprNode unaryExpr;
    };
};

typedef struct {
    NodeType type;
} ProgramNode;

typedef struct {
    Token *tokens;
    size_t tokens_len;
    size_t pos;
} Parser;

Parser create_parser(Lexer *l);

Token *consume(Parser *p);
Token *p_peek(Parser *p);

/**
 * (Backtracking)
 * look forward nth token.
 * Primarily used to test different rules of a same production.
 *
 * When analyzing data such as "2 + 3", it is important to search for a possible token after the `numeric` when trying to determine its meaning.
 * we should parse a `BinaryExpression` if it's an operator token, else a `NumericLiteral`
 */
Token *look_ahead(Parser *p, size_t n);

// TODO: Node printer

SymbolDeclarationNode *parse_symbol_declaration(Parser *p);
SymbolAssignmentNode *parse_symbol_assignment(Parser *p);
SymbolLiteralNode *parse_symbol_literal(Parser *p);
NumericLiteralNode *parse_numeric_literal(Parser *p);
BinaryExprNode *parse_binary_expr(Parser *p);
ComparisonExprNode *parse_comparison_expr(Parser *p);
UnaryExprNode *parse_unary_expr(Parser *p);
PragmaNode *parse_pragma(Parser *p);
Expression *parse_expression(Parser *p);
ProgramNode parse(char *source_text);

#endif//CLITA_PARSER_H
