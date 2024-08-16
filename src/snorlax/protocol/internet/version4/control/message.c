#include "message.h"

extern int32_t internet_control_message_protocol_version4_length_validate(uint8_t type, uint64_t packetlen) {
    snorlaxdbg(false, true, "implement", "calculate exactly");

    switch(type) {
        case internet_control_message_protocol_version4_type_echo_reply:                return packetlen >= sizeof(internet_control_message_protocol_version4_echo_t);
        case internet_control_message_protocol_version4_type_destination_unreachable:   return packetlen >= sizeof(internet_control_message_protocol_version4_destination_unreachable_t);
        case internet_control_message_protocol_version4_type_source_quench:             return packetlen >= sizeof(internet_control_message_protocol_version4_source_quench_t);
        case internet_control_message_protocol_version4_type_redirect:                  return packetlen >= sizeof(internet_control_message_protocol_version4_redirect_t);
        case internet_control_message_protocol_version4_type_echo:                      return packetlen >= sizeof(internet_control_message_protocol_version4_echo_t);
        case internet_control_message_protocol_version4_type_time_exceeded:             return packetlen >= sizeof(internet_control_message_protocol_version4_time_exceeded_t);
        case internet_control_message_protocol_version4_type_parameter_problem:         return packetlen >= sizeof(internet_control_message_protocol_version4_parameter_problem_t);
        case internet_control_message_protocol_version4_type_timestamp:                 return packetlen == sizeof(internet_control_message_protocol_version4_timestamp_t);
        case internet_control_message_protocol_version4_type_timestamp_reply:           return packetlen == sizeof(internet_control_message_protocol_version4_timestamp_t);
        case internet_control_message_protocol_version4_type_information_request:       return packetlen == sizeof(internet_control_message_protocol_version4_information_t);
        case internet_control_message_protocol_version4_type_information_reply:         return packetlen == sizeof(internet_control_message_protocol_version4_information_t);
        default: snorlaxdbg(true, false, "critical", "");                               return false;
    }
}