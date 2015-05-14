![round_logo](img/round_logo.png)

[English](round_overview_jp.md) Japanese

# 概要

## Roundとは ?

Roundは分散システム開発者や研究者向けの新しいオープンソースのフレームワークです。 Roundは、利用者が簡潔に分散アプリケーションを開発するのを支援します。

Roundの名前は「[円卓の騎士](http://ja.wikipedia.org/wiki/円卓の騎士)」に由来しており、クラスターの全てのノードが等しい役割を持ち、マスターノードが存在していないことを意味しています。

Roundは、分散アプリケーション開発の基盤フレームワークであり、以下のような多種多様な分散アプリケーションの開発を支援します。

- コンセンサスサービス (Chubby, ZooKeeper, etcd ...)
- 分散処理フレームワーク (Hadoop, Storm, Spark ...)
- 分散ファイルシステム (GFS, HDFS, ...)
- 分散データベース (Dynamo, Cassndra, ...)

Roundでの分散アプリケーション開発の詳細については「[Round Design Patterns](round_design_pattern.md)」を参照してください。

## 設計原則

Roundは以下の原則に基づいて設計されています。

### 簡潔性

簡潔性は重要な原則の一つです。Roundのコアモジュールは極めてシンプルであり最低限の機能のみ実装されています。簡潔さに関連する直交性も重要な原則です。これらの原則により、コアモジュールを簡潔に保つために、冗長な機能は実装されません。

### 明確性

コアモジュールの技術仕様については明確に定義されており利用者に公開されています。技術仕様は業界標準のネットワークプロトコルを拡張して定義されています。

Roundの初期バージョンはC++で実装されていますが、公開されているRoundの技術仕様から、JavaやGoなどの他のプログラミング言語でコアモジュールを実装することも可能です。

## 特徴

### Zeroconf

一般的なクラウドシステムでは、分散サービスを起動するために利用者による設定が必要となります。RoundではZeroconfにより利用者による設定を極力不要になるよう設計されています。

Zeroconfとは、利用者による設定が不要な、サービス発見の技術です。Roundでは、すべての新規ノードは特別な設定なしにクラスターに追加され、自動的に利用可能となります。

![round_overview_zeroconf](img/round_overview_zeroconf.png)

### 非集中型

Roundは非集中型の分散システムで、クラスターにある全てのノードは等しい役割を持ちます。 典型的な幾つかのコンセンサスサービスのような分散システムは集中型でマスターノードが存在しますが、Roundにはマスターノードは存在しません。

![round_overview_zeroconf](img/round_overview_decentralized.png)

### 自律的

各ノードは指定されたプログラミングにより指定された振る舞いにによる自律的なエージェントとして動作します。各ノードは指定された振る舞いにより、他ノードと同期または非同期のメッセージを自律的に交換します。

![round_overview_autonomous](img/round_overview_autonomous.png)

### 動的

ノードの振る舞いは、動的または静的なプログラミング言語で定義されます。各ノードにプログラミング言語スクリプトを送信することにより、動的に振る舞いを変更できます。

![round_overview_dynamics](img/round_overview_dynamics.png)

## 提供機能

Roundは、分散システムアプリケーションを簡単に開発するために以下の機能を提供します。

### 分散プログラミング

Roundでは、分散アプリケーション開発に必要となる分散アルゴリズムをサポートしています。

- リーダー選出
- コンセンサスアルゴリズム (Paxos, Two-Phase Commit, ....)
- ....

### 動的プログラミング

Roundのノードはプログラミング可能なRPC([Remote Procedure Call](http://en.wikipedia.org/wiki/Remote_procedure_call))ノードです。Roundでは、各ノードに動的にスクリプトを追加したり、イベントをそのスクリプトに関連付けたりしながら、分散システムアプリケーションを構築していきます。

![auto-configuration](img/round_core_module.png)

### 複数プログラミング言語対応

RoundはJavaScritやJavaなどの複数の動的プログラミング言語に対応していますので、利用者の好みのプログラミング言語で分散システムアプリケーションが開発できます。C++などの静的プログラミング言語にも対応しています。

![auto-configuration](img/round_overview_programming.png)

### 自動認識

新しく起動されたRoundノードは、ネットワークに自動的に追加されます。同じネットワークの他のノードは、ノードが追加されたり削除されたりすると、そのイベントを受信します。

![auto-configuration](img/round_overview_autoconfig.png)

Roundは、自走設定に以外にも自動設定でないネットワークや固定的な設定にも対応しています。

Monochrome iconset by [Danny Allen](http://dannya.org).
