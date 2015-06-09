FROM cybergarage/round-dev:latest
MAINTAINER Satoshi Konno <skonno@cybergarage.org>

# uHTTP for C++
WORKDIR /root
WORKDIR uhttp
RUN git pull
RUN ./bootstrap && ./configure && make && make install
WORKDIR /root
RUN rm -rf uhttp

# mUPnP for C++
WORKDIR /root
WORKDIR mupnp
RUN git pull
RUN ./bootstrap && ./configure && make && make install
WORKDIR /root
RUN rm -rf mupnp

# uSQL for C++
#WORKDIR /root
#WORKDIR usql
#RUN git pull
#RUN ./bootstrap && ./configure && make && make install
#WORKDIR /root
#RUN rm -rf usql

# Round
WORKDIR /root
WORKDIR round
# RUN git pull
RUN ./bootstrap && ./configure_ubuntu && make && make install
WORKDIR /root
RUN rm -rf round

WORKDIR /root
