#include <stdio.h>
#include <stdlib.h>
#include <rpc/rpc.h>
#include "file_interact.h" // Generated header file from RPCGEN

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    CLIENT *cl;
    int *file_id;
    data *file_data;
    char *filename = argv[1];

    cl = clnt_create("localhost", FILE_INTERACT_PROG, DEMO, "tcp");
    if (cl == NULL) {
        clnt_pcreateerror("Error connecting to server");
        exit(1);
    }

    // Open the file
    file_id = open_file_1(&filename, cl);
    if (file_id == NULL || *file_id == -1) {
        printf("File not found!\n");
        clnt_destroy(cl);
        exit(1);
    }

    // Read the file
    file_data = read_file_1(file_id, cl);
    if (file_data == NULL) {
        printf("Error reading file or file too large!\n");
    } else {
        printf("Data read from file:\n%s\n", *file_data);
    }

    // Close the file
    close_file_1(file_id, cl);

    // Free allocated memory
    free(file_id);

    // Destroy the RPC client
    clnt_destroy(cl);

    return 0;
}
