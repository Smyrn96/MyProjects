package com.myProject;
import io.javalin.Javalin;
import io.javalin.core.security.Role;
import io.javalin.websocket.WsContext;

import static io.javalin.apibuilder.ApiBuilder.*;

import java.io.File;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;

import com.myProject.Controller.AnnotationController;
import com.myProject.Controller.ChallengeController;
import com.myProject.Controller.ChatController;
import com.myProject.Controller.GameController;
import com.myProject.Controller.StreamController;
import com.myProject.Controller.TaskController;
import com.myProject.Controller.UserController;
import com.myProject.DB.BadgeDB;
import com.myProject.DB.GameDB;
import com.myProject.Model.Badge;


public class App {

	 
	 public static void main(String[] args) throws ClassNotFoundException {
		 try {
			Javalin app = Javalin.create(config -> {config.enableCorsForAllOrigins();}).start(7777);
			/*File f = new File("C:\\Users\\MANOSPC\\eclipse-workspace\\maven-project\\src\\main\\resources\\badge.png");
			File f1 = new File("C:\\Users\\MANOSPC\\eclipse-workspace\\maven-project\\src\\main\\resources\\badge1.png");
			File f2 = new File("C:\\Users\\MANOSPC\\eclipse-workspace\\maven-project\\src\\main\\resources\\badge2.png");
			Badge b=new Badge(f,"Badge");
			Badge b1=new Badge(f1,"Badge1");
			Badge b2=new Badge(f2,"Badge2");
			BadgeDB.addBadge(b);
			BadgeDB.addBadge(b1);
			BadgeDB.addBadge(b2);
			*/
			//BadgeDB.getBadge("Badge");
			//BadgeDB.getBadge("Badge1");
			//BadgeDB.getBadge("Badge2");
			
			
			app.ws(":uid/games/:id",ChatController.chat);
			app.ws("/games/tv/:id",StreamController.chat);
			
			app.routes(()->{
				path("/login",()->{
					post(UserController.loginUser);
				});
				path("/home",()->{
					get(GameController.getHomeGames);
				});
				path("/:userID/challenges",()->{
					get(ChallengeController.getChallenges);
					post(ChallengeController.addChallenge);
					path("/:id",()->{
						get(ChallengeController.getChallenge);
						put(ChallengeController.updateChallenge);
						delete(ChallengeController.deleteChallenge);
					});
				});
				path("/tasks",()->{
					get(TaskController.getTasks);
					post(TaskController.addTask);
					path("/:id",()->{
						put(TaskController.updateTask);
						get(TaskController.getTask);
						delete(TaskController.deleteTask);
						path("/games",()->{
							get(TaskController.getTaskGames);
							path("/stats",()->{
								get(TaskController.getTaskMessagesTags);
							});
						});
					});
				});
				path("/users",()->{
					get(UserController.getAllUsernames);
					post(UserController.addUser);
					path("/leaderboard",()->{
						get(UserController.getTopUsers);
					});
					path("/:id",()->{
						get(UserController.getSpecificName);
						put(UserController.updateUser);
						delete(UserController.deleteUser);
					});
					
				});
				path("/annotations/:uid",()->{
					get(AnnotationController.getAnnotations);
				});
				path("/annotations/:uid/:gid",()->{
					get(AnnotationController.getAnnotations);
					post(AnnotationController.addAnnotation);
						path("/:aid",()->{
							get(AnnotationController.getAnnotation);
							path("/ratings",()->{
								get(AnnotationController.getRatings);
								post(AnnotationController.addRating);
								path("/:rid",()->{
									get(AnnotationController.getRating);
								});
						});
					});
				});
				path("/games",()->{
					get(GameController.getAllGames);
					post(GameController.addGame);
					path("/tv",()->{
						get(GameController.getLiveGames);
						path("/:id",()->{
							get(GameController.getLiveGame);
						});
					});
					path("/:id",()->{
						path("/tags",()->{
							get(GameController.getGameTags);
						});
						put(GameController.joinGame);
						patch(GameController.editGame);
						get(GameController.getGame);
						path("/game_details",()->{
							path("/:uid",()->{
								get(GameController.getGameUserTags);
							});
						});
						path("/messages",()->{
							get(GameController.getAllMessages);
							post(GameController.addMessage);
							path("/:id",()->{
								get(GameController.getMessage);
								path("/tags",()->{
									get(GameController.getAllTags);
									post(GameController.addTag);
									path("/:id",()->{
										get(GameController.getTag);
										put(GameController.updateTag);
										delete(GameController.deleteTag);
									});
								});
							});
						});
					});
				});
			});
			
		 }catch(Exception e){
			 e.printStackTrace();
	         System.err.println(e.getClass().getName()+": "+e.getMessage());
	         System.exit(0);
		 }
		 System.out.println("Opened database successfully");
	       
	 }
}
