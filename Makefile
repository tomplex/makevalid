GEOS_CONFIG = /usr/local/geos/3.8.1/bin/geos-config

GCC_LIBS := $(shell $(GEOS_CONFIG) --static-clibs)
GCC_FLAGS := $(shell $(GEOS_CONFIG) --cflags)

build:
	gcc $(GCC_LIBS) $(GCC_FLAGS) -o makevalid main.c
	#gcc -L/usr/local/geos/3.8.1/lib -lgeos_c -lgeos -lm -I/usr/local/geos/3.8.1/include main.c -o makevalid


clean:
	rm makevalid

test: build
	./makevalid in.wkt out.wkt
