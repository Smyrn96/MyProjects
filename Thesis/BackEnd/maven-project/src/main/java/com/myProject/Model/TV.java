package com.myProject.Model;

import java.util.ArrayList;

public class TV {

	private ArrayList<Game> liveGames;
	
	public TV(){
		liveGames=new ArrayList<Game>();
	}
	
	public void addGame(Game game) {
		this.liveGames.add(game);
	}
	
	public void setLiveGames(ArrayList<Game> liveGames) {
		this.liveGames=liveGames;
	}
	
	public ArrayList<Game> getLiveGames(){
		return this.liveGames;
	}
	
	public boolean searchLiveGame(String game_id) {
		for(int i=0; i<this.liveGames.size(); i++) {
			if(this.liveGames.get(i).getGameID().equals(game_id)) {
				return true;
			}
		}
		return false;
	}
}
