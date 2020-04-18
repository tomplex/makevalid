## makevalid

Simple tool to "makevalid" files containing WKT geometries.

## build and install

Requires GEOS >= 3.8 & `cmake` >= 3.13.

```bash
git clone git@github.com:tomplex/makevalid.git
cd makevalid

# optionally specify location of GEOS library.
# /usr/ and /usr/local will be searched by default.
export GEOS_DIR=/usr/local/geos/3.8.1/
cmake . && make
```

This will create an executable called `makevalid` in your local directory. 