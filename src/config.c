#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

void print_help(int exit_code) {
    printf("Help!\n");
    exit(exit_code);
}

void print_error(char *msg, int exit_code) {
    printf("%s\n", msg);
    exit(exit_code);
}

void finish(MakeValidConfig *config) {
    fclose(config->read_fileobj);
    fclose(config->write_fileobj);
}

MakeValidConfig *parse_arguments(int argc, char *argv[]) {
    MakeValidConfig *config = (MakeValidConfig *) malloc(sizeof(MakeValidConfig));

    if (argc <= 1 || strncmp(argv[1], "--help", 6) == 0) {
        print_help(SUCCESS);
    }

    config->read_filename = argv[1];
    config->read_fileobj = fopen(config->read_filename, "r");

    if (argc == 2 || (argc == 3 && strncmp(argv[2], "-", 1) == 0)) {
        // print to stdout
        config->write_filename = "stdout";
        config->write_fileobj = stdout;
    } else if (argc == 3 && strncmp(argv[2], "-", 1) != 0) {
        config->write_filename = argv[2];
        config->write_fileobj = fopen(config->write_filename, "w");
    } else {
        print_help(FAILURE);
    }

    if (config->read_fileobj == NULL) {
        print_error("Couldn't open file for reading.\n", FAILURE);
    }

    if (config->write_fileobj == NULL) {
        print_error("Couldn't open file for writing.\n", FAILURE);
    }

    return config;
}