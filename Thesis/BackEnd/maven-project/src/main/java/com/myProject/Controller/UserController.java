package com.myProject.Controller;

import java.util.ArrayList;
import java.util.Objects;

import javax.servlet.http.Cookie;
import javax.servlet.http.HttpSession;

import org.json.JSONObject;

import com.myProject.DB.UserDB;
import com.myProject.Model.Leaderboard;
import com.myProject.Model.User;

import io.javalin.http.Context;
import io.javalin.http.Handler;

public class UserController {

	
	public static Handler getAllUsernames = ctx ->{
		ArrayList<User>allUsers;
		allUsers=UserDB.getUsers();
		ctx.json(allUsers);
	};
	
	public static Handler getSpecificName= ctx ->{
		String user_id= ctx.pathParam("id");
		//System.out.println(user_id);
		 User user = UserDB.getUser(user_id);
		 if(user==null) {
			 ctx.html("NO USER WITH THAT ID");
		 }else {
			 ctx.json(user);
			 ctx.status(200);
		 }
		 
	};
	
	public static Handler addUser=ctx->{
		User user;
		user=ctx.bodyAsClass(User.class);
		if(UserDB.checkUsername(user.getUsername()) && UserDB.checkPassword(user.getPassword())) {
			UserDB.addUser(user);
			ctx.cookie("user_id", user.getUserID());
			System.out.println(user.getUserID());
			String jsonString =new JSONObject()
					.put("userID", user.getUserID())
					.put("username", user.getUsername())
					.put("points",user.getScore())
					.put("gamesPlayed", user.getGamesPlayed())
					.put("flag", 1)
					.toString();
			ctx.json(jsonString);
			ctx.status(201);
		}else {
			String jsonString =new JSONObject()
					.put("flag", 0)
					.toString();
			ctx.json(jsonString);
			ctx.status(400);
		}
		
	};
	
	public static Handler updateUser=ctx->{
		String user_id= ctx.pathParam("id");
		User user;
		user=ctx.bodyAsClass(User.class);
		user.setUserID(user_id);
		if(UserDB.getUser(user_id)!=null) {
			UserDB.updateUser(user);
			ctx.status(200);
		}else {
			System.out.println("Wrong Input");
		}
	};
	
	public static Handler deleteUser=ctx->{
		String user_id= ctx.pathParam("id");
		User user=UserDB.getUser(user_id);
		 if(user==null) {
			 System.out.println("No user with the specific ID");
		 }else {
			 UserDB.deleteUser(user_id);
			 ctx.status(200);
		 }
	};
	
	public static Handler getTopUsers = ctx ->{
		Leaderboard leaderboard=new Leaderboard(); 
		leaderboard.setTopUsers(UserDB.getTopUsers());
		ctx.json(leaderboard.getTopUsers());
	};
	
	public static Handler loginUser=ctx->{
		User user;
		user=ctx.bodyAsClass(User.class);
		System.out.println(user.getUserID());
		if(UserDB.checkLogin(user.getUsername(),user.getPassword())) {
			user.setUserID(UserDB.getUserByUsername(user.getUsername()).getUserID());
			//ctx.sessionAttribute("userID", user.getUserID());
			/* Session id(HTTP Session Java servlets) */
			Cookie a1 = new Cookie("user_id", user.getUserID());
			a1.setHttpOnly(false);
			//a1.setDomain("127.0.0.1");
			System.out.println((String)ctx.sessionAttribute("userID"));
			String jsonString =new JSONObject()
					.put("userID", user.getUserID())
					.put("username", user.getUsername())
					.put("points",user.getScore())
					.put("flag", 1)
					.toString();
			ctx.cookie(a1);
			ctx.json(jsonString);
			
			ctx.status(200);
		}else {
			System.out.println("Wrong Input");
			String jsonString =new JSONObject()
					.put("userID","")
					.put("flag", 0)
					.toString();
			ctx.json(jsonString);
			ctx.status(400);
		}
		
	};
	
}
