all: test

CC = clang
CFLAGS = -std=gnu99 -Wall -Werror -g -O2 -fPIC
LDFLAGS =

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

-include $(SRCS:.c=.d)

$(OBJS): %.o:%.c
	$(CC) -c $(CFLAGS) -o $@ $<

test: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.d: %.c
	set -e; rm -f $@; \
	    $(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	    sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	    rm -rf $@.$$$$

clean:
	rm -f *.d *.o test

.PHONY: all clean
