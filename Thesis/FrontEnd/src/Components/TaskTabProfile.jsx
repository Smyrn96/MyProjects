import React, { Component } from "react";
import styles from "../CSS/TaskTabProfile.module.css";
import Modal from "react-bootstrap/Modal";

class TaskTabProfile extends Component {
  constructor(props) {
    super(props);
    this.state = {
      tags: [],
      messages: [],
      totalTags: 0,
      totalMessages: 0,
      showConfirm: false,
      showActive: false,
      showActivePrimary: false,
      show: false,
      selectedGames: [],
    };
  }

  componentDidMount() {
    Promise.all([
      fetch("http://localhost:7777/games").then((value) => value.json()),
      fetch(
        "http://localhost:7777/tasks/" + this.props.taskID + "/games"
      ).then((value) => value.json()),
    ])
      .then((value) => {
        this.setState(
          {
            games: value[0],
            taskGames: value[1],
            Participants: value[1].length * 2,

            isLoaded: true,
            timestamp: this.timestampTime(this.props.timestamp),
          },
          () => {
            this.fetchMethod();
            console.log(value[2]);
          }
        );

        console.log("HELLO THERE " + this.state);
        //json response
      })
      .catch((err) => {
        console.log(err);
      });
  }

  fetchMethod() {
    fetch("http://localhost:7777/tasks/" + this.props.taskID + "/games/stats")
      .then((value) => value.json())
      .then((value) => {
        this.setState({
          totalMessages: value[0],
          totalTags: value[1],
        });
      });
  }
  timestampTime(timestamp) {
    var dateObj = new Date(timestamp);
    var utcString = dateObj.toLocaleString();
    return utcString;
  }

  deactivateTask() {
    this.showActivePrimaryModal();
    fetch("http://localhost:7777/tasks/" + this.props.taskID, {
      method: "PUT",
      // We convert the React state to JSON and send it as the POST body
    })
      .then((res) => res.json())
      .then((response) => {
        console.log(response);

        this.showConfirmModalActive();
      })
      .catch((error) => console.error("Error:", error));
  }

  deleteTask() {
    this.showConfirmModal();
    fetch("http://localhost:7777/tasks/" + this.props.taskID, {
      method: "DELETE",
      // We convert the React state to JSON and send it as the POST body
    })
      .then((res) => res.json())
      .then((response) => {
        console.log(response);

        this.showModal();
      })
      .catch((error) => console.error("Error:", error));
  }

  showModal = (e) => {
    this.setState(
      {
        show: !this.state.show,
      },
      () => {
        setTimeout(() => {
          this.setState(
            {
              show: false,
            },
            () => {
              window.location.reload(false);
            }
          );
        }, 3000);
      }
    );
  };

  showConfirmModal = (e) => {
    this.setState({
      showConfirm: !this.state.showConfirm,
    });
  };

  showConfirmModalActive = (e) => {
    this.setState(
      {
        showActive: !this.state.showActive,
      },
      () => {
        setTimeout(() => {
          this.setState(
            {
              showActive: false,
            },
            () => {
              window.location.reload(false);
            }
          );
        }, 3000);
      }
    );
  };

  showActivePrimaryModal = (e) => {
    this.setState({
      showActivePrimary: !this.state.showActivePrimary,
    });
  };

  chooseActive(active) {
    if (active == true) {
      return "Yes";
    } else {
      return "No";
    }
  }

  render() {
    console.log(this.state);
    const { error, isLoaded, games, taskGames } = this.state;
    if (error) {
      return <div>Error: {error.message}</div>;
    } else if (!isLoaded) {
      return <div>Loading...</div>;
    } else {
      return (
        <>
          <div className={styles.singleTab}>
            <div className={styles.row}>
              <div className={styles.Username}>
                <div className={styles.titles}>Task Name</div>
                <div>{this.props.taskName}</div>
              </div>
              <div className={styles.Defender}>
                <div className={styles.titles}>Category</div>
                <div>{this.props.category}</div>
              </div>
              <div className={styles.Tags}>
                <div className={styles.titles}>Number of players</div>
                <div>2-player game</div>
              </div>

              <div className={styles.Time}>
                <div className={styles.titles}>Participants</div>
                <div>{this.state.taskGames.length * 2}</div>
              </div>
              <div className={styles.Date}>
                <div className={styles.titles}>Date</div>
                <div>{this.state.timestamp}</div>
              </div>
              <div className={styles.active}>
                <div className={styles.titles}>Active</div>
                <div className={styles.context}>
                  {this.chooseActive(this.props.active)}
                </div>
              </div>
            </div>
            <button
              onClick={() => {
                this.showActivePrimaryModal();
              }}
              className={styles.activeTask}
              value='Deactivate Task'
            >
              Deactivate Task
            </button>
            <button
              onClick={() => {
                this.props.history.push({
                  pathname: "/tasks/" + this.props.taskID + "/monitor",
                  state: {
                    taskID: this.props.taskID,
                    taskName: this.props.taskName,
                    taskDescription: this.props.taskDescription,
                    attackersDescription: this.props.attackersDescription,
                    defendersDescription: this.props.defendersDescription,
                    category: this.props.category,
                    attackerHints: this.props.attackerHints,
                    defenderHints: this.props.defenderHints,
                    maxMessages: this.props.maxMessages,
                    taskCreator: this.props.taskCreator,
                    timestamp: this.timestampTime(this.props.timestamp),
                    Participants: this.state.Participants,
                    selectedGames: this.state.selectedGames,
                    totalMessages: this.state.totalMessages,
                    totalTags: this.state.totalTags,
                  },
                });
              }}
              className={styles.monitor}
              value='Monitor Task'
            >
              Monitor Task
            </button>
            <button
              onClick={() => {
                this.showConfirmModal();
              }}
              className={styles.delete}
              value='Delete Task'
            >
              Delete Task
            </button>
          </div>
          <Modal centered show={this.state.showConfirm}>
            <div className={styles.title}>Delete task?</div>
            <div className={styles.cont}>
              Are you sure you want to delete this task?
            </div>
            <div className={styles.footer}>
              <button
                onClick={() => {
                  this.deleteTask();
                }}
                className={styles.yes}
                value='yes'
              >
                Yes
              </button>
              <button
                onClick={() => {
                  this.showConfirmModal();
                }}
                className={styles.cancel}
                value='cancel'
              >
                Cancel
              </button>
            </div>
          </Modal>
          <Modal centered show={this.state.showActivePrimary}>
            <div className={styles.title}>Deactivate task?</div>
            <div className={styles.cont}>
              Are you sure you want to deactivate this task?
            </div>
            <div className={styles.footer}>
              <button
                onClick={() => {
                  this.deactivateTask();
                }}
                className={styles.yes}
                value='yes'
              >
                Yes
              </button>
              <button
                onClick={() => {
                  this.showActivePrimaryModal();
                }}
                className={styles.cancel}
                value='cancel'
              >
                Cancel
              </button>
            </div>
          </Modal>
          <Modal centered show={this.state.show}>
            <div className={styles.title}>Delete task</div>
            <div className={styles.cont}>Task was succesfully deleted!</div>
            <img className={styles.image} src='../success.png'></img>
          </Modal>
          <Modal centered show={this.state.showActive}>
            <div className={styles.title}>Deactivate task</div>
            <div className={styles.cont}>Task was succesfully deactivated!</div>
            <img className={styles.image} src='../success.png'></img>
          </Modal>
        </>
      );
    }
  }
}

export default TaskTabProfile;
