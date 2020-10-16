import React, { Component } from "react";
import TopBar from "../Components/TopBarComponent";
import styles from "../CSS/Profile.module.css";
import GameTabProfile from "../Components/GameTabProfile";
import Cookies from "universal-cookie";

class Profile extends Component {
  constructor(props) {
    super(props);
    this.state = {
      user: Object,
      games: [],
    };
  }

  componentDidMount() {
    var cookies = new Cookies();
    var str = cookies.get("userID");
    console.log(str);

    Promise.all([
      fetch("http://localhost:7777/users/" + str).then((value) => value.json()),
      fetch("http://localhost:7777/games").then((value) => value.json()),
    ])
      .then((value) => {
        this.setState({
          user: value[0],
          games: value[1],
          isLoaded: true,
        });

        console.log("HELLO THERE " + this.state);
        //json response
      })
      .catch((err) => {
        console.log(err);
      });
  }

  myBadges() {
    if (this.state.user.score <= 100) {
      return <img className={styles.imageBadge} src='../Badge.png'></img>;
    } else if (this.state.user.score <= 300) {
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
    const { error, isLoaded, games, user } = this.state;
    if (error) {
      return <div>Error: {error.message}</div>;
    } else if (!isLoaded) {
      return <div>Loading...</div>;
    } else {
      console.log(this.state);
      return (
        <div className={styles.Main}>
          <TopBar />
          <div className={styles.profileDiv}>
            <img src='../../user.png'></img>
            <div className={styles.imageText}>Edit</div>
          </div>
          <div className={styles.username}>{this.state.user.username}</div>
          <div className={styles.stats}>
            <span className={styles.games}>Games </span>
            <span className={styles.games}>Points </span>
            <span className={styles.games}>Badges </span>
          </div>
          <div className={styles.stats1}>
            <div className={styles.games}>{this.state.user.gamesPlayed}</div>
            <div className={styles.points}>{this.state.user.score} </div>
            <div className={styles.badges}>{this.myBadges()} </div>
          </div>
          <div className={styles.history}>Match history</div>
          <div className={styles.tabs}>
            {this.state.games
              .filter(function (game) {
                // filter first for friends
                return (
                  (game.attackerUsername === user.username ||
                    game.defenderUsername === user.username) &&
                  game.finished === true
                ); // returns a new array
              })
              .map(function (game) {
                // map the new array to list items
                return (
                  <GameTabProfile
                    gameID={game.gameID}
                    attackerUsername={game.attackerUsername}
                    attackerPoints={game.attackerPoints}
                    defenderUsername={game.defenderUsername}
                    defenderPoints={game.defenderPoints}
                    tagsCount={game.tagsCount}
                    rounds={game.rounds}
                    completionTime={game.completionTime}
                    category={game.category}
                    date={game.startingTime}
                  />
                ); // don't forget unique key for each item
              })}
          </div>
        </div>
      );
    }
  }
}

export default Profile;
