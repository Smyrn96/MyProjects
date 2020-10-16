import React, { Component } from "react";
import styles from "../CSS/GameTabProfile.module.css";

class GameTabProfile extends Component {
  state = {
    tagsCount: 0,
  };

  componentDidMount() {
    Promise.all([
      fetch(
        "http://localhost:7777/games/" + this.props.gameID + "/tags"
      ).then((value) => value.json()),
    ]).then((value) => {
      console.log(value);
      this.setState({
        tagsCount: value[0].length,
      });
    });
  }
  timestampTime(timestamp) {
    var dateObj = new Date(timestamp);
    var utcString = dateObj.toLocaleDateString();
    return utcString;
  }

  toHHMMSS(seconds) {
    var sec_num = parseInt(seconds, 10); // don't forget the second param
    var hours = Math.floor(sec_num / 3600);
    var minutes = Math.floor((sec_num - hours * 3600) / 60);
    var seconds = sec_num - hours * 3600 - minutes * 60;

    if (hours < 10) {
      hours = "0" + hours;
    }
    if (minutes < 10) {
      minutes = "0" + minutes;
    }
    if (seconds < 10) {
      seconds = "0" + seconds;
    }
    return hours + ":" + minutes + ":" + seconds;
  }

  render() {
    return (
      <div className={styles.singleTab}>
        <div className={styles.row}>
          <div className={styles.Username}>
            <div className={styles.titles}>{this.props.attackerUsername}</div>
            <div>{this.props.attackerPoints}</div>
          </div>
          <div className={styles.Defender}>
            <div className={styles.titles}>{this.props.defenderUsername}</div>
            <div>{this.props.defenderPoints}</div>
          </div>
          <div className={styles.Tags}>
            <div className={styles.titles}>Tags</div>
            <div>{this.state.tagsCount}</div>
          </div>
          <div className={styles.Rounds}>
            <div className={styles.titles}>Messages</div>
            <div>{this.props.rounds}</div>
          </div>
          <div className={styles.Time}>
            <div className={styles.titles}>Time</div>
            <div>{this.toHHMMSS(this.props.completionTime)}</div>
          </div>
          <div className={styles.Category}>
            <div className={styles.titles}>Category</div>
            <div>{this.props.category}</div>
          </div>
          <div className={styles.Date}>
            <div className={styles.titles}>Date</div>
            <div>{this.timestampTime(this.props.date)}</div>
          </div>
        </div>
      </div>
    );
  }
}

export default GameTabProfile;
