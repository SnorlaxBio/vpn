/**
 * @file        snorlax/event/handler/array.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 10, 2024
 */

#include <stdlib.h>
#include <string.h>

#include "array.h"

extern event_handler_array_t * event_handler_array_gen(void) {
    event_handler_array_t * array = (event_handler_array_t *) calloc(1, sizeof(event_handler_array_t));

    return array;
}

extern event_handler_array_t * event_handler_array_rem(event_handler_array_t * array) {
    if(array->func) free(array->func);
    free(array);
    
    return nil;
}

extern void event_handler_array_set(event_handler_array_t * array, event_handler_t * func, uint32_t index) {
    if(array->size <= index) {
        uint32_t n = array->size;
        array->func = realloc(array->func, sizeof(event_handler_t) * (index + 1));
        memset(&array->func[n], 0, sizeof(event_handler_t) * (index + 1 - n));
        array->size = index + 1;
    }
    array->func[index] = func;
}