import React, { Component } from "react";
import styles from "../CSS/SingleTaskComponent.module.css";

class SingleTaskComponent extends Component {
  constructor(props) {
    super(props);
    this.state = {
      tasks: [],
    };
    this.goToTask = this.goToTask.bind(this);
  }

  goToTask() {
    this.props.history.push({
      pathname: "/tasks/" + this.props.taskID,
      state: {
        taskDescription: this.props.taskDescription,
        category: this.props.category,
        taskID: this.props.taskID,
        attackerHints: this.props.attackerHints,
        defenderHints: this.props.defenderHints,
        attackersDescription: this.props.attackersDescription,
        defendersDescription: this.props.defendersDescription,
        taskName: this.props.taskName,
        maxMessages: this.props.maxMessages,
        timestamp: this.props.timestamp,
      },
    });
  }

  render() {
    return (
      <>
        <div className={styles.box}>
          <li>
            <span className={styles.taskDescription}>
              {this.props.taskDescription}
            </span>
          </li>

          <div className={styles.catBox}>{this.props.category}</div>
          <div className={styles.dateBox}>
            Created
            {" " + this.props.timestamp}
          </div>
          <button
            onClick={this.goToTask}
            className={styles.More}
            value='More info'
          >
            More info
          </button>
        </div>
      </>
    );
  }
}

export default SingleTaskComponent;
