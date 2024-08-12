#include "message.h"

extern int32_t internet_control_message_protocol_version6_length_validate(uint8_t type, uint64_t packetlen) {
    printf("type => %d\n", type);
    switch(type) {
        case internet_control_message_protocol_version6_message_type_destination_unreachable:   return packetlen >= sizeof(internet_control_message_protocol_version6_destination_unreachable_t);
        case internet_control_message_protocol_version6_message_type_packet_too_big:            return packetlen >= sizeof(internet_control_message_protocol_version6_packet_too_big_t);
        case internet_control_message_protocol_version6_message_type_time_exceeded:             return packetlen >= sizeof(internet_control_message_protocol_version6_time_exceeded_t);
        case internet_control_message_protocol_version6_message_type_parameter_problem:         return packetlen >= sizeof(internet_control_message_protocol_version6_parameter_problem_t);
        case internet_control_message_protocol_version6_message_type_echo_request:              return packetlen >= sizeof(internet_control_message_protocol_version6_echo_t);
        case internet_control_message_protocol_version6_message_type_echo_reply:                return packetlen >= sizeof(internet_control_message_protocol_version6_echo_t);
        case internet_control_message_protocol_version6_message_type_router_solicitation:       return packetlen >= sizeof(internet_control_message_protocol_version6_router_solicitation_t);
        case internet_control_message_protocol_version6_message_type_router_advertisement:      return packetlen >= sizeof(internet_control_message_protocol_version6_router_advertisement_t);
        case internet_control_message_protocol_version6_message_type_neighbor_solicitation:     return packetlen >= sizeof(internet_control_message_protocol_version6_neighbor_solicitation_t);
        default: snorlaxdbg(true, false, "critical", "");                                       return false;
    }
}