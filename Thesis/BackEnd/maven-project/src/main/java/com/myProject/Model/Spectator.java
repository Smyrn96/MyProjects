package com.myProject.Model;

import java.sql.Timestamp;

public class Spectator {

	private String spectatorID;
	private String gameID;
	private Timestamp spectateStart;
	
	public Spectator() {}
	
	public void setSpectatorID(String spectatorID) {
		this.spectatorID=spectatorID;
	}
	
	public String getSpectatorID() {
		return this.spectatorID;
	}
	
	public void setGameID(String gameID) {
		this.gameID=gameID;
	}
	
	public String getGameID() {
		return this.gameID;
	}
	
	public void setTimestamp(Timestamp spectateStart) {
		this.spectateStart=spectateStart;
	}
	
	public Timestamp getTimestamp() {
		return this.spectateStart;
	}
}
