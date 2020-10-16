package com.myProject.Model;
import java.util.Date;
import java.util.UUID;
import java.sql.Time;
import java.sql.Timestamp;
import java.util.ArrayList;


public class Game {
	private String gameID;
	private boolean finished;
	private int completion_time;
	private Timestamp starting_time;
	private String category;
	private String task_id;
	private int rounds;
	private int tags_count;
	private String attacker_username;
	private String defender_username;
	private int attacker_points;
	private int defender_points;
	private boolean ongoing;
	private String role;
	private ArrayList<Message> messages;
	
	public Game() {this.ongoing=true;}
	
	public Game(Timestamp starting_time,String category,String task_id,String attacker_username,String defender_username) {
		this.gameID= ("#" + UUID.randomUUID().toString()).substring(0,7);
		this.starting_time=starting_time;
		this.category=category;
		this.task_id=task_id;
		this.attacker_username=attacker_username;
		this.defender_username=defender_username;
		this.messages=new ArrayList<Message>();
	}
	
	public void setGameID(String gameID) {
		this.gameID=gameID;
	}
	
	public String getGameID() {
		return this.gameID;
	}
	
	public void setCompletionTime(int completion_time) {
		this.completion_time=completion_time;
	}
	
	public int getCompletionTime() {
		return this.completion_time;
	}
	
	public void setStartingTime(Timestamp starting_time) {
		this.starting_time=starting_time;
	}
	
	public Timestamp getStartingTime() {
		return this.starting_time;
	}
	public void setTaskID(String task_id) {
		this.task_id=task_id;
	}
	
	public String getTaskID() {
		return this.task_id;
	}
	public void setCategory(String category) {
		this.category=category;
	}
	
	public String getCategory() {
		return this.category;
	}
	public void setRounds(int rounds) {
		this.rounds=rounds;
	}
	
	public int getRounds() {
		return this.rounds;
	}
	
	public void setAttackerUsername(String attacker_username) {
		this.attacker_username=attacker_username;
	}
	
	public String getAttackerUsername() {
		return this.attacker_username;
	}
	public void setDefenderUsername(String defender_username) {
		this.defender_username=defender_username;
	}
	
	public String getDefenderUsername() {
		return this.defender_username;
	}
	public void setAttackerPoints(int points) {
		this.attacker_points=points;
	}
	
	public int getAttackerPoints() {
		return this.attacker_points;
	}
	public void setDefenderPoints(int points) {
		this.defender_points=points;
	}
	
	public int getDefenderPoints() {
		return this.defender_points;
	}
	public void addMessage(Message message) {
		this.messages.add(message);
	}
	public Message getMessage(int index) {
		return this.messages.get(index);
	}
	public boolean removeMessage(Message message) {
		return this.messages.remove(message);
	}
	public void setOngoing(boolean ongoing) {
		this.ongoing=ongoing;
	}
	public void ongoingSwitch() {
		if(this.ongoing==true) {
			this.ongoing=false;
		}else {
			this.ongoing=true;
		}
	}
	public boolean isOngoing() {
		return this.ongoing;
	}
	
	public void setFinished(boolean finished) {
		this.finished=finished;
	}
	
	public boolean isFinished() {
		return this.finished;
	}
	
	public String getRole() {
		return this.role;
	}
	public void setRole(String role) {
		this.role=role;
	}
	public void setTagsCount(int tags_count) {
		this.tags_count=tags_count;
	}
	public int getTagsCount() {
		return this.tags_count;
	}
}
