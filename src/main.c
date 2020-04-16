#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <geos_c.h>

#define SUCCESS 0
#define FAILURE 1


void print_help(int exit_code) {
    printf("Help!\n");
    exit(exit_code);
}

void print_error(char *msg, int exit_code) {
    printf("%s\n", msg);
    exit(exit_code);
}


typedef struct MakeValidConfig {
    char *read_filename;
    char *write_filename;

    FILE *read_fileobj;
    FILE *write_fileobj;

} MakeValidConfig;

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

int process(MakeValidConfig *config) {
    initGEOS(NULL, NULL);

    GEOSWKTReader *reader = GEOSWKTReader_create();
    GEOSWKTWriter *writer = GEOSWKTWriter_create();

    size_t len = 0;

    char *line = NULL;
    char *wkt;

    int counter = 0;
    int fixed_counter = 0;

    GEOSGeometry *input_geom;
    GEOSGeometry *valid_geom;

    while (getline(&line, &len, config->read_fileobj) != -1) {
        counter++;

        input_geom = GEOSWKTReader_read(reader, line);
        if (!GEOSisValid(input_geom)) {
            fixed_counter++;
            valid_geom = GEOSMakeValid(input_geom);
            wkt = strcat(GEOSWKTWriter_write(writer, valid_geom), "\n");
        }
        else {
            wkt = line;
        }
        fwrite(wkt, sizeof(char), strlen(wkt), config->write_fileobj);
    }
    finishGEOS();

    fprintf(stderr, "Processed %d lines.\n", counter);
    fprintf(stderr, "Fixed %d geometries.\n", fixed_counter);

    return 0;
}



int main(int argc, char *argv[]) {
    MakeValidConfig *config = parse_arguments(argc, argv);

    int status = process(config);

    finish(config);

    return status;
}
