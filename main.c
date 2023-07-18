#include "lexer.h"
#include "parser.h"
#include <stdio.h>

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

    char *input = "2 * 50 + 8 * 200";
    Lexer l = create_lexer(input);
    Parser p = create_parser(&l);

    Expression *expr = parse_expression(&p);

    BinaryExprNode *expr1 = &expr->binaryExpr;
    BinaryExprNode *expr2 = &expr->binaryExpr.right->binaryExpr;
    BinaryExprNode *expr3 = &expr->binaryExpr.right->binaryExpr.right->binaryExpr;

    printf("> %d %s %d\n", expr1->left->value, expr1->op, expr2->left->value);
    printf("> %d %s %d\n", expr2->left->value, expr2->op, expr3->left->value);
    printf("> %d %s %d\n", expr3->left->value, expr3->op, expr3->right->numericLiteral.value);

    return 0;
}
