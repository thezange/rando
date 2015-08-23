CPPFLAGS += -Iinclude
IDIR = include
SDIR = src
BDIR = bin

HDRS = $(wildcard include/*.h)

SRCS = $(wildcard src/*.c)
BINS = $(patsubst src/%.c,bin/%.o,$(SRCS))

LIBS = -lSDL2 -lSDL2_image

all: main

main: $(BINS) $(LIBS)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o main $^

server: $(BINS) $(LIBS)

client: $(BINS) $(LIBS)

$(BDIR)/%.o: $(SDIR)/%.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<

.PHONY: clean
clean:
	rm -f $(BDIR)/*.o

