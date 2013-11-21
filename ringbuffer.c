#include <unistd.h>
#include "ringbuffer.h"

void ringbuf_init(void *buf, uint32_t entry_size, uint32_t entries)
{

}

void ringbuf_cleanup(ringbuf_t *rb)
{

}

static inline void ringbuf_wait(ringbuf_t *rb)
{
#ifdef RINGBUFFER_MUTEX_WAIT
    pthread_mutex_lock(&rb->mutex);
    pthread_cond_wait(&rb->cond, &rb->mutex);
    pthread_mutex_unlock(&rb->mutex);
#else
    usleep(WAIT_TIME);
#endif
}

inline int ringbuf_full(ringbuf_t *rb)
{
    if((rb->head + 1) == rb->tail)
        return 1;
    return 0;
}

inline int ringbuf_empty(ringbuf_t *rb)
{
    if(rb->head == rb->tail)
        return 1;
    return 0;
}

void *ringbuf_get(ringbuf_t *rb)
{
    void *ptr;
    uint32_t read;

retry:
    while(ringbuf_empty(rb)) {
        if(rb->shutdown != 0) {
            return NULL;
        }
        ringbuf_wait(rb);
    }

    read = rb->tail - 1;
    do {

        if(ringbuf_empty(rb)) {
            goto retry;
        }

        read++;
        uint32_t index = read % rb->entries;
        ptr =  rb->buf + index;
    } while (!__sync_bool_compare_and_swap(&rb->tail, read, (read+1)));

#ifdef RINGBUFFER_MUTEX_WAIT
    pthread_cond_signal(&rb->cond);
#endif

    return ptr;
}

int ringbuf_put(ringbuf_t *rb, void *ptr)
{
retry:
    while(ringbuf_full(rb)) {
        if(rb->shutdown != 0) {
            return -1;
        }
        ringbuf_wait(rb);
    }

    pthread_spin_lock(&rb->spin);

    if(ringbuf_full(rb)) {
        pthread_spin_unlock(&rb->spin);
        goto retry;
    }

    uint32_t index = rb->head % rb->entries;
    void **slot = rb->buf + index;
    *slot = ptr;
    __sync_add_and_fetch(&rb->head, 1);

    pthread_spin_unlock(&rb->spin);

#ifdef RINGBUFFER_MUTEX_WAIT
    pthread_cond_signal(&rb->cond);
#endif
    return 0;
}
