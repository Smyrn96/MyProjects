import React, { Component } from "react";
import TopBarAnnotation from "./TopBarAnnotationComponent";
import styles from "../CSS/AnnotationTabProfile.module.css";

class AnnotationTabProfile extends Component {
  state = {
    ratings: [],
    tags: [],
  };

  componentDidMount() {
    Promise.all([
      fetch(
        "http://localhost:7777/annotations/" +
          this.props.userID +
          "/" +
          this.props.gameID +
          "/" +
          this.props.annotationID +
          "/ratings"
      ).then((value) => value.json()),
      fetch(
        "http://localhost:7777/games/" + this.props.gameID + "/tags"
      ).then((value) => value.json()),
    ])
      .then((value) => {
        this.setState({
          ratings: value[0],
          tags: value[1],
        });
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
    return (
      <>
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
              <div className={styles.titles}>Total Ratings</div>
              <div>{this.state.ratings.length}</div>
            </div>

            <div className={styles.Time}>
              <div className={styles.titles}>Tags</div>
              <div>{this.state.tags.length}</div>
            </div>
            <div className={styles.Date}>
              <div className={styles.titles}>Date</div>
              <div>{this.timestampTime(this.props.created)}</div>
            </div>
          </div>
        </div>
      </>
    );
  }
}

export default AnnotationTabProfile;
