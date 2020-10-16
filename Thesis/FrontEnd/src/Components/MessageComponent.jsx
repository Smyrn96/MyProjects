import React, { Component } from "react";
import styles from "../CSS/MessageComponent.module.css";
import Cookies from "universal-cookie";
import Button from "react-bootstrap/Button";
import Modal from "react-bootstrap/Modal";
import StarRatingComponent from "react-star-rating-component";
import e from "cors";

class MessageComponent extends Component {
  constructor(props) {
    super(props);
    var cookies = new Cookies();
    this.state = {
      ratingForm: {
        rating_id: "",
        annotation_id: "",
        stars: 0,
        messageID: "",
        timestamp: "",
      },
      rating: 0,
      showP: false,
      cookie: cookies.get("userID"),
      show: false,
      showEdit: false,
      categories: [],
      sumbittedCategories: [],
      tagsPost: [],
      tags: [],
      counter: 0,
      formCounter: 0,
      form: {
        gameID: "",
        userID: "",
        context: "",
        category: "",
        messageID: "",
      },
    };

    this.state.tags[this.state.counter] = 1;
    this.showModal = this.showModal.bind(this);
    this.showModalEdit = this.showModalEdit.bind(this);
    this.onClose = this.onClose.bind(this);
    this.myChangeHandler = this.myChangeHandler.bind(this);
  }

  componentDidMount() {
    Promise.all([
      fetch(
        "http://localhost:7777/games/" +
          this.props.gameID +
          "/messages/" +
          this.props.messageID +
          "/tags"
      ).then((value) => value.json()),
    ])
      .then((value) => {
        this.setState(
          {
            tagsPost: value[0],
            isLoaded: true,
          },
          () => {
            console.log(value);
          }
        );

        console.log(value);
        //json response
      })
      .catch((err) => {
        console.log(err);
      });
  }

  showModal = (e) => {
    this.setState({
      show: !this.state.show,
    });
  };

  showModalEdit = (e) => {
    this.setState({
      showEdit: !this.state.showEdit,
    });
  };

  onClose = (e) => {
    this.setState(
      {
        formCounter: this.state.formCounter + 1,
        show: false,
        counter: 0,
        tags: [],
      },
      () => {
        this.state.tags[this.state.counter] = 1;
      }
    );
  };

  onCloseEdit = (e) => {
    this.setState({
      showEdit: false,
    });
  };

  myChangeHandler = (event) => {
    this.setState({
      categories: [
        ...this.state.categories,
        { index: event.target.name, category: event.target.value, tagID: "" },
      ],
    });
  };

  myChangeHandlerEdit = (event) => {
    this.state.categories[event.target.name].category = event.target.value;

    this.setState({
      categories: this.state.categories,
    });
  };

  addTag = (event) => {
    if (this.state.counter < 2) {
      this.setState({
        formCounter: this.state.formCounter + 1,
        counter: this.state.counter + 1,
        tags: [...this.state.tags, 1],
      });
    }
  };

  removeTag = (event) => {
    if (this.state.counter > 0) {
      var array = [...this.state.tags];
      array.splice(this.state.counter, 1);
      this.setState({
        tags: array,
        counter: this.state.counter - 1,
      });
    }
  };

  async postTags(form, key) {
    let response = await fetch(
      "http://localhost:7777/games/" +
        this.props.gameID +
        "/messages/" +
        this.props.messageID +
        "/tags",
      {
        method: "POST",
        // We convert the React state to JSON and send it as the POST body
        body: JSON.stringify(form),
      }
    );
    let json = await response.json();
    if (json != 0) {
      var resp = JSON.parse(json);
      this.state.categories[key].tagID = resp.tagID;
      this.setState({ categories: this.state.categories });
    }
  }

  allTags() {
    this.state.categories = this.state.categories.filter(
      (thing, index, self) =>
        index === self.findIndex((t) => t.category === thing.category)
    );

    console.log(this.state.categories);

    for (var i = 0; i < this.state.categories.length; i++) {
      console.log(this.state.categories[i]);
      var tag_id;

      var form = {
        gameID: this.props.gameID,
        tagID: this.state.categories[i].tagID,
        userID: this.state.cookie,
        context: "",
        category: this.state.categories[i].category,
        messageID: this.props.messageID,
      };

      var key = i;
      console.log(key);

      this.postTags(form, key);
    }
    /*
          .then((res) => res.json())
          .then((response) => {
            var response = JSON.parse(response);

            this.state.categories[key].tagID = response.tagID;
            this.setState({ categories: this.state.categories });
          })
          .catch((error) => console.error("Error:", error));*/

    this.setState({
      sumbittedCategories: this.state.categories,
    });
  }

  handleSubmit = (event) => {
    console.log(this.state.categories);

    this.allTags();
    this.onClose();

    event.preventDefault();
  };

  async postTagsEdit(form, key) {
    console.log(form.tagID);
    let response = await fetch(
      "http://localhost:7777/games/" +
        this.props.gameID +
        "/messages/" +
        this.props.messageID +
        "/tags/" +
        form.tagID,
      {
        method: "PUT",
        // We convert the React state to JSON and send it as the POST body
        body: JSON.stringify(form),
      }
    );
    let json = await response.json();
  }

  allTagsEdit() {
    this.state.categories = this.state.categories.filter(
      (thing, index, self) =>
        index === self.findIndex((t) => t.category === thing.category)
    );

    console.log(this.state.categories);

    for (var i = 0; i < this.state.categories.length; i++) {
      console.log(this.state.categories[i]);
      var tag_id;

      var form = {
        gameID: this.props.gameID,
        tagID: this.state.categories[i].tagID,
        userID: this.state.cookie,
        context: "",
        category: this.state.categories[i].category,
        messageID: this.props.messageID,
      };

      var key = i;
      console.log(key);

      this.postTagsEdit(form, key);
    }
    this.setState({
      sumbittedCategories: this.state.categories,
    });
  }

  handleSumbitEdit = (event) => {
    console.log(this.state.categories);

    this.allTagsEdit();
    this.onCloseEdit();

    event.preventDefault();
  };

  async deleteTagsFetch(form) {
    let response = await fetch(
      "http://localhost:7777/games/" +
        this.props.gameID +
        "/messages/" +
        this.props.messageID +
        "/tags/" +
        form.tagID,
      {
        method: "DELETE",
        // We convert the React state to JSON and send it as the POST body
        body: JSON.stringify(form),
      }
    );
    let json = await response.json();
  }

  deleteTagBack(index) {
    console.log(index);
    var form = {
      gameID: this.props.gameID,
      tagID: this.state.categories[index].tagID,
      userID: this.state.cookie,
      context: "",
      category: this.state.categories[index].category,
      messageID: this.props.messageID,
    };

    this.deleteTagsFetch(form);
  }

  deleteTag(index) {
    console.log(index);

    this.deleteTagBack(index);

    this.setState({
      categories: this.state.categories.filter(function (category) {
        return category.index !== index;
      }),
      formCounter: this.state.formCounter - 1,
    });

    this.setState({
      sumbittedCategories: this.state.sumbittedCategories.filter(function (
        category
      ) {
        return category.index !== index;
      }),
    });
    this.onCloseEdit();
  }

  visiblePencil() {
    if (Object.values(this.state.sumbittedCategories).length !== 0) {
      if (this.props.userID === this.state.cookie) {
        return (
          <img
            onClick={(e) => {
              this.showModalEdit();
            }}
            className={styles.pencil}
            src='../pencil.png'
          ></img>
        );
      } else {
        return (
          <img
            onClick={(e) => {
              this.showModalEdit();
            }}
            className={styles.pencil2}
            src='../pencil.png'
          ></img>
        );
      }
    }
  }

  selectedValue(cat) {
    if (cat.category === "Phising") {
      return (
        <>
          <option value='None'>None</option>
          <option selected value='Phising'>
            Phising
          </option>
          <option value='Off.Language'>Off.Language</option>
          <option value='Racism'>Racism</option>
        </>
      );
    } else if (cat.category === "Off.Language") {
      return (
        <>
          <option value='None'>None</option>
          <option value='Phising'>Phising</option>
          <option selected value='Off.Language'>
            Off.Language
          </option>
          <option value='Racism'>Racism</option>
        </>
      );
    } else if (cat.category === "Racism") {
      return (
        <>
          <option value='None'>None</option>
          <option value='Phising'>Phising</option>
          <option value='Off.Language'>Off.Language</option>
          <option selected value='Racism'>
            Racism
          </option>
        </>
      );
    }
  }

  onStarClick(nextValue, prevValue, name) {
    console.log(nextValue);
    this.setState({
      rating: nextValue,
      ratingForm: {
        stars: nextValue,
        messageID: this.props.messageID,
      },
    });
  }

  inputHandler = (e) => {
    this.setState(
      {
        ratingForm: {
          stars: e.target.value,
          messageID: e.target.name,
        },
      },
      () => {
        console.log(this.state.formRating);
      }
    );
  };

  sendRating() {
    setTimeout(() => {
      this.setState({
        showP: false,
      });
    }, 3000);

    console.log(this.state.ratingForm);
    fetch(
      "http://localhost:7777/annotations/" +
        this.props.userID +
        "/" +
        this.props.gameID +
        "/" +
        this.props.annotationID +
        "/ratings",
      {
        method: "POST",
        // We convert the React state to JSON and send it as the POST body
        body: JSON.stringify(this.state.ratingForm),
      }
    )
      .then((res) => res.json())
      .then((response) => {
        console.log(response);
      })
      .catch((error) => console.error("Error:", error));
    console.log(this.state.ratingForm);
  }

  render() {
    const { rating } = this.state;
    if (this.props.page != "Spectate" && this.props.page != "Annotate") {
      if (this.props.userID === this.state.cookie) {
        return (
          <>
            <div className={styles.message}>
              <div className={styles.id}>{this.props.username}</div>
              <div className={styles.contentNtag}>
                <div className={styles.content}>{this.props.context}</div>
                <div className={styles.imageD}>
                  <img
                    onClick={(e) => {
                      this.showModal();
                    }}
                    className={styles.image1}
                    src='../../profanity.png'
                  ></img>
                  {this.visiblePencil()}
                </div>
              </div>
              <div id={this.state.formCounter} className={styles.singleTag1}>
                {this.state.sumbittedCategories.map((i) => (
                  <span className={styles.t}>#{i.category},</span>
                ))}
              </div>
            </div>
            <Modal centered size='lg' show={this.state.show}>
              <div className={styles.title}>Tag an offense</div>
              {this.state.tags.map((tag) => (
                <div className={styles.wrapper}>
                  <div className={styles.line}>
                    <div className={styles.context}>{this.props.context}</div>
                    <div className={styles.selection}>Offensive Tag:</div>
                    <form onSubmit={this.handleSubmit}>
                      <select
                        onChange={this.myChangeHandler}
                        className={styles.select}
                        name={this.state.formCounter}
                      >
                        <option value='None'>None</option>
                        <option value='Phising'>Phising</option>
                        <option value='Off.Language'>Off.Language</option>
                        <option value='Racism'>Racism</option>
                      </select>
                    </form>
                  </div>
                  <div className={styles.editTags}>
                    <div
                      id='plus'
                      onClick={(e) => {
                        this.addTag(e);
                      }}
                      className={styles.plus}
                    >
                      <img src='../add.png'></img>
                      <div>Add a tag</div>
                    </div>
                    <div
                      onClick={(e) => {
                        this.removeTag(e);
                      }}
                      className={styles.minus}
                      id='minus'
                    >
                      <img src='../minus.png'></img>
                      <div>Remove a tag</div>
                    </div>
                  </div>
                </div>
              ))}
              <div className={styles.footer}>
                <button
                  onClick={this.handleSubmit}
                  className={styles.sumbit}
                  type='submit'
                  value='Submit'
                >
                  Submit
                </button>
                <button
                  className={styles.cancel}
                  onClick={(e) => {
                    this.onClose(e);
                  }}
                >
                  Cancel
                </button>
              </div>
            </Modal>

            <Modal centered size='lg' show={this.state.showEdit}>
              <div className={styles.title}>Edit offenses</div>
              {this.state.sumbittedCategories.map((cat) => (
                <div className={styles.wrapper}>
                  <div className={styles.line}>
                    <div className={styles.context}>{this.props.context}</div>
                    <div className={styles.selection}>Offensive Tag:</div>
                    <form onSubmit={this.handleSubmitEdit}>
                      <select
                        onChange={this.myChangeHandlerEdit}
                        className={styles.select}
                        name={this.state.counter}
                      >
                        {this.selectedValue(cat)}
                      </select>
                    </form>
                    <div
                      id={cat.index}
                      onClick={() => {
                        this.deleteTag(cat.index);
                      }}
                      className={styles.delete}
                    >
                      <img src='../dustbin.png'></img>
                    </div>
                  </div>
                </div>
              ))}
              <div className={styles.footer}>
                <button
                  onClick={this.handleSumbitEdit}
                  className={styles.sumbit}
                  type='submit'
                  value='Submit'
                >
                  Submit
                </button>
                <button
                  className={styles.cancel}
                  onClick={(e) => {
                    this.onCloseEdit(e);
                  }}
                >
                  Cancel
                </button>
              </div>
            </Modal>
          </>
        );
      } else {
        return (
          <>
            <div className={styles.message2}>
              <div className={styles.id2}>{this.props.username}</div>
              <div className={styles.contentNtag2}>
                <div className={styles.imageD2}>
                  {this.visiblePencil()}
                  <img
                    onClick={(e) => {
                      this.showModal();
                    }}
                    className={styles.image2}
                    src='../../profanity.png'
                  ></img>
                </div>
                <div className={styles.content2}>{this.props.context}</div>
              </div>
              <div id={this.state.formCounter} className={styles.singleTag2}>
                {this.state.sumbittedCategories.map((i) => (
                  <span className={styles.t}>#{i.category},</span>
                ))}
              </div>
            </div>
            <Modal centered size='lg' show={this.state.show}>
              <div className={styles.title}>Tag an offense</div>
              {this.state.tags.map((tag) => (
                <div className={styles.wrapper}>
                  <div className={styles.line}>
                    <div className={styles.context}>{this.props.context}</div>
                    <div className={styles.selection}>Offensive Tag:</div>
                    <form onSubmit={this.handleSubmit}>
                      <select
                        onChange={this.myChangeHandler}
                        className={styles.select}
                        name={this.state.formCounter}
                      >
                        <option value='None'>None</option>
                        <option value='Phising'>Phising</option>
                        <option value='Off.Language'>Off.Language</option>
                        <option value='Racism'>Racism</option>
                      </select>
                    </form>
                  </div>
                  <div className={styles.editTags}>
                    <div
                      id='plus'
                      onClick={(e) => {
                        this.addTag(e);
                      }}
                      className={styles.plus}
                    >
                      <img src='../add.png'></img>
                      <div>Add a tag</div>
                    </div>
                    <div
                      onClick={(e) => {
                        this.removeTag(e);
                      }}
                      className={styles.minus}
                      id='minus'
                    >
                      <img src='../minus.png'></img>
                      <div>Remove a tag</div>
                    </div>
                  </div>
                </div>
              ))}
              <div className={styles.footer}>
                <button
                  className={styles.sumbit}
                  onClick={this.handleSubmit}
                  className={styles.sumbit}
                  type='submit'
                  value='Submit'
                >
                  Submit
                </button>
                <button
                  className={styles.cancel}
                  onClick={(e) => {
                    this.onClose(e);
                  }}
                >
                  Cancel
                </button>
              </div>
            </Modal>

            <Modal centered size='lg' show={this.state.showEdit}>
              <div className={styles.title}>Edit offenses</div>
              {this.state.sumbittedCategories.map((cat) => (
                <div className={styles.wrapper}>
                  <div className={styles.line}>
                    <div className={styles.context}>{this.props.context}</div>
                    <div className={styles.selection}>Offensive Tag:</div>
                    <form onSubmit={this.handleSubmitEdit}>
                      <select
                        onChange={this.myChangeHandlerEdit}
                        className={styles.select}
                        name={this.state.counter}
                      >
                        {this.selectedValue(cat)}
                      </select>
                    </form>
                    <div
                      id={cat.index}
                      onClick={() => {
                        this.deleteTag(cat.index);
                      }}
                      className={styles.delete}
                    >
                      <img src='../dustbin.png'></img>
                    </div>
                  </div>
                </div>
              ))}
              <div className={styles.footer}>
                <button
                  onClick={this.handleSumbitEdit}
                  className={styles.sumbit}
                  type='submit'
                  value='Submit'
                >
                  Submit
                </button>
                <button
                  className={styles.cancel}
                  onClick={(e) => {
                    this.onCloseEdit(e);
                  }}
                >
                  Cancel
                </button>
              </div>
            </Modal>
          </>
        );
      }
    } else if (this.props.page == "Annotate") {
      if (this.props.attackerUsername == this.props.username) {
        return (
          <>
            <div className={styles.message}>
              <div className={styles.id}>{this.props.username}</div>
              <div className={styles.contentNtag}>
                <div className={styles.content}>{this.props.context}</div>
                <div className={styles.imageD}></div>
              </div>
              <div id={this.state.formCounter} className={styles.singleTag1}>
                {this.state.tagsPost.map((i) => {
                  if (this.state.tagsPost.length != 0) {
                    return <span className={styles.t}>#{i.category},</span>;
                  }
                })}
              </div>

              <div className={styles.rate}>
                <StarRatingComponent
                  name={this.props.messageID}
                  className={styles.stars}
                  starCount={5}
                  value={rating}
                  onStarClick={this.onStarClick.bind(this)}
                  editing={"true"}
                  starColor={"#011f4b"}
                  emptyStarColor={"#ccc"}
                />
              </div>

              <button
                onClick={() => {
                  this.setState({
                    showP: true,
                  });
                  this.sendRating();
                }}
                className={styles.rateB}
                value='Rate'
              >
                Rate
              </button>
              <div className={styles.box1}>
                <span> +{this.state.ratingForm.stars}</span>
              </div>
            </div>
            <Modal centered show={this.state.showP}>
              <div className={styles.title}>Message rated!</div>
              <div className={styles.image}>
                <img src='../success.png'></img>
              </div>

              <div className={styles.description}>
                User {this.props.username} earned {this.state.ratingForm.stars}{" "}
                points
              </div>
            </Modal>
          </>
        );
      } else {
        return (
          <>
            <div className={styles.message2}>
              <div className={styles.id2}>{this.props.username}</div>
              <div className={styles.contentNtag2}>
                <div className={styles.imageD2}></div>
                <div className={styles.content2}>{this.props.context}</div>
              </div>

              <div id={this.state.formCounter} className={styles.singleTag2}>
                {this.state.tagsPost.map((i) => {
                  if (this.state.tagsPost.length != 0) {
                    return <span className={styles.t}>#{i.category},</span>;
                  }
                })}
              </div>
              <div className={styles.rate2}>
                <StarRatingComponent
                  name={this.props.messageID}
                  className={styles.stars}
                  starCount={5}
                  value={rating}
                  onStarClick={this.onStarClick.bind(this)}
                  editing={"true"}
                  starColor={"#011f4b"}
                  emptyStarColor={"#ccc"}
                />
              </div>

              <button
                onClick={() => {
                  this.setState({
                    showP: true,
                  });
                  this.sendRating();
                }}
                className={styles.rateB}
                value='Rate'
              >
                Rate
              </button>
              <div className={styles.box2}>
                <span> +{this.state.ratingForm.stars}</span>
              </div>
            </div>
            <Modal centered show={this.state.showP}>
              <div className={styles.title}>Message rated!</div>
              <div className={styles.image}>
                <img src='../success.png'></img>
              </div>

              <div className={styles.description}>
                User {this.props.username} earned {this.state.ratingForm.stars}{" "}
                points
              </div>
            </Modal>
          </>
        );
      }
    } else {
      if (this.props.attackerUsername == this.props.username) {
        return (
          <>
            <div className={styles.message}>
              <div className={styles.id}>{this.props.username}</div>
              <div className={styles.contentNtagSpec}>
                <div className={styles.content}>{this.props.context}</div>
              </div>
              <div id={this.state.formCounter} className={styles.singleTag1}>
                {this.state.sumbittedCategories.map((i) => (
                  <span className={styles.t}>#{i.category},</span>
                ))}
              </div>
            </div>
            <Modal centered size='lg' show={this.state.show}>
              <div className={styles.title}>Tag an offense</div>
              {this.state.tags.map((tag) => (
                <div className={styles.wrapper}>
                  <div className={styles.line}>
                    <div className={styles.context}>{this.props.context}</div>
                    <div className={styles.selection}>Offensive Tag:</div>
                    <form onSubmit={this.handleSubmit}>
                      <select
                        onChange={this.myChangeHandler}
                        className={styles.select}
                        name={this.state.formCounter}
                      >
                        <option value='None'>None</option>
                        <option value='Phising'>Phising</option>
                        <option value='Off.Language'>Off.Language</option>
                        <option value='Racism'>Racism</option>
                      </select>
                    </form>
                  </div>
                  <div className={styles.editTags}>
                    <div
                      id='plus'
                      onClick={(e) => {
                        this.addTag(e);
                      }}
                      className={styles.plus}
                    >
                      <img src='../add.png'></img>
                      <div>Add a tag</div>
                    </div>
                    <div
                      onClick={(e) => {
                        this.removeTag(e);
                      }}
                      className={styles.minus}
                      id='minus'
                    >
                      <img src='../minus.png'></img>
                      <div>Remove a tag</div>
                    </div>
                  </div>
                </div>
              ))}
              <div className={styles.footer}>
                <button
                  onClick={this.handleSubmit}
                  className={styles.sumbit}
                  type='submit'
                  value='Submit'
                >
                  Submit
                </button>
                <button
                  className={styles.cancel}
                  onClick={(e) => {
                    this.onClose(e);
                  }}
                >
                  Cancel
                </button>
              </div>
            </Modal>

            <Modal centered size='lg' show={this.state.showEdit}>
              <div className={styles.title}>Edit offenses</div>
              {this.state.sumbittedCategories.map((cat) => (
                <div className={styles.wrapper}>
                  <div className={styles.line}>
                    <div className={styles.context}>{this.props.context}</div>
                    <div className={styles.selection}>Offensive Tag:</div>
                    <form onSubmit={this.handleSubmitEdit}>
                      <select
                        onChange={this.myChangeHandlerEdit}
                        className={styles.select}
                        name={this.state.counter}
                      >
                        {this.selectedValue(cat)}
                      </select>
                    </form>
                    <div
                      id={cat.index}
                      onClick={() => {
                        this.deleteTag(cat.index);
                      }}
                      className={styles.delete}
                    >
                      <img src='../dustbin.png'></img>
                    </div>
                  </div>
                </div>
              ))}
              <div className={styles.footer}>
                <button
                  onClick={this.handleSumbitEdit}
                  className={styles.sumbit}
                  type='submit'
                  value='Submit'
                >
                  Submit
                </button>
                <button
                  className={styles.cancel}
                  onClick={(e) => {
                    this.onCloseEdit(e);
                  }}
                >
                  Cancel
                </button>
              </div>
            </Modal>
          </>
        );
      } else {
        return (
          <>
            <div className={styles.message2}>
              <div className={styles.id2}>{this.props.username}</div>
              <div className={styles.contentNtagSpec2}>
                <div className={styles.content2}>{this.props.context}</div>
              </div>
              <div id={this.state.formCounter} className={styles.singleTag2}>
                {this.state.sumbittedCategories.map((i) => (
                  <span className={styles.t}>#{i.category},</span>
                ))}
              </div>
            </div>
            <Modal centered size='lg' show={this.state.show}>
              <div className={styles.title}>Tag an offense</div>
              {this.state.tags.map((tag) => (
                <div className={styles.wrapper}>
                  <div className={styles.line}>
                    <div className={styles.context}>{this.props.context}</div>
                    <div className={styles.selection}>Offensive Tag:</div>
                    <form onSubmit={this.handleSubmit}>
                      <select
                        onChange={this.myChangeHandler}
                        className={styles.select}
                        name={this.state.formCounter}
                      >
                        <option value='None'>None</option>
                        <option value='Phising'>Phising</option>
                        <option value='Off.Language'>Off.Language</option>
                        <option value='Racism'>Racism</option>
                      </select>
                    </form>
                  </div>
                  <div className={styles.editTags}>
                    <div
                      id='plus'
                      onClick={(e) => {
                        this.addTag(e);
                      }}
                      className={styles.plus}
                    >
                      <img src='../add.png'></img>
                      <div>Add a tag</div>
                    </div>
                    <div
                      onClick={(e) => {
                        this.removeTag(e);
                      }}
                      className={styles.minus}
                      id='minus'
                    >
                      <img src='../minus.png'></img>
                      <div>Remove a tag</div>
                    </div>
                  </div>
                </div>
              ))}
              <div className={styles.footer}>
                <button
                  className={styles.sumbit}
                  onClick={this.handleSubmit}
                  className={styles.sumbit}
                  type='submit'
                  value='Submit'
                >
                  Submit
                </button>
                <button
                  className={styles.cancel}
                  onClick={(e) => {
                    this.onClose(e);
                  }}
                >
                  Cancel
                </button>
              </div>
            </Modal>

            <Modal centered size='lg' show={this.state.showEdit}>
              <div className={styles.title}>Edit offenses</div>
              {this.state.sumbittedCategories.map((cat) => (
                <div className={styles.wrapper}>
                  <div className={styles.line}>
                    <div className={styles.context}>{this.props.context}</div>
                    <div className={styles.selection}>Offensive Tag:</div>
                    <form onSubmit={this.handleSubmitEdit}>
                      <select
                        onChange={this.myChangeHandlerEdit}
                        className={styles.select}
                        name={this.state.counter}
                      >
                        {this.selectedValue(cat)}
                      </select>
                    </form>
                    <div
                      id={cat.index}
                      onClick={() => {
                        this.deleteTag(cat.index);
                      }}
                      className={styles.delete}
                    >
                      <img src='../dustbin.png'></img>
                    </div>
                  </div>
                </div>
              ))}
              <div className={styles.footer}>
                <button
                  onClick={this.handleSumbitEdit}
                  className={styles.sumbit}
                  type='submit'
                  value='Submit'
                >
                  Submit
                </button>
                <button
                  className={styles.cancel}
                  onClick={(e) => {
                    this.onCloseEdit(e);
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
}

export default MessageComponent;
