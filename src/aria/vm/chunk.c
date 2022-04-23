#include <aria/vm/chunk.h>
#include <aria/vm/opcodes.h>

#include <stdlib.h>
#include <string.h>

void aria_chunk_new(aria_chunk* dst) {
    memset(dst, 0, sizeof(aria_chunk));
}

void aria_chunk_free(aria_chunk* dst) {
    free(dst->constants);
    free(dst->program);
    free(dst->tokens);
    aria_chunk_new(dst);
}

static aria_u8 aria_chunk_constant_realloc(aria_chunk* dst) {
    aria_usize new_capacity = dst->constants_capacity * 2 + 8;
    aria_value* new_constants = malloc(new_capacity * sizeof(aria_value));
    if (new_constants == NULL) {
        return ARIA_STATUS_ERR;
    }
    memcpy(new_constants, dst->constants, dst->constants_count * sizeof(aria_value));
    free(dst->constants);
    dst->constants = new_constants;
    dst->constants_capacity = new_capacity;
    return ARIA_STATUS_OK;
}

aria_u8 aria_chunk_constant(aria_chunk* dst, aria_value value, aria_usize* index) {
    if (dst->constants_capacity == dst->constants_count) {
        ARIA_CHECK(aria_chunk_constant_realloc(dst));
    }

    *index = dst->constants_count;
    dst->constants[dst->constants_count++] = value;
    return ARIA_STATUS_OK;
}

static aria_u8 aria_chunk_opcode_realloc(aria_chunk* dst) {
    aria_usize new_capacity = dst->program_capacity * 2 + 8;
    aria_u8* new_program = malloc(new_capacity * sizeof(aria_u8));
    if (new_program == NULL) {
        return ARIA_STATUS_ERR;
    }
    aria_token_info* new_tokens = malloc(new_capacity * sizeof(aria_token_info));
    if (new_tokens == NULL) {
        free(new_program);
        return ARIA_STATUS_ERR;
    }
    memcpy(new_program, dst->program, dst->program_count * sizeof(aria_u8));
    free(dst->program);
    memcpy(new_tokens, dst->tokens, dst->program_count * sizeof(aria_token_info));
    free(dst->tokens);
    dst->program_capacity = new_capacity;
    dst->program = new_program;
    dst->tokens = new_tokens;
    return ARIA_STATUS_OK;
}

aria_u8 aria_chunk_opcode(aria_chunk* dst, aria_u8 opcode, aria_token_info info) {
    if (dst->program_capacity == dst->program_count) {
        ARIA_CHECK(aria_chunk_opcode_realloc(dst));
    }

    dst->program[dst->program_count] = opcode;
    dst->tokens[dst->program_count++] = info;
    return ARIA_STATUS_OK;
}

aria_u8 aria_chunk_opcode_const(aria_chunk* chunk, aria_value value, aria_token_info info) {
    aria_usize index;
    ARIA_CHECK(aria_chunk_constant(chunk, value, &index));
    if (index < 256) {
        ARIA_CHECK(aria_chunk_opcode(chunk, ARIA_OPCODE_CONST_8, info));
        ARIA_CHECK(aria_chunk_opcode(chunk, (aria_u8)index, info));
        return ARIA_STATUS_OK;
    } else {
        return ARIA_STATUS_ERR;
    }
}
