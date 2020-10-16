import React, { Component } from "react";
import TopBarAnnotation from "../Components/TopBarAnnotationComponent";
import MessageComponent from "../Components/MessageComponent";
import styles from "../CSS/AnnotatePage.module.css";
import Cookies from "universal-cookie";
import Modal from "react-bootstrap/Modal";
import StarRatingComponent from "react-star-rating-component";

class AnnotatePage extends Component {
  constructor(props) {
    super(props);
    var cookies = new Cookies();
    this.state = {
      showEdit: false,
      task: "",
      cookie: cookies.get("userID"),
      annotationID: "",
      form: {
        userID: "",
        gameID: "",
      },
      ratingAttacker: 0,
      ratingDefender: 0,
      ratingGame: 0,
    };
  }

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
      fetch(
        "http://localhost:7777/games/" + this.props.location.state.gameID
      ).then((value) => value.json()),
    ])
      .then((value) => {
        this.setState(
          {
            messages: value[0],
            tasks: value[1],
            users: value[2],
            gameTags: value[3],
            game: value[4],
            isLoaded: true,
          },
          () => {
            console.log(value);
            this.getTask();
          }
        );

        console.log(this.props.location.state.annotationID);
        //json response
      })
      .catch((err) => {
        console.log(err);
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

  onStarClick(nextValue, prevValue, name) {
    console.log(nextValue);
    if (name == "attacker") {
      this.setState({
        ratingAttacker: nextValue,
      });
    } else if (name == "defender") {
      this.setState({
        ratingDefender: nextValue,
      });
    } else {
      this.setState({
        ratingGame: nextValue,
      });
    }
  }

  showEditModal = (e) => {
    this.setState({
      showEdit: !this.state.showEdit,
    });
  };

  sendRating() {
    var attacker = {
      ratingID: "",
      annotationID: "",
      stars: this.state.ratingAttacker,
      messageID: "totalAttacker",
      timestamp: "",
    };

    var defender = {
      ratingID: "",
      annotationID: "",
      stars: this.state.ratingDefender,
      messageID: "totalDefender",
      timestamp: "",
    };
    var game = {
      ratingID: "",
      annotationID: "",
      stars: this.state.ratingGame,
      messageID: "totalGame",
      timestamp: "",
    };

    console.log(this.state.ratingForm);
    if (attacker.stars != 0) {
      fetch(
        "http://localhost:7777/annotations/" +
          this.cookie +
          "/" +
          this.props.location.state.gameID +
          "/" +
          this.props.location.state.annotationID +
          "/ratings",
        {
          method: "POST",
          // We convert the React state to JSON and send it as the POST body
          body: JSON.stringify(attacker),
        }
      )
        .then((res) => res.json())
        .then((response) => {
          console.log(response);
        })
        .catch((error) => console.error("Error:", error));
    }

    if (defender.stars != 0) {
      fetch(
        "http://localhost:7777/annotations/" +
          this.cookie +
          "/" +
          this.props.location.state.gameID +
          "/" +
          this.props.location.state.annotationID +
          "/ratings",
        {
          method: "POST",
          // We convert the React state to JSON and send it as the POST body
          body: JSON.stringify(defender),
        }
      )
        .then((res) => res.json())
        .then((response) => {
          console.log(response);
        })
        .catch((error) => console.error("Error:", error));
    }
    if (game.stars != 0) {
      fetch(
        "http://localhost:7777/annotations/" +
          this.cookie +
          "/" +
          this.props.location.state.gameID +
          "/" +
          this.props.location.state.annotationID +
          "/ratings",
        {
          method: "POST",
          // We convert the React state to JSON and send it as the POST body
          body: JSON.stringify(game),
        }
      )
        .then((res) => res.json())
        .then((response) => {
          console.log(response);
        })
        .catch((error) => console.error("Error:", error));
    }
    this.showEditModal();
    setTimeout(() => {
      this.props.history.push({
        pathname:
          "/annotations/" + this.props.location.state.gameID + "/game_details",
        state: {
          userID: this.state.cookie,
          gameID: this.props.location.state.gameID,
          annotationID: this.props.location.state.annotationID,
          attackerUsername: this.state.game.attackerUsername,
          defenderUsername: this.state.game.defenderUsername,
          attackerPoints: this.state.game.attackerPoints,
          defenderPoints: this.state.game.defenderPoints,
        },
      });
    }, 1000);
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
      ratingAttacker,
      ratingDefender,
      ratingGame,
    } = this.state;
    if (error) {
      return <div>Error: {error.message}</div>;
    } else if (!isLoaded) {
      return <div>Loading...</div>;
    } else {
      return (
        <>
          <div className={styles.Main}>
            <TopBarAnnotation />
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
                  <MessageComponent
                    page='Annotate'
                    attackerUsername={this.state.game.attackerUsername}
                    annotationID={this.props.location.state.annotationID}
                    defenderUsername={this.state.game.defenderUsername}
                    gameID={message.gameID}
                    messageID={message.messageID}
                    username={this.getUsername(message.userID)}
                    userID={message.userID}
                    context={message.context}
                  />
                ))}
              </div>
              <div className={styles.pad}>
                <input
                  className={styles.type}
                  size='40'
                  onChange={this.typeMessage}
                  onKeyDown={this.keyPress}
                  readOnly
                  name='message'
                  id='type'
                ></input>

                <button
                  onClick={() => this.showEditModal()}
                  className={styles.forfeit}
                >
                  Rate
                </button>
              </div>
            </div>
          </div>
          <Modal centered show={this.state.showEdit}>
            <div className={styles.title}>
              <h2>Rate Users and Game</h2>
            </div>
            <div className={styles.line}>
              <div className={styles.attackerTitle}>Rate Attacker</div>
              <StarRatingComponent
                name='attacker'
                className={styles.stars}
                starCount={5}
                value={ratingAttacker}
                onStarClick={this.onStarClick.bind(this)}
                editing={"true"}
                starColor={"#011f4b"}
                emptyStarColor={"#ccc"}
              />
            </div>
            <div className={styles.line}>
              <div className={styles.attackerTitle}>Rate Defender</div>
              <StarRatingComponent
                name='defender'
                className={styles.stars}
                starCount={5}
                value={ratingDefender}
                onStarClick={this.onStarClick.bind(this)}
                editing={"true"}
                starColor={"#011f4b"}
                emptyStarColor={"#ccc"}
              />
            </div>
            <div className={styles.line}>
              <div className={styles.attackerTitle}>Rate Game</div>
              <StarRatingComponent
                name='game'
                className={styles.stars}
                starCount={5}
                value={ratingGame}
                onStarClick={this.onStarClick.bind(this)}
                editing={"true"}
                starColor={"#011f4b"}
                emptyStarColor={"#ccc"}
              />
            </div>
            <div className={styles.footer}>
              <button
                onClick={() => {
                  this.sendRating();
                }}
                className={styles.sumbit}
                type='submit'
                value='Submit'
              >
                Submit
              </button>
              <button
                className={styles.cancel}
                onClick={(e) => {
                  this.showEditModal(e);
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
}

export default AnnotatePage;
