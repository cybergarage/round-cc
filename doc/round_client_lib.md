![round_logo](./img/round_logo.png)

# Client Libraries

The client libraries handles add the following parameters into RPC requests automatically.

- id
- ts (Lamport Timestamp)

The libraries handles the RPC responses and updates local information of Client.

- Clusters
- Nodes in clusters
- Timestamp (Lamport Timestamp)

## JavaScript

Round supports JavaScript using [SpilderMonky](https://developer.mozilla.org/ja/docs/SpiderMonkey). Currently Round provides the following special functions.

### Functions

#### set_registry(key, value)

The set_registry function sets the specified key and value into the local node registry.

##### Parameters

- key : string
- value : string

##### Return value

- true or false

##### Example

The following code shows how to use the set_registry function.

```
var key = "name";
var val = "Satoshi Konno";
var ok = set_registry(key, val);
```

#### get_registry(key)

The get_registry function returns a registry by the specified key from the local node registry.

##### Parameters

- key : string

##### Return value

- a specified registry JSON string, or false when the specified registry is not found.

```
{
  "key"  : <string value>
  "value": <string value>,
  "ts"   : <integer value>
  "lts"  : <integer value>
}
```

##### Example

The following code shows how to use the get_registry function.

```
var result = get_registry("name");
if (result != false) {
  var jsonReg = JSON.parse(result);
  var jsonReg.value);
}
```

#### post_method(method, params, obj)

The post_method

#### get_network_state()

The get_network_state function

#### get_cluster_state()

The get_cluster_state function

#### get_network_state ()

The get_network_state function

## C++

Under Development :wink:

## Java

Under Development :wink:

## Go

Under Development :wink:

## Lua

[JSON4Lua](http://json.luaforge.net)

# Native Interfaces

Round is implemented by C++, you can add static system methods by the native programming language.

## Adding Native Methods

### Sever and Method class

First, create a sub class of Round::Server() to add the native methods. Next, create a sub class of Round::Method() and add the method class using Round::Server::addMethod() in Round::Server::initialize().


```
#include <round/Round.h>

class MyMethod : public Round::Method {
  .....
  bool exec(const Node *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
    .....
  }
}

class MyServer : public Round::Server {
  .....
  void initialize() {
    addMethod(new MyMethod());
  }
}
```
