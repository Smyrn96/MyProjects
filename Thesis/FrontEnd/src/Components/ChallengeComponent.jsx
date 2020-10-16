import React, { Component } from "react";
import styles from "../CSS/Challenges.module.css";

class ChallengeComponent extends Component {
  constructor(props) {
    super(props);
    this.changeState = this.changeState.bind(this);
  }

  state = {};

  changeState() {
    this.setState({
      title: "Play 5 games",
      progress: 2,
      max: 5,
      reward: "500",
    });
  }

  render() {
    return (
      <div className={styles.challengeGrid}>
        <div className={styles.challenge}>
          <div className={styles.challengeInfo}>{this.props.title}</div>
          <div className={styles.percentage}>
            {(this.props.progress / this.props.max) * 100 + "%"}
          </div>
          <progress
            className={styles.pr}
            value={this.props.progress}
            max={this.props.max}
          />
        </div>
        <div className={styles.reward}>
          <h3>Reward</h3>
          <div className={styles.info}>{this.props.reward}</div>
        </div>
      </div>
    );
  }
}

export default ChallengeComponent;
