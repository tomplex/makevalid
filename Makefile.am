AUTOMAKE_OPTIONS = foreign subdir-objects

bin_PROGRAMS = makevalid

makevalid_SOURCES = src/*.c

makevalid_CFLAGS=$(GEOS_CONFIG --cflags)
makevalid_LDFLAGS=$(GEOS_CONFIG --static-clibs)
