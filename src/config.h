#include <stdio.h>


#ifndef GEOS_MBC_CONFIG_H
#define GEOS_MBC_CONFIG_H
#define SUCCESS 0
#define FAILURE 1

void print_help(int exit_code);
void print_error(char *msg, int exit_code);

typedef struct MakeValidConfig {
    char *read_filename;  // File to read
    char *write_filename;  // File to write. Defaults to stdout.

    FILE *read_fileobj;
    FILE *write_fileobj;

    int write_all;

} MakeValidConfig;

void finish(MakeValidConfig *config);
MakeValidConfig *parse_arguments(int argc, char *argv[]);

#endif //GEOS_MBC_CONFIG_H
