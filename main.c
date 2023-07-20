#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    char *input = "Forony ngeza_ve ho diso. Raiso ngeza_ve ka soloy Marina.";
    Lexer l = create_lexer(input);
    Parser p = create_parser(&l);

    printf("========================= (1) =========================\n");

    SymbolDeclarationNode *declaration = parse_symbol_declaration(&p);
    printf("symbol: %s\n", declaration->identifier->name);
    printf("initial_value: %s\n", declaration->init->literalExpr.booleanLiteral.value == 0 ? "False" : "True");

    printf("========================= (2) =========================\n");

    SymbolAssignmentNode *assignment = parse_symbol_assignment(&p);
    printf("symbol: %s\n", assignment->identifier->name);
    printf("new_value: %s\n", assignment->val->literalExpr.booleanLiteral.value == 0 ? "False" : "True");
    return 0;
}
