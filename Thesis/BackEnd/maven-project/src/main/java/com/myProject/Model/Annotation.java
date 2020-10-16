package com.myProject.Model;

import java.sql.Timestamp;

public class Annotation {

	
	private String annotationID;
	private String gameID;
	private String userID;
	private Timestamp created;
	
	
	public Annotation() {}
	
	
	public void setAnnotationID(String annotationID) {
		this.annotationID=annotationID;
	}
	
	public void setGameID(String gameID) {
		this.gameID=gameID;
	}
	public void setUserID(String userID) {
		this.userID=userID;
	}
	public void setCreated(Timestamp created) {
		this.created=created;
	}
	
	public String getAnnotationID() {
		return this.annotationID;
	}
	
	public String getGameID() {
		return this.gameID;
	}
	public String getUserID() {
		return this.userID;
	}
	public Timestamp getCreated() {
		return this.created;
	}
}
