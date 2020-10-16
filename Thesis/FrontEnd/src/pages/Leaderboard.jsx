import React, { Component } from "react";
import styles from "../CSS/Leaderboard.module.css";
import TopBar from "../Components/TopBarComponent";
import LeaderboardComponent from "../Components/LeaderboardTabComponent";
import Cookies from "universal-cookie";

class Leaderboard extends Component {
  constructor(props) {
    super(props);
    this.state = {
      error: null,
      isLoaded: false,
      players: [],
    };
  }

  componentDidMount() {
    fetch("http://localhost:7777/users/leaderboard")
      .then((res) => res.json())
      .then(
        (result) => {
          this.setState({
            isLoaded: true,
            players: result,
          });
          console.log(result[0].userID);
        },
        // Note: it's important to handle errors here
        // instead of a catch() block so that we don't swallow
        // exceptions from actual bugs in components.
        (error) => {
          this.setState({
            isLoaded: true,
            error,
          });
        }
      );
  }

  render() {
    var cookies = new Cookies();
    var str = cookies.get("userID");
    console.log("HELLO" + str);
    const { error, isLoaded, players } = this.state;
    if (error) {
      return <div>Error: {error.message}</div>;
    } else if (!isLoaded) {
      return <div>Loading...</div>;
    } else {
      return (
        <div className={styles.Main}>
          <TopBar />
          <div className={styles.tabs}>
            <div className={styles.Leaderboard}>
              <h1>Leaderboard</h1>
            </div>
          </div>
          <div className={styles.MainGrid}>
            <div className={styles.TitleGrid}>
              <div className={styles.Options}>
                <span className={styles.Player}>Player</span>
                <span className={styles.Rating}>Rating</span>
                <span className={styles.Badges}>Badges</span>
              </div>
              <ul className={styles.list}>
                {players.map((player) => (
                  <li>
                    <LeaderboardComponent
                      userID={player.username}
                      rating={player.score}
                    />
                  </li>
                ))}
              </ul>
            </div>
          </div>
        </div>
      );
    }
  }
}

export default Leaderboard;
