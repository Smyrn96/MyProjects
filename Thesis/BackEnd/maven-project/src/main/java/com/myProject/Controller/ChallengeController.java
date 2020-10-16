package com.myProject.Controller;

import java.io.PrintWriter;
import java.util.ArrayList;

import javax.servlet.http.Cookie;

import com.myProject.DB.ChallengeDB;
import com.myProject.DB.UserDB;
import com.myProject.Model.Challenge;
import com.myProject.Model.User;

import io.javalin.http.Handler;

public class ChallengeController {

	public static Handler getChallenges = ctx ->{
		String user_id= ctx.pathParam("userID");
		ArrayList<Challenge>allChallenges;
		allChallenges=ChallengeDB.getChallenges(user_id);
		ctx.json(allChallenges);
	};
	
	public static Handler addChallenge=ctx->{
		String user_id= ctx.pathParam("userID");
		Challenge challenge;
		challenge=ctx.bodyAsClass(Challenge.class);
		challenge.setUserID(user_id);
		if(challenge.getDescription()!=null && challenge.getMaxProgress()!=0 && challenge.getRewardPoints()!=0 ) {
			ChallengeDB.addChallenge(challenge);
			ctx.status(201);
		}else{
			System.out.println("Wrong input");
			ctx.status(400);
		}
		
	};
	
	public static Handler deleteChallenge=ctx->{
		String challenge_id= ctx.pathParam("id");
		if(ChallengeDB.getChallenge(challenge_id)!=null) {
			ChallengeDB.deleteChallenge(challenge_id);
			ctx.status(200);
			ctx.json("OK");
		}else {
			System.out.println("No challenge with that id");
			ctx.status(400);
		}
		
	};
	
	public static Handler getChallenge= ctx ->{
		String challenge_id= ctx.pathParam("id");
		 Challenge challenge = ChallengeDB.getChallenge(challenge_id);
		 if(challenge==null) {
			 ctx.html("NO challenge WITH THAT ID");
		 }else {
			 ctx.json(challenge);
		 }
		 
	};
	
	public static Handler updateChallenge=ctx->{
		Challenge challenge;
		challenge=ctx.bodyAsClass(Challenge.class);
		if(ChallengeDB.getChallenge(challenge.getChallengeID())!=null && challenge.getProgress()>=0) {
			ChallengeDB.updateChallenge(challenge);
			ctx.status(200);
			ctx.json(challenge);
		}else{
			System.out.println("Wrong input");
			ctx.status(400);
		}
	};
	
}
