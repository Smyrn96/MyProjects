package com.myProject.Model;
import java.sql.Statement;
import java.sql.Timestamp;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.UUID;

import com.myProject.App;

public class User {
	private String userID;
	private String username;
	private String password;
	private int score;
	private int gamesPlayed;
	private Timestamp date;
	private ArrayList<Badge> badges;
	private ArrayList<Game> matchHistory;
	
	public User() {
	}
	
	public User(String username,String password) {
		this.username=username;
		this.password=password;
		this.userID=("#" + UUID.randomUUID().toString()).substring(0,7);
		this.score=0;
		this.badges=new ArrayList<Badge>();
		this.matchHistory=new ArrayList<Game>();
	}
	
	public void setUsername(String username) {
		this.username=username;
	}
	
	public String getUsername() {
		return this.username;
	}
	
	
	public void setGamesPlayed(int gamesPlayed) {
		this.gamesPlayed=gamesPlayed;
	}
	
	public int getGamesPlayed() {
		return this.gamesPlayed;
	}
	
	
	public void setPassword(String password) {
		this.password=password;
	}
	
	public String getPassword() {
		return this.password;
	}
	
	public void setUserID(String userID) {
		this.userID=userID;
	}
	
	public String getUserID() {
		return this.userID;
	}
	
	public void setScore(int score) {
		this.score=score;
	}
	
	public int getScore() {
		return this.score;
	}
	
	public void setDate(Timestamp date) {
		this.date=date;
	}
	
	public Timestamp getDate() {
		return this.date;
	}
	
	public void addBadge(Badge badge) {
		this.badges.add(badge);
	}
	public boolean removeBadge(Badge badge) {
		return this.badges.remove(badge);
	}
	
	public void addGame(Game game) {
		this.matchHistory.add(game);
	}
	public boolean removeGame(Game game) {
		return this.matchHistory.remove(game);
	}
	
	public String toString(){
		return "Username: "+this.username+" UserID: "+this.userID+" Points: "+this.score;
	}
}
