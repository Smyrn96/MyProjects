import React, { Component } from "react";
import TopBarTasksComponent from "../Components/TopBarTasksComponent";
import styles from "../CSS/TasksPage.module.css";
import SingleTaskComponent from "../Components/SingleTaskComponent";

class TasksPage extends Component {
  state = {};

  componentDidMount() {
    fetch("http://localhost:7777/tasks")
      .then((value) => value.json())
      .then((value) => {
        this.setState({
          tasks: value,
          isLoaded: true,
        });

        console.log(this.state.tasks);
        //json response
      })
      .catch((err) => {
        console.log(err);
      });
  }

  timestampTime(timestamp) {
    var dateObj = new Date(timestamp);
    var utcString = dateObj.toLocaleString();
    return utcString;
  }

  render() {
    const { error, isLoaded, tasks } = this.state;

    if (error) {
      return <div>Error: {error.message}</div>;
    } else if (!isLoaded) {
      return <div>Loading...</div>;
    } else {
      return (
        <>
          <TopBarTasksComponent />
          <div className={styles.title}>
            <h1>Tasks</h1>
          </div>
          <div className={styles.MainGrid}>
            {this.state.tasks.map((task) => (
              <SingleTaskComponent
                taskDescription={task.taskDescription}
                category={task.category}
                taskID={task.taskID}
                attackerHints={task.attackerHints}
                defenderHints={task.defenderHints}
                attackersDescription={task.attackersDescription}
                defendersDescription={task.defendersDescription}
                taskName={task.taskName}
                maxMessages={task.maxMessages}
                timestamp={this.timestampTime(task.timestamp)}
                history={this.props.history}
              />
            ))}
          </div>
        </>
      );
    }
  }
}

export default TasksPage;
