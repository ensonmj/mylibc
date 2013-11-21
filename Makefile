# Default target.
all: lib dll

CFLAGS = -std=gnu99 -Wall -Werror -g -O2 -fPIC
LDFLAGS = -shared -pthread

src = ringbuffer.c
objs = $(src:.c=.o)

-include $(src:.c=.d)

$(objs): %.o:%.c
	$(CC) -c $(CFLAGS) -o $@ $<

lib: $(objs)
	ar crv libmyc.a $(objs)

dll: $(objs)
	$(CC) $(LDFLAGS) -o libmyc.so $(objs)

%.d: %.c
	set -e; rm -f $@; \
	    $(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	    sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	    rm -rf $@.$$$$

clean:
	rm -f *.d *.o libmyc.a libmyc.so

.PHONY: all clean lib
