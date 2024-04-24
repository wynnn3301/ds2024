#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 100
#define MAX_KEY_VALUES 1000

typedef struct {
    char key[MAX_WORD_LENGTH];
    int value;
} KeyValue;

void map(const char *line, KeyValue *kv, int *kv_count) {
    char temp_line[strlen(line) + 1]; // Create a temporary copy of the line
    strcpy(temp_line, line);
    char *token = strtok(temp_line, " .,\t\n\r"); // common delimiters
    while (token != NULL) {
        strcpy(kv[*kv_count].key, token);
        kv[*kv_count].value = 1;
        (*kv_count)++;
        token = strtok(NULL, " .,\t\n\r");
    }
}

void reduce(const KeyValue *input, int input_size) {
    KeyValue result[input_size];
    int result_size = 0;

    for (int i = 0; i < input_size; i++) {
        int j;
        for (j = 0; j < result_size; j++) {
            if (strcmp(input[i].key, result[j].key) == 0) {
                result[j].value++;
                break;
            }
        }
        if (j == result_size) {
            strcpy(result[result_size].key, input[i].key);
            result[result_size].value = 1;
            result_size++;
        }
    }

    for (int i = 0; i < result_size; i++) {
        printf("%s: %d\n", result[i].key, result[i].value);
    }
}

int main() {
    FILE *file;
    char line[1000];
    KeyValue kv[MAX_KEY_VALUES];
    int kv_count = 0;

    file = fopen("file_to_test.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {
        map(line, kv, &kv_count);
    }

    fclose(file);

    reduce(kv, kv_count);

    return 0;
}
