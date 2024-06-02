/**
 * @file        snorlax/eva/type.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 2, 2024
 */

#ifndef   __SNORLAX__EVA_TYPE__H__
#define   __SNORLAX__EVA_TYPE__H__

#define snorlax_eva_engine_type_epoll           1

#define snorlax_eva_event_type_none             (0x00000000u)

#define snorlax_eva_event_type_open             (0x00000001u << 0u)
#define snorlax_eva_event_type_read             (0x00000001u << 1u)
#define snorlax_eva_event_type_write            (0x00000001u << 2u)
#define snorlax_eva_event_type_close            (0x00000001u << 3u)
#define snorlax_eva_event_type_exception        (0x00000001u << 4u)
#define snorlax_eva_event_type_time             (0x00000001u << 5u)

#endif // __SNORLAX__EVA_TYPE__H__
