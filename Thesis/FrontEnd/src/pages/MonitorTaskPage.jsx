import React, { Component } from "react";
import TopBarTasksComponent from "../Components/TopBarTasksComponent";
import MonitorTaskGameTab from "../Components/MonitorTaskGameTab";
import styles from "../CSS/MonitorTaskPage.module.css";
import Cookies from "universal-cookie";

class MonitorTaskPage extends Component {
  constructor(props) {
    super(props);
    var cookies = new Cookies();
    this.state = {
      taskID: this.props.location.state.taskID,
      cookie: cookies.get("userID"),
      totalMessages: 0,
      totalTags: 0,
    };
  }

  componentDidMount() {
    Promise.all([
      fetch("http://localhost:7777/games").then((value) => value.json()),
      fetch(
        "http://localhost:7777/tasks/" +
          this.props.location.state.taskID +
          "/games"
      ).then((value) => value.json()),
    ])
      .then((value) => {
        this.setState(
          {
            games: value[0],
            gamesTask: value[1],
            isLoaded: true,
          },
          () => {
            console.log(this.state.gamesTask);
          }
        );

        console.log(this.state.games[0]);
        //json response
      })
      .catch((err) => {
        console.log(err);
      });
  }

  spectateGame(game) {
    this.props.history.push({
      pathname:
        "/tasks/" +
        this.props.location.state.taskID +
        "/monitor/" +
        game.gameID,
      state: {
        userID: this.state.cookie,
        gameID: game.gameID,
        source: "Task",
        taskID: this.props.location.state.taskID,
      },
    });
  }

  render() {
    var taskID = this.state.taskID;
    const { error, isLoaded, tasks, user, games } = this.state;
    if (error) {
      return <div>Error: {error.message}</div>;
    } else if (!isLoaded) {
      return <div>Loading...</div>;
    } else {
      return (
        <>
          <TopBarTasksComponent />
          <div className={styles.MonitorTask}>
            <h1>Monitor Task</h1>
          </div>
          <div className={styles.main}>
            <div className={styles.left}>
              <div className={styles.title}>Task Name</div>
              <div className={styles.content}>
                {this.props.location.state.taskName}
              </div>
              <div className={styles.title}>Task Description</div>
              <div className={styles.content}>
                {this.props.location.state.taskDescription}
              </div>
              <div className={styles.title}>Category</div>
              <div className={styles.content}>
                {this.props.location.state.category}
              </div>
              <div className={styles.title}>Number of Players</div>
              <div className={styles.content}>2-player game</div>
              <div className={styles.title}>Created Date</div>
              <div className={styles.content}>
                {this.props.location.state.timestamp}
              </div>
            </div>
            <div className={styles.center}>
              {this.state.games
                .filter(function (game) {
                  // filter first for friends
                  return game.taskID == taskID && game.finished == 1;
                })
                .map(function (game) {
                  // map the new array to list items
                  return (
                    <span
                      onClick={() => {
                        this.spectateGame(game);
                      }}
                      className={styles.dummy}
                    >
                      <MonitorTaskGameTab
                        onClick={() => {
                          this.spectateGame();
                        }}
                        userID={this.state.cookie}
                        gameID={game.gameID}
                        attackerUsername={game.attackerUsername}
                        defenderUsername={game.defenderUsername}
                        attackerPoints={game.attackerPoints}
                        defenderPoints={game.defenderPoints}
                        category={game.category}
                      />
                    </span>
                  ); // don't forget unique key for each item
                }, this)}
            </div>
            <div className={styles.right}>
              <div className={styles.title}>Total Participants</div>
              <div className={styles.content}>
                {this.props.location.state.Participants}
              </div>
              <div className={styles.title}>Total Messages</div>
              <div className={styles.content}>
                {this.props.location.state.totalMessages}
              </div>
              <div className={styles.title}>Total Tags</div>
              <div className={styles.content}>
                {" "}
                {this.props.location.state.totalTags}
              </div>
              <div className={styles.title}>Average Messages Per Game</div>
              <div className={styles.content}>
                {(
                  this.props.location.state.totalMessages /
                  (this.props.location.state.Participants / 2)
                ).toFixed(2)}
              </div>
              <div className={styles.title}>Average Tags Per Game</div>
              <div className={styles.content}>
                {(
                  this.props.location.state.totalTags /
                  (this.props.location.state.Participants / 2)
                ).toFixed(2)}
              </div>
            </div>
          </div>
        </>
      );
    }
  }
}

export default MonitorTaskPage;
