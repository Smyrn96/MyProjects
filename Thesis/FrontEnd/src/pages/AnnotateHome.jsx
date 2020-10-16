import React, { Component } from "react";
import TopBarAnnotation from "../Components/TopBarAnnotationComponent";
import styles from "../CSS/AnnotateHome.module.css";
import Cookies from "universal-cookie";
import SpectateBoxComponent from "../Components/SpectateBoxComponent";
import { Prompt } from "react-router-dom";

class AnnotateHome extends Component {
  constructor(props) {
    super(props);
    var cookies = new Cookies();
    this.state = {
      cookie: cookies.get("userID"),
      games: [],

      isLoaded: false,
    };
  }

  componentDidMount() {
    fetch("http://localhost:7777/games")
      .then((value) => value.json())
      .then((value) => {
        this.setState({
          games: value,
          isLoaded: true,
        });
        console.log(value);
        //json response
      })
      .catch((err) => {
        console.log(err);
      });
  }

  async setAnnotation(game, form) {
    let response = await fetch(
      "http://localhost:7777/annotations/" +
        this.state.cookie +
        "/" +
        game.gameID,
      {
        method: "POST",
        // We convert the React state to JSON and send it as the POST body
        body: JSON.stringify(form),
      }
    );
    let json = await response.json();
    this.setState(
      {
        annotationID: json.annotationID,
      },
      () => {
        console.log(this.state.cookie);
        this.props.history.push({
          pathname: "/annotations/" + game.gameID,
          state: {
            userID: this.state.cookie,
            gameID: game.gameID,
            annotationID: this.state.annotationID,
          },
        });
      }
    );
    console.log(json.annotationID);
  }

  annotateGame(game) {
    var form = {
      userID: this.state.cookie,
      gameID: game.gameID,
    };

    this.setAnnotation(game, form);
  }
  render() {
    var cookie = new Cookies();
    const { error, isLoaded, games } = this.state;
    if (error) {
      return <div>Error: {error.message}</div>;
    } else if (!isLoaded) {
      return <div>Loading...</div>;
    } else {
      return (
        <>
          <TopBarAnnotation />
          <div className={styles.Main}>
            <div className={styles.tabs}>
              <div className={styles.Spectate}>
                <h1>Annotate a game</h1>
              </div>
            </div>
            <div className={styles.MainGrid}>
              <ul className={styles.row}>
                {this.state.games
                  .filter(function (game) {
                    // filter first for friends
                    return (
                      game.attackerUsername !== "" &&
                      game.defenderUsername !== "" &&
                      game.finished == true &&
                      game.ongoing == false
                    ); // returns a new array
                  })
                  .map(function (game) {
                    return (
                      <li
                        onClick={() => {
                          this.annotateGame(game);
                        }}
                      >
                        <SpectateBoxComponent
                          attackerID={game.attackerUsername}
                          attackerPoints={game.attackerPoints}
                          defenderID={game.defenderUsername}
                          defenderPoints={game.defenderPoints}
                          category={game.category}
                        />
                      </li>
                    );
                  }, this)}
              </ul>
            </div>
          </div>
        </>
      );
    }
  }
}

export default AnnotateHome;
