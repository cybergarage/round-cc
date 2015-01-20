![round_logo](./img/round_logo.png)

# RQL - Round Query Language

RQL (Round Query Language) is a DSL (Domain specific language) for Round. RQL supports to call RPC methods more easily.

## Specification

```
RQL = (
    RPC-method-query |
    key-value-query
  )
```

### RPC method

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
