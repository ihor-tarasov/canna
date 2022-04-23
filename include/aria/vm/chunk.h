#ifndef ARIA_VM_CHUNK_H
#define ARIA_VM_CHUNK_H

#include <aria/common.h>
#include <aria/types/value.h>
#include <aria/lexer/token.h>

typedef struct aria_chunk {
    aria_value* constants;
    aria_u8* program;
    aria_token_info* tokens;
    aria_usize constants_count;
    aria_usize program_count;
    aria_usize constants_capacity;
    aria_usize program_capacity;
} aria_chunk;

void aria_chunk_new(aria_chunk* dst);
void aria_chunk_free(aria_chunk* dst);
aria_u8 aria_chunk_constant(aria_chunk* dst, aria_value value, aria_usize* index);
aria_u8 aria_chunk_opcode(aria_chunk* dst, aria_u8 opcode, aria_token_info info);
aria_u8 aria_chunk_opcode_const(aria_chunk* chunk, aria_value value, aria_token_info info);

#endif // ARIA_VM_CHUNK_H
