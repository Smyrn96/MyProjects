package com.myProject.Model;

import java.sql.Timestamp;
import java.util.UUID;

public class Tag {
	private String tagID;
	private String gameID;
	private String userID;
	private String messageID;
	private String context;
	private String category;
	private Timestamp timestamp;
	
	public Tag() {
		
	}
	
	public Tag(String context) {
		this.context=context;
		this.tagID=("#" + UUID.randomUUID().toString()).substring(0,7);
	}
	
	public void setUserID(String userID) {
		this.userID=userID;
	}
	public String getUserID() {
		return this.userID;
	}
	
	public void setMessageID(String messageID) {
		this.messageID=messageID;
	}
	public String getMessageID() {
		return this.messageID;
	}
	
	public void setTagID(String tagID) {
		this.tagID=tagID;
	}
	
	public void setContext(String context) {
		this.context=context;
	}
	
	public String getTagID() {
		return this.tagID;
	}
	public void setGameID(String gameID) {
		this.gameID=gameID;
	}
	public String getGameID() {
		return this.gameID;
	}
	public String getTagContext() {
		return this.context;
	}
	public void setCategory(String category) {
		this.category=category;
	}
	
	public String getCategory() {
		return this.category;
	}
	
	public void setTimestamp(Timestamp timestamp) {
		this.timestamp=timestamp;
	}
	
	public Timestamp getTimestamp() {
		return this.timestamp;
	}
	
}
