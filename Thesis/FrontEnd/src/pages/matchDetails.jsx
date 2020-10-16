import React, { Component } from "react";
import styles from "../CSS/matchDetails.module.css";
import TopBar from "../Components/TopBarComponent";
import Modal from "react-bootstrap/Modal";
import Cookies from "universal-cookie";

class matchDetails extends Component {
  constructor(props) {
    super(props);
    var cookies = new Cookies();
    this.state = {
      tags: [],
      attackerTags: [],
      defenderTags: [],
      matchingTags: [],
      showChallenge: false,
      attackerXP: 0,
      defenderXP: 0,
      attackerTotal: 0,
      defenderTotal: 0,
      attackerPoints: this.props.location.state.attackerPoints,
      defenderPoints: this.props.location.state.defenderPoints,
      cookie: cookies.get("userID"),
    };
  }

  componentDidMount() {
    Promise.all([
      fetch(
        "http://localhost:7777/games/" + this.props.location.state.gameID
      ).then((value) => value.json()),
      fetch(
        "http://localhost:7777/games/" +
          this.props.location.state.gameID +
          "/messages"
      ).then((value) => value.json()),
      fetch("http://localhost:7777/users").then((value) => value.json()),
      fetch(
        "http://localhost:7777/games/" +
          this.props.location.state.gameID +
          "/game_details/" +
          this.props.location.state.attackerUserID
      ).then((value) => value.json()),
      fetch(
        "http://localhost:7777/games/" +
          this.props.location.state.gameID +
          "/game_details/" +
          this.props.location.state.defenderUserID
      ).then((value) => value.json()),
      fetch(
        "http://localhost:7777/" + this.state.cookie + "/challenges"
      ).then((value) => value.json()),
    ])
      .then((value) => {
        this.setState(
          {
            game: value[0],
            messages: value[1],
            users: value[2],
            attackerTags: value[3],
            defenderTags: value[4],
            challenges: value[5],
            isLoaded: true,
          },
          () => {
            console.log(this.state.challenges);
            console.log(this.state.defenderTags);
            this.updateUser();
          }
        );

        console.log(this.state.users);
        //json response
      })
      .catch((err) => {
        console.log(err);
      });
  }

  async deleteChallenge(key) {
    let response = await fetch(
      "http://localhost:7777/" +
        this.state.cookie +
        "/challenges/" +
        this.state.challenges[key].challengeID,
      {
        method: "DELETE",
        // We convert the React state to JSON and send it as the POST body
      }
    );
    let json = await response.json();
  }

  async updateChallenges(form, key) {
    let response = await fetch(
      "http://localhost:7777/" +
        this.state.cookie +
        "/challenges/" +
        this.state.challenges[key].challengeID,
      {
        method: "PUT",
        // We convert the React state to JSON and send it as the POST body
        body: JSON.stringify(form),
      }
    );
    let json = await response.json();
  }

  async updateUser() {
    await this.matchTags();
    if (
      this.props.location.state.forfeit == "yes" &&
      this.findUser(this.props.location.state.attackerUsername).userID ==
        this.state.cookie
    ) {
      this.setState({
        attackerXP: 0,
        defenderXP: 10,
      });
      var formA = {
        score:
          this.state.attackerTags.length * 2 +
          this.props.location.state.attackerPoints +
          this.state.matchingTags.length * 3 +
          0,
        gamesPlayed:
          this.findUser(this.props.location.state.attackerUsername)
            .gamesPlayed + 1,
      };

      var formD = {
        score:
          this.state.defenderTags.length * 2 +
          this.props.location.state.defenderPoints +
          this.state.matchingTags.length * 3 +
          10,
        gamesPlayed:
          this.findUser(this.props.location.state.defenderUsername)
            .gamesPlayed + 1,
      };
      this.setState(
        {
          attackerTotal: formA.score,
          defenderTotal: formD.score,
        },
        () => {
          console.log(this.state.attackerTotal);
        }
      );
    } else if (
      this.props.location.state.forfeit == "yes" &&
      this.findUser(this.props.location.state.defenderUsername).userID ==
        this.state.cookie
    ) {
      this.setState({
        attackerXP: 10,
        defenderXP: 0,
      });
      var formA = {
        score:
          this.state.attackerTags.length * 2 +
          this.props.location.state.attackerPoints +
          this.state.matchingTags.length * 3 +
          10,
        gamesPlayed:
          this.findUser(this.props.location.state.attackerUsername)
            .gamesPlayed + 1,
      };
      var formD = {
        score:
          this.state.defenderTags.length * 2 +
          this.props.location.state.defenderPoints +
          this.state.matchingTags.length * 3 +
          0,
        gamesPlayed:
          this.findUser(this.props.location.state.defenderUsername)
            .gamesPlayed + 1,
      };
      this.setState(
        {
          attackerTotal: formA.score,
          defenderTotal: formD.score,
        },
        () => {
          console.log(this.state.attackerTotal);
        }
      );
    } else if (
      this.props.location.state.forfeit == "no" &&
      this.findUser(this.props.location.state.attackerUsername).userID ==
        this.state.cookie
    ) {
      this.setState({
        attackerXP: 10,
        defenderXP: 0,
      });
      var formA = {
        score:
          this.state.attackerTags.length * 2 +
          this.props.location.state.attackerPoints +
          this.state.matchingTags.length * 3 +
          10,
        gamesPlayed:
          this.findUser(this.props.location.state.attackerUsername)
            .gamesPlayed + 1,
      };

      var formD = {
        score:
          this.state.defenderTags.length * 2 +
          this.props.location.state.defenderPoints +
          this.state.matchingTags.length * 3 +
          0,
        gamesPlayed:
          this.findUser(this.props.location.state.defenderUsername)
            .gamesPlayed + 1,
      };
      this.setState(
        {
          attackerTotal: formA.score,
          defenderTotal: formD.score,
        },
        () => {
          console.log(this.state.attackerTotal);
        }
      );
    } else if (
      this.props.location.state.forfeit == "no" &&
      this.findUser(this.props.location.state.defenderUsername).userID ==
        this.state.cookie
    ) {
      this.setState({
        attackerXP: 0,
        defenderXP: 10,
      });
      var formA = {
        score:
          this.state.attackerTags.length * 2 +
          this.props.location.state.attackerPoints +
          this.state.matchingTags.length * 3 +
          0,
        gamesPlayed:
          this.findUser(this.props.location.state.attackerUsername)
            .gamesPlayed + 1,
      };

      var formD = {
        score:
          this.state.defenderTags.length * 2 +
          this.props.location.state.defenderPoints +
          this.state.matchingTags.length * 3 +
          10,
        gamesPlayed:
          this.findUser(this.props.location.state.defenderUsername)
            .gamesPlayed + 1,
      };
      this.setState(
        {
          attackerTotal: formA.score,
          defenderTotal: formD.score,
        },
        () => {
          console.log(this.state.attackerTotal);
        }
      );
    } else {
      this.setState({
        attackerXP: 10,
        defenderXP: 10,
      });
      var formA = {
        score:
          this.state.attackerTags.length * 2 +
          this.props.location.state.attackerPoints +
          this.state.matchingTags.length * 3 +
          10,
        gamesPlayed:
          this.findUser(this.props.location.state.attackerUsername)
            .gamesPlayed + 1,
      };

      var formD = {
        score:
          this.state.defenderTags.length * 2 +
          this.props.location.state.defenderPoints +
          this.state.matchingTags.length * 3 +
          10,
        gamesPlayed:
          this.findUser(this.props.location.state.defenderUsername)
            .gamesPlayed + 1,
      };
      this.setState(
        {
          attackerTotal: formA.score,
          defenderTotal: formD.score,
        },
        () => {
          console.log(this.state.attackerTotal);
        }
      );
    }

    /*  this.setState(
      {
        attackerTotal: formA.score,
        defenderTotal: formD.score,
      },
      () => {
        console.log(this.state.attackerTotal);
      }
    );*/

    if (
      this.findUserID(this.props.location.state.attackerUsername) ==
      this.state.cookie
    ) {
      for (var i = 0; i < this.state.challenges.length; i++) {
        console.log(
          this.state.challenges[i].progress +
            "___________" +
            this.state.challenges[i].maxProgress -
            1
        );
        if (this.state.challenges[i].category == "games") {
          if (
            this.state.challenges[i].progress ==
            this.state.challenges[i].maxProgress - 1
          ) {
            formA.score = formA.score + this.state.challenges[i].rewardPoints;

            this.setState(
              {
                tempChallengeDescription: this.state.challenges[i].description,
                tempRewardPoints: this.state.challenges[i].rewardPoints,
                attackerTotal: formA.score,
              },
              () => {
                console.log(this.state.attackerTotal);
              }
            );

            this.showModalChallenge();
            this.deleteChallenge(i);
          } else {
            var form = {
              challengeID: this.state.challenges[i].challengeID,
              progress: this.state.challenges[i].progress + 1,
            };

            this.updateChallenges(form, i);
          }
        }
      }
      fetch("http://localhost:7777/users/" + this.state.cookie, {
        method: "PUT",
        // We convert the React state to JSON and send it as the POST body
        body: JSON.stringify(formA),
      })
        .then((res) => res.json())
        .then((response) => {
          var response = JSON.parse(response);
          console.log(response);
        })
        .catch((error) => console.error("Error:", error));
    } else if (
      this.findUserID(this.props.location.state.defenderUsername) ==
      this.state.cookie
    ) {
      for (var i = 0; i < this.state.challenges.length; i++) {
        console.log(
          this.state.challenges[i].progress +
            "___________" +
            this.state.challenges[i].maxProgress -
            1
        );
        if (this.state.challenges[i].category == "games") {
          if (
            this.state.challenges[i].progress ==
            this.state.challenges[i].maxProgress - 1
          ) {
            formD.score = formD.score + this.state.challenges[i].rewardPoints;

            this.setState(
              {
                tempChallengeDescription: this.state.challenges[i].description,
                tempRewardPoints: this.state.challenges[i].rewardPoints,
                defenderTotal: formD.score,
              },
              () => {
                console.log(this.state.attackerTotal);
              }
            );
            this.showModalChallenge();
            this.deleteChallenge(i);
          } else {
            var form = {
              challengeID: this.state.challenges[i].challengeID,
              progress: this.state.challenges[i].progress + 1,
            };

            this.updateChallenges(form, i);
          }
        }
      }

      fetch("http://localhost:7777/users/" + this.state.cookie, {
        method: "PUT",
        // We convert the React state to JSON and send it as the POST body
        body: JSON.stringify(formD),
      })
        .then((res) => res.json())
        .then((response) => {
          var response = JSON.parse(response);
          console.log(response);
        })
        .catch((error) => console.error("Error:", error));
    }
  }
  findUserID(username) {
    for (var i = 0; i < this.state.users.length; i++) {
      if (this.state.users[i].username === username) {
        return this.state.users[i].userID;
      }
    }
  }
  findUser(username) {
    for (var i = 0; i < this.state.users.length; i++) {
      if (this.state.users[i].username === username) {
        return this.state.users[i];
      }
    }
  }
  showModalChallenge = (e) => {
    this.setState(
      {
        showChallenge: !this.state.showChallenge,
      },
      () => {
        setTimeout(() => {
          this.setState({
            showChallenge: false,
          });
        }, 3000);
      }
    );
  };

  async matchTags() {
    for (var i = 0; i < this.state.attackerTags.length; i++) {
      for (var j = 0; j < this.state.defenderTags.length; j++) {
        if (
          this.state.attackerTags[i].messageID ===
            this.state.defenderTags[j].messageID &&
          this.state.attackerTags[i].category ===
            this.state.defenderTags[j].category
        ) {
          console.log("HELLO THERE");
          this.setState({
            matchingTags: [
              ...this.state.matchingTags,
              this.state.defenderTags[j],
            ],
          });
        }
      }
    }
  }

  render() {
    const {
      error,
      isLoaded,
      game,
      messages,
      users,
      attackerTags,
      defenderTags,
      challenges,
    } = this.state;

    if (error) {
      return <div>Error: {error.message}</div>;
    } else if (!isLoaded) {
      return <div>Loading...</div>;
    } else {
      console.log(this.props.location.state.attackerUserID);
      console.log(this.props.location.state.defenderUserID);
      return (
        <>
          <TopBar />
          <div className={styles.title}>
            <h1>{this.props.location.state.title}</h1>
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
                {this.props.location.state.attackerMessages}
              </div>
              <div className={styles.messagesTitle}>Messages</div>
              <div className={styles.defenderMessages}>
                {this.props.location.state.defenderMessages}
              </div>
            </div>
            <div className={styles.Tags}>
              <div className={styles.attackerTags}>
                {this.state.attackerTags.length}
              </div>
              <div className={styles.tagsTitle}>Tags</div>
              <div className={styles.defenderTags}>
                {this.state.defenderTags.length}
              </div>
            </div>
            <div className={styles.Matching}>
              <div className={styles.matchingAttacker}>
                {this.state.matchingTags.length}
              </div>
              <div className={styles.matchingTitle}>Matching tags</div>
              <div className={styles.matchingDefender}>
                {this.state.matchingTags.length}
              </div>
            </div>
            <div className={styles.earning}>
              <div className={styles.earningAttacker}>
                +{this.state.matchingTags.length * 10}
              </div>
              <div className={styles.earningTitle}>Earning XP</div>
              <div className={styles.earningDefender}>
                +{this.state.matchingTags.length * 10}
              </div>
            </div>
            <div className={styles.matchXP}>
              <div className={styles.attackerXP}>+{this.state.attackerXP}</div>
              <div className={styles.titleXP}>Match XP</div>
              <div className={styles.defenderXP}>+{this.state.defenderXP}</div>
            </div>
            <div className={styles.total}>
              <div className={styles.attackerTotal}>
                {this.state.attackerTotal}
              </div>
              <div className={styles.totalTitle}>Total</div>
              <div className={styles.defenderTotal}>
                {this.state.defenderTotal}
              </div>
            </div>
          </div>
          <Modal size='lg' centered show={this.state.showChallenge}>
            <div className={styles.titleModal}>
              <h1>Challenge complete!</h1>
            </div>
            <img className={styles.imageTick} src='../../success.png'></img>
            <div className={styles.cont}>
              <h4>
                "{this.state.tempChallengeDescription}" is completed and you
                earned {this.state.tempRewardPoints} points
              </h4>
            </div>
          </Modal>
        </>
      );
    }
  }
}

export default matchDetails;
