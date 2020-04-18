FROM debian:buster

RUN apt update && apt install -y \
    wget \
    build-essential \
    libtool \
    cmake

RUN cd /tmp/ && \
    wget http://download.osgeo.org/geos/geos-3.8.1.tar.bz2 && \
    tar -xf geos-3.8.1.tar.bz2 && \
    cd geos-3.8.1 && \
    ./configure && \
    make -j4 && \
    make install && \
    cd / && \
    rm -rf /tmp/geos*

RUN ldconfig

COPY . /makevalid
WORKDIR /makevalid

RUN cd /makevalid && \
    cmake . && \
    make

ENTRYPOINT ["/bin/bash"]
