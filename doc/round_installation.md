![round_logo](./img/round_logo.png)

# Getting Started

## Installation

Official binary distributions are available for Linux and Mac OS X. If a binary distribution is not available for your combination of operating system and architecture, try installing from source.

### MacOSX

#### Homebrew

[Java for OS X 2014-001](http://support.apple.com/kb/DL1572)

To get started on OSX run the following in a terminal:

```
brew install round++
```

### Ubuntu

#### Docker

To get started with Docker on Linux run the following in a terminal:

```
docker run  cybergarage/round:<version>
```

### Installing from source

Round is an open source project, distributed under a [BSD-style license](../LICENSE). Round needs the following packages to comple from the source codes.

### Package requirements

| Package | Version |
|-|-|
| [Chrome V8](https://developers.google.com/v8/) | 3.25.30 or later |
| [OpenSSL](https://www.openssl.org) | 1.0.1 or later |
| libxml2 | ??? |
| [Jansson](http://www.digip.org/jansson/) | 2.6 or later |
| [mUPnP for C++](http://www.cybergarage.org/do/view/Main/CyberLinkForCC) | ??? |
| [µHTTP for C++](http://www.cybergarage.org/do/view/Main/HttpEngineForCC) | ??? |

## Running Round

First start a single-machine cluster of etcd:

```
./bin/roundd/roundd -f
```

Next, let's start the client utility command:

```
./bin/round/round
```
