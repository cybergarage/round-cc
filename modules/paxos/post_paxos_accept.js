function post_paxos_accept(params) {
  var jsonParams = JSON.parse(result);
  var pn = jsonParams.pn;

  var lastPn = get_registry("_round.paxos.pn");

  if (pn < lastPn) {
    return "false";
  }

  set_registry(pn);
  
  var methodName = jsonParams.method;
  var methodParams = jsonParams.params;

  var postResults = post_method(methodName, methodParams);

  return "true";
};
