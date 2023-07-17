#include "parser.h"
#include "lexer.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Parser create_parser(Lexer *l) {
    Token *t = lex(l);
    Parser p = {
            .tokens = t,
            .tokens_len = l->scanned_tc,
            .pos = 0};
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

ProgramNode parse(char *source_text) {
    Lexer l = create_lexer(source_text);
    Token *tokens = lex(&l);

    size_t i = 0;
    while (tokens[i].kind != Eof) {
        print_token(&tokens[i]);
        i++;
    }
    ProgramNode node;
    node.type = Program;
    return node;
}

// TODO: parse fn for the original pragma syntax
PragmaNode *parse_pragma(Parser *p) {
    PragmaNode *node = malloc(sizeof(PragmaNode));

    if (node == NULL) {
        report_error("Failed to allocate memory for pragma definition");
    }
    node->name = parse_symbol_literal(p)->name;

    if (consume(p)->kind != Colon) {
        report_error("Expected a 'Colon' in pragma definition");
    }

    node->argument = parse_numeric_literal(p);
    return node;
}

SymbolDeclarationNode *parse_symbol_declaration(Parser *p) {
    if (consume(p)->kind != Forony) {
        report_error("Expected 'Forony' in symbol declaration");
    }
    SymbolLiteralNode *symbol = parse_symbol_literal(p);

    if (consume(p)->kind != Ho) {
        report_error("Expected 'Ho' in symbol declaration");
    }

    NumericLiteralNode *numeric = parse_numeric_literal(p);

    SymbolDeclarationNode *node = malloc(sizeof(SymbolDeclarationNode));
    if (node == NULL) {
        report_error("Failed to allocate memory for symbol declaration");
    }

    node->type = SymbolDeclaration;
    node->identifier = symbol;
    node->initialValue = numeric;
    return node;
}

SymbolAssignmentNode *parse_symbol_assignment(Parser *p) {
    if (consume(p)->kind != Raiso) {
        report_error("Expected 'Raiso' in symbol assignment");
    }
    SymbolLiteralNode *symbol = parse_symbol_literal(p);

    if (consume(p)->kind != Kasoloy) {
        report_error("Expected 'Kasoloy' in symbol assignment");
    }

    NumericLiteralNode *numeric = parse_numeric_literal(p);

    SymbolAssignmentNode *node = malloc(sizeof(SymbolAssignmentNode));
    if (node == NULL) {
        report_error("Failed to allocate memory for symbol assignment");
    }

    node->type = SymbolAssignment;
    node->identifier = symbol;
    node->value = numeric;
    return node;
}

SymbolLiteralNode *parse_symbol_literal(Parser *p) {
    Token *t = consume(p);

    if (t->kind != Symbol) {
        report_error("Expected symbol literal");
    }

    SymbolLiteralNode *node = malloc(sizeof(SymbolLiteralNode));
    if (node == NULL) {
        report_error("Failed to allocate memory for symbol literal");
    }

    node->type = SymbolLiteral;
    node->name = strdup(t->text);
    return node;
}

NumericLiteralNode *parse_numeric_literal(Parser *p) {
    Token *t = consume(p);

    if (t->kind != Numeric) {
        report_error("Expected numeric literal");
    }

    NumericLiteralNode *node = malloc(sizeof(NumericLiteralNode));
    if (node == NULL) {
        report_error("Failed to allocate memory for numeric literal");
    }

    node->type = NumericLiteral;
    node->value = strtol(t->text, NULL, 10);
    return node;
}

BinaryExprNode *parse_binary_expr(Parser *p) {
    NumericLiteralNode *left = parse_numeric_literal(p);

    Token *op = consume(p);
    TokenKind kind = op->kind;
    if (kind != Plus && kind != Minus && kind != Times && kind != Division) {
        report_error("Expected binary operator (+, -, *, /)");
    }

    NumericLiteralNode *right = parse_numeric_literal(p);

    BinaryExprNode *node = malloc(sizeof(BinaryExprNode));
    if (node == NULL) {
        report_error("Failed to allocate memory for binary expression");
    }

    node->type = BinaryExpr;
    node->left = left;
    node->right = right;
    node->op = strdup(op->text);
    return node;
}

ComparisonExprNode *parse_comparison_expr(Parser *p) {
    NumericLiteralNode *left = parse_numeric_literal(p);

    Token *op = consume(p);
    TokenKind kind = op->kind;
    if (kind != Equals && kind != Gt && kind != Gte && kind != Lt && kind != Lte) {
        report_error("Expected comparison operator (=, >, >=, <, <=)");
    }

    NumericLiteralNode *right = parse_numeric_literal(p);

    ComparisonExprNode *node = malloc(sizeof(ComparisonExprNode));
    if (node == NULL) {
        report_error("Failed to allocate memory for comparison expression");
    }

    node->type = ComparisonExpr;
    node->left = left;
    node->right = right;
    node->op = strdup(op->text);
    return node;
}

UnaryExprNode *parse_unary_expr(Parser *p) {
    if (consume(p)->kind != Minus) {
        report_error("Expected unary operator (-)");
    }
    NumericLiteralNode *numeric = parse_numeric_literal(p);

    UnaryExprNode *node = malloc(sizeof(UnaryExprNode));
    if (node == NULL) {
        report_error("Failed to allocate memory for unary expression");
    }
    node->type = UnaryExpr;
    node->expr = numeric;
    node->op = '-';
    return node;
}
