#include <aria/types/opers.h>

#define ARIA_VALUE_OPER_INT(lhs, rhs, op) \
    ((aria_int)(((aria_u64)(lhs)) op ((aria_u64)(rhs))))

#define ARIA_OPER_ARITHM_GENERATE_FUNCTION(name, op)                          \
aria_u8 aria_opers_##name(aria_value lhs, aria_value rhs, aria_value* dst) {  \
    switch (lhs.type) {                                                       \
        case ARIA_VALUE_TYPE_INT:                                             \
            switch (rhs.type) {                                               \
                case ARIA_VALUE_TYPE_INT:                                     \
                    *dst = ARIA_VALUE_INT(                                    \
                        ARIA_VALUE_OPER_INT(lhs.as_int, rhs.as_int, +));      \
                    return ARIA_OPER_STATUS_OK;                               \
                case ARIA_VALUE_TYPE_REAL:                                    \
                    *dst = ARIA_VALUE_REAL(((aria_real)lhs.as_int) +          \
                        rhs.as_real);                                         \
                    return ARIA_OPER_STATUS_OK;                               \
                default:                                                      \
                    return ARIA_OPER_STATUS_UNSUPPORTED;                      \
            }                                                                 \
        case ARIA_VALUE_TYPE_REAL:                                            \
            switch (rhs.type) {                                               \
                case ARIA_VALUE_TYPE_INT:                                     \
                    *dst = ARIA_VALUE_REAL(lhs.as_real +                      \
                        ((aria_real)rhs.as_int));                             \
                    return ARIA_OPER_STATUS_OK;                               \
                case ARIA_VALUE_TYPE_REAL:                                    \
                    *dst = ARIA_VALUE_REAL(lhs.as_real + rhs.as_real);        \
                    return ARIA_OPER_STATUS_OK;                               \
                default:                                                      \
                    return ARIA_OPER_STATUS_UNSUPPORTED;                      \
            }                                                                 \
        default:                                                              \
            return ARIA_OPER_STATUS_UNSUPPORTED;                              \
    }                                                                         \
}

ARIA_OPER_ARITHM_GENERATE_FUNCTION(add, +)
ARIA_OPER_ARITHM_GENERATE_FUNCTION(sub, -)
ARIA_OPER_ARITHM_GENERATE_FUNCTION(mul, *)
ARIA_OPER_ARITHM_GENERATE_FUNCTION(div, /)
