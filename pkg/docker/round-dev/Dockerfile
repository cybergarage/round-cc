FROM ubuntu:14.04
MAINTAINER Satoshi Konno <skonno@cybergarage.org>

# Update base packages
RUN apt-get update && apt-get upgrade -y

# Install base packages
RUN apt-get install -y git g++ make automake autoconf

# Git configuration
RUN git config --global user.email "skonno@cybergarage.org"
RUN git config --global user.name "Satoshi Konno"

# uHTTP for C++
RUN apt-get install -y libedit-dev
WORKDIR /tmp
RUN git clone https://github.com/cybergarage/uHTTP4CC.git uhttp
WORKDIR uhttp
RUN ./bootstrap && ./configure && make && make install

# mUPnP for C++
RUN apt-get install -y libxml2-dev
WORKDIR /tmp
RUN git clone https://github.com/cybergarage/mUPnPCC.git mupnp
WORKDIR mupnp
RUN ./bootstrap && ./configure && make && make install

# Round
RUN apt-get install -y libboost-all-dev libssl-dev libjansson-dev openjdk-6-jdk libmozjs185-dev libv8-dev tcl-dev
WORKDIR /tmp
#RUN git clone https://github.com/cybergarage/Round.git round
RUN git clone http://192.168.100.10/git/round round
WORKDIR round
#RUN ./bootstrap && ./configure_ubuntu && make && make install

WORKDIR ~
