FROM cybergarage/round-dev:latest
MAINTAINER Satoshi Konno <skonno@cybergarage.org>

# uHTTP for C++
WORKDIR /tmp
WORKDIR uhttp
RUN git pull
RUN ./bootstrap && ./configure && make && make install
WORKDIR /tmp
RUN rm -rf uhttp

# mUPnP for C++
WORKDIR /tmp
WORKDIR mupnp
RUN git pull
RUN ./bootstrap && ./configure && make && make install
WORKDIR /tmp
RUN rm -rf mupnp

# Round
WORKDIR /tmp
WORKDIR round
RUN git pull
RUN ./bootstrap && ./configure && make && make install
WORKDIR /tmp
RUN rm -rf round

# JNI
ENV JAVA_HOME `update-java-alternatives -l | head -n 1 | awk '{print $3}'`
ENV LD_LIBRARY_PATH $JAVA_HOME/jre/lib/amd64:$JAVA_HOME/jre/lib/amd64/server

WORKDIR ~
