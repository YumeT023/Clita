#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>


void fn(int *table);

int main() {
    char *input = "Forony mpanisa ho 2";
    Lexer l = create_lexer(input);

    Parser p = create_parser(10);
    Token *t = lex(&l);

    while (t->kind != Eof) {
        p.tokens[p.tokens_len] = *t;
        p.tokens_len++;
        t = lex(&l);
    }

    SymbolDeclarationNode *node = parse_symbol_declaration(&p);
    printf("<SymbolDeclaration>::%s = %d", node->identifier->name, node->initialValue->value);

    free(node->initialValue);
    free(node->identifier);
    free(node);
    free(p.tokens);
    free(t);
    return 0;
}
