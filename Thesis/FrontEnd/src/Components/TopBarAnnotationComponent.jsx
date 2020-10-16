import React, { Component } from "react";
import styles from "../CSS/TopBarAnnotation.module.css";
import { NavLink } from "react-router-dom";

class TopBarAnnotation extends Component {
  state = {};
  render() {
    return (
      <>
        <div className={styles.TopBar}>
          <div className={styles.LogoAndTitle}>
            <NavLink className={styles.Logo} to='/annotations/home'>
              <div>
                <img src='../../sword_1.png' className={styles.sword} />
              </div>
            </NavLink>
            <h1 className={styles.LogoName}>VerbAttack</h1>
          </div>
          <nav>
            <ul className={styles.Menu}>
              <li>
                <NavLink
                  to='/annotations/home'
                  activeClassName={styles.active}
                  id='1'
                >
                  Annotate a game
                </NavLink>
              </li>

              <li>
                <span className={styles.User}>
                  <img src='../../user.png' alt='user' />
                  <div>Username</div>
                </span>
                <div className={styles.dropdown}>
                  <NavLink className={styles.profile} to='/annotations/profile'>
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
        </div>{" "}
      </>
    );
  }
}

export default TopBarAnnotation;
