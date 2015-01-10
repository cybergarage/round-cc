![round_logo](img/round_logo.png)

[English](round_overview_jp.md) Japanese

# 概要

## Roundとは ?

Roundは分散システム開発者や研究者向けの新しいオープンソースのフレームワークです。 Roundは、利用者が簡潔に分散アプリケーションを開発するのを支援します。

Roundの名前は「[円卓の騎士](http://ja.wikipedia.org/wiki/円卓の騎士)」に由来しており、クラスターの全てのノードが等しい役割を持ち、マスターノードが存在していないことを意味しています。

## 設計原則

Roundは以下の原則に基づいて設計されて``います。

### 簡潔性

簡潔性は重要な原則の一つです。Roundのコアモジュールは極めてシンプルであり最低限の機能のみ実装されています。簡潔さに関連する直交性も重要な原則です。これらの原則により、コアモジュールを簡潔に保つために、冗長な機能は実装されません。

### 明確性

コアモジュールの技術仕様については明確に定義されており利用者に公開されています。技術仕様は業界標準のネットワークプロトコルを拡張して定義されています。

Roundの初期バージョンはC++で実装されていますが、公開されているRoundの技術仕様から、JavaやGoなどの他のプログラミング言語でコアモジュールを実装することも可能です。

## Design Features

### Zeroconf

In typical cloud systems, some configurations such as the ip address and the service port are needed to add a new node manually, but the manual configurations are obstacle for auto scale distributed systems. In Round, all new nodes are added into a cluster without special configuration and the nodes are available soon automatically.

![round_overview_zeroconf](img/round_overview_zeroconf.png)

In Round, some noficication events are defined for the node statues. When a node status is changed, the notification message is sent to all other nodes  in the same cluster. For example, each existing node is recieved a notirication message when a new node is added or removed.

### Decentralized

Round is a decentralized and distributed system, every nodes in a cluster has equal roll, the cluster has no master node. In typical distributed systems are centric, they has a master node.

![round_overview_zeroconf](img/round_overview_decentralized.png)

### Dynamics

The behaviors of node are defined using a dynamic programming language script, so the distributed strategies and algorithms are configurable dynamically. To send a script, developers can change the strategy and algorithm of all nodes in the cluster dynamically.

![round_overview_dynamics](img/round_overview_dynamics.png)

### Autonomous

Each node run as an autonomous agent in the cluster, a node communicate to other nodes based on the specified behaviors using the message protocol synchronously or asynchronously.

![round_overview_autonomous](img/round_overview_autonomous.png)

The some basic behaviors are defined as default, and developers can override the default behaviors or add new behaviors using some programming languages such as JavaScript or Java.

## Support Functions

Round supports the following functions to develop distrubted applications or systems.

### Auto Configuration

To add a new node into a cluster.

### Service Discovery

### Dynamic Configuration

### Messaging

Node can communicate to other nodes in the same cluster using [RPC (remote procedure call)](http://en.wikipedia.org/wiki/Remote_procedure_call).

### Security

Monochrome iconset by [Danny Allen](http://dannya.org).
