#include <aria/lexer/parser.h>
#include <aria/types/value.h>
#include <aria/vm/opcodes.h>

#define ARIA_PARSER_NEXT(p) (p)->code = aria_lexer(&(p)->token, (p)->code)

static aria_u8 aria_parse_primary(aria_parser* parser) {
    aria_token_info info = parser->token.info;
    switch (parser->token.type) {
        case ARIA_TOKEN_TYPE_INT: {
            aria_value value = ARIA_VALUE_INT(atoi(info.begin));
            aria_chunk_opcode_const(parser->chunk, value, info);
            break;
        }
        case ARIA_TOKEN_TYPE_REAL: {
            aria_value value = ARIA_VALUE_REAL(atof(info.begin));
            aria_chunk_opcode_const(parser->chunk, value, info);
            break;
        }
        case ARIA_TOKEN_TYPE_UNKNOWN:
            parser->error = ARIA_PASRER_ERROR_UNKNOWN_CHAR;
            return ARIA_STATUS_ERR;
        case ARIA_TOKEN_TYPE_EOF:
            parser->error = ARIA_PARSER_ERROR_UNEXPECTED_EOF;
            return ARIA_STATUS_ERR;
        default:
            parser->error = ARIA_PARSER_ERROR_UNEXPECTED;
            return ARIA_STATUS_ERR;
    }
    ARIA_PARSER_NEXT(parser);
    return ARIA_STATUS_OK;
}

static aria_u8 aria_parse_factor(aria_parser* parser) {
    ARIA_CHECK(aria_parse_primary(parser));
    while (true) {
        switch (parser->token.type) {
            case ARIA_TOKEN_TYPE_ASTERISK: {
                aria_token_info info = parser->token.info;
                ARIA_PARSER_NEXT(parser);
                ARIA_CHECK(aria_parse_primary(parser));
                ARIA_CHECK(aria_chunk_opcode(parser->chunk, ARIA_OPCODE_MUL, info));
                break;
            }
            default:
                return ARIA_STATUS_OK;
        }
    }
}

static aria_u8 aria_parse_term(aria_parser* parser) {
    ARIA_CHECK(aria_parse_factor(parser));
    while (true) {
        switch (parser->token.type) {
            case ARIA_TOKEN_TYPE_PLUS: {
                aria_token_info info = parser->token.info;
                ARIA_PARSER_NEXT(parser);
                ARIA_CHECK(aria_parse_factor(parser));
                ARIA_CHECK(aria_chunk_opcode(parser->chunk, ARIA_OPCODE_ADD, info));
                break;
            }
            default:
                return ARIA_STATUS_OK;
        }
    }
}

aria_u8 aria_parse(aria_parser* parser) {
    ARIA_PARSER_NEXT(parser);
    if (parser->token.type != ARIA_TOKEN_TYPE_EOF) {
        ARIA_CHECK(aria_parse_term(parser));
    }
    switch (parser->token.type) {
        case ARIA_TOKEN_TYPE_EOF:
            aria_chunk_opcode(parser->chunk, ARIA_OPCODE_RET, parser->token.info);
            return ARIA_STATUS_OK;
        case ARIA_TOKEN_TYPE_UNKNOWN:
            parser->error = ARIA_PASRER_ERROR_UNKNOWN_CHAR;
            return ARIA_STATUS_ERR;
        default:
            parser->error = ARIA_PARSER_ERROR_UNEXPECTED;
            return ARIA_STATUS_ERR;
    }
}
