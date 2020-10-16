import React, { Component, PureComponent } from "react";
import styles from "../CSS/Login.module.css";
import { Redirect } from "react-router-dom";
import { useHistory } from "react-router-dom";
import Cookies from "universal-cookie";

class Login extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      username: "",
      form: {
        username: " ",
        password: " ",
      },
      isValidUser: "0",
      userID: "",
      role: "Player",
    };
  }

  myChangeHandlerRole = (event) => {
    this.setState({
      role: event.target.value,
    });

    console.log(this.state.role);
  };

  myChangeHandler = (event) => {
    this.setState({
      form: {
        ...this.state.form,
        [event.target.name]: event.target.value,
      },
    });

    console.log(this.state.form);
  };

  handleSubmit = (event) => {
    console.log(this.state.role);
    fetch("http://localhost:7777/login", {
      method: "POST",
      // We convert the React state to JSON and send it as the POST body
      body: JSON.stringify(this.state.form),
    })
      .then((res) => res.json())
      .then((response) => {
        var response = JSON.parse(response);

        this.setState({
          userID: response.userID,
          isValidUser: response.flag,
        });
        if (response.flag === 1) {
          const cookies = new Cookies();
          cookies.set("userID", response.userID, { path: "/" });
          console.log(cookies.get("userID"));
          if (this.state.role == "Player") {
            this.props.history.push({
              pathname: "/home",
              state: {
                userID: response.userID,
                username: response.username,
                points: response.points,
              },
            });
          } else if (this.state.role == "Task") {
            this.props.history.push({
              pathname: "/tasks/home",
              state: {
                userID: response.userID,
                username: response.username,
                points: response.points,
              },
            });
          } else if (this.state.role === "Annotator") {
            console.log("Annotator here");
            this.props.history.push({
              pathname: "/annotations/home",
              state: {
                userID: response.userID,
                username: response.username,
                points: response.points,
              },
            });
          }
        } else {
          document.getElementById("pop").style.visibility = "visible";
          document.getElementById("myForm").reset();
        }
      })
      .catch((error) => console.error("Error:", error));

    event.preventDefault();
  };

  routeChange = (event) => {
    this.props.history.push({
      pathname: "/signup",
    });
    event.preventDefault();
  };

  render() {
    return (
      <div className={styles.Main}>
        <div className={styles.TopBar}>
          <div className={styles.LogoANDName}>
            <div className={styles.Logo}>
              <img src='../../sword_1.png' className={styles.sword} />
            </div>
            <h1 className={styles.LogoName}>ChatAttack</h1>
          </div>
          <div className={styles.rightSide}>
            <div className={styles.languge}>
              <img
                src='../../global.png'
                alt='Logo'
                className={styles.LanguageImage}
              />
            </div>
            <div className={styles.SignUp}>
              <button
                id={styles.sign}
                class='btn btn-primary'
                onClick={this.routeChange}
              >
                SignUp
              </button>
            </div>
          </div>
        </div>
        <div className={styles.MainGrid}>
          <div className={styles.LoginTitle}>User Login</div>

          <div id='pop' className={styles.pop}>
            Username/Password is not valid. Try again
          </div>
          <form id='myForm'>
            <div className={styles.Username}>Username</div>
            <input
              type='username'
              className={styles.usernameInput}
              onChange={this.myChangeHandler}
              name='username'
              id='inputs'
            />
            <div className={styles.Password}>Password</div>
            <input
              type='password'
              className={styles.passwordInput}
              onChange={this.myChangeHandler}
              name='password'
              id='inputs'
            />
            <div className={styles.RoleTitle}>Role</div>
            <select onChange={this.myChangeHandlerRole} className={styles.role}>
              <option className={styles.Player} value='Player' name='Player'>
                Player
              </option>
              <option className={styles.TaskAdmin} value='Task' name='Task'>
                Task Administrator
              </option>
              <option
                className={styles.Annotator}
                value='Annotator'
                name='Annotator'
              >
                Annotator
              </option>
            </select>
            <div className={styles.Remember}>Remember me</div>
            <input type='checkbox' className={styles.RememberInput} />
            <div className={styles.Forgot}>
              <a href='/'>Forgot your password?</a>
            </div>

            <button
              className='btn btn-primary'
              id={styles.login}
              onClick={this.handleSubmit}
            >
              Login
            </button>
          </form>
          <div className={styles.NewUser}>
            New User?{" "}
            <a href='/' className={styles.Register}>
              Register{" "}
            </a>
            now!
          </div>
        </div>
      </div>
    );
  }
}

export default Login;
