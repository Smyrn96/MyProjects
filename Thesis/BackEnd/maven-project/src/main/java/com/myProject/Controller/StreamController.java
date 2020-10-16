package com.myProject.Controller;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.function.Consumer;

import javax.servlet.http.Cookie;

import com.myProject.DB.GameDB;
import com.myProject.DB.SpectatorDB;

import io.javalin.websocket.WsContext;
import io.javalin.websocket.WsHandler;

public class StreamController {
	
	 private static Map<WsContext, String> userUsernameMap = new ConcurrentHashMap<>();
	
	 public static Consumer<WsHandler>chat = ws ->{
		ws.onConnect(ctx->{
			String game_id= ctx.pathParam("id");
			String user_id =ctx.cookie("user_id");
			
			System.out.println(user_id);
			//String user_id=SpectatorDB.getSpectatorGame(game_id);
			
			userUsernameMap.put(ctx,user_id);
			System.out.println(user_id + " entered the chat room "+ ctx.getSessionId());
		});
		
		
		ws.onClose(ctx -> {
			String user_id=userUsernameMap.get(ctx);
			userUsernameMap.remove(ctx);
		     
		    System.out.println(user_id + " left the chat room "+ ctx.getSessionId());    
		 });
	 };
	}
