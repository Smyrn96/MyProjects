import React, { Component } from "react";
import styles from "../CSS/SignUp.module.css";
import Cookies from "universal-cookie";

class Register extends Component {
  state = {
    form: {
      username: " ",
      password: " ",
      score: 0,
      gamesPlayed: 0,
    },
    userID: "",
    isValidUser: 0,
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

  checkPassword() {
    var pass = document.getElementById("password").value;
    var con = document.getElementById("confirm").value;

    if (pass === con) {
      document.getElementById("warning").style.visibility = "hidden";
    } else {
      document.getElementById("warning").style.visibility = "visible";
    }
  }

  routeChange = (event) => {
    this.props.history.push({
      pathname: "/login",
    });
    event.preventDefault();
  };

  handleSubmit = (event) => {
    //alert("A form was submitted: " + this.state);
    fetch("http://localhost:7777/users", {
      method: "POST",
      // We convert the React state to JSON and send it as the POST body
      body: JSON.stringify(this.state.form),
    })
      .then((res) => res.json())
      .then((response) => {
        console.log(response);
        var response = JSON.parse(response);

        this.setState({
          userID: response.userID,
          isValidUser: response.flag,
        });

        if (response.flag === 1) {
          const cookies = new Cookies();
          cookies.set("userID", response.userID, { path: "/" });
          console.log(cookies.get("userID"));

          fetch("http://localhost:7777/" + response.userID + "/challenges", {
            method: "POST",
            body: JSON.stringify({
              description: "Play 5 games",
              progress: "0",
              maxProgress: "5",
              badgeReward: "",
              rewardPoints: "100",
              daily: "true",
              category: "games",
            }),
          }).then((res) => this.setState({ site2: res }));

          this.props.history.push({
            pathname: "/home",
            state: {
              userID: response.userID,
              username: response.username,
              points: response.points,
            },
          });
        } else {
          document.getElementById("pop").style.visibility = "visible";
          document.getElementById("myForm").reset();
        }
      })
      .catch((error) => console.error("Error:", error));

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
              Login
            </button>
          </div>
        </div>
        <div className={styles.MainGrid}>
          <div className={styles.LoginTitle}>Sign Up</div>
          <div id='pop' className={styles.pop}>
            Username or Password already exists
          </div>
          <form id='myForm' className={styles.register}>
            <div className={styles.username}>
              <div>Username</div>
              <input
                type='username'
                pattern='[A-Za-z0-9\-_\.]{6,20}'
                title='Username should be between 6-20 characters in length,no special characters or spaces and can be A-Z,a-z,0-9'
                onChange={this.myChangeHandler}
                name='username'
              ></input>
            </div>
            <div className={styles.password}>
              <div>Password</div>
              <input
                id='password'
                type='password'
                pattern='^(?=.*\d).{4,8}$'
                title='Password must be between 4 and 8 digits long and include at least one numeric digit.'
                onChange={this.myChangeHandler}
                name='password'
              ></input>
            </div>
            <div className={styles.confirm} onChange={this.checkPassword}>
              <div>Confirm Password</div>
              <input
                id='confirm'
                type='password'
                pattern='^(?=.*\d).{4,8}$'
                title='Password must be between 4 and 8 digits long and include at least one numeric digit.'
              ></input>
            </div>
            <span className={styles.warning} id='warning'>
              Passwords do not match
            </span>
            <div className={styles.email}>
              <div>Email</div>
              <input
                type='email'
                pattern='^\w+@[a-zA-Z_]+?\.[a-zA-Z]{2,3}$'
              ></input>
            </div>
            <div className={styles.a}>
              <div className={styles.avatar}>Avatar</div>
              <input type='file' id='img' name='img' accept='image/*'></input>
            </div>
            <div>
              <input
                className={styles.submit}
                type='submit'
                onClick={this.handleSubmit}
              ></input>
            </div>
          </form>
        </div>
      </div>
    );
  }
}

export default Register;
