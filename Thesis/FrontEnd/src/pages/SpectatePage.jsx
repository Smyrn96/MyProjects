import React, { Component } from "react";
import TopBar from "../Components/TopBarComponent";
import MessageComponent from "../Components/MessageComponent";
import styles from "../CSS/SpectatePage.module.css";
import Modal from "react-bootstrap/Modal";

class SpectatePage extends Component {
  state = {
    task: "",
    dummy: 0,
    messages: [],
    gameTags: [],
    timer: "",
    timer2: "",
    timer3: "",
    show: false,
  };

  componentDidMount() {
    Promise.all([
      fetch("http://localhost:7777/tasks").then((value) => value.json()),
      fetch("http://localhost:7777/users").then((value) => value.json()),
      fetch(
        "http://localhost:7777/games/" +
          this.props.location.state.gameID +
          "/tags"
      ).then((value) => value.json()),
      fetch(
        "http://localhost:7777/games/" + this.props.location.state.gameID
      ).then((value) => value.json()),
    ])
      .then((value) => {
        this.setState(
          {
            tasks: value[0],
            users: value[1],
            gameTags: value[2],
            game: value[3],
            isLoaded: true,
          },
          () => {
            console.log(value);
            this.getTask();
          }
        );

        console.log(value);
        //json response
      })
      .catch((err) => {
        console.log(err);
      });

    this.timer = setInterval(() => this.getMessages(), 1000);
    this.timer2 = setInterval(() => this.getTags(), 1000);
    this.timer3 = setInterval(() => this.getGameDetails(), 3000);
  }

  componentWillUnmount() {
    clearInterval(this.timer);
    clearInterval(this.timer2);
    clearInterval(this.timer3);
  }
  async getMessages() {
    fetch(
      "http://localhost:7777/games/" +
        this.props.location.state.gameID +
        "/messages",
      { method: "GET" }
    )
      .then((response) => response.json())
      .then((responseData) => {
        this.setState({
          messages: responseData,
        });
        console.log(responseData);
      })
      .catch((error) => {
        console.error(error);
      });
  }
  async getTags() {
    fetch(
      "http://localhost:7777/games/" +
        this.props.location.state.gameID +
        "/tags",
      { method: "GET" }
    )
      .then((response) => response.json())
      .then((responseData) => {
        this.setState({
          gameTags: responseData,
        });
        console.log(responseData);
      })
      .catch((error) => {
        console.error(error);
      });
  }

  async getGameDetails() {
    fetch("http://localhost:7777/games/" + this.props.location.state.gameID, {
      method: "GET",
    })
      .then((response) => response.json())
      .then((responseData) => {
        if (responseData.finished == 1) {
          this.setState(
            {
              show: !this.state.show,
              game: responseData,
            },
            () => {
              setTimeout(() => {
                this.props.history.push({
                  pathname: "/home",
                });
              }, 2500);
            }
          );
        }

        console.log(responseData);
      })
      .catch((error) => {
        console.error(error);
      });
  }

  getUsername(userID) {
    for (var i = 0; i < this.state.users.length; i++) {
      console.log(this.state.users[i].username + "__________________" + userID);
      if (userID == this.state.users[i].userID) {
        console.log(this.state.users[i].username);
        return this.state.users[i].username;
      }
    }
  }

  getTask() {
    for (var i = 0; i < this.state.tasks.length; i++) {
      if (this.state.game.taskID == this.state.tasks[i].taskID) {
        this.setState(
          {
            task: this.state.tasks[i],
          },
          console.log(this.state.task.taskName)
        );
      }
    }
  }

  userTags(message) {
    if (this.getUsername(message.userID) == this.state.game.attackerUsername) {
      return (
        <div id={this.state.formCounter} className={styles.singleTag1}>
          {this.state.gameTags
            .filter(function (tag) {
              return tag.messageID == message.messageID;
            })

            .map((tag) => {
              if (
                this.getUsername(tag.userID) == this.state.game.attackerUsername
              ) {
                return (
                  <span className={styles.attackerTags}>#{tag.category},</span>
                );
              } else if (
                this.getUsername(tag.userID) == this.state.game.defenderUsername
              ) {
                return (
                  <span className={styles.defenderTags}>#{tag.category},</span>
                );
              }
            })}
        </div>
      );
    } else {
      return (
        <div id={this.state.formCounter} className={styles.singleTag2}>
          {this.state.gameTags
            .filter(function (tag) {
              return tag.messageID == message.messageID;
            })

            .map((tag) => {
              if (
                this.getUsername(tag.userID) == this.state.game.attackerUsername
              ) {
                return (
                  <span className={styles.attackerTags}>#{tag.category},</span>
                );
              } else if (
                this.getUsername(tag.userID) == this.state.game.defenderUsername
              ) {
                return (
                  <span className={styles.defenderTags}>#{tag.category},</span>
                );
              }
            })}
        </div>
      );
    }
  }
  check() {
    if (this.state.game.finished == 1) {
      this.showModal();
      //this.delay();
    }
  }
  showModal = (e) => {
    this.setState({
      show: !this.state.show,
    });
  };

  delay() {
    setTimeout(() => {
      this.setState({
        show: false,
      });
    }, 3000);
  }

  render() {
    const {
      error,
      isLoaded,
      games,
      messages,
      tasks,
      users,
      gameTags,
      game,
      task,
    } = this.state;
    if (error) {
      return <div>Error: {error.message}</div>;
    } else if (!isLoaded) {
      return <div>Loading...</div>;
    } else {
      return (
        <div className={styles.Main}>
          <TopBar />
          <div className={styles.MainGrid}>
            <div className={styles.topLeft}>
              <div className={styles.Task}>Task</div>
              <div className={styles.Role}>
                Name: {this.state.task.taskName}
              </div>
              <div className={styles.Role}>Role: Attacker</div>
              <div className={styles.Role}>
                Username: {this.state.game.attackerUsername}
              </div>
              <div className={styles.Role}>
                Points: {this.state.game.attackerPoints}
              </div>

              <div className={styles.Description}>
                Description: {this.state.task.attackersDescription}{" "}
              </div>
              <div className={styles.Category}>
                Task category: {this.state.task.category}
              </div>
              <div className={styles.Hints}>Hints/Guidelines</div>
              <div className={styles.guide}>
                <div className={styles.hints}>
                  {this.state.task.attackerHints}
                </div>
              </div>
            </div>
            <div className={styles.botLeft}>
              <div className={styles.Task}>Task</div>
              <div className={styles.Role}>
                Name: {this.state.task.taskName}
              </div>
              <div className={styles.Role}>Role: Defender</div>
              <div className={styles.Role}>
                Username: {this.state.game.defenderUsername}
              </div>
              <div className={styles.Role}>
                Points: {this.state.game.defenderPoints}
              </div>

              <div className={styles.Description}>
                {" "}
                Description: {this.state.task.defendersDescription}
              </div>
              <div className={styles.Category}>
                Task category: {this.state.task.category}
              </div>
              <div className={styles.Hints}>Hints/Guidelines</div>
              <div className={styles.guide}>
                <div className={styles.hints}>
                  {" "}
                  {this.state.task.defenderHints}
                </div>
              </div>
            </div>
            <div id='chat' className={styles.chatSide}>
              {" "}
              {this.state.messages.map((message) => (
                <>
                  <MessageComponent
                    page='Spectate'
                    attackerUsername={this.state.game.attackerUsername}
                    defenderUsername={this.state.game.defenderUsername}
                    gameID={message.gameID}
                    messageID={message.messageID}
                    username={this.getUsername(message.userID)}
                    userID={message.userID}
                    context={message.context}
                  />
                  {this.userTags(message)}
                </>
              ))}
            </div>
            <div className={styles.pad}>
              <button
                onClick={() => {
                  this.props.history.push({
                    pathname: "/home",
                  });
                }}
                className={styles.forfeit}
              >
                Exit
              </button>
            </div>
          </div>
          <Modal centered size='lg' show={this.state.show}>
            <div className={styles.titleModal}>
              <h1>Game finished</h1>
            </div>
            <img className={styles.imageTic} src='../success.png'></img>
            <div className={styles.cont}>
              <h5>
                The live game is over and you will be redirected to main menu
              </h5>{" "}
            </div>
          </Modal>
        </div>
      );
    }
  }
}

export default SpectatePage;
