package com.myProject.Model;

import java.util.ArrayList;

public class Leaderboard {
	
	private ArrayList<User> topUsers;
	
	public Leaderboard(){
		this.topUsers=new ArrayList<User> ();
	}
	
	public void setTopUsers(ArrayList<User> topUsers) {
		this.topUsers=topUsers;
	}
	
	public ArrayList<User> getTopUsers(){
		return this.topUsers;
	}
	
	public void addTopUser(User user) {
		this.topUsers.add(user);
	}
	
	
}
