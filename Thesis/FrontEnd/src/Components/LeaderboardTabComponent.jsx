import React, { Component } from "react";
import styles from "../CSS/LeaderboardComponent.module.css";

class LeaderboardComponent extends Component {
  state = {};

  myBadges() {
    if (this.props.rating <= 100) {
      return <img className={styles.imageBadge} src='../Badge.png'></img>;
    } else if (this.props.rating <= 300) {
      return (
        <>
          <img className={styles.imageBadge} src='../Badge.png'></img>
          <img className={styles.imageBadge} src='../Badge1.png'></img>
        </>
      );
    } else {
      return (
        <>
          <img className={styles.imageBadge} src='../Badge.png'></img>
          <img className={styles.imageBadge} src='../Badge1.png'></img>
          <img className={styles.imageBadge} src='../Badge2.png'></img>
        </>
      );
    }
  }

  render() {
    return (
      <div className={styles.Main}>
        <div className={styles.player}>{this.props.userID}</div>
        <div className={styles.rating}>{this.props.rating}</div>
        <div className={styles.badges}>{this.myBadges()}</div>
      </div>
    );
  }
}

export default LeaderboardComponent;
