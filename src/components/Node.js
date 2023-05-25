import Content from './Content.js'

class Node {
  constructor(layer=-1, index=-1, cont=(new Content())) {
    this.layer = layer;
    this.index = index;
    this.cont = cont;
  }

  isNullNode() {
    return this.cont.isnull;
  }
}

export default Node;