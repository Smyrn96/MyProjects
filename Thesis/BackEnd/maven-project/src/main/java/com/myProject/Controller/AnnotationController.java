package com.myProject.Controller;

import java.util.ArrayList;

import com.myProject.DB.AnnotationDB;
import com.myProject.DB.ChallengeDB;
import com.myProject.DB.GameDB;
import com.myProject.DB.UserDB;
import com.myProject.Model.Challenge;
import com.myProject.Model.Annotation;
import com.myProject.Model.Rating;

import io.javalin.http.Handler;

public class AnnotationController {

	
	
	public static Handler getRatings = ctx ->{
		String annotation_id= ctx.pathParam("aid");
		ArrayList<Rating>allRatings;
		allRatings=AnnotationDB.getRatings(annotation_id);
		ctx.json(allRatings);
	};
	
	
	public static Handler addRating=ctx->{
		String annotation_id=ctx.pathParam("aid");
		Rating rating;
		rating=ctx.bodyAsClass(Rating.class);
		rating.setAnnotationID(annotation_id);
		if(AnnotationDB.getAnnotation(annotation_id)!=null) {
			rating=AnnotationDB.addRating(rating);
			ctx.json(rating);
			ctx.status(201);
		}else{
			System.out.println("Wrong input");
			ctx.status(400);
		}
		
	};
	
	
	public static Handler getRating= ctx ->{
		String rating_id= ctx.pathParam("rid");
		 Rating rating = AnnotationDB.getRating(rating_id);
		 if(rating==null) {
			 ctx.html("NO challenge WITH THAT ID");
		 }else {
			 ctx.json(rating);
		 }
		 
	};
	
	
	public static Handler getAnnotations = ctx ->{
		String user_id= ctx.pathParam("uid");
		ArrayList<Annotation>allAnnotations;
		allAnnotations=AnnotationDB.getAnnotations(user_id);
		ctx.json(allAnnotations);
	};
	
	public static Handler addAnnotation=ctx->{
		String user_id= ctx.pathParam("uid");
		String game_id=ctx.pathParam("gid");
		Annotation annotation;
		annotation=ctx.bodyAsClass(Annotation.class);
		annotation.setUserID(user_id);
		annotation.setGameID(game_id);
		if(UserDB.getUser(user_id)!=null && GameDB.getGame(game_id)!=null) {
			annotation=AnnotationDB.addAnnotation(annotation);
			ctx.json(annotation);
			ctx.status(201);
		}else{
			System.out.println("Wrong input");
			ctx.status(400);
		}
		
	};
	
	
	public static Handler getAnnotation= ctx ->{
		String annotation_id= ctx.pathParam("aid");
		 Annotation annotation = AnnotationDB.getAnnotation(annotation_id);
		 if(annotation==null) {
			 ctx.html("NO challenge WITH THAT ID");
		 }else {
			 ctx.json(annotation);
		 }
		 
	};
	
}
