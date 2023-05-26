export const get_graph_state = (store) => store.graph;

export const get_graph = (store) =>
get_graph_state(store) ? get_graph_state(store).graph : {};
