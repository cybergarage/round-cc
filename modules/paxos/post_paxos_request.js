function post_paxos_request(params) {
  var lastPn = get_registry("_round.paxos.pn");
  var pn = lastPn + 1;

  var prepareResults = post_method("post_paxos_prepare", pn, "*");
  var jsonPrepareResults = JSON.parse(prepareResults);

  var jsonParams = JSON.parse(result);
  var methodName = jsonParams.method;
  var methodParams = jsonParams.params;
  
  var acceptResults = post_method("post_paxos_accept", pn + params, "*");
  var jsonAcceptResults = JSON.parse(acceptResults);

  return params;
};
