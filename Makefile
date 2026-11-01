CC ?= cc
CPPFLAGS ?= -Isrc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -O2
TARGET := cache-simulator
DEBUG_TARGET := cache-simulator-debug
SOURCES := main.c src/cache.c src/replacement.c src/hierarchy.c src/parse_config.c
HEADERS := src/cache.h src/config.h src/hierarchy.h src/parse_config.h src/replacement.h

.PHONY: all debug run clean

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ $(SOURCES) $(LDLIBS)

$(DEBUG_TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CPPFLAGS) $(CFLAGS) -O0 -g3 $(LDFLAGS) -o $@ $(SOURCES) $(LDLIBS)

debug: $(DEBUG_TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) $(TARGET) $(DEBUG_TARGET)
