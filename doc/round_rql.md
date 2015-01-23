![round_logo](./img/round_logo.png)

# RQL - Round Query Language

RQL (Round Query Language) is a DSL (Domain specific language) for Round. RQL supports to call RPC methods more easily.

## Specification

```
RQL = (
    RPC-method-query |
    package-query |
    key-value-query
  )
```

### RPC method

The RPC method query call the specified method into the node with the paramters.

```
RPC-method-query = method-name target params

target       = [cluster "."] node
cluster      = cluster-name)
node         = ("all" | "*" | hash-code)

method-name  = TOKEN
params       = TOKEN
cluster-name = TOKEN
hash-code    = NODE_HASH
```

#### Examples

```
set_key * {"key": "name", "value": "Satoshi Konno"}
```

### Package method

The package query manages the modules defined methods and routes.

```
package-query = "rpm" command

command = (install-command | remove-command | list-command)

install-command = "install" package-name url
remove-command = "remove" package-name
list-command = "list"

package-name = TOKEN
url          = URL_TOKEN
```

The queries are implemented as general methods such as package_install() or package_remove(), then you can call the methods directly as the following

```
package_install * {"url" : " http://github.com/cybergarage/Round/modules/sample.mod/"}
```

#### Examples

```
set_key * {"key": "", "value": ""}
```

## HTTP Request

### Request-Line

RQL supports only GET methods. The request entry point must be begin with "/rql" as the following. The RQL in the request line must be encoded by URL Encode.

```
Request-Line = Method SP Request-URI SP HTTP-Version CRLF

Method = "PUT" | "GET"
Request-URI = "/rql" "?" "query=" RQL

ROL = URLEncoded-RQL
```
