import React, { Component } from "react";
import TopBarAnnotation from "../Components/TopBarAnnotationComponent";
import styles from "../CSS/AnnotateGameDetails.module.css";

class AnnotateGameDetails extends Component {
  state = {
    attackerCounter: 0,
    defenderCounter: 0,
    attackerCounterRate: 0,
    defenderCounterRate: 0,
    userPoints: 0,
    userBeforePoints: 0,
  };

  componentDidMount() {
    Promise.all([
      fetch(
        "http://localhost:7777/games/" +
          this.props.location.state.gameID +
          "/messages"
      ).then((value) => value.json()),
      fetch(
        "http://localhost:7777/annotations/" +
          this.props.location.state.userID +
          "/" +
          this.props.location.state.gameID +
          "/" +
          this.props.location.state.annotationID +
          "/ratings"
      ).then((value) => value.json()),
      fetch("http://localhost:7777/users").then((value) => value.json()),
      fetch(
        "http://localhost:7777/users/" + this.props.location.state.userID
      ).then((value) => value.json()),
      fetch(
        "http://localhost:7777/games/" + this.props.location.state.gameID
      ).then((value) => value.json()),
    ])
      .then((value) => {
        this.setState(
          {
            messages: value[0],
            ratings: value[1],
            users: value[2],
            user: value[3],
            game: value[4],
            isLoaded: true,
          },
          () => {
            console.log(value);
            this.findUserMessages();
          }
        );

        console.log(this.props.location.state.annotationID);
        //json response
      })
      .catch((err) => {
        console.log(err);
      });
  }

  getUser(username) {
    for (var i = 0; i < this.state.users.length; i++) {
      console.log("EDW " + this.state.users[i].userID + this.state.cookie);
      if (this.state.users[i].username === username) {
        console.log("EDW " + this.state.users[i].userID);
        return this.state.users[i];
      }
    }
  }

  chooseUser(sender) {
    for (var i = 0; i < this.state.users.length; i++) {
      console.log("EDW " + this.state.users[i].userID + this.state.cookie);
      if (this.state.users[i].username === sender) {
        console.log("EDW " + this.state.users[i].userID);
        return this.state.users[i].userID;
      }
    }
  }
  returnUserID(messageID) {
    for (var i = 0; i < this.state.messages.length; i++) {
      console.log("EDW " + this.state.users[i].userID + this.state.cookie);
      if (this.state.messages[i].messageID === messageID) {
        console.log("EDW " + this.state.users[i].userID);
        return this.state.messages[i].userID;
      }
    }
    return 0;
  }

  findUserMessages() {
    var attackerCounter = 0;
    var defenderCounter = 0;
    for (var i = 0; i < this.state.ratings.length; i++) {
      if (this.returnUserID(this.state.ratings[i].messageID) != 0) {
        if (
          this.chooseUser(this.props.location.state.attackerUsername) ==
          this.returnUserID(this.state.ratings[i].messageID)
        ) {
          this.setState({
            attackerCounter:
              this.state.attackerCounter + this.state.ratings[i].stars,
          });
        } else if (
          this.chooseUser(this.props.location.state.defenderUsername) ==
          this.returnUserID(this.state.ratings[i].messageID)
        ) {
          this.setState({
            defenderCounter:
              this.state.attackerCounter + this.state.ratings[i].stars,
          });
        }
      } else if (this.state.ratings[i].messageID == "totalAttacker") {
        attackerCounter = attackerCounter + this.state.ratings[i].stars;
      } else if (this.state.ratings[i].messageID == "totalDefender") {
        defenderCounter = defenderCounter + this.state.ratings[i].stars;
      } else if (this.state.ratings[i].messageID == "totalGame") {
        attackerCounter = attackerCounter + this.state.ratings[i].stars;
        defenderCounter = defenderCounter + this.state.ratings[i].stars;
      }
    }
    this.setState(
      {
        attackerCounterRate: attackerCounter,
        defenderCounterRate: defenderCounter,
      },
      () => {
        var formΑ = {
          score:
            this.getUser(this.props.location.state.attackerUsername).score +
            this.state.attackerCounter +
            this.state.attackerCounterRate,
          gamesPlayed: this.getUser(this.props.location.state.attackerUsername)
            .gamesPlayed,
        };

        console.log(this.state.attackerCounterRate);

        fetch(
          "http://localhost:7777/users/" +
            this.chooseUser(this.props.location.state.attackerUsername),
          {
            method: "PUT",
            // We convert the React state to JSON and send it as the POST body
            body: JSON.stringify(formΑ),
          }
        )
          .then((res) => res.json())
          .then((response) => {
            var response = JSON.parse(response);
            console.log(response);
          })
          .catch((error) => console.error("Error:", error));

        var formD = {
          score:
            this.getUser(this.props.location.state.defenderUsername).score +
            this.state.defenderCounter +
            this.state.defenderCounterRate,
          gamesPlayed: this.getUser(this.props.location.state.defenderUsername)
            .gamesPlayed,
        };

        fetch(
          "http://localhost:7777/users/" +
            this.chooseUser(this.props.location.state.defenderUsername),
          {
            method: "PUT",
            // We convert the React state to JSON and send it as the POST body
            body: JSON.stringify(formD),
          }
        )
          .then((res) => res.json())
          .then((response) => {
            var response = JSON.parse(response);
            console.log(response);
          })
          .catch((error) => console.error("Error:", error));
      }
    );

    var points = this.state.user.score;
    this.setState({
      userBeforePoints: this.state.user.score,
      totalRatings: this.state.ratings.length * 2,
    });
    console.log(points);
    points = points + 10 + this.state.ratings.length * 2;
    console.log(points);

    this.setState(
      {
        userPoints: points,
      },
      () => {
        var form = {
          score: points,
          gamesPlayed: this.state.user.gamesPlayed,
        };

        fetch(
          "http://localhost:7777/users/" + this.props.location.state.userID,
          {
            method: "PUT",
            // We convert the React state to JSON and send it as the POST body
            body: JSON.stringify(form),
          }
        )
          .then((res) => res.json())
          .then((response) => {
            var response = JSON.parse(response);
            console.log(response);
          })
          .catch((error) => console.error("Error:", error));
      }
    );
  }

  render() {
    console.log(this.state.defenderCounterRate);
    return (
      <>
        <TopBarAnnotation />
        <div className={styles.title}>
          <h1>Annotation Completed</h1>
        </div>
        <div className={styles.mainGrid}>
          <div className={styles.roleTitle}>
            <div className={styles.attacker}>Attacker</div>
            <div className={styles.defender}>Defender</div>
          </div>
          <div className={styles.username}>
            <div className={styles.attackerUsername}>
              {this.props.location.state.attackerUsername}
            </div>
            <div className={styles.usernameTitle}>Username</div>
            <div className={styles.defenderUsername}>
              {this.props.location.state.defenderUsername}
            </div>
          </div>
          <div className={styles.Points}>
            <div className={styles.attackerPoints}>
              {this.props.location.state.attackerPoints}
            </div>
            <div className={styles.pointsTitle}>Points</div>
            <div className={styles.defenderPoints}>
              {this.props.location.state.defenderPoints}
            </div>
          </div>
          <div className={styles.Messages}>
            <div className={styles.attackerMessages}>
              +{this.state.attackerCounter}
            </div>
            <div className={styles.messagesTitle}>Message Ratings</div>
            <div className={styles.defenderMessages}>
              +{this.state.defenderCounter}
            </div>
          </div>

          <div className={styles.Matching}>
            <div className={styles.matchingAttacker}>
              +{this.state.attackerCounterRate}
            </div>
            <div className={styles.matchingTitle}>Game Ratings</div>
            <div className={styles.matchingDefender}>
              +{this.state.defenderCounterRate}
            </div>
          </div>
          <div className={styles.matchXP}>
            <div className={styles.titleBefore}>
              Annotator Points: {this.state.userBeforePoints}
            </div>
          </div>
          <div className={styles.matchXP}>
            <div className={styles.titleXP}>Match XP: +10</div>
          </div>
          <div className={styles.matchXP}>
            <div className={styles.titleTotal}>
              Total Ratings: +{this.state.totalRatings}
            </div>
          </div>
          <div className={styles.annotatorTotal}>
            <div className={styles.annotatorTotalTitle}>
              Annotator total: {this.state.userPoints}
            </div>
          </div>
        </div>
      </>
    );
  }
}

export default AnnotateGameDetails;
