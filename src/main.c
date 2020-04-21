#include <stdio.h>
#include <string.h>

#include <geos_c.h>

#include "config.h"


int process(makevalidconfig_t *config) {
    initGEOS(NULL, NULL);

    GEOSWKTReader *reader = GEOSWKTReader_create();
    GEOSWKTWriter *writer = GEOSWKTWriter_create();

    size_t len = 0;
    char *line = NULL;
    char *wkt;
    char *id;
    int counter = 0;
    int fixed_counter = 0;
    int valid;

    GEOSGeometry *input_geom;
    GEOSGeometry *valid_geom;

    if (config->header == TRUE) {
        // Skip the header
        fprintf(stderr, "Skipping header.\n");
        getline(&line, &len, config->read_fileobj);
    }

    while (getline(&line, &len, config->read_fileobj) != -1) {
        counter++;

        id = strtok(line, config->delimiter);
        wkt = strtok(NULL, config->delimiter);

        input_geom = GEOSWKTReader_read(reader, wkt);
        valid = GEOSisValid(input_geom);

        if (valid == TRUE && config->write_all == FALSE) {
            // If it's valid and we don't want to write out all input geometries,
            // just continue to the next record.
            continue;
        } else if (valid == FALSE) {
            fixed_counter++;
            valid_geom = GEOSMakeValid(input_geom);
            wkt = GEOSWKTWriter_write(writer, valid_geom);
            strcat(wkt, "\n");
        }

        fwrite(id, 1, strlen(id), config->write_fileobj);
        putc('|', config->write_fileobj);
        fwrite(wkt, 1, strlen(wkt), config->write_fileobj);
    }
    finishGEOS();

    if (!config->quiet) {
        fprintf(stderr, "Processed %d lines.\n", counter);
        fprintf(stderr, "Fixed %d geometries.\n", fixed_counter);
    }

    return 0;
}

int main(int argc, char *argv[]) {
    makevalidconfig_t *config = parse_arguments(argc, argv);

    int status = process(config);

    finish(config);

    return status;
}
