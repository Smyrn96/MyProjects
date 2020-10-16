package com.myProject.Controller;

import java.util.ArrayList;

import org.json.JSONObject;

import com.myProject.DB.GameDB;
import com.myProject.DB.MessageDB;
import com.myProject.DB.TaskDB;
import com.myProject.DB.UserDB;
import com.myProject.Model.Game;
import com.myProject.Model.Task;
import com.myProject.Model.User;

import io.javalin.http.Handler;

public class TaskController {

	public static Handler getTasks = ctx ->{
		ArrayList<Task>allTasks;
		allTasks=TaskDB.getTasks();
		ctx.json(allTasks);
	};
	
	public static Handler addTask=ctx->{
		Task task;
		task=ctx.bodyAsClass(Task.class);
		if(TaskDB.checkTaskName(task.getTaskName()) && task.getTaskDescription()!=null && task.getCategory()!=null && task.getAttackerHints()!=null && task.getDefenderHints()!=null && task.getAttackersDescription()!=null && task.getDefendersDescription()!=null) {
			TaskDB.addTask(task);
			String jsonString =new JSONObject()
					.put("taskID", task.getTaskID())
					.put("timestamp", task.getTimestamp())
					.toString();
			ctx.json(jsonString);
			ctx.status(201);
		}else {
			System.out.println("Wrong Input");
		}
		
	};
	
	public static Handler deleteTask=ctx->{
		String task_id= ctx.pathParam("id");
		System.out.println(task_id);
		Task task=TaskDB.getTask(task_id);
		if(task==null) {
			 System.out.println("No task with the specific ID");
		 }else {
			TaskDB.deleteTask(task_id);
			ctx.json("OK");
			ctx.status(200);
		 }
	};
	
	public static Handler updateTask=ctx->{
		String task_id= ctx.pathParam("id");
		System.out.println(task_id);
		Task task=TaskDB.getTask(task_id);
		if(task==null) {
			 System.out.println("No task with the specific ID");
		 }else {
			TaskDB.deactivateTask(task_id);
			ctx.json("OK");
			ctx.status(200);
		 }
	};
	
	public static Handler getTask= ctx ->{
		String task_id= ctx.pathParam("id");
		 Task task = TaskDB.getTask(task_id);
		 if(task==null) {
			 ctx.html("NO TASK WITH THAT ID");
		 }else {
			 ctx.json(task);
			 ctx.status(200);
		 }
		 
	};
	public static Handler getTaskGames= ctx ->{
		String task_id= ctx.pathParam("id");
		ArrayList<Game>allGames = TaskDB.getTaskGames(task_id);
		 if(allGames==null) {
			 ctx.html("NO TASK WITH THAT ID");
		 }else {
			 ctx.json(allGames);
			 ctx.status(200);
		 }
		 
		 
	};
	
	public static Handler getTaskMessagesTags= ctx ->{
		String task_id= ctx.pathParam("id");
		
		ArrayList<Game> games=new ArrayList<Game>();
		games=TaskDB.getTaskGames(task_id);
		
	
		System.out.println(games);
	
		int counter=0;
		for(int i=0; i<games.size(); i++) {
			counter=counter+MessageDB.getAllMessages(games.get(i).getGameID()).size();
		}
		
		int counter1=0;
		for(int i=0; i<games.size(); i++) {
			counter1=counter1+GameDB.getGameTags(games.get(i).getGameID()).size();
		}
		int []a =new int[2];
		a[0]=counter;
		a[1]=counter1;
		String jsonString =new JSONObject()
				.put("totalMessages", counter)
				.put("totalTags", counter1)
				.toString();
		ctx.json(a);
		ctx.status(200);
	};
	
	
}
