import React, { Component } from "react";
import TopBarTasksComponent from "../Components/TopBarTasksComponent";
import styles from "../CSS/SingleTaskPage.module.css";

class SingleTaskPage extends Component {
  state = {};
  render() {
    return (
      <>
        <TopBarTasksComponent />
        <div className={styles.header}>
          <h1>Task {this.props.location.state.taskID}</h1>
        </div>
        <div className={styles.MainGrid}>
          <div className={styles.wrapper}>
            <div className={styles.title}>Task Name</div>
            <div className={styles.content}>
              {this.props.location.state.taskName}
            </div>
            <div className={styles.title}>Task Description</div>
            <div className={styles.content}>
              {this.props.location.state.taskDescription}
            </div>
            <div className={styles.title}>Attacker‘s Description/Scenario</div>
            <div className={styles.content}>
              {this.props.location.state.attackersDescription}
            </div>
            <div className={styles.title}>Defender‘s Description/Scenario</div>
            <div className={styles.content}>
              {this.props.location.state.defendersDescription}
            </div>
            <div className={styles.title}>Max Messages </div>
            <div className={styles.content}>
              {this.props.location.state.maxMessages}
            </div>
          </div>
          <div className={styles.wrapper2}>
            <div className={styles.title}>Category</div>
            <div className={styles.content}>
              {this.props.location.state.category}
            </div>
            <div className={styles.title}>Attacker’s Hints/Guidelines</div>
            <div className={styles.content}>
              {this.props.location.state.attackerHints}
            </div>
            <div className={styles.title}>Defender's Hints/Guidelines</div>
            <div className={styles.content}>
              {this.props.location.state.taskName}
            </div>
            <div className={styles.title}>Number of players</div>
            <div className={styles.content}>2-players game</div>
            <div className={styles.title}>Created</div>
            <div className={styles.content}>
              {this.props.location.state.timestamp}
            </div>
          </div>
        </div>
      </>
    );
  }
}

export default SingleTaskPage;
