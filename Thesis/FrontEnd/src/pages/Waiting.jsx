import React, { Component } from "react";
import styles from "../CSS/Waiting.module.css";
import TopBar from "../Components/TopBarComponent";

class WaitingPage extends Component {
  constructor(props) {
    super(props);
    this.state = {
      game: this.props.location.state,
      userID: "",
      Role: "",
    };
  }

  chooseRole(props) {
    console.log(props);
    if (
      (props.attackerID === "null" || props.attackerID === "") &&
      props.defenderID !== "null"
    ) {
      this.state.Role = "Defender";
      this.Points = props.defenderPoints;
      return props.defenderID;
    } else if (
      props.attackerID !== "null" &&
      (props.defenderID === "null" || props.defenderID === "")
    ) {
      console.log("MANOS1");
      this.state.Role = "Attacker";
      this.Points = props.attackerPoints;
      return props.attackerID;
    }
  }

  render() {
    return (
      <div className={styles.Main}>
        <TopBar />

        <div className={styles.MainGrid}>
          <div className={styles.title}>Waiting for an opponent</div>
          <ul className={styles.stats}>
            <li>userID : {this.chooseRole(this.state.game)}</li>
            <li>Role : {this.state.Role}</li>
            <li>TaskID : {this.state.game.taskID}</li>
            <li>Category : {this.state.game.category}</li>
          </ul>
        </div>
      </div>
    );
  }
}

export default WaitingPage;
