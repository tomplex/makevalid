#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "config.h"

void print_help() {
    char *usage =
        "Usage: makevalid [OPTIONS] INPUT_FILE\n\n"
        "Read INPUT_FILE and load WKT geometries, and fix any which are invalid. \n"
        "INPUT_FILE must be a file with two fields separated by a pipe [|]. The first field "
        "should be an ID, and the second should be the WKT geometry to be made valid. If data should be"
        "read from stdin, then INPUT_FILE should be a dash, e.g. -.\n"
        "By default, output is written to stdout and only changed geometries are written.\n\n"
        "Required arguments:\n"
        "\tINPUT_FILE\tthe input file to be read. '-' indicates the program should read from stdin.\n\n"
        "Options:\n"
        "\t-o\tspecify output file\n"
        "\t-a\twrite all geometries, not just those which have been fixed\n"
        "\t-s\tskip the first line of the file\n"
        "\t-q\tdon't print number geometries processed & fixed to stderr";
    printf("%s", usage);
    exit(SUCCESS);
}

void print_error(char *msg, int exit_code) {
    printf("%s\n", msg);
    exit(exit_code);
}

void finish(makevalidconfig_t *config) {
    fclose(config->read_fileobj);
    fclose(config->write_fileobj);
    free(config);
}

makevalidconfig_t *parse_arguments(int argc, char *argv[]) {
    makevalidconfig_t *config = (makevalidconfig_t *) malloc(sizeof(makevalidconfig_t));

    if (argc <= 1 || strncmp(argv[1], "--help", 6) == 0) {
        print_help();
    }

    // default options
    if (strcmp(argv[argc - 1], "-") == 0) {
        config->read_filename = "stdin";
        config->read_fileobj = stdin;
    } else {
        config->read_filename = argv[argc - 1];
        config->read_fileobj = fopen(config->read_filename, "r");
    }
    config->write_filename = "stdout";
    config->write_fileobj = stdout;
    config->write_all = FALSE;
    config->delimiter = "|";
    config->quiet = FALSE;

    static const char *options = "asqo:";
    int c;

    while ((c = getopt(argc, argv, options)) != -1) {
        switch (c) {
            case 'o':
                config->write_filename = optarg;
                config->write_fileobj = fopen(config->write_filename, "w");
                break;
            case 's':
                config->header = TRUE;
                break;
            case 'a':
                config->write_all = TRUE;
                break;
            case 'q':
                config->quiet = TRUE;
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