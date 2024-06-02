/**
 * @file        snorlax/bucket.h
 * @brief       
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 2, 2024
 */

#ifndef   __SNORLAX__BUCKET__H__
#define   __SNORLAX__BUCKET__H__

#include <stdint.h>

union snorlax_bucket {
    int8_t i8;
    int16_t i16;
    int32_t i32;
    int64_t i64;
    uint8_t u8;
    uint16_t u16;
    uint32_t u32;
    uint64_t u64;
    void * p;
};

typedef union snorlax_bucket snorlax_bucket_t;

#endif // __SNORLAX__BUCKET__H__
