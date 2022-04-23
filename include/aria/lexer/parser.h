#ifndef ARIA_LEXER_PARSER_H
#define ARIA_LEXER_PARSER_H

#include <aria/common.h>
#include <aria/lexer/token.h>

enum {
    ARIA_PASRER_ERROR_UNKNOWN_CHAR,
    ARIA_PARSER_ERROR_UNEXPECTED,
    ARIA_PARSER_ERROR_UNEXPECTED_EOF
};

typedef struct aria_chunk aria_chunk;

typedef struct aria_parser {
    const char* code;
    aria_token token;
    aria_u8 error;
    aria_chunk* chunk;
} aria_parser;

aria_u8 aria_parse(aria_parser* parser);

#endif // ARIA_LEXER_PARSER_H
