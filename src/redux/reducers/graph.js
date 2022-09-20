import { UPDATE_GRAPH } from "../actionTypes";

const initState = { 
  graph: {
    nodes: [],
    neighbors: [],
    paths: [],
  }
};

export default function(state = initState, action) {
  switch (action.type) {
    case UPDATE_GRAPH: {
      return { 
        api: action.payload.api,
      };
    }
    default: {
      return state;
    }
  }
}