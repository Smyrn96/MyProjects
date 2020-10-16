import React, { Component } from "react";
import styles from "../CSS/TopBar.module.css";
import { NavLink } from "react-router-dom";

class TopBar extends Component {
  constructor(props) {
    super(props);
    this.state = { style: {} };
  }

  render() {
    return (
      <div className={styles.TopBar}>
        <div className={styles.LogoAndTitle}>
          <NavLink className={styles.Logo} to='/home'>
            <div>
              <img src='../../sword_1.png' className={styles.sword} />
            </div>
          </NavLink>
          <h1 className={styles.LogoName}>VerbAttack</h1>
        </div>
        <nav>
          <ul className={styles.Menu}>
            <li>
              <NavLink to='/home' activeClassName={styles.active} id='1'>
                Play
              </NavLink>
            </li>
            <li>
              <NavLink to='/tv' id='2' activeClassName={styles.active}>
                Spectate
              </NavLink>
            </li>
            <li>
              <NavLink
                to='/users/leaderboard'
                id='3'
                activeClassName={styles.active}
              >
                Leaderboard
              </NavLink>
            </li>
            <li>
              <NavLink
                to={{
                  pathname: "/challenges",
                  user: this.props.user,
                }}
                id='4'
                activeClassName={styles.active}
              >
                Challenges
              </NavLink>
            </li>
            <li>
              <span className={styles.User}>
                <img src='../../user.png' alt='user' />
                <div>Username</div>
              </span>
              <div className={styles.dropdown}>
                <NavLink className={styles.profile} to='/profile'>
                  <div>
                    <img src='../../userMenu1.png'></img>
                    <span className={styles.text}>Profile</span>
                  </div>
                </NavLink>
                <NavLink className={styles.settings} to='/profile'>
                  <div>
                    <img src='../../settingsMenu.png'></img>
                    <span className={styles.text}>Settings</span>
                  </div>
                </NavLink>
                <NavLink className={styles.privacy} to='/profile'>
                  <div>
                    <img src='../../privacyMenu.png'></img>
                    <span className={styles.text}>Privacy</span>
                  </div>
                </NavLink>
                <NavLink to='/login'>
                  <div className={styles.logout}>
                    <img src='../../logoutMenu.png'></img>
                    <span className={styles.text}>Logout</span>
                  </div>
                </NavLink>
              </div>
            </li>
          </ul>
        </nav>
      </div>
    );
  }
}
export default TopBar;
