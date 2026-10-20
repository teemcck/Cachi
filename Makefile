CC ?= cc
CPPFLAGS ?= -Isrc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -O2
TARGET := cache-simulator
SOURCES := main.c src/cache.c src/hierarchy.c
HEADERS := src/cache.h src/config.h src/hierarchy.h

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ $(SOURCES) $(LDLIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) $(TARGET)
