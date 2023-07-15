#include "lexer.h"
#include <stdlib.h>

int main() {
    char *input = "ISA AMPIDIRINA: 5.\n"
                  "\n"
                  "BAIKO:\n"
                  "Forony lehibe_indrindra ho fidirana_faha[1].\n"
                  "Forony mpanisa ho 2.\n"
                  "Ataovy\n"
                  "  ``Raha fidirana_faha[mpanisa] > lehibe_indrindra dia\n"
                  "      raiso lehibe_indrindra kasoloy fidirana_faha[mpanisa].\n"
                  "    Raiso mpanisa kasoloy mpanisa + 1.\n"
                  "  ''\n"
                  "rambola mpanisa <= isa_nampidirina.\n"
                  "\n"
                  "ISA AVOAKA: lehibe_indrindra.";

    Lexer l = create_lexer(input);

    Token *t = lex(&l);
    while (t->kind != Eof) {
        print_token(t);
        t = lex(&l);
    }
    free(t);
    return 0;
}
