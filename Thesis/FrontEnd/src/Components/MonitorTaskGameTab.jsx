import React, { Component } from "react";
import styles from "../CSS/MonitorTaskGameTab.module.css";

class MonitorTaskGameTab extends Component {
  state = {};

  render() {
    return (
      <>
        <div className={styles.box}>
          <div className={styles.category}>{this.props.category}</div>
          <img className={styles.flash} src='../../flash1.png'></img>

          <div className={styles.attacker}>
            <img src='../../sword1.png'></img>{" "}
            <div>{this.props.attackerPoints}</div>
          </div>
          <div className={styles.defender}>
            <img src='../../shield1.png'></img>{" "}
            <div>{this.props.defenderPoints}</div>
          </div>
          <div className={styles.userRow}>
            <div className={styles.User1}>{this.props.attackerUsername}</div>
            <div className={styles.User2}>{this.props.defenderUsername}</div>
          </div>
        </div>
      </>
    );
  }
}

export default MonitorTaskGameTab;
