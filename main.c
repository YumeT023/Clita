#include "lexer.h"
#include "parser.h"
#include <stdio.h>

int main() {
    char *input = "";
    Lexer l = create_lexer(input);
    Parser p = create_parser(&l);
    return 0;
}
