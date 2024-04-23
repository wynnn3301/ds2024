#include <stdio.h>
#include <stdlib.h>
#include <rpc/rpc.h>
#include "file_interact.h" // Generated header file from RPCGEN

FILE *opened_files[100]; // Maximum of 100 opened files

int *open_file_1_svc(char **filename, struct svc_req *rqstp) {
    int *file_id = (int *)malloc(sizeof(int));
    *file_id = -1; // Default value for file not found

    FILE *file = fopen(*filename, "r");
    if (file != NULL) {
        for (int i = 0; i < 100; ++i) {
            if (opened_files[i] == NULL) {
                opened_files[i] = file;
                *file_id = i; // Return the index as file id
                break;
            }
        }
    }

    return file_id;
}

void *close_file_1_svc(int *file_id, struct svc_req *rqstp) {
    if (*file_id >= 0 && *file_id < 100) {
        if (opened_files[*file_id] != NULL) {
            fclose(opened_files[*file_id]);
            opened_files[*file_id] = NULL;
        }
    }
}

data *read_file_1_svc(int *file_id, struct svc_req *rqstp) {
    static data file_data; // Static to return it safely

    if (*file_id >= 0 && *file_id < 100) {
        if (opened_files[*file_id] != NULL) {
            fseek(opened_files[*file_id], 0, SEEK_END);
            long file_size = ftell(opened_files[*file_id]);
            fseek(opened_files[*file_id], 0, SEEK_SET);

            if (file_size <= 500) {
                fread(file_data, 1, file_size, opened_files[*file_id]);
                return &file_data;
            }
        }
    }

    // Return empty data if file not open or too large
    return NULL;
}

int main(int argc, char **argv) {
    // Registering the server program
    register FILE_INTERACT_PROG(FILE_INTERACT_PROG_VERSION, DEMO, open_file_1, 0, NULL);
    register FILE_INTERACT_PROG(FILE_INTERACT_PROG_VERSION, DEMO, close_file_1, 0, NULL);
    register FILE_INTERACT_PROG(FILE_INTERACT_PROG_VERSION, DEMO, read_file_1, 0, NULL);

    // Running the server
    svc_run();

    return 0;
}
