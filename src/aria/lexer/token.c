#include <aria/lexer/token.h>

#define IS_DIGIT(c) ((c) >= '0' && (c) <= '9')

const char* aria_lexer(aria_token* token, const char* code) {
    char c = *code;
    
    while (c == ' ' || c == '\t' || c == '\n') {
        c = *(++code);
    }

    token->info.begin = code;

    if (IS_DIGIT(c)) {
        bool has_dot = false;
        while (IS_DIGIT(c) || c == '.') {
            if (c == '.') {
                if (has_dot) {
                    break;
                } else {
                    has_dot = true;
                }
            }
            c = *(++code);
        }
        token->info.end = code;
        token->type = has_dot ? ARIA_TOKEN_TYPE_REAL : ARIA_TOKEN_TYPE_INT;
        return code;
    }

    switch (c) {
        case '+': token->type = ARIA_TOKEN_TYPE_PLUS; break;
        case '*': token->type = ARIA_TOKEN_TYPE_ASTERISK; break;
        case '\0':
            token->type = ARIA_TOKEN_TYPE_EOF;
            token->info.end = code;
            return code;
        default:
            token->type = ARIA_TOKEN_TYPE_UNKNOWN;
            token->info.end = code;
            return code;
    }

    ++code;
    token->info.end = code;
    return code;
}
