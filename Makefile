vpath %.c src src/server src/client

CPPFLAGS += -Iinclude
IDIR = include
SDIR = src
BDIR = bin

HDRS = $(wildcard include/*.h)

SRCS = $(wildcard src/*.c)
SSRCS = $(wildcard src/server/*.c)
CSRCS = $(wildcard src/client/*.c)

BINS = $(patsubst src/%.c,bin/%.o,$(SRCS))
SBINS = $(patsubst src/server/%.c,bin/%.o,$(SSRCS))
CBINS = $(patsubst src/client/%.c,bin/%.o,$(CSRCS))

LIBS = -lSDL2 -lSDL2_net

all: server client

server: $(BINS) $(SBINS) $(LIBS)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o server $^

client: $(BINS) $(CBINS) $(LIBS)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o client $^

$(BDIR)/%.o: %.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<

.PHONY: clean
clean:
	rm -f $(BDIR)/*.o client server

