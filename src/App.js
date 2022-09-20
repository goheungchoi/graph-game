import {
  BrowserRouter as Router,
  Switch,
  Route,
} from 'react-router-dom';
import api from './libs/WSApi.js';
import Home from './routes/Home.js';

function App() {
  try {
    api.onmessage = (msg, data) => {
      if ("event" in data) {
        if (data.event == "UpdateGraph") {
          console.log(data.details);
          addEntity(data.details);
        }
        if (data.event == "UpdateEntity") {
        }
        if (data.event == "RemoveEntity") {
          removeEntity(data.details.id);
        }
      }
    }
  } catch(exception) {
    alert('<p>Error' + exception);
  }

  return (
    <div className="App">
      <Router>
        <Switch>
          <Route path="/about/" component={About} />
          <Route exact path="/" component={Home} />
        </Switch>
      </Router>
    </div>
  );
}

export default App;
