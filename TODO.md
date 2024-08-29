### 20240829 | [SIMULTANEOUS CONNECTION SYNCHRONIZATION](https://github.com/SnorlaxBio/dev/blob/main/RFC/RFC9293/FunctionalSpecification.md#3-functional-specification)
### 20240829 | [RESET](https://github.com/SnorlaxBio/dev/blob/main/RFC/RFC9293/FunctionalSpecification.md#3-functional-specification)

RESET 은 SYN SEQ & ACK 특히, SEQ 가 상태에 맞지 않게 오는 경우 RST 를 보내야 한다. - NO SUCH CONNECTION EXISTS...

`transmission_control_protocol_context_reply_gen_reset(...): transmission_control_protocol_context_t *` 라는 함수를 만들어서, 이러한 경우가 있으면 바로 호출하여 전달할 수 있도록 하자.

### 20240829 | transmission_control_protocol_context_t * transmission_control_protocol_context_reply_gen(transmission_control_protocol_context_t * context)

역방향으로 패킷을 전송하는 문맥을 만든다.

### 20240829 | STATE MACHINE 다시 짜자... 
