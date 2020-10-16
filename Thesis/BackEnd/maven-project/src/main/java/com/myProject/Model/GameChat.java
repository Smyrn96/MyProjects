package com.myProject.Model;


import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

import org.eclipse.jetty.websocket.api.Session;
import com.myProject.Model.User;

public class GameChat {

	private Map<Session,String> map;
	private int players;
	private String chat_id;
	
	public GameChat() {
		map=new ConcurrentHashMap<Session,String>();
		players=1;
	}
	
	public void setMap(Map map) {
		this.map=map;
	}
	
	public Map getMap() {
		return this.map;
	}
	
	public void incrementPlayers() {
		this.players++;
	}
	
	public void decrementPlayers() {
		this.players--;
	}
	
	public void setPlayers(int players) {
		this.players=players;
	}
	public int getPlayers() {
		return this.players;
	}
}
