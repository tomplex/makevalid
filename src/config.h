#include <stdio.h>

#ifndef GEOS_MAKEVALID_CONFIG_H
#define GEOS_MAKEVALID_CONFIG_H

#define SUCCESS 0
#define FAILURE 1
#define TRUE 1
#define FALSE 0


void print_help();
void print_error(char *msg, int exit_code);

typedef struct MakeValidConfig {
    char *read_filename;  // File to read
    char *write_filename;  // File to write (o)ut. Defaults to stdout. (-o)

    int header;  // is there a header to (s)kip (-s)
    int write_all;  // write (a)ll geometries to output file (-a)

    FILE *read_fileobj;
    FILE *write_fileobj;

    const char *delimiter;
} MakeValidConfig;

void finish(MakeValidConfig *config);
MakeValidConfig *parse_arguments(int argc, char *argv[]);

#endif //GEOS_MAKEVALID_CONFIG_H
