/**
 * @file        snorlax/list.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 2, 2024
 */

#include "list.h"

extern snorlax_list_t * snorlax_list_gen(uint32_t type) {
    switch(type) {
        case snorlax_list_double_linked:    return snorlax_list_double_linked_gen();
    }
}