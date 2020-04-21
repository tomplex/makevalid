## makevalid

Simple tool to "makevalid" files containing WKT geometries.


## usage

`makevalid` is a simple command-line tool which reads an input file containing two fields: an ID and a WKT geometry. 
The fields should be pipe-delimited. 

```bash
./makevalid --help  # print help info
Usage: makevalid [OPTIONS] INPUT_FILE

Read INPUT_FILE and load WKT geometries, and fix any which are invalid.
INPUT_FILE must be a file with two fields separated by a pipe [|]. The first field should be an ID, and the second should be the WKT geometry to be made valid. The file should have no header.
By default, output is written to stdout and only changed geometries are written.

Options:
	-o	specify output file.
	-a	output all geometries, not just those which have been fixed.
	-s	skip the first line of the file (a header).
```

`makevalid` will print to stdout by default. You can use the `-o FILENAME` option to specify an output file to write to, instead.
By default, only geometries which are altered (made valid) will be written. To write them all instead, use `-a`.
If your file has a header, you can use `-s` to skip the first line. The header will not be written to the output file. 

`makevalid` will write the number of geometries processed and the number fixed to stderr when the program is complete.
To silence it, use `-q`.

## build and install

Requires GEOS >= 3.8 & `cmake` >= 3.13. The standard system locations
will be searched for GEOS. Please note that the build will not try all 
possible GEOS installations but just the first found by `cmake`. If that version
is not >=3.8, you will have to specify the path to your installation explicitly. 

```bash
git clone git@github.com:tomplex/makevalid.git
cd makevalid

# optionally specify location of GEOS library.
# /usr/ and /usr/local will be searched by default.
cmake -DGEOS_DIR=/usr/local/geos/3.8.1/ . && make
```

This will create an executable called `makevalid` in your local directory. 

If you explictly specify a directory, it should be the root install directory for geos, such that 
the directory contains the GEOS `bin`, `include`, and `lib` directories, like so:

```bash
❯ ll /usr/local/geos/3.8.1/
total 0
drwxr-xr-x   5 root  wheel  160 Apr  8 17:56 .
drwxr-xr-x   4 root  wheel  128 Apr 21 00:27 ..
drwxr-xr-x   3 root  wheel   96 Apr  8 17:56 bin
drwxr-xr-x   5 root  wheel  160 Apr  8 17:56 include
drwxr-xr-x  10 root  wheel  320 Apr  8 17:56 lib
```

This directory is equivalent to the `--prefix` used when installing GEOS from source.

If you are on Linux/MacOS, you can install GEOS from source like so, assuming `wget` 
is installed. You should be able to use `curl` interchangeably.

```bash
pushd /tmp
wget http://download.osgeo.org/geos/geos-3.8.1.tar.bz2

tar -xf geos-3.8.1.tar.bz2
pushd geos-3.8.1/
./configure --prefix=/usr/local/geos/3.8.1
make -j 4 
sudo make install
popd; popd
```

This will install GEOS from source in the directory `/usr/local/geos/3.8.1`. You can then run the install commands for makevalid
above, verbatim.
