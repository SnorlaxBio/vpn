/**
 * @file        snorlax/event/type.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 5, 2024
 */

#ifndef   __SNORLAX__EVENT_TYPE__H__
#define   __SNORLAX__EVENT_TYPE__H__

#define snorlax_event_command           (0x00000001u <<  0u)
#define snorlax_event_io                (0x00000001u <<  1u)
#define snorlax_event_time              (0x00000001u <<  2u)

// #define snorlax_event_category_io       (0x00000001u <<  0u)
// #define snorlax_event_type_send         0       /**!< 바로 수행된다. */
// #define snorlax_event_type_post         1       /**!< 단순한 이벤트로 큐에 삽입된다. */

#endif // __SNORLAX__EVENT_TYPE__H__
