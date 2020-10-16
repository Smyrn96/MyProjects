import React, { Component } from "react";
import TopBarTasksComponent from "../Components/TopBarTasksComponent";
import styles from "../CSS/MonitorSpectatePage.module.css";
import MessageComponent from "../Components/MessageComponent";
import Modal from "react-bootstrap/Modal";

class MonitorSpectatePage extends Component {
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
      fetch(
        "http://localhost:7777/games/" +
          this.props.location.state.gameID +
          "/messages"
      ).then((value) => value.json()),
    ])
      .then((value) => {
        this.setState(
          {
            tasks: value[0],
            users: value[1],
            gameTags: value[2],
            game: value[3],
            messages: value[4],
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

  getUsername(userID) {
    for (var i = 0; i < this.state.users.length; i++) {
      console.log(this.state.users[i].username + "__________________" + userID);
      if (userID == this.state.users[i].userID) {
        console.log(this.state.users[i].username);
        return this.state.users[i].username;
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
        <>
          <TopBarTasksComponent />
          <div className={styles.Main}>
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
                      pathname: "/tasks/home",
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
        </>
      );
    }
  }
}

export default MonitorSpectatePage;
