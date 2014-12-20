![round_logo](./img/round_logo.png)

# Getting Started

## Getting Round

The latest release and setup instructions are available at [GitHub](https://github.com/cybergarage/Round).

## Installing Round

### Installing from distribution

Official binary distributions are available for Linux, FreeBSD, Mac OS X. If a binary distribution is not available for your combination of operating system and architecture, try installing from source.

### System requirements

| Operating system	| Architectures | Notes |
|-|-|-|
| FreeBSD 8 or later | amd64, 386, arm | 	Debian GNU/kFreeBSD not supported |
| Linux 2.6.23 or later with glibc | amd64, 386, arm | 	CentOS/RHEL 5.x not supported |
| Mac OS X 10.6 or later | amd64, 386 | You only need to install the command line tools for Xcode .|

### Installing from source

Round is an open source project, distributed under a [BSD-style license](../LICENSE). Round needs the following packages to comple from the source codes.

### Package requirements

| Package | Version |
|-|-|
| [Chrome V8](https://developers.google.com/v8/) | 3.25.30 or later |
| [OpenSSL](https://www.openssl.org) | 1.0.1 or later |
| libxml2 | ??? |
| [Jansson](http://www.digip.org/jansson/) | 2.6 or later |
| [CyberLink for C++](http://www.cybergarage.org/do/view/Main/CyberLinkForCC) | ??? |
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

## Next Steps
