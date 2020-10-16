import React, { Component } from "react";
import TopBar from "../Components/TopBarComponent";
import styles from "../CSS/Spectate.module.css";
import SpectateBoxComponent from "../Components/SpectateBoxComponent";
import Cookies from "universal-cookie";

class Spectate extends Component {
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
    fetch("http://localhost:7777/games/tv")
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

  spectateGame(game) {
    console.log(this.state.cookie);
    this.props.history.push({
      pathname: "/tv/" + game.gameID,
      state: { userID: this.state.cookie, gameID: game.gameID },
    });
  }
  render() {
    var cookie = new Cookies();
    console.log(cookie.get("myCat"));
    const { error, isLoaded, games } = this.state;
    if (error) {
      return <div>Error: {error.message}</div>;
    } else if (!isLoaded) {
      return <div>Loading...</div>;
    } else {
      return (
        <div className={styles.Main}>
          <TopBar></TopBar>
          <div className={styles.tabs}>
            <div className={styles.Spectate}>
              <h1>Spectate</h1>
            </div>
          </div>
          <div className={styles.MainGrid}>
            <ul className={styles.row}>
              {this.state.games
                .filter(function (game) {
                  // filter first for friends
                  return (
                    game.attackerUsername !== "" && game.defenderUsername !== ""
                  ); // returns a new array
                })
                .map(function (game) {
                  return (
                    <li
                      onClick={() => {
                        this.spectateGame(game);
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
      );
    }
  }
}

export default Spectate;
