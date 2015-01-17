![round_logo](./img/round_logo.png)

# Getting Started

Official binary distributions are available for Linux and Mac OS X. If a binary distribution is not available for your combination of operating system and architecture, try installing from source.

## Linux

### Docker

To get started with Docker on Linux, run the following in a terminal:

```
docker run cybergarage/round:<version>
```

## MacOSX

First, you have to install the following package on MacOSX.

- [Java for OS X 2014-001](http://support.apple.com/kb/DL1572)

### Homebrew

To get started on MacOSX, run the following in a terminal:

```
brew install round++
```

## Installing from source

Round is an open source project, distributed under a [BSD-style license](../LICENSE). Round needs the following packages to comple from the source codes.

### Package requirements

To compile from source, install the following packages on your platform.

| Package | Version | Mandatory ｜
|---|---|---|
| [OpenSSL](https://www.openssl.org) | 1.0.1 or later | O |
| [libxml2](http://xmlsoft.org/) | 2.2 or later | O |
| [Jansson](http://www.digip.org/jansson/) | 2.6 or later | O |
| [Spider Monkey ](https://developer.mozilla.org/ja/docs/SpiderMonkey) | 1.8.5 or later | O |
| [ANTLR3 C](http://www.antlr3.org/download.html) | 3.2 or later | O |
| [uHTTP for C++](http://www.cybergarage.org/do/view/Main/HttpEngineForCC) | 0.7.1 or later | O |
| [mUPnP for C++](http://www.cybergarage.org/do/view/Main/CyberLinkForCC) | 0.8 or later | O |
| [uSQL for C++](https://github.com/cybergarage/uSQL4CC) | 3.0 or later | O |
| [Chrome V8](https://developers.google.com/v8/) | 3.25.30 or later | - |
| [Java (JNI)](https://java.com/) | 1.6.0 or later | - |
| [Tcl](http://www.tcl.tk/) | 8.5.9 or later | - |

### Installation

To install on your platform, run the following in a terminal:

```
./boostrap && ./configure && make && sudo make install
```

## Running Round

First start a single-machine cluster of etcd:

```
./bin/roundd/roundd
```

Next, let's start the client utility command:

```
./bin/round/round
```
