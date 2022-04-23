#include <stdio.h>

#include <aria/vm/opcodes.h>
#include <aria/types/opers.h>

int main(int argc, char** argv) {

    aria_value constants[] = {
        ARIA_VALUE_REAL(2)
    };

    uint8_t program[] = {
        ARIA_OPCODE_CONST_8, 0,
        ARIA_OPCODE_CONST_8, 0,
        ARIA_OPCODE_MUL,
        ARIA_OPCODE_CONST_8, 0,
        ARIA_OPCODE_ADD,
        ARIA_OPCODE_RET,
    };

#define ARIA_STACK_SIZE 1024

    aria_value stack[ARIA_STACK_SIZE];
    aria_value* sp = stack;
    uint8_t* pc = program;

    int running = 1;
    while (running) {
        switch (*pc) {
            case ARIA_OPCODE_CONST_8:
                *sp = constants[pc[1]];
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
