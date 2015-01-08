FROM ubuntu:12.04
MAINTAINER Satoshi Konno <skonno@cybergarage.org>

# Update base packages
RUN apt-get update && apt-get upgrade -y

# Install base packages
RUN apt-get install -y git g++ make automake autoconf

# uHTTP for C++
RUN apt-get install -y libedit-dev
WORKDIR /tmp
RUN git clone https://github.com/cybergarage/uHTTP4CC.git uhttp
WORKDIR uhttp
RUN ./bootstrap && ./configure && make && make install
WORKDIR /tmp
RUN rm -rf uhttp

# mUPnP for C++
RUN apt-get install -y libxml2-dev
WORKDIR /tmp
RUN git clone https://github.com/cybergarage/mUPnPCC.git mupnp
WORKDIR mupnp
RUN ./bootstrap && ./configure && make && make install
WORKDIR /tmp
RUN rm -rf mupnp

# Round
RUN apt-get install -y libboost-all-dev libssl-dev libjansson-dev openjdk-6-jdk libmozjs185-dev libv8-dev
WORKDIR /tmp
RUN git clone https://github.com/cybergarage/Round.git round
WORKDIR round
RUN ./bootstrap && ./configure_ubuntu && make && make install
WORKDIR /tmp
RUN rm -rf round

# JNI 
ENV LD_LIBRARY_PATH /usr/lib/jvm/java-6-openjdk-amd64/jre/lib/amd64:/usr/lib/jvm/java-6-openjdk-amd64/jre/lib/amd64/server
