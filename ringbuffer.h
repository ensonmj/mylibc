#ifndef __RINGBUFFER_H_
#define __RINGBUFFER_H_

#include <stdint.h>
#include <pthread.h>

#define WAIT_TIME 5

typedef struct ringbuf_ {
    void *buf;
    uint32_t entry_size;
    uint32_t entries;

    uint32_t head;
    uint32_t tail;

#ifdef RINGBUFFER_MUTEX_WAIT
    pthread_cond_t cond;
    pthread_mutex_t mutex;
#endif
    pthread_spinlock_t spin;
    volatile uint32_t shutdown;
} ringbuf_t;

ringbuf_t *ringbuf_init(void *buf, uint32_t entry_size, uint32_t entries);
void ringbuf_cleanup(ringbuf_t *rb);

void *ringbuf_get(ringbuf_t *rb);
int ringbuf_put(ringbuf_t *rb, void *ptr);

#endif
