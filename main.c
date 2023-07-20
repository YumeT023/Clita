#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    char *input = "``"
                  "Raiso a ka soloy 0."
                  "Forony b ho 11 ."
                  "Forony c ho 12."
                  "Forony d ho 13."
                  "Forony e ho 14."
                  "Forony f ho 15."
                  "Forony g ho 750."
                  "Forony h ho 400."
                  "Raiso h ka soloy 15500."
                  "Forony j ho 10."
                  "Forony k ho 10."
                  "Forony l ho 10."
                  "Forony m ho 10."
                  "''";
    Lexer l = create_lexer(input);
    Parser p = create_parser(&l);

    Block *block = parse_block(&p);

    for (int i = 0; i < block->stmt_c; i++) {
        Statement stmt = block->statements[i];
        switch (stmt.type) {
            case SymbolAssignment:
                printf("assignment: %s -> %d\n", stmt.symbolAssignment.identifier->name, stmt.symbolAssignment.val->literalExpr.numericLiteral.value);
                break;
            case SymbolDeclaration:
                printf("declaration: %s -> %d\n", stmt.symbolDeclaration.identifier->name, stmt.symbolDeclaration.init->literalExpr.numericLiteral.value);
                break;
        }
    }

    return 0;
}
