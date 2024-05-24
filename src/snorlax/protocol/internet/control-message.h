/**
 * @file        snorlax/protocol/internet/control-message.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       May 24, 2024
 */

#ifndef   __SNORLAX__PROTOCOL_INTERNET_CONTROL_MESSAGE__H__
#define   __SNORLAX__PROTOCOL_INTERNET_CONTROL_MESSAGE__H__

#include <stdio.h>
#include <stdint.h>

#include <snorlax/protocol.h>
#include <snorlax/protocol/internet.h>

#define snorlax_protocol_internet_control_message_type_echo_req                     8
#define snorlax_protocol_internet_control_message_type_echo_res                     0
#define snorlax_protocol_internet_control_message_type_destination_unreachable      3
#define snorlax_protocol_internet_control_message_type_source_quench                4
#define snorlax_protocol_internet_control_message_type_redirect                     5
#define snorlax_protocol_internet_control_message_type_time_exceeded                11
#define snorlax_protocol_internet_control_message_type_parameter_problem            12
#define snorlax_protocol_internet_control_message_type_timestamp_req                13
#define snorlax_protocol_internet_control_message_type_timestamp_res                14
#define snorlax_protocol_internet_control_message_type_information_req              15
#define snorlax_protocol_internet_control_message_type_information_res              16

struct snorlax_protocol_internet_control_message {
    uint8_t  type;
    uint8_t  code;
    uint16_t checksum;
};

struct snorlax_protocol_internet_control_message_destination_unreachable {
    uint8_t  type;
    uint8_t  code;
    uint16_t checksum;
    uint32_t unused;
};

struct snorlax_protocol_internet_control_message_time_exceeded {
    uint8_t  type;
    uint8_t  code;
    uint16_t checksum;
    uint32_t unused;
};

struct snorlax_protocol_internet_control_message_parameter_problem {
    uint8_t  type;
    uint8_t  code;
    uint16_t checksum;
    uint8_t  pointer;
    uint8_t  unused[3];
};

struct snorlax_protocol_internet_control_message_source_quench {
    uint8_t  type;
    uint8_t  code;
    uint16_t checksum;
    uint32_t unused;
};

struct snorlax_protocol_internet_control_message_redirect {
    uint8_t  type;
    uint8_t  code;
    uint16_t checksum;
    uint32_t address;
};

struct snorlax_protocol_internet_control_message_echo {
    uint8_t  type;
    uint8_t  code;
    uint16_t checksum;
    uint16_t identifier;
    uint16_t sequence;
};

struct snorlax_protocol_internet_control_message_timestamp {
    uint8_t  type;
    uint8_t  code;
    uint16_t checksum;
    uint16_t identifier;
    uint16_t sequence;
    struct {
        uint32_t originate;
        uint32_t receive;
        uint32_t transmit;
    } timestamp;
};

struct snorlax_protocol_internet_control_message_information {
    uint8_t  type;
    uint8_t  code;
    uint16_t checksum;
    uint16_t identifier;
    uint16_t sequence;
};


typedef struct snorlax_protocol_internet_control_message snorlax_protocol_internet_control_message_t;

typedef struct snorlax_protocol_internet_control_message_destination_unreachable snorlax_protocol_internet_control_message_destination_unreachable_t;
typedef struct snorlax_protocol_internet_control_message_time_exceeded snorlax_protocol_internet_control_message_time_exceeded_t;
typedef struct snorlax_protocol_internet_control_message_parameter_problem snorlax_protocol_internet_control_message_parameter_problem_t;
typedef struct snorlax_protocol_internet_control_message_source_quench snorlax_protocol_internet_control_message_source_quench_t;
typedef struct snorlax_protocol_internet_control_message_redirect snorlax_protocol_internet_control_message_redirect_t;
typedef struct snorlax_protocol_internet_control_message_echo snorlax_protocol_internet_control_message_echo_t;
typedef struct snorlax_protocol_internet_control_message_timestamp snorlax_protocol_internet_control_message_timestamp_t;
typedef struct snorlax_protocol_internet_control_message_information snorlax_protocol_internet_control_message_information_t;

#ifdef    SNORLAX_DEBUG
extern void snorlax_protocol_internet_control_message_debug(FILE * stream, const snorlax_protocol_internet_t internet, const uint8_t * segment);
extern void snorlax_protocol_internet_control_message_destination_unreachable_debug(FILE * stream, const snorlax_protocol_internet_t internet, const uint8_t * segment);
extern void snorlax_protocol_internet_control_message_time_exceeded_debug(FILE * stream, const snorlax_protocol_internet_t internet, const uint8_t * segment);
extern void snorlax_protocol_internet_control_message_parameter_problem_debug(FILE * stream, const snorlax_protocol_internet_t internet, const uint8_t * segment);
extern void snorlax_protocol_internet_control_message_source_quench_debug(FILE * stream, const snorlax_protocol_internet_t internet, const uint8_t * segment);
extern void snorlax_protocol_internet_control_message_redirect_debug(FILE * stream, const snorlax_protocol_internet_t internet, const uint8_t * segment);
extern void snorlax_protocol_internet_control_message_echo_debug(FILE * stream, const snorlax_protocol_internet_t internet, const uint8_t * segment);
extern void snorlax_protocol_internet_control_message_timestamp_debug(FILE * stream, const snorlax_protocol_internet_t internet, const uint8_t * segment);
extern void snorlax_protocol_internet_control_message_information_debug(FILE * stream, const snorlax_protocol_internet_t internet, const uint8_t * segment);

#endif // SNORLAX_DEBUG

#endif // __SNORLAX__PROTOCOL_INTERNET_CONTROL_MESSAGE__H__
