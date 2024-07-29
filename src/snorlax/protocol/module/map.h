/**
 * @file        snorlax/protocol/module/map.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       July 29, 2024
 */

#ifndef   __SNORLAX__PROTOCOL_MODULE_MAP__H__
#define   __SNORLAX__PROTOCOL_MODULE_MAP__H__

#include <snorlax.h>

struct protocol_module;
struct protocol_module_map;
struct protocol_module_map_func;

typedef struct protocol_module protocol_module_t;
typedef struct protocol_module_map protocol_module_map_t;
typedef struct protocol_module_map_func protocol_module_map_func_t;

typedef uint32_t (*protocol_module_map_index_t)(uint32_t);

struct protocol_module_map {
    protocol_module_map_func_t * func;
    sync_t * sync;
    uint64_t size;
    protocol_module_t ** modules;
    protocol_module_map_index_t index;
};

extern protocol_module_map_t * protocol_module_map_gen(protocol_module_t ** modules, uint64_t n, protocol_module_map_index_t index);

struct protocol_module_map_func {
    protocol_module_map_t * (*rem)(protocol_module_map_t *);
    protocol_module_t * (*get)(protocol_module_map_t *, uint32_t);
};

#define protocol_module_map_rem(map)                    ((map) ? (map)->func->rem(map) : nil)
#define protocol_module_map_get(map, no)                ((map) ? (map)->func->get(map, no) : nil)

#endif // __SNORLAX__PROTOCOL_MODULE_MAP__H__
