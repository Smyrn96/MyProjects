import React, { Component } from "react";
import styles from "../CSS/Chat.module.css";
import TopBar from "../Components/TopBarComponent";
import TimerComponent from "../Components/TimerComponent";
import MessageComponent from "../Components/MessageComponent";
import Cookies from "universal-cookie";
import { Prompt } from "react-router-dom";
import Modal from "react-bootstrap/Modal";

class Chat extends Component {
  constructor(props) {
    super(props);
    var cookies = new Cookies();
    this.state = {
      flag: 0,
      tags: [],
      reason: "",
      show: false,
      showWait: false,
      showEnd: false,
      showEndConfirm: false,
      time: 0,
      attackerUsername: "",
      defenderUsername: "",
      localMessages: [],
      attackerMessages: [],
      defenderMessages: [],
      isBlocking: true,
      chatUsers: [],
      cookie: cookies.get("userID"),
      message: "",
      temp: [],
      form: {
        context: "",
        userID: "",
      },
      messages: [],
      tasks: [],
      users: [],
      gameTags: [],
    };
    this.attackerOrDefenderMessage = this.attackerOrDefenderMessage.bind(this);
    this.typeMessage = this.typeMessage.bind(this);
    this.closeChat = this.closeChat.bind(this);
    this.activeUsers = this.activeUsers.bind(this);
    this.keyPress = this.keyPress.bind(this);
  }

  ws = new WebSocket(
    "ws://localhost:7777/" +
      this.props.location.state.userID +
      "/games/" +
      this.props.location.state.gameID
  );

  componentDidMount() {
    Promise.all([
      fetch(
        "http://localhost:7777/games/" +
          this.props.location.state.gameID +
          "/messages"
      ).then((value) => value.json()),
      fetch("http://localhost:7777/tasks").then((value) => value.json()),
      fetch("http://localhost:7777/users").then((value) => value.json()),
      fetch(
        "http://localhost:7777/games/" +
          this.props.location.state.gameID +
          "/tags"
      ).then((value) => value.json()),
    ])
      .then((value) => {
        this.setState({
          messages: value[0],
          tasks: value[1],
          users: value[2],
          gameTags: value[3],
          isLoaded: true,
        });

        console.log(value);
        //json response
      })
      .catch((err) => {
        console.log(err);
      });

    this.ws.onopen = () => {
      // on connecting, do nothing but log it to the console
      console.log("Role:" + this.props.location.state.role + "connected");
    };

    this.ws.onmessage = (msg) => this.updateChat(msg);

    this.ws.onclose = () => {
      console.log(
        "User:" + this.props.location.state.defenderUsername + "disconnected"
      );

      // automatically try to reconnect on connection loss
    };

    //this.ws.onmessage = (msg) => updateChat(msg);
  }

  chooseUserUsername(userID) {
    for (var i = 0; i < this.state.users.length; i++) {
      console.log("EDW " + this.state.users[i].userID + this.state.cookie);
      if (this.state.users[i].userID === userID) {
        console.log("EDW " + this.state.users[i].userID);
        return this.state.users[i].username;
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

  chooseUserScore(sender) {
    for (var i = 0; i < this.state.users.length; i++) {
      console.log("EDW " + this.state.users[i].userID + this.state.cookie);
      if (this.state.users[i].username === sender) {
        console.log("EDW " + this.state.users[i].userID);
        return this.state.users[i].score;
      }
    }
  }
  getOpponent(username) {
    if (username == this.state.attackerUsername) {
      return this.state.defenderUsername;
    } else {
      return this.state.attackerUsername;
    }
  }
  getTime(value) {
    this.setState({
      time: value,
    });
  }

  updateChat(msg) {
    console.log(msg);
    let data = JSON.parse(msg.data);
    console.log(data);

    var slash = data.userMessage.slice(0, 8);
    var userAfter = data.userMessage.slice(8);
    var user = data.userMessage.slice(8, data.userMessage.indexOf("!-!"));
    var reason = data.userMessage.slice(data.userMessage.indexOf("!-!") + 3);
    this.setState({
      reason: reason,
    });
    var slash2 = data.userMessage.slice(0, 10);
    var user2 = data.userMessage.slice(10);
    console.log(slash2);

    if (data.userMessage === "joined the chat") {
      if (this.props.location.state.attackerUsername === data.userlist[0]) {
        this.setState((state) => ({
          chatUsers: data.userlist,
          attackerUsername: data.userlist[0],
          defenderUsername: data.userlist[1],
        }));
      } else if (
        this.props.location.state.defenderUsername === data.userlist[0]
      ) {
        this.setState((state) => ({
          chatUsers: data.userlist,
          defenderUsername: data.userlist[0],
          attackerUsername: data.userlist[1],
        }));
      } else {
        if (this.props.location.state.role === "Attacker") {
          this.setState((state) => ({
            chatUsers: data.userlist,
            defenderUsername: data.userlist[0],
            attackerUsername: data.userlist[1],
          }));
        } else if (this.props.location.state.role === "Defender") {
          this.setState(
            (state) => ({
              chatUsers: data.userlist,
              attackerUsername: data.userlist[0],
              defenderUsername: data.userlist[1],
            }),
            () => {
              console.log("HELLOOOOOOOOOOOOOOO" + data.userlist[0]);
            }
          );
        }
      }

      this.forceUpdate();
    } else if (slash === "Forfeit!") {
      if (userAfter != this.chooseUserUsername(this.state.cookie)) {
        this.setState(
          {
            isBlocking: false,
          },
          () => {
            console.log(slash);
            this.props.history.push({
              pathname:
                "/games/" + this.props.location.state.gameID + "/matchDetails",
              state: {
                title: this.chooseUserUsername(this.state.cookie) + " won",
                gameID: this.props.location.state.gameID,
                attackerUserID: this.chooseUser(this.state.attackerUsername),
                defenderUserID: this.chooseUser(this.state.defenderUsername),
                attackerUsername: this.state.attackerUsername,
                defenderUsername: this.state.defenderUsername,
                attackerPoints: this.chooseUserScore(
                  this.state.attackerUsername
                ),
                defenderPoints: this.chooseUserScore(
                  this.state.defenderUsername
                ),
                taskID: this.props.location.state.taskID,
                category: this.props.location.state.category,
                completionTime: this.state.time,
                rounds: this.state.localMessages.length,
                tagsCount: this.state.gameTags.length,
                attackerMessages: this.state.attackerMessages.length,
                defenderMessages: this.state.defenderMessages.length,
                forfeit: "no",
              },
            });
          }
        );
      }
    } else if (slash === "EndGame!") {
      if (user != this.chooseUserUsername(this.state.cookie)) {
        this.showModalEndConfirm();
      }
    } else if (slash === "EndGaOK!") {
      if (userAfter != this.chooseUserUsername(this.state.cookie)) {
        this.setState(
          {
            isBlocking: false,
          },
          () => {
            console.log(slash);
            this.props.history.push({
              pathname:
                "/games/" + this.props.location.state.gameID + "/matchDetails",
              state: {
                title: "Game Finished",
                gameID: this.props.location.state.gameID,
                attackerUserID: this.chooseUser(this.state.attackerUsername),
                defenderUserID: this.chooseUser(this.state.defenderUsername),
                attackerUsername: this.state.attackerUsername,
                defenderUsername: this.state.defenderUsername,
                attackerPoints: this.chooseUserScore(
                  this.state.attackerUsername
                ),
                defenderPoints: this.chooseUserScore(
                  this.state.defenderUsername
                ),
                taskID: this.props.location.state.taskID,
                category: this.props.location.state.category,
                completionTime: this.state.time,
                rounds: this.state.localMessages.length,
                tagsCount: this.state.gameTags.length,
                attackerMessages: this.state.attackerMessages.length,
                defenderMessages: this.state.defenderMessages.length,
              },
            });
          }
        );
      }
    } else if (slash === "EndGaNO!") {
      if (userAfter != this.chooseUserUsername(this.state.cookie)) {
        this.closeModalWait();
      }
    } else {
      var messID = data.userMessage.slice(1, 8);
      var con = data.userMessage.slice(8);

      console.log(messID);
      console.log(con);

      var responseJson = {
        context: con,
        userID: this.chooseUser(data.sender),
        username: data.sender,
        messageID: messID,
        gameID: this.props.location.state.gameID,
      };
      if (responseJson.userID != this.state.cookie) {
        this.setState(
          (state) => ({
            localMessages: [...state.localMessages, responseJson],
          }),

          this.attackerOrDefenderMessage(this.state, responseJson)
        );
        var messageBody = document.querySelector("#chat");
        messageBody.scrollTop =
          messageBody.scrollHeight - messageBody.clientHeight;
      }
    }
  }

  attackerOrDefenderMessage(state, Json) {
    console.log(
      this.props.location.state.defenderUsername + "___________" + Json.username
    );
    console.log(
      this.props.location.state.attackerUsername + "___________" + Json.username
    );
    if (this.props.location.state.attackerUsername === Json.username) {
      this.setState((state) => ({
        attackerMessages: [...state.attackerMessages, Json],
      }));
    } else if (this.props.location.state.defenderUsername == Json.username) {
      this.setState((state) => ({
        defenderMessages: [...state.defenderMessages, Json],
      }));
    } else {
      if (this.props.location.state.role === "Attacker") {
        this.setState((state) => ({
          defenderMessages: [...state.defenderMessages, Json],
        }));
      } else {
        this.setState((state) => ({
          attackerMessages: [...state.attackerMessages, Json],
        }));
      }
    }
  }

  typeMessage = (event) => {
    console.log(event.target.value);

    this.setState({
      message: event.target.value,
    });
  };
  handleClick = () => {
    if (this.state.message !== "") {
      document.getElementById("type").value = "";

      var requestJ = {
        context: this.state.message,
        userID: this.state.cookie,
      };

      var responseJson = {
        context: this.state.message,
        userID: this.state.cookie,
        username: this.chooseUserUsername(this.state.cookie),
        messageID: "",
        gameID: "",
      };

      fetch(
        "http://localhost:7777/games/" +
          this.props.location.state.gameID +
          "/messages",
        {
          method: "POST",
          // We convert the React state to JSON and send it as the POST body
          body: JSON.stringify(requestJ),
        }
      )
        .then((res) => res.json())
        .then((response) => {
          var response = JSON.parse(response);
          console.log(response);
          responseJson.messageID = response.message_id;
          responseJson.gameID = response.gameID;
          this.ws.send("#" + responseJson.messageID + this.state.message);
          console.log(responseJson);
          this.setState(
            (state) => ({
              localMessages: [...state.localMessages, responseJson],
            }),

            this.attackerOrDefenderMessage(this.state, responseJson)
          );
          var messageBody = document.querySelector("#chat");
          messageBody.scrollTop =
            messageBody.scrollHeight - messageBody.clientHeight;
        })
        .catch((error) => console.error("Error:", error));
    }
  };
  keyPress(e) {
    if (e.keyCode == 13) {
      if (this.state.message !== "") {
        document.getElementById("type").value = "";

        var requestJ = {
          context: this.state.message,
          userID: this.state.cookie,
        };

        var responseJson = {
          context: this.state.message,
          userID: this.state.cookie,
          username: this.chooseUserUsername(this.state.cookie),
          messageID: "",
          gameID: "",
        };

        fetch(
          "http://localhost:7777/games/" +
            this.props.location.state.gameID +
            "/messages",
          {
            method: "POST",
            // We convert the React state to JSON and send it as the POST body
            body: JSON.stringify(requestJ),
          }
        )
          .then((res) => res.json())
          .then((response) => {
            var response = JSON.parse(response);
            console.log(response);
            responseJson.messageID = response.message_id;
            responseJson.gameID = response.gameID;
            this.ws.send("#" + responseJson.messageID + this.state.message);
            console.log(responseJson);
            this.setState(
              (state) => ({
                localMessages: [...state.localMessages, responseJson],
              }),

              this.attackerOrDefenderMessage(this.state, responseJson)
            );
            var messageBody = document.querySelector("#chat");
            messageBody.scrollTop =
              messageBody.scrollHeight - messageBody.clientHeight;
          })
          .catch((error) => console.error("Error:", error));
      }
    }
  }

  chooseDescription() {
    if (this.props.location.state.role === "Attacker") {
      return this.props.location.state.attackerDescription;
    } else {
      return this.props.location.state.defenderDescription;
    }
  }

  chooseHints() {
    if (this.props.location.state.role === "Attacker") {
      return this.props.location.state.attackerHints;
    } else {
      return this.props.location.state.defenderHints;
    }
  }

  chooseRole() {
    if (this.props.location.state.role === "Attacker") {
      return this.props.location.state.attackerUsername;
    } else if (this.props.location.state.role === "Defender") {
      return this.props.location.state.defenderUsername;
    }
  }

  activeUsers() {
    if (this.state.chatUsers.length === 2) {
      this.state.flag = 1;
      return "Both connected. Feel free to talk!";
    }
  }

  async getTagsGame() {
    let response = await fetch(
      "http://localhost:7777/games/" +
        this.props.location.state.gameID +
        "/tags",
      {
        method: "GET",
        // We convert the React state to JSON and send it as the POST body
      }
    );
    let json = await response.json();
    this.setState({
      gameTags: json,
    });
  }

  userEnd = (e) => {
    this.showModalEnd();
    this.ws.send(
      "EndGame!" +
        this.chooseUserUsername(this.state.cookie) +
        "!-!" +
        this.state.reason
    );
    this.showModalWait();
  };

  userEndSecond = (e) => {
    this.setState(
      {
        isBlocking: false,
      },
      () => {
        this.ws.send("EndGaOK!" + this.chooseUserUsername(this.state.cookie));
        this.gameDetails();
      }
    );
  };
  closeModalWait = (e) => {
    this.setState({
      showWait: false,
    });
  };
  showModalWait = (e) => {
    this.setState({
      showWait: !this.state.showWait,
    });
  };

  showModalEnd = (e) => {
    this.setState({
      showEnd: !this.state.showEnd,
    });
    this.getTagsGame();
  };

  forfeitWindowEnd() {
    this.setState({
      showEnd: !this.state.showEnd,
    });
  }

  showModal = (e) => {
    this.setState({
      show: !this.state.show,
    });
  };

  showModalEndConfirm = (e) => {
    this.setState({
      showEndConfirm: !this.state.showEndConfirm,
    });
  };

  forfeitWindow() {
    this.setState({
      show: !this.state.show,
    });
  }

  closeChat() {
    this.forfeitWindow();
  }

  endGame() {
    if (this.state.localMessages.length !== 0) {
      return (
        <div
          onClick={() => {
            this.showModalEnd();
          }}
          className={styles.end}
        >
          Is the task completed? End the game!
        </div>
      );
    }
  }

  async updateGameFetch(form) {
    let response = await fetch(
      "http://localhost:7777/games/" + this.props.location.state.gameID,
      {
        method: "PATCH",
        // We convert the React state to JSON and send it as the POST body
        body: JSON.stringify(form),
      }
    );
    let json = await response.json();
  }

  gameDetails = (e) => {
    if (e != null && e.target.id === "Forfeit") {
      var form = {
        completionTime: this.state.time,
        rounds: this.state.localMessages.length,
        tagsCount: this.state.gameTags.length,
        ongoing: false,
        finished: true,
      };
      this.updateGameFetch(form);

      this.ws.send("Forfeit!" + this.chooseUserUsername(this.state.cookie));

      this.setState(
        {
          isBlocking: false,
        },
        () => {
          this.props.history.push({
            pathname:
              "/games/" + this.props.location.state.gameID + "/matchDetails",
            state: {
              title: this.chooseUserUsername(this.state.cookie) + " lost",
              gameID: this.props.location.state.gameID,
              attackerUserID: this.chooseUser(this.state.attackerUsername),
              defenderUserID: this.chooseUser(this.state.defenderUsername),
              attackerUsername: this.state.attackerUsername,
              defenderUsername: this.state.defenderUsername,
              attackerPoints: this.chooseUserScore(this.state.attackerUsername),
              defenderPoints: this.chooseUserScore(this.state.defenderUsername),
              taskID: this.props.location.state.taskID,
              category: this.props.location.state.category,
              completionTime: this.state.time,
              rounds: this.state.localMessages.length,
              tagsCount: this.state.gameTags.length,
              attackerMessages: this.state.attackerMessages.length,
              defenderMessages: this.state.defenderMessages.length,
              forfeit: "yes",
            },
          });
        }
      );
    } else {
      //this.ws.send("EndGame" + this.chooseUserUsername(this.state.cookie));
      var form = {
        completionTime: this.state.time,
        rounds: this.state.localMessages.length,
        tagsCount: this.state.gameTags.length,
        ongoing: false,
        finished: true,
      };
      this.updateGameFetch(form);

      this.props.history.push({
        pathname:
          "/games/" + this.props.location.state.gameID + "/matchDetails",
        state: {
          title: "Game Finished",
          gameID: this.props.location.state.gameID,
          attackerUserID: this.chooseUser(this.state.attackerUsername),
          defenderUserID: this.chooseUser(this.state.defenderUsername),
          attackerUsername: this.state.attackerUsername,
          defenderUsername: this.state.defenderUsername,
          attackerPoints: this.chooseUserScore(this.state.attackerUsername),
          defenderPoints: this.chooseUserScore(this.state.defenderUsername),
          taskID: this.props.location.state.taskID,
          category: this.props.location.state.category,
          completionTime: this.state.time,
          rounds: this.state.localMessages.length,
          tagsCount: this.state.gameTags.length,
          attackerMessages: this.state.attackerMessages.length,
          defenderMessages: this.state.defenderMessages.length,
        },
      });
    }
  };

  myChangeHandlerReason = (e) => {
    this.setState({
      [e.target.id]: e.target.value,
    });
  };

  render() {
    console.log(this.state.attackerUsername);
    console.log(this.state.defenderUsername);
    return (
      <>
        <Prompt
          when={this.state.isBlocking}
          message={() =>
            `Are you sure you want to leave? Leavers lose the game!`
          }
        />
        <div className={styles.Main}>
          <TopBar />
          <div className={styles.MainGrid}>
            <div className={styles.topLeft}>
              <div className={styles.Task}>Task</div>
              <div className={styles.Role}>
                Role: {this.props.location.state.role}
              </div>
              <div className={styles.Description}>
                Description : {this.chooseDescription()}
              </div>
              <div className={styles.Category}>
                Task category: {this.props.location.state.category}
              </div>
              <div className={styles.Hints}>Hints/Guidelines</div>
              <div className={styles.guide}>
                <div className={styles.hints}>{this.chooseHints()}</div>
              </div>
            </div>
            <div className={styles.botLeft}>
              <div className={styles.Task}>Time</div>
              <div className={styles.timer}>
                <TimerComponent
                  time={this.getTime.bind(this)}
                  flag={this.state.flag}
                />
              </div>
              <div className={styles.info}>Info</div>
              <div className={styles.total}>
                Total messages : {this.state.localMessages.length}
              </div>
              <ul className={styles.list}>
                <li>Attacker: {this.state.attackerMessages.length}</li>
                <li>Defender: {this.state.defenderMessages.length}</li>
              </ul>
            </div>
            <div id='chat' className={styles.chatSide}>
              <div className={styles.topText}>
                <ul className={styles.chatList}>
                  {this.state.chatUsers.map((chat) => (
                    <li>
                      User <span>{chat}</span> joined the chat
                    </li>
                  ))}
                </ul>
                {this.activeUsers()}
              </div>

              {this.state.localMessages.map((message) => (
                <MessageComponent
                  page=''
                  attackerUsername=''
                  defenderUsername=''
                  gameID={message.gameID}
                  messageID={message.messageID}
                  username={message.username}
                  userID={message.userID}
                  context={message.context}
                />
              ))}
              {this.endGame()}
            </div>
            <div className={styles.pad}>
              <input
                className={styles.type}
                placeholder='Type a message...'
                size='40'
                onChange={this.typeMessage}
                onKeyDown={this.keyPress}
                name='message'
                id='type'
              ></input>
              <img
                onClick={this.handleClick}
                className={styles.send}
                src='../../send-button.png'
              ></img>
              <button
                onClick={() => this.closeChat()}
                className={styles.forfeit}
              >
                Forfeit
              </button>
            </div>
          </div>
        </div>
        <Modal centered show={this.state.show}>
          <div className={styles.title}>Forfeit?</div>
          <div className={styles.cont}>Are you sure you want to leave?</div>
          <div className={styles.footer}>
            <button
              onClick={this.gameDetails}
              className={styles.sumbit}
              value='Yes'
              id='Forfeit'
            >
              Leave
            </button>
            <button
              className={styles.cancel}
              onClick={(e) => {
                this.forfeitWindow();
              }}
            >
              Cancel
            </button>
          </div>
        </Modal>
        <Modal centered show={this.state.showEnd}>
          <div className={styles.title}>Task Completed?</div>
          <div className={styles.cont}>Are you sure the game is over?</div>
          <textarea
            className={styles.reason}
            onChange={this.myChangeHandlerReason}
            placeholder='Explain the reason you terminate the game...'
            name='TerminateReason'
            id='reason'
          ></textarea>
          <div className={styles.footer}>
            <button
              onClick={(e) => {
                this.userEnd();
              }}
              className={styles.sumbit}
              value='Yes'
              id='Finish'
            >
              Leave
            </button>
            <button
              className={styles.cancel}
              onClick={(e) => {
                this.forfeitWindowEnd();
              }}
            >
              Cancel
            </button>
          </div>
        </Modal>

        <Modal size='lg' centered show={this.state.showWait}>
          <div className={styles.title}>Ending Confirmation</div>
          <div className={styles.cont}>
            Waiting for{" "}
            {this.getOpponent(this.chooseUserUsername(this.state.cookie))} to
            confirm the ending of the game
          </div>
          <div class='text-center'>
            <div class='spinner-border' role='status'>
              <span class='sr-only'>Loading...</span>
            </div>
          </div>
          <div className={styles.footer}></div>
        </Modal>

        <Modal centered size='lg' show={this.state.showEndConfirm}>
          <div className={styles.title}>Task Completed Confirmation</div>
          <div className={styles.cont1}>
            Do you agree with &nbsp;
            {this.getOpponent(this.chooseUserUsername(this.state.cookie))} that
            the task is completed? (Reason: {this.state.reason})
          </div>
          <div className={styles.footer}>
            <button
              onClick={(e) => {
                this.userEndSecond();
              }}
              className={styles.sumbit1}
              value='Yes'
              id='Finish'
            >
              Yes
            </button>
            <button
              className={styles.cancel}
              onClick={(e) => {
                this.showModalEndConfirm();
                this.ws.send(
                  "EndGaNO!" + this.chooseUserUsername(this.state.cookie)
                );
              }}
            >
              Cancel
            </button>
          </div>
        </Modal>
      </>
    );
  }
}

export default Chat;
