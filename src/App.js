import {
  BrowserRouter as Router,
  Routes,
  Route,
} from 'react-router-dom';

import Home from './routes/Home.js';
import About from './routes/About.js';

function App() {

  return (
    <div className="App">
      {/* <Routes>
        <Route path="/about/" element={About} />
        <Route exact path="/" element={Home} />
      </Routes> */}
      <Home />
    </div>
  );
}

export default App;
