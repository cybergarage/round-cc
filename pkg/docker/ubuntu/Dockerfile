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

# CyberLink for C++
RUN apt-get install -y libxml2-dev
WORKDIR /tmp
RUN git clone https://github.com/cybergarage/CyberLink4CC.git clinkcc
WORKDIR clinkcc
RUN ./bootstrap && ./configure && make && make install
WORKDIR /tmp
RUN rm -rf clinkcc

# Round
RUN apt-get install -y libboost-all-dev libssl-dev libjansson-dev libv8-dev openjdk-6-jdk
WORKDIR /tmp
RUN git clone https://github.com/cybergarage/Round.git round
WORKDIR round
RUN ./bootstrap && ./configure_ubuntu && make && make install
WORKDIR /tmp
RUN rm -rf round

# JNI 
ENV JAVA_HOME `update-java-alternatives -l | head -n 1 | awk '{print $3}'`
ENV LD_LIBRARY_PATH $JAVA_HOME/jre/lib/amd64:$JAVA_HOME/jre/lib/amd64/server
