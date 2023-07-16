#include "parser.h"

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

    ProgramNode node = parse("Raiso mpanisa kasoloy 105000");
    return 0;
}
