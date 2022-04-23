#ifndef ARIA_TYPES_OPERS_H
#define ARIA_TYPES_OPERS_H

#include <aria/types/value.h>

#define ARIA_OPER_STATUS_OK 0
#define ARIA_OPER_STATUS_UNSUPPORTED 1

aria_u8 aria_opers_add(aria_value lhs, aria_value rhs, aria_value* dst);
aria_u8 aria_opers_sub(aria_value lhs, aria_value rhs, aria_value* dst);
aria_u8 aria_opers_mul(aria_value lhs, aria_value rhs, aria_value* dst);
aria_u8 aria_opers_div(aria_value lhs, aria_value rhs, aria_value* dst);

#endif // ARIA_TYPES_OPERS_H
