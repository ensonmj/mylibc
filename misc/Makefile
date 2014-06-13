all: test

CC = clang
CPPFLAGS =
CFLAGS = -std=gnu99 -Wall -Werror -g -O0 -fPIC
LDFLAGS =

ifdef TEST_SORT
CPPFLAGS = -DTEST_SORT
else ifdef TEST_LUA
CPPFLAGS = -DTEST_LUA
LDFLAGS = -llua
endif

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

-include $(SRCS:.c=.d)

$(OBJS): %.o:%.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $<

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
