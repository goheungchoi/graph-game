export const get_graph_state = (store) => store.graph;

export const get_graph = (store) =>
  get_api_state(store) ? get_api_state(store).graph : {};
