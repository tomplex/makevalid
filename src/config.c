#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "config.h"

void print_help() {
    char *usage =
        "Usage: makevalid [OPTIONS] INPUT_FILE\n\n"
        "Read INPUT_FILE and load WKT geometries, and fix any which are invalid. \n"
        "By default, output is written to stdout and only changed geometries are written.\n\n"
        "Options:\n"
        "\t-o\tspecify output file.\n"
        "\t-a\toutput all geometries, not just those which have been fixed.\n";
    printf("%s", usage);
    exit(SUCCESS);
}

void print_error(char *msg, int exit_code) {
    printf("%s\n", msg);
    exit(exit_code);
}

void finish(MakeValidConfig *config) {
    fclose(config->read_fileobj);
    fclose(config->write_fileobj);
    free(config);
}

MakeValidConfig *parse_arguments(int argc, char *argv[]) {
    MakeValidConfig *config = (MakeValidConfig *) malloc(sizeof(MakeValidConfig));

    if (argc <= 1 || strncmp(argv[1], "--help", 6) == 0) {
        print_help(SUCCESS);
    }

    // default options
    config->read_filename = argv[argc-1];
    config->read_fileobj = fopen(config->read_filename, "r");
    config->write_filename = "stdout";
    config->write_fileobj = stdout;
    config->write_all = 0;

    static const char *options = "ao:";
    int c;

    while ((c = getopt(argc, argv, options)) != -1) {
        switch (c) {
            case 'o':
                config->write_filename = optarg;
                config->write_fileobj = fopen(config->write_filename, "w");
                break;
            case 'a':
                config->write_all = 1;
                break;
        }
    }

    if (config->read_fileobj == NULL) {
        print_error("Couldn't open file for reading.\n", FAILURE);
    }

    if (config->write_fileobj == NULL) {
        print_error("Couldn't open file for writing.\n", FAILURE);
    }

    return config;
}