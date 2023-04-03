import React from "react";
import './App.css';
import { Home } from "./pages/Home";
import { useHistory} from "react-router-dom";
import {BrowserRouter as Router, Switch, Route} from "react-router-dom";

function App() {
 
  let history = useHistory(); 
  global.fullname = "";
  global.match = "";

  return (
    <Router>
      <div className="App">
        <Switch>
          <Route exact path="/">
              <Home />
          </Route>
        </Switch>
      </div>
      
    </Router>
    
  );
}

export default App;