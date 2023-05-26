import React from "react";

import Content from "../components/Content.js";
import Node from "../components/Node.js"
import Edge from "../components/Edge.js"
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

    // Bind methods to the component instance
    this.handleNodeClick = this.handleNodeClick.bind(this);
  }

  componentDidMount() {
    const data = {
      cmd: 'CreateGame',
      data: 
      {
        level: 15
      },
    }

    ws.sendCommand(data.cmd, data)
    .then(response => {
      console.log(response);
      this.setState({
        nodes: response.details.nodemap.map((node) => {
          return new Node(node[0], node[1].pos, new Content(node[2][0], node[2][1]));
        }),
        edges: response.details.edgemap.map((edge) => {
          return new Edge(edge[0][0], edge[1][0]);
        }),
        selectedNodes: [new Node("red", [0, 0], new Content())],
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
        layer: JSON.parse(node.layer),
        index: JSON.parse(node.index),
      },
    }
    ws.sendCommand(data.cmd, data)
    .then(response => {
      console.log(response.details);
      this.setState({
        isdone: response.details.isdone,
        selectedNodes: response.details.playernodes.map((node) => {
          return new Node(node[0], node[1].pos, new Content(node[2][0], node[2][1]));
        }), 
        userPath: response.details.playeredges.map((edge) => {
          return new Edge(edge[0][0], edge[1][0]);
        }),
        consumedNodes: [...this.state.consumedNodes, ...response.details.newnodes.map((node) => {
          return new Node(node[0], node[1].pos, new Content(node[2][0], node[2][1]));
        })], 
        entityPath: [...this.state.entityPath, ...response.details.newedges.map((edge) => {
          return new Edge(edge[0][0], edge[1][0]);
        })],
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

      console.log(this.state.nodes);

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