FROM debian:buster

RUN apt update && apt install -y \
    wget \
    build-essential \
    libtool


RUN cd /tmp/ && \
    wget http://download.osgeo.org/geos/geos-3.8.1.tar.bz2 && \
    tar -xf geos-3.8.1.tar.bz2 && \
    cd geos-3.8.1 && \
    ./configure && \
    make -j4 && \
    make install && \
    cd / && \
    rm -rf /tmp/geos*

COPY . /makevalid

RUN cd /makevalid && \
    autoconf && \
    automake --add-missing && \
    ./configure && \
    make && \
    make install

ENTRYPOINT ["/bin/bash"]
