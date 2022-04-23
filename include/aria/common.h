#ifndef ARIA_COMMON_H
#define ARIA_COMMON_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint8_t aria_u8;
typedef uint64_t aria_u64;
typedef int64_t aria_i64;
typedef double aria_f64;
typedef size_t aria_usize;

#define ARIA_STATUS_OK 0
#define ARIA_STATUS_ERR 1
#define ARIA_CHECK(s) \
    do { if ((s) == ARIA_STATUS_ERR) { return ARIA_STATUS_ERR; } } while(0)

#endif // ARIA_COMMON_H
