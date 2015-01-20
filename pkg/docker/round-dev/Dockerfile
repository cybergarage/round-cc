FROM ubuntu:14.04
MAINTAINER Satoshi Konno <skonno@cybergarage.org>

# Update base packages
RUN apt-get update && apt-get upgrade -y

# Install base packages
RUN apt-get install -y git g++ make automake autoconf
RUN apt-get install -y build-essential devscripts debheper dh-make fakeroot pbuilder cdbs

# Set Packaging ENV
ENV DEBFULLNAME "Satoshi Konno"
ENV DEBEMAIL skonno@cybergarage.org

# Git configuration
RUN git config --global user.email "skonno@cybergarage.org"
RUN git config --global user.name "Satoshi Konno"

# uHTTP for C++
RUN apt-get install -y libedit-dev
WORKDIR /root
RUN git clone https://github.com/cybergarage/uHTTP4CC.git uhttp
WORKDIR uhttp
RUN ./bootstrap && ./configure && make && make install

# mUPnP for C++
RUN apt-get install -y libxml2-dev
WORKDIR /root
RUN git clone https://github.com/cybergarage/mUPnPCC.git mupnp
WORKDIR mupnp
RUN ./bootstrap && ./configure && make && make install

# uSQL for C++
RUN apt-get install -y libantlr3c-dev
WORKDIR /root
RUN git clone https://github.com/cybergarage/uSQL4CC.git usql
WORKDIR usql
RUN ./bootstrap && ./configure && make && make install

# Round
RUN apt-get install -y libboost-all-dev libssl-dev libjansson-dev openjdk-6-jdk libmozjs185-dev libv8-dev tcl-dev
WORKDIR /root
#RUN git clone https://github.com/cybergarage/Round.git round
COPY round /root/round
WORKDIR round
RUN ./bootstrap && ./configure_ubuntu --enable-script-java=no && make && make install

# JNI
WORKDIR /root
#ENV JVM_HOME `update-java-alternatives -l | head -n 1 | awk '{print $3}'`
ENV JVM_HOME /usr/lib/jvm/java-1.6.0-openjdk-amd64
ENV LD_LIBRARY_PATH $JVM_HOME/jre/lib/amd64:$JVM_HOME/jre/lib/amd64/server

WORKDIR /root
