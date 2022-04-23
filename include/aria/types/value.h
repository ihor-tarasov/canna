#ifndef ARIA_TYPES_VALUE_H
#define ARIA_TYPES_VALUE_H

#include <aria/common.h>

#define ARIA_VALUE_TYPE_INT  0
#define ARIA_VALUE_TYPE_REAL 1

typedef aria_i64 aria_int;
typedef aria_f64 aria_real;

typedef struct aria_value {
    uint8_t type;

    union {
        aria_int  as_int;
        aria_real as_real;
    };
} aria_value;

void aria_value_print(aria_value value);

#define ARIA_VALUE_INT(value) \
    ((aria_value){.type = ARIA_VALUE_TYPE_INT, .as_int = (value)})
#define ARIA_VALUE_REAL(value) \
    ((aria_value){.type = ARIA_VALUE_TYPE_REAL, .as_real = (value)})

#endif // ARIA_TYPES_VALUE_H
