import React, { Component } from "react";
import TopBarTasksComponent from "../Components/TopBarTasksComponent";
import styles from "../CSS/TaskHome.module.css";
import Modal from "react-bootstrap/Modal";
import Cookies from "universal-cookie";

class TaskHome extends Component {
  constructor(props) {
    super(props);
    var cookies = new Cookies();
    this.state = {
      show: false,
      cookie: cookies.get("userID"),
      form: {
        taskName: "",
        taskDescription: "",
        attackersDescription: "",
        defendersDescription: "",
        category: "",
        attackerHints: "",
        defenderHints: "",
        maxMessages: 5,
        taskCreator: "",
      },
    };
  }

  showModal(response) {
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
              this.props.history.push({
                pathname: "/tasks/" + response.taskID,
                state: {
                  taskID: response.taskID,
                  taskName: this.state.form.taskName,
                  taskDescription: this.state.form.taskDescription,
                  attackersDescription: this.state.form.attackersDescription,
                  defendersDescription: this.state.form.defendersDescription,
                  category: this.state.form.category,
                  attackerHints: this.state.form.attackerHints,
                  defenderHints: this.state.form.defenderHints,
                  maxMessages: this.state.form.maxMessages,
                  taskCreator: this.state.form.taskCreator,
                  timestamp: this.timestampTime(response.timestamp),
                },
              });
            }
          );
        }, 3000);
      }
    );
  }

  myChangeHandler = (event) => {
    this.setState(
      {
        form: {
          ...this.state.form,
          [event.target.name]: event.target.value,
          taskCreator: this.state.cookie,
        },
      },
      console.log(this.state.form)
    );
  };

  timestampTime(timestamp) {
    var dateObj = new Date(timestamp);
    var utcString = dateObj.toLocaleString();
    return utcString;
  }

  handleSubmit = (event) => {
    fetch("http://localhost:7777/tasks", {
      method: "POST",
      // We convert the React state to JSON and send it as the POST body
      body: JSON.stringify(this.state.form),
    })
      .then((res) => res.json())
      .then((response) => {
        var response = JSON.parse(response);

        this.showModal(response);
        /*
        this.props.history.push({
          pathname: "/tasks/" + response.taskID,
          state: {
            taskID: response.taskID,
            taskName: this.state.form.taskName,
            taskDescription: this.state.form.taskDescription,
            attackersDescription: this.state.form.attackersDescription,
            defendersDescription: this.state.form.defendersDescription,
            category: this.state.form.category,
            attackerHints: this.state.form.attackerHints,
            defenderHints: this.state.form.defenderHints,
            maxMessages: this.state.form.maxMessages,
            taskCreator: this.state.form.taskCreator,
            timestamp: this.timestampTime(response.timestamp),
            //history: this.props.history,
          },
        });*/
      })
      .catch((error) => console.error("Error:", error));
  };

  render() {
    return (
      <>
        <TopBarTasksComponent></TopBarTasksComponent>
        <h1 className={styles.Create}>Create a Task</h1>
        <div className={styles.MainGrid}>
          <form id='myForm' className={styles.myForm}>
            <div className={styles.wrapper}>
              <div className={styles.Username}>Task name</div>
              <input
                type='text'
                placeholder='Name the task...'
                className={styles.usernameInput}
                onChange={this.myChangeHandler}
                name='taskName'
                id='inputs'
              />
              <div className={styles.Password}>Task Description/Scenario</div>
              <input
                type='text'
                placeholder='Describe generally the task...'
                className={styles.passwordInput}
                onChange={this.myChangeHandler}
                name='taskDescription'
                id='inputs'
              />
              <div className={styles.Username}>
                Attacker's Task Description/Scenario
              </div>
              <textarea
                className={styles.ADescription}
                onChange={this.myChangeHandler}
                placeholder="Describe attacker's task..."
                name='attackersDescription'
                id='inputs'
              ></textarea>
              <div className={styles.Password}>
                Defender's Task Description/Scenario
              </div>
              <textarea
                className={styles.DDescription}
                onChange={this.myChangeHandler}
                placeholder="Describe defender's task..."
                name='defendersDescription'
                id='inputs'
              ></textarea>
            </div>
            <div className={styles.wrapper}>
              <div className={styles.inline}>
                <div className={styles.Username}>Category</div>
                <div className={styles.maxMessages}>Max messages</div>
              </div>
              <div className={styles.inline}>
                <select
                  className={styles.categoryInput}
                  onChange={this.myChangeHandler}
                  name='category'
                  id='inputs'
                >
                  <option>Any</option>
                  <option>Racism</option>
                  <option>Off.Language</option>
                  <option>Phising</option>
                </select>

                <input
                  type='number'
                  min='5'
                  step='1'
                  max='20'
                  placeholder='5'
                  className={styles.spinBox}
                  onChange={this.myChangeHandler}
                  name='maxMessages'
                  id='inputs'
                />
              </div>
              <div className={styles.Password}>Number of players</div>
              <input
                type='text'
                value='2-players game'
                readonly
                className={styles.numberInput}
                onChange={this.myChangeHandler}
                name='password'
                id='inputs'
              />
              <div className={styles.Username}>Attacker's Hints/Guidelines</div>
              <textarea
                className={styles.ADescription}
                onChange={this.myChangeHandler}
                placeholder="Describe attacker's task..."
                name='attackerHints'
                id='inputs'
              ></textarea>
              <div className={styles.Password}>Defender's Hints/Guidelines</div>
              <textarea
                className={styles.DDescription}
                onChange={this.myChangeHandler}
                placeholder="Describe defender's task..."
                name='defenderHints'
                id='inputs'
              ></textarea>
            </div>
          </form>
          <button
            onClick={() => {
              this.handleSubmit();
            }}
            type='button'
            value='Create'
            className={styles.createButton}
          >
            Create
          </button>
        </div>

        <Modal centered show={this.state.show}>
          <div className={styles.title}>New task</div>
          <div className={styles.cont}>Task was succesfully created!</div>
          <img className={styles.image} src='../success.png'></img>
        </Modal>
      </>
    );
  }
}

export default TaskHome;
