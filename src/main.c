#include <stdio.h>
#include <string.h>

#include <geos_c.h>

#include "config.h"


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
