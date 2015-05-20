function post_paxos_accept(params) {
  var jsonParams = JSON.parse(result);
  var methodName = jsonParams.method;
  var methodParams = jsonParams.params;

  var pn = get_node ....
  var prepareResults = post_method("all", "post_paxos_prepare", pn);
  var jsonPrepareResults = JSON.parse(prepareResults);

  var acceptResults = post_method("all", "post_paxos_accept", pn + params);
  var jsonAcceptResults = JSON.parse(acceptResults);

  return params;
};
