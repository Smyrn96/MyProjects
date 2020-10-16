import React, { Component } from "react";
import TopBar from "../Components/TopBarComponent";
import styles from "../CSS/Home.module.css";
import GameTagComponent from "../Components/GameTabComponent";
import Cookies from "universal-cookie";

class Home extends Component {
  constructor(props) {
    super(props);
    var cookies = new Cookies();
    this.state = {
      style1: {
        borderBottom: "3px solid white",
        paddingBottom: "8px",
        fontWeight: "900",
      },
      style2: {},
      flag: "true",
      games: [],
      users: [],
      Role: "",
      Role1: "",
      Points: 0,
      form: {
        category: "",
        taskID: "",
        role: "",
        completionTime: 0,
        attackerUsername: "",
        defenderUsername: "",
      },
      cookie: cookies.get("userID"),
      user: {
        userID: "",
        username: "",
        score: "",
      },
      taskDetails: {
        description: "",
        attackerDescription: "",
        defenderDescription: "",
        attackerHints: "",
        defenderHints: "",
      },
    };

    this.selectorFunct = this.selectorFunct.bind(this);
    this.selectMainGrid = this.selectMainGrid.bind(this);
    this.chooseRole = this.chooseRole.bind(this);
    this.selectSpecificUser = this.selectSpecificUser.bind(this);
    this.chooseTaskDetails = this.chooseTaskDetails.bind(this);
    const urls = ["http://localhost:7777/games", "http://localhost:7777/tasks"];
  }

  myChangeHandler = (event) => {
    if (event.target.value === "Attacker") {
      this.setState({
        form: {
          ...this.state.form,
          [event.target.name]: event.target.value,
          attackerUsername: this.state.user.username,
          attackerPoints: this.state.user.score,
        },
      });
    } else if (event.target.value === "Defender") {
      this.setState({
        form: {
          ...this.state.form,
          [event.target.name]: event.target.value,
          defenderUsername: this.state.user.username,
          defenderPoints: this.state.user.score,
        },
      });
    } else {
      this.setState({
        form: {
          ...this.state.form,
          [event.target.name]: event.target.value,
        },
      });
    }

    console.log(this.state.form);
  };

  chooseTaskDetails(props) {
    for (var i = 0; i < this.state.tasks.length; i++) {
      console.log("EDW task: " + this.state.tasks[i].taskID);
      if (this.state.tasks[i].taskID === props) {
        console.log("EDW " + this.state.tasks[i]);
        this.setState({
          taskDetails: {
            ...this.state.taskDetails,
            description: this.state.tasks[i].taskDescription,
            attackerDescription: this.state.tasks[i].attackersDescription,
            defenderDescription: this.state.tasks[i].defendersDescription,
            attackerHints: this.state.tasks[i].attackerHints,
            defenderHints: this.state.tasks[i].defenderHints,
          },
        });
      }
    }
  }

  componentDidMount() {
    Promise.all([
      fetch("http://localhost:7777/games/tv").then((value) => value.json()),
      fetch("http://localhost:7777/tasks").then((value) => value.json()),
      fetch("http://localhost:7777/users").then((value) => value.json()),
    ])
      .then((value) => {
        this.setState({
          games: value[0],
          tasks: value[1],
          users: value[2],
          isLoaded: true,
        });
        this.selectSpecificUser();

        console.log(value);
        //json response
      })
      .catch((err) => {
        console.log(err);
      });
    this.timer = setInterval(() => this.getGames(), 1000);
  }

  componentWillUnmount() {
    clearInterval(this.timer);
  }
  async getGames() {
    fetch("http://localhost:7777/games/tv", { method: "GET" })
      .then((response) => response.json())
      .then((responseData) => {
        this.setState({
          games: responseData,
        });
        console.log(responseData);
      })
      .catch((error) => {
        console.error(error);
      });
  }

  handleSubmit = (event) => {
    fetch("http://localhost:7777/games", {
      method: "POST",
      // We convert the React state to JSON and send it as the POST body
      body: JSON.stringify(this.state.form),
    })
      .then((res) => res.json())
      .then((response) => {
        console.log(response);
        var response = JSON.parse(response);

        this.chooseTaskDetails(this.state.form.taskID);
        var role = this.chooseSecondRole(response, this.selectSpecificUser());
        console.log(role);
        console.log(response.attackerUsername);
        console.log(response.defenderUsername);
        this.props.history.push({
          pathname: "/games/" + response.gameID,
          state: {
            userID: this.state.cookie,
            gameID: response.gameID,
            role: role,
            attackerUsername: response.attackerUsername,
            defenderUsername: response.defenderUsername,
            attackerPoints: response.attackerPoints,
            defenderPoints: response.defenderPoints,
            taskID: response.taskID,
            category: response.category,
            description: this.state.taskDetails.description,
            attackerDescription: this.state.taskDetails.attackerDescription,
            defenderDescription: this.state.taskDetails.defenderDescription,
            attackerHints: this.state.taskDetails.attackerHints,
            defenderHints: this.state.taskDetails.defenderHints,
          },
        });
      })
      .catch((error) => console.error("Error:", error));

    event.preventDefault();
  };

  selectMainGrid(props) {
    console.log(this.state.flag);
    if (this.state.flag === "true") {
      return (
        <div className={styles.TitleGrid}>
          <div className={styles.Options}>
            <span style={{ backgroundColor: "red" }} className={styles.Player}>
              Player
            </span>
            <span className={styles.Rating}>Rating</span>
            <span className={styles.Role}>Role</span>
            <span className={styles.Category}>Category</span>
          </div>
        </div>
      );
    } else {
      return (
        <div className={styles.TitleGrid}>
          <div className={styles.Options}>
            <span className={styles.Player}>Player</span>
            <span className={styles.Rating}>Rating</span>
            <span className={styles.Role}>Role</span>
            <span className={styles.Category}>Category</span>
          </div>
        </div>
      );
    }
  }

  selectSpecificUser() {
    for (var i = 0; i < this.state.users.length; i++) {
      console.log("EDW " + this.state.users[i].userID + this.state.cookie);
      if (this.state.users[i].userID === this.state.cookie) {
        console.log("EDW " + this.state.users[i].userID);
        this.setState({
          user: {
            ...this.state.user,
            userID: this.state.users[i].userID,
            username: this.state.users[i].username,
            score: this.state.users[i].score,
          },
        });
        return this.state.user;
      }
    }
  }

  selectorFunct(props) {
    if (props === "Quick") {
      this.setState({
        style1: {
          borderBottom: "3px solid white",
          paddingBottom: "8px",
          fontWeight: "900",
        },
        style2: {},
        flag: "true",
      });
    } else {
      this.setState({
        style1: {},
        style2: {
          borderBottom: "3px solid white",
          paddingBottom: "8px",
          fontWeight: "900",
        },
        flag: "false",
      });
    }
  }

  click = (game) => {
    console.log(this.state.user.userID);

    fetch("http://localhost:7777/games/" + game.gameID, {
      method: "PUT",
      // We convert the React state to JSON and send it as the POST body
      body: JSON.stringify(this.state.user),
    })
      .then((res) => res.json())
      .then((response) => {
        console.log(response);
        var response = JSON.parse(response);

        this.chooseTaskDetails(response.taskID);

        console.log(response);
        console.log(response.attackerUsername);
        console.log(response.defenderUsername);
        this.props.history.push({
          pathname: "/games/" + game.gameID,
          state: {
            userID: this.state.cookie,
            gameID: game.gameID,
            role: this.chooseSecondRole(response, this.state.user),
            attackerUsername: response.attackerUsername,
            defenderUsername: response.defenderUsername,
            attackerPoints: game.attackerPoints,
            defenderPoints: game.defenderPoints,
            taskID: game.taskID,
            category: game.category,
            description: this.state.taskDetails.description,
            attackerDescription: this.state.taskDetails.attackerDescription,
            defenderDescription: this.state.taskDetails.defenderDescription,
            attackerHints: this.state.taskDetails.attackerHints,
            defenderHints: this.state.taskDetails.defenderHints,
          },
        });
      })
      .catch((error) => console.error("Error:", error));
  };

  chooseSecondRole(game, user) {
    console.log(game);
    console.log(user);
    if (game.attackerUsername === user.username) {
      console.log("HI I AM ATTACKER");
      return "Attacker";
    } else if (game.defenderUsername === user.username) {
      return "Defender";
    }
  }

  chooseRole(props) {
    console.log(props);
    if (
      (props.attackerUsername === "null" || props.attackerUsername === "") &&
      props.defenderUsername !== "null"
    ) {
      this.state.Role = "Defender";
      this.Points = props.defenderPoints;
      return props.defenderUsername;
    } else if (
      props.attackerUsername !== "null" &&
      (props.defenderUsername === "null" || props.defenderUsername === "")
    ) {
      console.log("MANOS1");
      this.state.Role = "Attacker";
      this.Points = props.attackerPoints;
      return props.attackerUsername;
    }
  }
  render() {
    console.log("value " + this.state.user.username);
    const { error, isLoaded, games, tasks } = this.state;

    let gamesHome = this.state.games.filter(function (game) {
      return (
        (game.attackerUsername === "" && game.defenderUsername !== "") ||
        (game.attackerUsername !== "" && game.defenderUsername === "")
      );
    });

    if (error) {
      return <div>Error: {error.message}</div>;
    } else if (!isLoaded) {
      return <div>Loading...</div>;
    } else {
      let grid;
      if (this.state.flag === "true") {
        grid = (
          <div className={styles.MainGrid}>
            <div className={styles.TitleGrid}>
              <div className={styles.Options}>
                <span className={styles.Player}>Player</span>
                <span className={styles.Rating}>Rating</span>
                <span className={styles.Role}>Role</span>
                <span className={styles.Category}>Category</span>
              </div>
              <ul className={styles.list}>
                {gamesHome.map((game) => (
                  <li
                    onClick={() => this.click(game)}
                    name='gameID'
                    value='MANOS'
                  >
                    <GameTagComponent
                      userID={this.chooseRole(game)}
                      rating={this.Points}
                      role={this.state.Role}
                      category={game.category}
                    />
                  </li>
                ))}
              </ul>
            </div>
          </div>
        );
      } else {
        grid = (
          <>
            <div className={styles.SecondaryGrid}>
              <div className={styles.smallTitle}>
                <div className={styles.New}>New game</div>
              </div>
              <form onSubmit={this.handleSubmit}>
                <div className={styles.categoryOption}>
                  <img src='../grid.png'></img>
                  <div>Choose a task category: </div>
                  <select
                    className={styles.select1}
                    onChange={this.myChangeHandler}
                    name='category'
                  >
                    <option value='Any'>Any</option>
                    <option value='Phising'>Phising</option>
                    <option value='Off.Language'>Off.Language</option>
                    <option value='Racism'>Racism</option>
                  </select>
                </div>
                <div className={styles.categoryOption}>
                  <img src='../list.png'></img>
                  <div>Choose an ongoing task: </div>
                  <select
                    className={styles.select1}
                    onChange={this.myChangeHandler}
                    name='taskID'
                  >
                    <option value='Any'>Any</option>
                    {tasks
                      .filter(function (task) {
                        return task.active == true;
                      })
                      .map((task) => (
                        <option value={task.taskID}>{task.taskName}</option>
                      ))}
                  </select>
                </div>
                <div className={styles.categoryOption}>
                  <img src='../swordNshield.png'></img>
                  <div>Choose your role: </div>
                  <select
                    className={styles.select1}
                    onChange={this.myChangeHandler}
                    name='role'
                  >
                    <option value='Any'>Any</option>
                    <option value='Attacker'>Attacker</option>
                    <option value='Defender'>Defender</option>
                  </select>
                </div>
                <div className={styles.button}>
                  <input type='submit' value='Create' id={styles.sign} />
                </div>
              </form>
            </div>
          </>
        );
      }
      return (
        <div className={styles.Main}>
          <TopBar user={this.state.user}></TopBar>
          <div className={styles.tabs}>
            <div
              className={styles.Quick}
              style={{ cursor: "pointer" }}
              onClick={() => this.selectorFunct("Quick")}
            >
              <h1 style={this.state.style1}>Quick pairing</h1>
            </div>
            <div
              className={styles.Create}
              style={{ cursor: "pointer" }}
              onClick={() => this.selectorFunct("Create")}
            >
              <h1 style={this.state.style2}>Create a game</h1>
            </div>
          </div>
          <div>{grid}</div>
        </div>
      );
    }
  }
}

export default Home;
