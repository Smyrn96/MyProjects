import React, { Component } from "react";
import styles from "../CSS/GameTabComponent.module.css";

class GameTagComponent extends Component {
  state = {};
  render() {
    return (
      <div className={styles.Main} style={{ cursor: "pointer" }}>
        <div className={styles.player}>{this.props.userID}</div>
        <div className={styles.rating}>{this.props.rating}</div>
        <div className={styles.role}>{this.props.role}</div>
        <div className={styles.category}>{this.props.category}</div>
      </div>
    );
  }
}

export default GameTagComponent;
