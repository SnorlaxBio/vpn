/**
 * @file        snorlax/protocol/internet.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       July 29, 2024
 */

#ifndef   __SNORLAX__PROTOCOL_INTERNET__H__
#define   __SNORLAX__PROTOCOL_INTERNET__H__

#include <snorlax.h>
#include <snorlax/protocol.h>

#if       __BYTE_ORDER == __LITTLE_ENDIAN
#define internet_protocol_version_get(datagram)     (datagram[0] >> 4)
#else  // __BYTE_ORDER == __LITTLE_ENDIAN
#define internet_protocol_version_get(datagram)     (datagram[0] & 0x0Fu)
#endif // __BYTE_ORDER == __LITTLE_ENDIAN

struct internet_protocol_module;
struct internet_protocol_module_func;
struct internet_protocol_context;
struct internet_protocol_context_func;

typedef uint8_t internet_protocol_packet_t;

typedef struct internet_protocol_module internet_protocol_module_t;
typedef struct internet_protocol_module_func internet_protocol_module_func_t;
typedef struct internet_protocol_context internet_protocol_context_t;
typedef struct internet_protocol_context_func internet_protocol_context_func_t;

struct internet_protocol_module {
    protocol_module_func_t * func;
    sync_t * sync;
    protocol_module_t * parent;
    protocol_module_map_t * map;
};

struct internet_protocol_module_func {
    internet_protocol_module_t * (*rem)(internet_protocol_module_t *);
    int32_t (*deserialize)(internet_protocol_module_t *, protocol_packet_t *, uint32_t, protocol_context_t *, internet_protocol_context_t **);
    int32_t (*serialize)(internet_protocol_module_t *, protocol_context_t *, internet_protocol_context_t *, protocol_packet_t **, uint32_t *);
    void (*debug)(internet_protocol_module_t *, FILE *, internet_protocol_context_t *);
};

struct internet_protocol_context {

};

struct internet_protocol_context_func {

};

#endif // __SNORLAX__PROTOCOL_INTERNET__H__
