#include "message.h"

extern int32_t internet_control_message_protocol_version6_message_length_validate(uint8_t type, uint64_t packetlen) {
    switch(type) {
        case internet_control_message_protocol_version6_message_type_destination_unreachable:   return packetlen >= sizeof(internet_control_message_protocol_version6_destination_unreachable_message_t);
        case internet_control_message_protocol_version6_message_type_packet_too_big:            return packetlen >= sizeof(internet_control_message_protocol_version6_packet_too_big_message_t);
        case internet_control_message_protocol_version6_message_type_time_exceeded:             return packetlen >= sizeof(internet_control_message_protocol_version6_time_exceeded_message_t);
        case internet_control_message_protocol_version6_message_type_parameter_problem:         return packetlen >= sizeof(internet_control_message_protocol_version6_parameter_problem_message_t);
        case internet_control_message_protocol_version6_message_type_echo_request:              return packetlen >= sizeof(internet_control_message_protocol_version6_echo_message_t);
        case internet_control_message_protocol_version6_message_type_echo_reply:                return packetlen >= sizeof(internet_control_message_protocol_version6_echo_message_t);
        default: snorlaxdbg(true, false, "critical", "");                                       return false;
    }
}