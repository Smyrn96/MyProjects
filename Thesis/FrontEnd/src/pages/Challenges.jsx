import React, { Component } from "react";
import TopBar from "../Components/TopBarComponent";
import styles from "../CSS/Challenges.module.css";
import ChallengeComponent from "../Components/ChallengeComponent";
import Cookies from "universal-cookie";

class Challenges extends Component {
  constructor(props) {
    super(props);
  }
  state = {
    challenges: [],
    isLoaded: false,
    userID: "",
  };

  componentDidMount() {
    var cookies = new Cookies();
    var str = cookies.get("userID");
    fetch("http://localhost:7777/" + str + "/challenges")
      .then((value) => value.json())
      .then((value) => {
        this.setState({
          challenges: value,
          isLoaded: true,
        });
        console.log(value);
        //json response
      })
      .catch((err) => {
        console.log(err);
      });
  }

  render() {
    const { error, isLoaded, challenges } = this.state;
    if (error) {
      return <div>Error: {error.message}</div>;
    } else if (!isLoaded) {
      return <div>Loading...</div>;
    } else {
      return (
        <div className={styles.Main}>
          <TopBar />
          <div className={styles.tabs}>
            <div className={styles.Challenges}>
              <h1>Challenges</h1>
            </div>
          </div>
          <div className={styles.MainGrid}>
            <div className={styles.TitleGrid}>
              <div className={styles.Options}>
                <div className={styles.Daily}>Daily challenges</div>
              </div>
            </div>
            <ul className={styles.row}>
              {this.state.challenges
                .filter(function (challenge) {
                  // filter first for friends
                  return challenge.daily === true; // returns a new array
                })
                .map(function (challenge) {
                  // map the new array to list items
                  return (
                    <li>
                      <ChallengeComponent
                        title={challenge.description}
                        progress={challenge.progress}
                        max={challenge.maxProgress}
                        reward={challenge.rewardPoints}
                      />
                    </li>
                  ); // don't forget unique key for each item
                })}
            </ul>

            <div className={styles.TitleGrid2}>
              <div className={styles.Options}>
                <div className={styles.General}>General challenges</div>
              </div>
            </div>
            <ul className={styles.gen}>
              {this.state.challenges
                .filter(function (challenge) {
                  // filter first for friends
                  return challenge.daily === false; // returns a new array
                })
                .map(function (challenge) {
                  // map the new array to list items
                  return (
                    <li>
                      <ChallengeComponent
                        title={challenge.description}
                        progress={challenge.progress}
                        max={challenge.maxProgress}
                        reward={challenge.rewardPoints}
                      />
                    </li>
                  ); // don't forget unique key for each item
                })}
            </ul>
          </div>
        </div>
      );
    }
  }
}

export default Challenges;
