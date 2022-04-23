#include <stdio.h>

#include <aria/vm/opcodes.h>
#include <aria/types/opers.h>
#include <aria/lexer/parser.h>
#include <aria/vm/chunk.h>

int main(int argc, char** argv) {
    aria_chunk chunk;
    aria_chunk_new(&chunk);

    aria_parser parser;
    parser.chunk = &chunk;
    parser.code = "2 + 2 * 2";

    aria_parse(&parser);

#define ARIA_STACK_SIZE 1024

    aria_value stack[ARIA_STACK_SIZE];
    aria_value* sp = stack;
    uint8_t* pc = chunk.program;

    int running = 1;
    while (running) {
        switch (*pc) {
            case ARIA_OPCODE_CONST_8:
                *sp = chunk.constants[pc[1]];
                ++sp; pc += 2;
                break;
            case ARIA_OPCODE_ADD:
                aria_opers_add(sp[-2], sp[-1], sp - 2);
                --sp; ++pc;
                break;
            case ARIA_OPCODE_MUL:
                aria_opers_mul(sp[-2], sp[-1], sp - 2);
                --sp; ++pc;
                break;
            case ARIA_OPCODE_RET:
                running = 0;
                break;
            default:
                printf("Unsupported opcode 0x%X", *pc);
                break;
        }
    }

    if (sp != stack) {
        aria_value_print(sp[-1]);
    }
    return 0;
}
