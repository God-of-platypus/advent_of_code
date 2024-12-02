#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_LINE_LENGTH 1024
#define MAX_MEMO 100000

typedef struct {
    int pos;
    int count;
    int infospos;
} Key;

typedef struct {
    Key key;
    uint64_t value;
} MemoEntry;

typedef struct {
    MemoEntry entries[MAX_MEMO];
    int size;
} Memo;

void init_memo(Memo* memo) {
    memo->size = 0;
}

uint64_t find_in_memo(Memo* memo, Key key) {
    for (int i = 0; i < memo->size; ++i) {
        if (memo->entries[i].key.pos == key.pos &&
            memo->entries[i].key.count == key.count &&
            memo->entries[i].key.infospos == key.infospos) {
            return memo->entries[i].value;
        }
    }
    return -1; // Not found
}

void add_to_memo(Memo* memo, const Key key, const uint64_t value) {
    if (memo->size < MAX_MEMO) {
        memo->entries[memo->size].key = key;
        memo->entries[memo->size].value = value;
        memo->size++;
    }
}

uint64_t getcount(Memo* memo, const char* line, int* infos, const int pos, const int count, const int infospos, const int infos_len) {
    const Key key = {pos, count, infospos};
    const uint64_t memo_value = find_in_memo(memo, key);

    if (memo_value != -1) {
        return memo_value;
    }

    uint64_t ret = 0;
    if (pos == strlen(line)) {
        ret = (infospos == infos_len) ? 1 : 0;
    } else if (line[pos] == '#') {
        ret = getcount(memo, line, infos, pos + 1, count + 1, infospos, infos_len);
    } else if (line[pos] == '.' || infospos == infos_len) {
        if (infospos < infos_len && count == infos[infospos]) {
            ret = getcount(memo, line, infos, pos + 1, 0, infospos + 1, infos_len);
        } else if (count == 0) {
            ret = getcount(memo, line, infos, pos + 1, 0, infospos, infos_len);
        }
    } else {
        // Handle `?` wildcard
        ret = getcount(memo, line, infos, pos + 1, count + 1, infospos, infos_len);
        if (infospos < infos_len && count == infos[infospos]) {
            ret += getcount(memo, line, infos, pos + 1, 0, infospos + 1, infos_len);
        } else if (count == 0) {
            ret += getcount(memo, line, infos, pos + 1, 0, infospos, infos_len);
        }
    }

    add_to_memo(memo, key, ret);
    return ret;
}

uint64_t part1(const char* line, int* infos, int infos_len) {
    char payload[MAX_LINE_LENGTH];
    snprintf(payload, sizeof(payload), "%s.", line); // Add trailing `.`
    Memo memo;
    init_memo(&memo);
    return getcount(&memo, payload, infos, 0, 0, 0, infos_len);
}

uint64_t part2(const char* line, const int* infos, const int infos_len) {
    char payload[MAX_LINE_LENGTH] = {0};
    int extended_infos[infos_len * 5];
    for (int i = 0; i < 5; ++i) {
        strcat(payload, line);
        strcat(payload, "?");
        memcpy(&extended_infos[i * infos_len], infos, infos_len * sizeof(int));
    }
    payload[strlen(payload) - 1] = '.'; // Replace the last `?` with `.`
    Memo memo;
    init_memo(&memo);
    return getcount(&memo, payload, extended_infos, 0, 0, 0, infos_len * 5);
}

int main() {
    FILE* file = fopen("input.txt", "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char line[MAX_LINE_LENGTH];
    uint64_t part1_total = 0, part2_total = 0;
    int overflow_count = 0;

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        line[strcspn(line, "\n")] = '\0'; // Remove trailing newline

        char payload[MAX_LINE_LENGTH];
        char infos_str[MAX_LINE_LENGTH];
        sscanf(line, "%s %s", payload, infos_str);

        int infos[MAX_LINE_LENGTH];
        int infos_len = 0;
        char* token = strtok(infos_str, ",");
        while (token) {
            infos[infos_len++] = atoi(token);
            token = strtok(NULL, ",");
        }

        part1_total += part1(payload, infos, infos_len);
        const uint64_t tmp= part2(payload, infos, infos_len);
        if (tmp + part2_total < tmp || tmp + part2_total < part2_total) {
            printf("Tmp value: %llu\n", tmp);
            printf("Part2: %llu\n", part2_total);
            printf("There is an overflow\n");
            overflow_count++;
        }
        part2_total += tmp;
    }

    fclose(file);

    printf("Part 1: %llu\n", part1_total);
    printf("Part 2: %llu\n", part2_total);

    return 0;
}
