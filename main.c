#include "lexer.h"
#include "parser.h"
#include <stdio.h>

int main() {
    char *input = "Forony mpanisa ho tsy_aiko.";
    Lexer l = create_lexer(input);
    Parser p = create_parser(&l);

    SymbolAssignmentNode *node = parse_symbol_declaration(&p);
    printf("symbol: %s\n", node->identifier->name);
    printf("newvalue: %s", node->val->literalExpr.symbolLiteral.name);
    return 0;
}
