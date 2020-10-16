import React, { Component } from "react";
import Cookies from "universal-cookie";
import TopBarTasksComponent from "../Components/TopBarTasksComponent";
import TaskTabProfile from "../Components/TaskTabProfile";
import styles from "../CSS/TasksProfile.module.css";

class TasksProfile extends Component {
  constructor(props) {
    super(props);
    var cookies = new Cookies();
    this.state = {
      cookie: cookies.get("userID"),
      stateCounter: 0,
      totalTags: [],
      totalMessages: [],
    };
  }

  componentDidMount() {
    Promise.all([
      fetch("http://localhost:7777/users/" + this.state.cookie).then((value) =>
        value.json()
      ),
      fetch("http://localhost:7777/tasks").then((value) => value.json()),
      fetch("http://localhost:7777/games").then((value) => value.json()),
    ])
      .then((value) => {
        this.setState(
          {
            user: value[0],
            tasks: value[1],
            games: value[2],
            isLoaded: true,
          },
          () => {
            this.countTasks();
          }
        );

        console.log(this.state.tasks);
        //json response
      })
      .catch((err) => {
        console.log(err);
      });
  }

  countTasks() {
    var counter = 0;
    for (var i = 0; i < this.state.tasks.length; i++) {
      if (this.state.tasks[i].taskCreator == this.state.cookie) {
        counter++;
      }
    }
    this.setState({
      stateCounter: counter,
    });
  }

  render() {
    var history = this.props.history;
    const { error, isLoaded, tasks, user, games } = this.state;
    if (error) {
      return <div>Error: {error.message}</div>;
    } else if (!isLoaded) {
      return <div>Loading...</div>;
    } else {
      return (
        <>
          <TopBarTasksComponent />
          <div className={styles.profileDiv}>
            <img src='../../user.png'></img>
            <div className={styles.imageText}>Edit</div>
          </div>
          <div className={styles.username}>{this.state.user.username}</div>
          <div className={styles.stats}>
            <span className={styles.Tasks}>Tasks Created </span>
          </div>
          <div className={styles.stats1}>
            <div className={styles.games}>{this.state.stateCounter}</div>
          </div>
          <div className={styles.history}>Tasks history</div>
          <div className={styles.tabs}>
            {this.state.tasks
              .filter(function (task) {
                // filter first for friends
                return task.taskCreator == user.userID;
              })
              .map(function (task) {
                // map the new array to list items
                return (
                  <TaskTabProfile
                    taskName={task.taskName}
                    taskID={task.taskID}
                    taskDescription={task.taskDescription}
                    attackersDescription={task.attackersDescription}
                    defendersDescription={task.defendersDescription}
                    category={task.category}
                    attackerHints={task.attackerHints}
                    defenderHints={task.defenderHints}
                    maxMessages={task.maxMessages}
                    taskCreator={task.taskCreator}
                    timestamp={task.timestamp}
                    active={task.active}
                    history={history}
                  />
                ); // don't forget unique key for each item
              }, this)}
          </div>
        </>
      );
    }
  }
}

export default TasksProfile;
