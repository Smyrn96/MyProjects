package com.myProject.Controller;

import java.awt.List;
import java.util.ArrayList;

import javax.servlet.http.Cookie;
import javax.servlet.http.HttpSession;

import org.json.JSONArray;
import org.json.JSONObject;

import com.myProject.DB.GameDB;
import com.myProject.Model.Game;
import com.myProject.Model.Message;
import com.myProject.Model.Spectator;
import com.myProject.Model.TV;
import com.myProject.Model.Tag;
import com.myProject.Model.User;
import com.myProject.DB.MessageDB;
import com.myProject.DB.SpectatorDB;
import com.myProject.DB.TagDB;
import com.myProject.DB.TaskDB;
import com.myProject.DB.UserDB;

import io.javalin.http.Handler;

public class GameController {

	public static Handler getAllGames = ctx ->{
		ArrayList<Game>allGames;
		allGames=GameDB.getGames();
		ctx.json(allGames);
		System.out.println(ctx.cookieMap());
	};
	public static Handler getHomeGames = ctx ->{
		ArrayList<Game>homeGames;
		homeGames=GameDB.getHomeGames();
		ctx.json(homeGames);
	};
	
	public static Handler getGame= ctx ->{
		String game_id= ctx.pathParam("id");
		//System.out.println(user_id);
		 Game game = GameDB.getGame(game_id);
		 if(game==null) {
			 ctx.html("NO Game WITH THAT ID");
		 }else {
			 ctx.json(game);
			 ctx.status(200);
		 }
		 
	};
	
	
	
	
	
public static Handler getTaskTags= ctx ->{
		
		
		JSONArray arr = new JSONArray(ctx.body());
		ArrayList<String> l = new ArrayList<String>();
		for(int i = 0; i < arr.length(); i++){
		    l.add(arr.getJSONObject(i).getString("gameID"));
		}
	
		System.out.println(l);
	
		int counter=0;
		for(int i=0; i<l.size(); i++) {
			counter=counter+GameDB.getGameTags(l.get(i)).size();
		}
		ctx.json(counter);
	};
	
	public static Handler addGame=ctx->{
		Game game;
		game=ctx.bodyAsClass(Game.class);
		System.out.println(game.getAttackerUsername() +"   "+game.getDefenderUsername());
		
		if((UserDB.getUserByUsername(game.getAttackerUsername())!=null || UserDB.getUserByUsername(game.getDefenderUsername())!=null) && TaskDB.getTask(game.getTaskID())!=null) {
			GameDB.addGame(game);
			String jsonString =new JSONObject()
					.put("gameID", game.getGameID())
					.put("attackerUsername", game.getAttackerUsername())
					.put("defenderUsername", game.getDefenderUsername())
					.put("attackerPoints", game.getAttackerPoints())
					.put("defenderPoints", game.getDefenderPoints())
					.put("taskID", game.getTaskID())
					.put("category", game.getCategory())
					.put("flag", 1)
					.toString();
			ctx.json(jsonString);
			ctx.status(201);
		}else {
			String jsonString =new JSONObject()
					.put("gameID", "")
					.put("flag", 0)
					.toString();
			ctx.json(jsonString);
			System.out.println("Wrong Input");
		}
	
	};
	
	public static Handler getAllMessages = ctx ->{
		String game_id= ctx.pathParam("id");
		ArrayList<Message>allMessages;
		if(GameDB.getGame(game_id)!=null) {
			allMessages=MessageDB.getAllMessages(game_id);
			ctx.json(allMessages);
		}else{
			System.out.println("No game with that id");
		}
		
	};
	public static Handler addMessage=ctx->{
		String game_id= ctx.pathParam("id");
		Message message;
		message=ctx.bodyAsClass(Message.class);
		message.setGameID(game_id);
		if(GameDB.getGame(game_id)!=null) {
			if(message.getUserID()!=null && message.getContext()!=null) {
				MessageDB.addMessage(message);
				String jsonString =new JSONObject()
						.put("gameID", message.getGameID())
						.put("context", message.getContext())
						.put("userID", message.getUserID())
						.put("message_id", message.getMessageID())
						.put("timestamp", message.getTimestamp())
						.toString();
				ctx.json(jsonString);
				ctx.status(201);
			}else {
				System.out.println("Wrong Input");
			}
		}
		
		
	};
	
	public static Handler getMessage= ctx ->{
		String message_id= ctx.pathParam("id");
		//System.out.println(user_id);
		 Message message = MessageDB.getMessage(message_id);
		 if(message==null) {
			 ctx.html("NO message WITH THAT ID");
		 }else {
			 ctx.json(message);
			 ctx.status(200);
		 }
		 
	};
	
	public static Handler getAllTags = ctx ->{
		String message_id= ctx.pathParam("id");
		ArrayList<Tag>allTags;
		 Message message = MessageDB.getMessage(message_id);
		 if(message==null) {
			 System.out.println("No message with that id");
		 }else {
			 allTags=TagDB.getMessageTags(message_id);
			ctx.json(allTags);
			ctx.status(200);
		 }
	};
	
	public static Handler addTag=ctx->{
		String message_id= ctx.pathParam("id");
		Tag tag;
		tag=ctx.bodyAsClass(Tag.class);
		tag.setMessageID(message_id);
		if(MessageDB.getMessage(message_id)!=null) {
			if(UserDB.getUser(tag.getUserID())!=null && tag.getCategory()!=null && TagDB.getTag(tag.getTagID())==null ) {
				TagDB.addTag(tag);	
				String jsonString =new JSONObject()
						.put("tagID", tag.getTagID())
						.toString();
				ctx.json(jsonString);
				ctx.status(201);
			}else {
				ctx.json("0");
				System.out.println("Wrong Input");
			}
		}
		
	};
	
	public static Handler getTag= ctx ->{
		String tag_id= ctx.pathParam("id");
		 Tag tag = TagDB.getTag(tag_id);
		 if(tag==null) {
			 ctx.html("NO tag WITH THAT ID");
		 }else {
			 ctx.json(tag);
			 ctx.status(200);
		 }
		 
	};
	
	public static Handler updateTag=ctx->{
		String tag_id= ctx.pathParam("id");
		Tag tag;
		tag=ctx.bodyAsClass(Tag.class);
		tag.setTagID(tag_id);
		if(UserDB.getUser(tag.getUserID())!=null && tag.getCategory()!=null ) {
			TagDB.updateTag(tag);
			ctx.status(200);
			ctx.json("OK");
		}else {
			System.out.println("Wrong Input");
		}
	};
	
	public static Handler deleteTag=ctx->{
		String tag_id= ctx.pathParam("id");
		if(TagDB.getTag(tag_id)!=null) {
			TagDB.deleteTag(tag_id);
			ctx.status(200);
			ctx.json("OK");
		}else {
			ctx.json("0");
			System.out.println("Wrong Input");
		}
	
	};
	public static Handler getLiveGames = ctx ->{
		
		
		ArrayList<Game>allGames;
		allGames=GameDB.getLiveGames();
		ctx.json(allGames);
		ctx.status(200);
	};
	public static Handler getLiveGame = ctx ->{
		String game_id= ctx.pathParam("id");
		Game game = null;
		Spectator spec=null;
		TV tv =new TV();
		tv.setLiveGames(GameDB.getLiveGames());//websockets to live streaming
		if(tv.searchLiveGame(game_id)) {
			game=GameDB.getGame(game_id);
			spec=new Spectator();
			spec.setGameID(game_id);
			spec.setSpectatorID(ctx.cookie("user_id"));
			SpectatorDB.addSpectator(spec);
			ctx.json(game);
			ctx.status(200);
		}else {
			ctx.html("No live game with that id");
		}
		
	};
	public static Handler getGameUserTags = ctx ->{
		String user_id= ctx.pathParam("uid");
		String game_id= ctx.pathParam("id");
		ArrayList<Tag>allTags;
		System.out.println(user_id+" "+game_id);
		if(GameDB.getGame(game_id)!=null && UserDB.getUser(user_id)!=null) {
			allTags=GameDB.getGameUserTags(game_id,user_id);
			ctx.json(allTags);
			ctx.status(200);
		}else {
			ctx.html("No live game with that id");
		}
		
	};
	
	public static Handler getGameTags = ctx ->{
		String game_id= ctx.pathParam("id");
		ArrayList<Tag>allTags;
		if(GameDB.getGame(game_id)!=null) {
			allTags=GameDB.getGameTags(game_id);
			ctx.json(allTags);
			ctx.status(200);
		}else {
			ctx.html("No live game with that id");
		}
		
	};
	
	
	
	
	public static Handler joinGame=ctx->{
		String game_id= ctx.pathParam("id");
	
		User user =ctx.bodyAsClass(User.class);
		
		System.out.println(game_id+" EDW"+user);
		Game game=GameDB.getGame(game_id);
		if(game!=null) {
			if(GameDB.joinGame(game_id, user)) {
				 game=GameDB.getGame(game_id);
				String jsonString =new JSONObject()
						.put("gameID", game.getGameID())
						.put("attackerUsername", game.getAttackerUsername())
						.put("defenderUsername", game.getDefenderUsername())
						.put("attackerPoints", game.getAttackerPoints())
						.put("defenderPoints", game.getDefenderPoints())
						.put("taskID", game.getTaskID())
						.put("category", game.getCategory())
						.put("flag", 1)
						.toString();
				ctx.json(jsonString);
				ctx.status(200);
			}
			
		}else {
			ctx.html("No live game with that id");
		}
		
		
		
	};
	public static Handler editGame=ctx->{
		String game_id= ctx.pathParam("id");
	
		Game game=ctx.bodyAsClass(Game.class);
		game.setGameID(game_id);
		if(game!=null) {
				 GameDB.editGame(game);
				String jsonString =new JSONObject()
						.put("gameID", game.getGameID())
						.put("attackerUsername", game.getAttackerUsername())
						.put("defenderUsername", game.getDefenderUsername())
						.put("attackerPoints", game.getAttackerPoints())
						.put("defenderPoints", game.getDefenderPoints())
						.put("taskID", game.getTaskID())
						.put("category", game.getCategory())
						.put("flag", 1)
						.toString();
				ctx.json(jsonString);
				ctx.status(200);
			}
			
		
		
		
		
	};
}
