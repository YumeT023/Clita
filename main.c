#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    char *input = "``"
                  "Forony a ho 0."
                  "Forony b ho 11 ."
                  "Forony c ho 12."
                  "Forony d ho 13."
                  "Forony e ho 14."
                  "Forony f ho 15."
                  "Forony g ho 750."
                  "Forony h ho 400."
                  "Forony i ho 15500."
                  "Forony j ho 10."
                  "Forony k ho 10."
                  "Forony l ho 10."
                  "Forony m ho 10."
                  "''";
    Lexer l = create_lexer(input);
    Parser p = create_parser(&l);

    Block *block = parse_block(&p);

    for (int i = 0; i < block->stmt_c; i++) {
        SymbolDeclarationNode dl = block->statements[i].symbolDeclaration;
        printf("symbol: %s -> %d\n", dl.identifier->name, dl.init->literalExpr.numericLiteral.value);
    }

    return 0;
}
