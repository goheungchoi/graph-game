import React from "react";

import Content from "../components/Content.js";
import Node from "../components/Node.js"
import Edge from "../components/Edge.js"
import Graph from '../components/Graph.js'

import ws from '../libs/WSApi.js';
import { connect } from 'react-redux'
import { update_graph } from '../redux/actions'
import { get_graph } from '../redux/selectors.js'

class Home extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      level: this.props.graph.level,
      isdone: this.props.graph.isdone,
      nodes: this.props.graph.nodes,
      edges: this.props.graph.edges,
      selectedNodes: this.props.graph.selectedNodes, 
      userPath: this.props.graph.userPath,
      consumedNodes: this.props.graph.consumedNodes, 
      entityPath: this.props.graph.entityPath,
    }

    // Bind methods to the component instance
    this.handleNodeClick = this.handleNodeClick.bind(this);
    this.sendGetPlayerMove = this.sendGetPlayerMove.bind(this);
  }

  sendCreateGame(_level) {
    const data = {
      cmd: 'CreateGame',
      data: 
      {
        level: _level
      },
    }

    ws.sendCommand(data.cmd, data)
    .then(response => {
      console.log(response);
      this.setState({
        isdone: false,
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

  sendGetPlayerMove (_layer, _index) {
    const data = {
      cmd: 'GetPlayerMove',
      data: 
      {
        layer: _layer,
        index: _index,
      },
    }
    ws.sendCommand(data.cmd, data)
    .then(response => {
      const funcs = async() => {
        const getGraphData = async () => {
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
        }
  
        const createNewGame = async() => {
          if (this.state.isdone) {
            this.sendCreateGame(this.state.level+1);
            this.setState({
              level: this.state.level+1,
              isdone: false,
              nodes: [],
              edges: [],
              selectedNodes: [], 
              userPath: [],
              consumedNodes: [], 
              entityPath: [],
            })
            console.log(this.state.level);
          }
        }
  
        await getGraphData();
        await createNewGame();
      }
      
      funcs();
    })
    .catch(error => {
      console.error(error);
    });
  }

  componentDidMount() {
    this.sendCreateGame(this.state.level);
  }

  handleNodeClick(node) {
    this.sendGetPlayerMove(node.layer, node.index);
  }

  render() {
    const { 
      level,
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
          level={level}
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

export default connect(
  state => ({ 
    graph: get_graph(state) }), 
  { update_graph }) 
  (Home);