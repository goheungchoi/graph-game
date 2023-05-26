import { UPDATE_GRAPH } from "../actionTypes";

const initState = { 
  graph: {
    level: 1,
    isdone: false,
    nodes: [],
    edges: [],
    selectedNodes: [], 
    userPath: [],
    consumedNodes: [], 
    entityPath: [],
  }
};

export default function(state = initState, action) {
  switch (action.type) {
    case UPDATE_GRAPH: {
      return { 
        graph: action.payload.graph,
      };
    }
    default: {
      return state;
    }
  }
}