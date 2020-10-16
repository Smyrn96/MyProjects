package com.myProject.Model;


import java.util.UUID;
import java.sql.Timestamp;
import java.util.ArrayList;

public class Message {
	private String gameID;
	private String messageID;
	private String userID;
	private String context;
	private Timestamp timestamp;
	private int flag;
	private ArrayList<Tag>tags;
	
	public Message() {
		this.messageID=("#" + UUID.randomUUID().toString()).substring(0,7);
		this.flag=0;
	}
	
	public Message(String context) {
		this.context=context;
		this.messageID=("#" + UUID.randomUUID().toString()).substring(0,7);
	}
	

	public void setUserID(String userID) {
		this.userID=userID;
	}
	
	public void setMessageID(String messageID) {
		this.messageID=messageID;
	}
	
	public void setContext(String context) {
		this.context=context;
	}
	
	public void setTimestamp(Timestamp timestamp) {
		this.timestamp=timestamp;
	}
	
	public String getMessageID() {
		return this.messageID;
	}
	
	public String getContext() {
		return this.context;
	}
	
	public Timestamp getTimestamp() {
		return this.timestamp;
	}
	public void addTag(Tag tag) {
		this.tags.add(tag);
	}
	public Tag getMessage(int index) {
		return this.tags.get(index);
	}
	public boolean removeTag(Tag tag) {
		return this.tags.remove(tag);
	}
	public String getGameID() {
		return this.gameID;
	}
	
	public void setGameID(String gameID) {
		this.gameID=gameID;
	}
	public String getUserID() {
		return this.userID;
	}
	

	public void setFlag(int flag) {
		this.flag=flag;
	}
	
	public int getFlag() {
		return this.flag;
	}
}
