#include "parse_config.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* trim(char *text)
{
    char *end;

    while (isspace((unsigned char)*text)) {
        ++text;
    }
    end = text + strlen(text);
    while (end > text && isspace((unsigned char)end[-1])) {
        *--end = '\0';
    }
    return text;
}

Config* parse_config_file(const char* path, size_t* count)
{
    FILE* file;
    Config* configs = NULL;
    Config current = {0};
    char line[256];
    int in_section = 0;

    if (path == NULL || count == NULL) return NULL;
    file = fopen(path, "r");
    if (file == NULL) return NULL;
    *count = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        char *text = trim(line);
        char *comment = strchr(text, '#');
        char *equals;

        if (comment != NULL) {
            *comment = '\0';
        }
        text = trim(text);
        if (*text == '\0') {
            continue;
        }

        if (*text == '[') {
            if (in_section) {
                Config* grown = realloc(configs, (*count + 1) * sizeof(*configs));
                if (grown == NULL) {
                    free(configs);
                    fclose(file);
                    *count = 0;
                    return NULL;
                }
                configs = grown;
                configs[(*count)++] = current;
            }
            current = (Config){0};
            in_section = 1;
            continue;
        }

        if (!in_section || (equals = strchr(text, '=')) == NULL) {
            continue;
        }
        *equals = '\0';
        {
            char* key = trim(text);
            char* value = trim(equals + 1);

            if (strcmp(key, "capacity") == 0) {
                current.capacity = atoi(value);
            } else if (strcmp(key, "block_size") == 0) {
                current.block_size = atoi(value);
            } else if (strcmp(key, "associativity") == 0) {
                current.associativity = atoi(value);
            } else if (strcmp(key, "replacement") == 0) {
                if (strcmp(value, "FIFO") == 0) current.replacement = FIFO;
                else if (strcmp(value, "MRU") == 0) current.replacement = MRU;
                else if (strcmp(value, "RR") == 0) current.replacement = RR;
                else current.replacement = LRU;
            }
        }
    }

    if (in_section) {
        Config* grown = realloc(configs, (*count + 1) * sizeof(*configs));
        if (grown == NULL) {
            free(configs);
            fclose(file);
            *count = 0;
            return NULL;
        }
        configs = grown;
        configs[(*count)++] = current;
    }

    fclose(file);
    return configs;
}
