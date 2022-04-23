#include <aria/types/value.h>

#include <stdio.h>
#include <assert.h>

void aria_value_print(aria_value value) {
    switch (value.type) {
        case ARIA_VALUE_TYPE_INT:
            printf("%ld", (long int)value.as_int);
            break;
        case ARIA_VALUE_TYPE_REAL:
            printf("%g", (double)value.as_real);
            break;
        default:
            assert(0);
            break;
    }
}
