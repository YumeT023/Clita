#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>


int main() {
    //    char *input = "Forony mpanisa ho 2";
    //    char *input = "20 + 5";
    char *input = "Raiso mpanisa kasoloy 5";
    Lexer l = create_lexer(input);

    Parser p = create_parser(10);
    Token *t = lex(&l);

    while (t->kind != Eof) {
        p.tokens[p.tokens_len] = *t;
        p.tokens_len++;
        t = lex(&l);
    }

    SymbolAssignmentNode *node = parse_symbol_assignment(&p);
    printf("<SymbolAssignment>:: %s = %d", node->identifier->name, node->value->value);
    //    BinaryExprNode *node = parse_binary_expr(&p);
    //    printf("<BinaryExpr>:: %d %c %d", node->left->value, node->op, node->right->value);
    //    SymbolDeclarationNode *node = parse_symbol_declaration(&p);
    //    printf("<SymbolDeclaration>:: %s = %d", node->identifier->name, node->initialValue->value);

    free(node->value);
    free(node->identifier);
    free(node);
    free(p.tokens);
    free(t);
    return 0;
}
