import React from "react";
import logo from "./logo.svg";
import "./App.css";
import {
  BrowserRouter as Router,
  Route,
  Switch,
  Link,
  Redirect,
} from "react-router-dom";

import Login from "../src/pages/Login";
import Home from "../src/pages/Home";
import Spectate from "../src/pages/Spectate";
import Leaderboard from "./pages/Leaderboard";
import Challenges from "./pages/Challenges";
import Profile from "./pages/Profile";
import Chat from "./pages/Chat";
import WaitingPage from "./pages/Waiting";
import Register from "./pages/SignUp";
import matchDetails from "./pages/matchDetails";
import TaskHome from "./pages/TaskHome";
import { CookiesProvider } from "react-cookie";
import TasksPage from "./pages/TasksPage";
import SingleTaskPage from "./pages/SingleTaskPage";
import TasksProfile from "./pages/TasksProfile";
import MonitorTaskPage from "./pages/MonitorTaskPage";
import SpectatePage from "./pages/SpectatePage";
import AnnotateHome from "./pages/AnnotateHome";
import AnotatePage from "./pages/AnotatePage";
import AnnotateGameDetails from "./pages/AnnotateGameDetails";
import AnnotateProfile from "./pages/AnnotateProfile";
import MonitorSpectatePage from "./pages/MonitorSpectatePage";

function App() {
  return (
    <Router>
      <script src='https://cdn.jsdelivr.net/npm/js-cookie@2/src/js.cookie.min.js'></script>
      <Switch>
        <Route exact path='/login' component={Login} />
        <Route exact path='/' component={Login} />
        <Route exact path='/home' component={Home} />
        <Route exact path='/annotations/home' component={AnnotateHome} />
        <Route exact path='/annotations/profile' component={AnnotateProfile} />
        <Route exact path='/annotations/:id' component={AnotatePage} />
        <Route
          exact
          path='/annotations/:id/game_details'
          component={AnnotateGameDetails}
        />
        <Route exact path='/tasks/home' component={TaskHome} />
        <Route exact path='/tasks/allTasks' component={TasksPage} />
        <Route exact path='/tasks/profile' component={TasksProfile} />
        <Route exact path='/tasks/:id' component={SingleTaskPage} />
        <Route exact path='/tasks/:id/monitor' component={MonitorTaskPage} />
        <Route
          exact
          path='/tasks/:id/monitor/:id'
          component={MonitorSpectatePage}
        />
        <Route exact path='/tv' component={Spectate} />
        <Route exact path='/users/leaderboard' component={Leaderboard} />
        <Route exact path='/tv/:id' component={SpectatePage} />
        <Route exact path='/challenges' component={Challenges} />
        <Route exact path='/profile' component={Profile} />
        <Route exact path='/games/:id' component={Chat} />
        <Route exact path='/games/:id/matchDetails' component={matchDetails} />
        <Route exact path='/signup' component={Register} />
      </Switch>
    </Router>
  );
}

export default App;
