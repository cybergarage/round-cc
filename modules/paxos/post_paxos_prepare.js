function post_paxos_prepare(params) {
  var jsonParams = JSON.parse(result);
  var pn = jsonParams.pn;

  var lastPn = get_registry("_round.paxos.pn");

  if (lastPn < pn) {
    set_registry(pn);
    return pn;
  }

  return lastPn;
};
