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
    char *input = "Marina Diso";
    Lexer l = create_lexer(input);

    Parser p = create_parser(10);
    Token *t = lex(&l);

    while (t->kind != Eof) {
        p.tokens[p.tokens_len] = *t;
        p.tokens_len++;
        print_token(t);
        t = lex(&l);
    }

    //    UnaryExprNode *node = parse_unary_expr(&p);
    //    printf("<UnaryExpr>:: %c%d", node->op, node->expr->value);
    //    SymbolAssignmentNode *node = parse_symbol_assignment(&p);
    //    printf("<SymbolAssignment>:: %s = %d", node->identifier->name, node->value->value);
    //    BinaryExprNode *node = parse_binary_expr(&p);
    //    printf("<BinaryExpr>:: %d %s %d", node->left->value, node->op, node->right->value);
    //    SymbolDeclarationNode *node = parse_symbol_declaration(&p);
    //    printf("<SymbolDeclaration>:: %s = %d", node->identifier->name, node->initialValue->value);

    //    free(node->left);
    //    free(node->right);
    //    free(node);
    free(p.tokens);
    free(t);
    return 0;
}
