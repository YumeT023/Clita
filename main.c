#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    //    char *input = "Forony mpanisa ho 2";
    //    char *input = "20 + 5";
    //    char *input = "20 < 5";
    //    char *input = "Raiso mpanisa kasoloy 5";
    //    char *input = "-600";
    //    char *input = "Marina Diso";

    //    ComparisonExprNode *node = parse_comparison_expr(&p);
    //    printf("<ComparisonExpr>:: %d %s %d", node->left->value, node->op, node->right->value);
    //    UnaryExprNode *node = parse_unary_expr(&p);
    //    printf("<UnaryExpr>:: %c%d", node->op, node->expr->value);
    //    SymbolAssignmentNode *node = parse_symbol_assignment(&p);
    //    printf("<SymbolAssignment>:: %s = %d", node->identifier->name, node->value->value);
    //    BinaryExprNode *node = parse_binary_expr(&p);
    //    printf("<BinaryExpr>:: %d %s %d", node->left->value, node->op, node->right->value);
    //    SymbolDeclarationNode *node = parse_symbol_declaration(&p);
    //    printf("<SymbolDeclaration>:: %s = %d", node->identifier->name, node->initialValue->value);

    char *input = "5 mpanisa -20 5 + 6705 100";
    Lexer l = create_lexer(input);
    Parser p = create_parser(&l);

    Expression *nl5 = parse_expression(&p);
    Expression *sl = parse_expression(&p);
    Expression *u_expr = parse_expression(&p);
    Expression *b_expr = parse_expression(&p);
    Expression *nl100 = parse_expression(&p);

    printf("NumericLiteral: %d\n", nl5->numericLiteral.value);
    printf("SymbolLiteral: %s\n", sl->symbolLiteral.name);
    printf("UnaryExpression: %c%d\n", u_expr->unaryExpr.op, u_expr->unaryExpr.expr->value);
    printf("BinaryExpression: %d %s %d\n", b_expr->binaryExpr.left->value, b_expr->binaryExpr.op, b_expr->binaryExpr.right->value);
    printf("NumericLiteral: %d\n", nl100->numericLiteral.value);

    return 0;
}
