import { UPDATE_GRAPH } from "./actionTypes.js";

export const update_graph = (graph) => ({
  type: UPDATE_GRAPH,
  payload: { graph: {level:1} },
})