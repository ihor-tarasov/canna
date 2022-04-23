#ifndef ARIA_LEXER_TOKEN_H
#define ARIA_LEXER_TOKEN_H

#include <aria/common.h>

enum {
    ARIA_TOKEN_TYPE_INT,
    ARIA_TOKEN_TYPE_REAL,
    ARIA_TOKEN_TYPE_UNKNOWN,
    ARIA_TOKEN_TYPE_PLUS,          // +
    ARIA_TOKEN_TYPE_ASTERISK,      // *
    ARIA_TOKEN_TYPE_EOF,
};

typedef struct aria_token_info {
    const char* begin;
    const char* end;
} aria_token_info;

typedef struct aria_token {
    aria_u8 type;
    aria_token_info info;
} aria_token;

const char* aria_lexer(aria_token* token, const char* code);

#endif // ARIA_LEXER_TOKEN_H
