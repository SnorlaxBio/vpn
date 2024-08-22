#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

#include "control.h"

#include "../version4.h"
#include "../version6.h"

extern uint16_t transmission_control_protocol_checksum_cal(transmission_control_protocol_packet_t * segment, uint64_t segmentlen, internet_protocol_pseudo_t * pseudo, uint64_t pseudolen) {
#ifndef   RELEASE
    snorlaxdbg(segment == nil, false, "critical", "");
    snorlaxdbg(segmentlen == 0, false, "critical", "");
    snorlaxdbg(pseudo == nil, false, "critical", "");
    snorlaxdbg(pseudolen == 0, false, "critical", "");
#endif // RELEASE

    uint16_t checksum = segment->checksum;
    segment->checksum = 0;

    snorlaxdbg(false, true, "debug", "segmentlen => %lu", segmentlen);

    uint32_t value = internet_protocol_checksum_sum((protocol_packet_t *) pseudo, pseudolen);
    value = value + internet_protocol_checksum_sum((protocol_packet_t *) segment, segmentlen);

    while(value >> 16) value = (value >> 16) + (value & 0x0000FFFFu);

    segment->checksum = checksum;

    return (int16_t) (~value);
}

extern int32_t transmission_control_protocol_address_pair_init(transmission_control_protocol_address_pair_t * pair, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(pair == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    uint8_t version = internet_protocol_context_version_get(parent);

    if(version == 4) {
        internet_protocol_version4_context_t * version4 = (internet_protocol_version4_context_t *) parent;
        if(internet_protocol_version4_module_local_is((internet_protocol_version4_module_t *) version4->module, internet_protocol_version4_context_source_get(version4))) {
            pair->version4.local.addr = internet_protocol_version4_context_source_get(version4);
            pair->version4.local.port = transmission_control_protocol_context_source_get(context);
            pair->version4.foreign.addr = internet_protocol_version4_context_destination_get(version4);
            pair->version4.foreign.port = transmission_control_protocol_context_destination_get(context);
        } else if(internet_protocol_version4_module_local_is((internet_protocol_version4_module_t *) version4->module, internet_protocol_version4_context_destination_get(version4))) {
            pair->version4.foreign.addr = internet_protocol_version4_context_source_get(version4);
            pair->version4.foreign.port = transmission_control_protocol_context_source_get(context);
            pair->version4.local.addr = internet_protocol_version4_context_destination_get(version4);
            pair->version4.local.port = transmission_control_protocol_context_destination_get(context);
        } else {
            snorlaxdbg(false, true, "debug", "");
            return fail;
        }
    } else if(version == 6) {
        internet_protocol_version6_context_t * version6 = (internet_protocol_version6_context_t *) parent;

        if(internet_protocol_version6_module_local_is((internet_protocol_version6_module_t *) version6->module, internet_protocol_version6_context_source_get(version6))) {
            memcpy(pair->version6.local.addr, internet_protocol_version6_context_source_get(version6), 16);
            pair->version6.local.port = transmission_control_protocol_context_source_get(context);
            memcpy(pair->version6.foreign.addr, internet_protocol_version6_context_destination_get(version6), 16);
            pair->version6.foreign.port = transmission_control_protocol_context_destination_get(context);
        } else if(internet_protocol_version6_module_local_is((internet_protocol_version6_module_t *) version6->module, internet_protocol_version6_context_destination_get(version6))) {
            memcpy(pair->version6.foreign.addr, internet_protocol_version6_context_source_get(version6), 16);
            pair->version6.foreign.port = transmission_control_protocol_context_source_get(context);
            memcpy(pair->version6.local.addr, internet_protocol_version6_context_destination_get(version6), 16);
            pair->version6.local.port = transmission_control_protocol_context_destination_get(context);
        } else {
            snorlaxdbg(false, true, "debug", "");
            return fail;
        }
    } else {
        snorlaxdbg(true, false, "critical", "");

        return fail;
    }

    return success;
}