import Content from './Content.js'

class Node {
  constructor(color, pos, cont=(new Content())) {
    this.color = color;
    this.layer = pos[0];
    this.index = pos[1];
    this.cont = cont;
  }

  isNullNode() {
    return this.cont.isnull;
  }
}

export default Node;