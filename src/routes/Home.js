import React from "react";

import Graph from '../components/Graph.js'

import ws from '../libs/WSApi.js';

class Home extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      level: 50,
      isdone: false,
      nodes: [],
      edges: [],
      selectedNodes: [], 
      userPath: [],
      consumedNodes: [], 
      entityPath: [],
    }
  }

  componentDidMount() {
    const data = {
      cmd: 'CreateGame',
      data: 
      {
        level: 1
      },
    }

    ws.sendCommand(data.cmd, data)
    .then(response => {
      console.log(response);
      this.setState({
        nodes: response.details.nodes,
        edges: response.details.edges,
      });
    })
    .catch(error => {
      console.error(error);
    });
  }

  handleNodeClick(node) {
    const data = {
      cmd: 'GetPlayerMove',
      data: 
      {
        layer: node.layer,
        index: node.index
      },
    }
    ws.sendCommand(data.cmd, data)
    .then(response => {
      console.log(response);
      this.setState({
        isdone: response.details.isdone,
        selectedNodes: response.details.playernodes, 
        userPath: response.details.playeredges,
        consumedNodes: [...this.state.consumedNodes, ...response.details.newnodes], 
        entityPath: [...this.state.entityPath, ...response.details.newedges],
      });
    })
    .catch(error => {
      console.error(error);
    });
  }

  render() {
    const { 
      level,
      isdone,
      nodes,
      edges,
      selectedNodes, 
      userPath,
      consumedNodes, 
      entityPath, } = this.state;

    return (
      <div>
        <Graph 
          nodes={nodes}
          edges={edges}
          selectedNodes={selectedNodes}
          userPath={userPath}
          consumedNodes={consumedNodes}
          entityPath={entityPath}
          onNodeClick={this.handleNodeClick}
        />

      </div>
    )
  }
}

export default Home;