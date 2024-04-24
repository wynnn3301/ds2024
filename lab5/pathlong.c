#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LENGTH 256

char longest_path[MAX_PATH_LENGTH] = ""; // Store the longest path found

// Map function
void map(FILE *file) {
    char path[MAX_PATH_LENGTH];
    while (fgets(path, MAX_PATH_LENGTH, file) != NULL) {
        int length = strlen(path);
        // Remove newline character if present
        if (path[length - 1] == '\n')
            path[length - 1] = '\0';
        
        // Check if path length is greater than current longest path length
        if (length > strlen(longest_path)) {
            strcpy(longest_path, path);
        }
    }
}

// Reduce function
void reduce(FILE *file) {
    // Perform mapping on the chunk
    map(file);
}

int main() {
    FILE *file = fopen("longest_path_test.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Perform mapping on the entire file
    map(file);
    
    // Close file
    fclose(file);
    
    // Reduce the results
    printf("The longest path found: %s\n", longest_path);

    return 0;
}
