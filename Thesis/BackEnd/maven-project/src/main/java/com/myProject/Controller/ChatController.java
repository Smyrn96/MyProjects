package com.myProject.Controller;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.Map;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;
import java.util.function.Consumer;

import com.fasterxml.jackson.databind.util.JSONPObject;
import com.fasterxml.jackson.databind.util.TypeKey;
import com.myProject.DB.ChallengeDB;
import com.myProject.DB.GameDB;
import com.myProject.Model.Challenge;
import com.myProject.Model.Game;

import io.javalin.http.Handler;
import io.javalin.websocket.WsContext;
import io.javalin.websocket.WsHandler;
import kotlin.Pair;

public class ChatController {
	
	 private static Map<WsContext, String> userUsernameMap = new ConcurrentHashMap<>();
	 private static Map<String , Pair<Pair<WsContext, String>,Pair<WsContext, String>>> gamesMap = new ConcurrentHashMap<>();
	 private static Map<String, Pair<WsContext, String>> spectateGameMap = new ConcurrentHashMap<>();
	 private static int nextUserNumber = 0;
	 private static int flag=0;
	 private static WsContext left;
	 private static Map<String ,Integer > GamesAndUsers=new ConcurrentHashMap<>();
	 private static Map<String, String> messagesMap=new ConcurrentHashMap<>();
	 
	public static Consumer<WsHandler>chat = ws ->{
		
		
		ws.onConnect(ctx->{
			 
			System.out.println();
			int numberOfPlayers;
			
			String game_id= ctx.pathParam("id");
			
			if(GamesAndUsers.containsKey(game_id)) {
				numberOfPlayers=GamesAndUsers.get(game_id);
			}else {
				numberOfPlayers=0;
			}
			
			if(numberOfPlayers==0) {
				
				String user_id;
				if(!GameDB.getGame(game_id).getAttackerUsername().equals("")) {
					 user_id=GameDB.getGame(game_id).getAttackerUsername();
					 flag=1;
				}else {
					 user_id=GameDB.getGame(game_id).getDefenderUsername();
					 flag=0;
				}
				numberOfPlayers++;
				GamesAndUsers.put(game_id, numberOfPlayers);
				userUsernameMap.put(ctx,user_id);
				left=ctx;
				ctx.session.setIdleTimeout(800000);
				System.out.println("Game "+game_id+numberOfPlayers+"!!"+user_id + " entered the chat room "+  gamesMap.values().toString()+"-----------"+left);
				
			}else if(numberOfPlayers==1) {
				String user_id;
				
				if(flag==1) {
					user_id=GameDB.getGame(game_id).getDefenderUsername();
				}else {
					user_id=GameDB.getGame(game_id).getAttackerUsername();
				}
				
				numberOfPlayers++;
				GamesAndUsers.put(game_id, numberOfPlayers);
				userUsernameMap.put(ctx,user_id);
				System.out.println(numberOfPlayers+"!!!"+user_id + " entered the chat room "+ userUsernameMap.values().toString());
				Pair l= new Pair(ctx,user_id);
				if(left!=null) {
					Pair r=new Pair(left,userUsernameMap.get(left));
					gamesMap.put(game_id,new Pair(l,r));
				}
				ctx.session.setIdleTimeout(800000);
				
				
				 broadcastMessage(userUsernameMap.get(ctx),"joined the chat",game_id);
				System.out.println("VALUES HERE___________"+ gamesMap.values().toString());
			}
			else {
			/*	System.out.println("HELLO SPECTATOR HERE");
				String user_id= ctx.pathParam("uid");
				Pair p= new Pair(ctx,user_id);
				
				userUsernameMap.put(ctx,user_id);
				spectateGameMap.put(game_id,p);
				System.out.println(numberOfPlayers+"!!!"+user_id + " SPECTATES the chat room "+ userUsernameMap.values().toString());*/
			}
		});
		
		
		ws.onClose(ctx -> {
			int numberOfPlayers;
			String game_id= ctx.pathParam("id");
			
			if(GamesAndUsers.containsKey(game_id)) {
				numberOfPlayers=GamesAndUsers.get(game_id);
				if(numberOfPlayers>0) {
					 String user_id = userUsernameMap.get(ctx);
				     userUsernameMap.remove(ctx);
				     numberOfPlayers--;
				     GamesAndUsers.put(game_id, numberOfPlayers);
				     System.out.println(user_id + " left the chat room "+ ctx.getSessionId());
				}
			}
			spectateGameMap.remove(game_id);
			
		    
		 });
		
		 ws.onMessage(ctx -> {
			 String game_id= ctx.pathParam("id");
			 System.out.println(ctx.message());
			 
			 if(gamesMap.get(game_id).getFirst().getFirst().equals(ctx)){
				 broadcastMessage(gamesMap.get(game_id).getFirst().getSecond(), ctx.message(),game_id);
			 }else if(gamesMap.get(game_id).getSecond().getFirst().equals(ctx)) {
				 broadcastMessage(gamesMap.get(game_id).getSecond().getSecond(), ctx.message(),game_id);
			 }
			
		 });
		 		 
	};

	
	private static void broadcastMessage(String sender,String message,String game_id) {
		
		
		ArrayList<WsContext> con=new ArrayList();
		ArrayList <String> users=new ArrayList();
		
		con.add(gamesMap.get(game_id).getFirst().getFirst());
		con.add(gamesMap.get(game_id).getSecond().getFirst());
		/*if(!spectateGameMap.isEmpty() ) {
			con.add(spectateGameMap.get(game_id).getFirst());
		}
	*/
		
		users.add(gamesMap.get(game_id).getFirst().getSecond());
		users.add(gamesMap.get(game_id).getSecond().getSecond());
		
		con.stream().filter(ctx->ctx.session.isOpen()).forEach(session->{
			try {
				System.out.println(new JSONObject()
				        .put("userMessage", message)
				        .put("sender", sender)
				        .put("userlist", users).toString());
				session.send(
						new JSONObject()
				        .put("userMessage", message)
				        .put("sender", sender)
				        .put("userlist", users).toString()
				        
				);
			} catch (JSONException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		});
	}
	
	
}
