![round_logo](./img/round_logo.png)

# Round APIs

## APIs


### Request

| Parameter | M/U | Detail | Default | Constants |
|-|-|-|-|-|
| Method | M | Operation Method | - | GET, PUT |
| Sync | O | URI | Sync | Async,Sync |

HTTP and HTTPU, HTTMU,

```
PUT /rpc/do HTTP/1.1
Accept : "application/json-rpc"
{
  "jsonrpc": "2.0",
  "method": "subtract",
  "params": [42, 23], "id": 1
}
```

```
PUT /rpc/do HTTP/1.1
Accept : "application/json-rpc"
{
  "jsonrpc": "2.0",
  "method": "subtract",
  "params": [42, 23], "id": 1
}
```

Location


If a request is selected, the response will be returned over HTTPU.

### Response

HTTP or HTTPU
