import React from 'react'
import PropTypes from 'prop-types'
import Node from './Node.js'
import Edge from './Edge.js'
import Content from './Content.js'

import {drawCircle, drawLine} from './canvas_util.js'

const NUM_LAYERS = 5
const NUM_NODES_PER_LAYER = [1, 6, 12, 12, 6];
const RADIUS_INCREMENT = 100;

class Graph extends React.Component {

  constructor(props) {
    super(props);
    this.state = {
    };

    this.canvRef = React.createRef();

    this.nodemap = [];
    this.edgemap = [];

    this.initMaps();
    this.initGraph = this.initGraph.bind(this);
  }

  initMaps() {
    for (let i=0; i<NUM_LAYERS; i++) {
      for (let j=0; j<NUM_NODES_PER_LAYER[i]; j++) {
        const n = new Node("White", [i, j], new Content());
        this.nodemap.push(n);
      }
    }

    //console.log(this.nodemap);

    for (let i=0; i<NUM_LAYERS; i++) {
      for (let j=0; j<NUM_NODES_PER_LAYER[i]; j++) {
        const a = [i, j];
        if (i === 0) {
          for (let k=0; k<NUM_NODES_PER_LAYER[i+1]; k++) {
            const b = [i+1, k]
            this.edgemap.push(new Edge(a, b));
          }
        } else if (i === 1) {
          const adj = (j+1)%NUM_NODES_PER_LAYER[i];
          this.edgemap.push(new Edge(a, [i, adj]))
          for (let k=0; k<4; k++){
            const t = NUM_NODES_PER_LAYER[i+1]+((j*2)-k+1);
            const b = [i+1, t%NUM_NODES_PER_LAYER[i+1]];
            this.edgemap.push(new Edge(a, b));
          }
        } else if (i === 2) {
          const adj = (j+1)%NUM_NODES_PER_LAYER[i];
          this.edgemap.push(new Edge(a, [i, adj]))
          for (let k=0; k<2; k++){
            const t = j+k;
            const b = [i+1, t%NUM_NODES_PER_LAYER[i+1]];
            this.edgemap.push(new Edge(a, b));
          }
        } else if (i === 3) {
          const adj = (j+1)%NUM_NODES_PER_LAYER[i];
          this.edgemap.push(new Edge(a, [i, adj]))
        } else if (i === 4) {
          for (let k=0; k<3; k++){
            const t = NUM_NODES_PER_LAYER[i-1]+((j*2)-k+1)
            const b = [i-1, t%NUM_NODES_PER_LAYER[i-1]];
            this.edgemap.push(new Edge(a, b));
          }
        }
      }
    }

    //console.log(this.edgemap);
  }

  getCoorForPercent(percent, rad, offset=0) {
    const x = rad * Math.cos(2 * Math.PI * percent + offset);
    const y = rad * Math.sin(2 * Math.PI * percent + offset);
    return [x, y];
  }

  getNodeCoorOnCanvas(layer, index) {
    const rad = layer * RADIUS_INCREMENT;
    const anglePercent = index / NUM_NODES_PER_LAYER[layer];
    let offset = -Math.PI/2;
    if (layer === 2) offset += 15/180 * Math.PI;
    let [x, y] = this.getCoorForPercent(anglePercent, rad, offset);

    const width = this.canvRef.current.width;
    const height = this.canvRef.current.height;
    return [(x+width/2), (y+height/2)];
  }

  drawNodeMap = () => this.nodemap.forEach((node) => {
    const [x, y] = this.getNodeCoorOnCanvas(node.layer, node.index);
    const ctx = this.canvRef.current.getContext("2d");

    drawCircle(ctx, [x, y], 25, "#edeae4", "#c4c3c0", 5);
  })

  drawEdgeMap = () => this.edgemap.forEach((edge) => {
    const [x1, y1] = this.getNodeCoorOnCanvas(edge.a[0], edge.a[1]);
    const [x2, y2] = this.getNodeCoorOnCanvas(edge.b[0], edge.b[1]);

    const ctx = this.canvRef.current.getContext("2d");
    drawLine(ctx, [x1, y1], [x2, y2], "#e0e0e0", 5);
  })

  drawNodes = () => this.props.nodes.forEach((node) => {
    const [x, y] = this.getNodeCoorOnCanvas(node.layer, node.index);
    const ctx = this.canvRef.current.getContext("2d");

    drawCircle(ctx, [x, y], 25, "#adadad", "#050505", 10);
    console.log([x, y]);
  })

  drawEdges = () => this.props.edges.forEach((edge) => {
    const [x1, y1] = this.getNodeCoorOnCanvas(edge.a[0], edge.a[1]);
    const [x2, y2] = this.getNodeCoorOnCanvas(edge.b[0], edge.b[1]);

    const ctx = this.canvRef.current.getContext("2d");
    drawLine(ctx, [x1, y1], [x2, y2], "#adadad", 10);
  })

  drawSelectedNodes = () => this.props.selectedNodes.forEach((node) => {
    const [x, y] = this.getNodeCoorOnCanvas(node.layer, node.index);
    const ctx = this.canvRef.current.getContext("2d");

    drawCircle(ctx, [x, y], 25, "#5c0101", "#050505", 10);
  })

  drawUserPath = () => this.props.userPath.forEach((edge) => {
    const [x1, y1] = this.getNodeCoorOnCanvas(edge.a[0], edge.a[1]);
    const [x2, y2] = this.getNodeCoorOnCanvas(edge.b[0], edge.b[1]);

    const ctx = this.canvRef.current.getContext("2d");
    drawLine(ctx, [x1, y1], [x2, y2], "#5c0101", 10);
  })

  drawConsumedNodes = () => this.props.consumedNodes.forEach((node) => {
    const [x, y] = this.getNodeCoorOnCanvas(node.layer, node.index);
    const ctx = this.canvRef.current.getContext("2d");

    drawCircle(ctx, [x, y], 25, "#242424", "#242424", 10);
  })

  drawEntityPath = () => this.props.entityPath.forEach((edge) => {
    const [x1, y1] = this.getNodeCoorOnCanvas(edge.a[0], edge.a[1]);
    const [x2, y2] = this.getNodeCoorOnCanvas(edge.b[0], edge.b[1]);

    const ctx = this.canvRef.current.getContext("2d");
    drawLine(ctx, [x1, y1], [x2, y2], "#242424", 10);
  })

  addHoverEventListenerOnCanvas = () => {
    this.canvRef.current.addEventListener('mousemove', 
    (event)=>{
      const [x, y] = [event.pageX, event.pageY];
      const locs = this.nodemap.map((node) => {
        return this.getNodeCoorOnCanvas(node.layer, node.index);
      })

      function dist ([x1, y1], [x2, y2]) {
        const x = x2 - x1;
        const y = y2 - y1;
        return Math.sqrt(x*x + y*y);
      }

      let isIn = false;

      locs.forEach((e) => {
        isIn = isIn || (dist([x, y], e) < 25);
      })

      if (isIn) {
        this.canvRef.current.style.cursor='pointer';
      } else {
        this.canvRef.current.style.cursor='default';
      }
    }, 
    false);
  }

  addClickEventListenerOnCanvas= () => {
    this.canvRef.current.addEventListener('click', 
    (event)=>{
      const [x, y] = [event.pageX, event.pageY];

      function dist ([x1, y1], [x2, y2]) {
        const x = x2 - x1;
        const y = y2 - y1;
        return Math.sqrt(x*x + y*y);
      }

      this.nodemap.forEach((n) => {
        const [nx, ny] = this.getNodeCoorOnCanvas(n.layer, n.index);
        if (dist([x, y], [nx, ny]) < 25) {
          this.props.onNodeClick(n);
        }
      })
    }, 
    false);
  }

  initGraph() {
    if (this.canvRef.current) {
      const w = this.canvRef.current.width;
      const h = this.canvRef.current.height;
      const ctx = this.canvRef.current.getContext('2d');
      ctx.clearRect(0, 0, w, h);
      this.drawEdgeMap();
      this.drawNodeMap();
      this.addClickEventListenerOnCanvas();
      this.addHoverEventListenerOnCanvas();
    }
  }

  componentDidMount() {
    console.log(this.canvRef.current);
    this.initGraph();
  }

  componentDidUpdate(prevProp) {

    if (prevProp.level !== this.props.level) {
      this.initGraph();
    }

    if (prevProp.nodes !== this.props.nodes) {
      console.log(this.props.nodes);
      this.drawEdges();
      this.drawNodes();
    }

    if (prevProp.selectedNodes !== this.props.selectedNodes) {
      console.log(this.props.selectedNodes);
      this.drawUserPath();
      this.drawSelectedNodes();
    }

    if (prevProp.consumedNodes !== this.props.consumedNodes) {
      console.log(this.props.consumedNodes);
      this.drawEntityPath();
      this.drawConsumedNodes();
    }

  }

  render() {
    const { 
      nodes, edges, 
      selectedNodes, userPath,
      consumedNodes, entityPath } = this.props;

    return (
      <canvas 
        ref={this.canvRef}
        id='graph'
        width='1000'
        height='880'>
      </canvas>
      
    )
  }
}

Graph.propTypes = {
  nodes: PropTypes.arrayOf(PropTypes.object),
  edges: PropTypes.arrayOf(PropTypes.object),
  selectedNodes: PropTypes.arrayOf(PropTypes.object),
  userPath: PropTypes.arrayOf(PropTypes.object),
  consumedNodes: PropTypes.arrayOf(PropTypes.object),
  entityPath: PropTypes.arrayOf(PropTypes.object),
}

export default Graph;