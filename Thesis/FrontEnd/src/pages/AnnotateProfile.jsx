import React, { Component } from "react";
import TopBarAnnotation from "../Components/TopBarAnnotationComponent";
import Cookies from "universal-cookie";
import styles from "../CSS/AnnotationProfile.module.css";
import AnnotationTabProfile from "../Components/AnnotationTabProfile";

class AnnotateProfile extends Component {
  constructor(props) {
    super(props);
    var cookies = new Cookies();
    this.state = {
      cookie: cookies.get("userID"),
      stateCounter: 0,
      ratings: [],
    };
  }

  componentDidMount() {
    Promise.all([
      fetch("http://localhost:7777/users/" + this.state.cookie).then((value) =>
        value.json()
      ),
      fetch(
        "http://localhost:7777/annotations/" + this.state.cookie
      ).then((value) => value.json()),
      fetch("http://localhost:7777/games").then((value) => value.json()),
    ])
      .then((value) => {
        this.setState(
          {
            user: value[0],
            annotations: value[1],
            games: value[2],
            isLoaded: true,
          },
          () => {
            this.countTasks();
          }
        );

        console.log("HELLO THERE " + this.state);
        //json response
      })
      .catch((err) => {
        console.log(err);
      });
  }

  countTasks() {
    var counter = 0;
    for (var i = 0; i < this.state.annotations.length; i++) {
      if (this.state.annotations[i].userID == this.state.cookie) {
        counter++;
      }
    }
    this.setState({
      stateCounter: counter,
    });
  }

  findGame(gameID) {
    for (var i = 0; i < this.state.games.length; i++) {
      if (this.state.games[i].gameID == gameID) {
        return this.state.games[i];
      }
    }
  }

  async getRatingsWait(annotation) {
    let response = await fetch(
      "http://localhost:7777/annotations/" +
        annotation.userID +
        "/" +
        annotation.gameID +
        "/" +
        annotation.annotationID +
        "/ratings",
      {
        method: "GET",
        // We convert the React state to JSON and send it as the POST body
      }
    );
    let json = await response.json();
    this.setState({
      ratings: json,
    });
  }

  getRatings(annotation) {
    this.getRatingsWait(annotation);
    return this.state.ratings.length;
  }

  render() {
    var history = this.props.history;
    const { error, isLoaded, annotations, user, games } = this.state;
    if (error) {
      return <div>Error: {error.message}</div>;
    } else if (!isLoaded) {
      return <div>Loading...</div>;
    } else {
      return (
        <>
          <TopBarAnnotation />
          <div className={styles.profileDiv}>
            <img src='../../user.png'></img>
            <div className={styles.imageText}>Edit</div>
          </div>
          <div className={styles.username}>{this.state.user.username}</div>
          <div className={styles.stats}>
            <span className={styles.Tasks}>Games Annotated </span>
          </div>
          <div className={styles.stats1}>
            <div className={styles.games}>{this.state.stateCounter}</div>
          </div>
          <div className={styles.history}>Annotations history</div>
          <div className={styles.tabs}>
            {this.state.annotations
              .filter(function (annotation) {
                // filter first for friends
                return annotation.userID == this.state.cookie;
              }, this)
              .map(function (annotation) {
                // map the new array to list items
                return (
                  <AnnotationTabProfile
                    annotationID={annotation.annotationID}
                    attackerUsername={
                      this.findGame(annotation.gameID).attackerUsername
                    }
                    attackerPoints={
                      this.findGame(annotation.gameID).attackerPoints
                    }
                    defenderUsername={
                      this.findGame(annotation.gameID).defenderUsername
                    }
                    defenderPoints={
                      this.findGame(annotation.gameID).defenderPoints
                    }
                    gameID={annotation.gameID}
                    userID={annotation.userID}
                    created={annotation.created}
                  />
                );
                // don't forget unique key for each item
              }, this)}
          </div>
        </>
      );
    }
  }
}

export default AnnotateProfile;
