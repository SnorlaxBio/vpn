/**
 * @file        snorlax/descriptor.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 8, 2024
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include "descriptor.h"
#include "descriptor/event.h"
#include "descriptor/event/type.h"


#include "event/queue.h"

static descriptor_func_t func = {
    descriptor_rem
};

extern descriptor_t * descriptor_gen(int descriptor) {
    descriptor_t * o = (descriptor_t *) calloc(1, sizeof(descriptor_t));

    o->func = &func;
    o->queue = event_queue_gen();
    o->descriptor = descriptor;
    o->buffer.in = buffer_gen(16);
    o->buffer.out = buffer_gen(16);
    o->handler = event_handler_array_gen();

    event_handler_array_set(o->handler, nil, descriptor_event_type_max);
    
    return o;
}

/**
 * @todo        이벤트 객체에 등록되어서 아직 처리되지 못한 이벤트가 존재할 경우
 *              이벤트를 처리하고 삭제하도록 한다.
 * @todo        파일 디스크립터가 오픈된 상태이고 버퍼에 쓰기와 읽기가 가능한 상태이면
 *              나머지를 모두 읽고 쓰고 난 후에 파일 디스크립터를 닫도록 한다.
 */
extern descriptor_t * descriptor_rem(descriptor_t * o) {
    event_engine_unreg(o->engine, o);

    o->queue = event_queue_rem(o->queue, nil);
    o->buffer.in = buffer_rem(o->buffer.in);
    o->buffer.out = buffer_rem(o->buffer.out);
    if(o->descriptor >= 0) {
        close(o->descriptor);
        o->descriptor = invalid;
    }
    o->handler = event_handler_array_rem(o->handler);

    free(o);

    return nil;
}

extern int descriptor_open(descriptor_t * o) {
    return o->descriptor >= 0 ? o->descriptor : fail;
}

extern int descriptor_close(descriptor_t * o) {
    if(o->descriptor >= 0) {
        close(o->descriptor);
        o->descriptor = invalid;
    }
    return success;
}

extern int64_t descriptor_write(descriptor_t * o) {
    
}

extern int64_t descriptor_read(descriptor_t * o) {

}

// static descriptor_t * descriptor_rem(descriptor_t * o);
// static int descriptor_open(descriptor_t * o);
// static int descriptor_close(descriptor_t * o);
// static int64_t descriptor_read(descriptor_t * o);
// static int64_t descriptor_write(descriptor_t * o);

// static descriptor_func_t func = {
//     descriptor_rem,
//     descriptor_open,
//     descriptor_close,
//     descriptor_read,
//     descriptor_write
// };

// extern descriptor_t * descriptor_gen(int descriptor) {
//     descriptor_t * o = (descriptor_t *) calloc(1, sizeof(descriptor_t));

//     o->func = &func;
//     o->descriptor = descriptor;
//     o->buffer.in = buffer_gen(4096);
//     o->buffer.out = buffer_gen(4096);
//     o->queue = event_queue_gen();

//     return o;
// }

// static descriptor_t * descriptor_rem(descriptor_t * o) {
//     // todo: gracefully remove event
//     event_queue_rem(o->queue, nil);

//     // todo: gracefully buffer read & write
//     o->buffer.in = buffer_rem(o->buffer.in);
//     o->buffer.out = buffer_rem(o->buffer.out);

//     if(o->descriptor >= 0) {
//         close(o->descriptor);
//         o->descriptor = invalid;
//     }

//     free(o);

//     return nil;
// }

// static int descriptor_open(descriptor_t * o) {
//     if(o->descriptor < 0) {
//         // TODO: ERROR
//     }
//     return o->descriptor >=0 ? success : fail;
// }

// static int descriptor_close(descriptor_t * o) {
//     if(o->descriptor >= 0) {
//         // TODO: GRACEFULLY CLOSE
//         close(o->descriptor);
//         o->descriptor = invalid;
//     }
//     return success;
// }

// // DESCRIPTOR READ & WRITE 의 콜백은 어느 시점에 정의하여야 하는가?
// static int64_t descriptor_read(descriptor_t * o) {
//     if(o->descriptor >= 0) {
//         if(buffer_remain(o->buffer.in) < 4096){
//             buffer_capacity_set(o->buffer.in, o->buffer.in->capacity + 4096);
//         } else if(buffer_len(o->buffer.in) == 0) {
//             buffer_reset(o->buffer.in, 4096);
//         }

//         int64_t n = read(o->descriptor, buffer_back(o->buffer.in), buffer_remain(o->buffer.in));
//         if(n > 0) {
//             o->buffer.in->size = o->buffer.in->size + n;
//             return n;
//         } else if(n == 0) {
//             // TODO: CHECK (PIPE, TERMINAL, SOCKET IS CLOSE, BUT FILE'S ... )
//             return fail;
//         } else {
//             if(errno == EAGAIN) {
//                 return success;
//             }
//             // TODO: CLOSE LOGIC WHERE ...
//             return fail;
//         }
//     }
//     return fail;
// }

// static int64_t descriptor_write(descriptor_t * o) {
//     if(o->descriptor >= 0) {
//         if(buffer_len(o->buffer.out) > 0) {
//             int64_t n = write(o->descriptor, buffer_front(o->buffer.out), buffer_len(o->buffer.out));
//             if(n > 0) {
//                 o->buffer.out->position = o->buffer.out->position + n;
//                 if(buffer_len(o->buffer.out) == 0) {
//                     buffer_reset(o->buffer.out, 4096);
//                 }
//             } else if(n == 0) {
//                 // TODO: WHY?
//                 return 0;
//             } else {
//                 if(errno == EAGAIN) {
//                     return success;
//                 }
//                 // TODO: CLOSE?
//                 return fail;
//             }
//         }
//         return success;
//     }
//     return fail;
// }
