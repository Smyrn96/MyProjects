package com.myProject.DB;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.Date;

import com.myProject.Model.Game;
import com.myProject.Model.Task;
import com.myProject.Model.User;


public class TaskDB {
	
	public static ArrayList<Task> getTasks() throws ClassNotFoundException{
		ArrayList<Task> tasks=new ArrayList<Task>();
		
		Connection c=null;
		Statement stmt = null;
		
		try {
			c=ProjectDB.getConnection();
			stmt=c.createStatement();
			
			
			ResultSet rs=stmt.executeQuery("SELECT * FROM tasks;");
			
			while(rs.next()==true) {
				Task task=new Task();
				task.setTaskID(rs.getString("task_id"));
				task.setTaskName(rs.getString("task_name"));
				task.setTaskDescription(rs.getString("description"));
				task.setCategory(rs.getString("category"));
				task.setAttackerHints(rs.getString("attacker_hints"));
				task.setDefenderHints(rs.getString("defender_hints"));
				task.setAttackersDescription(rs.getString("attacker_description"));
				task.setDefendersDescription(rs.getString("defender_description"));
				task.setMaxMessages(rs.getInt("max_messages"));
				task.setTimestamp(rs.getTimestamp("timestamp"));
				task.setTaskCreator(rs.getString("task_creator"));
				task.setActive(rs.getBoolean("active"));
				tasks.add(task);
			}
			rs.close();
			
		}catch(SQLException ex) {
			
		}finally {
			ProjectDB.closeConnection(c, stmt);
		}
		return tasks;
	}
	
	public static ArrayList<Game> getTaskGames(String task_id) {
		ArrayList<Game> games=new ArrayList<Game>();
		Connection con=null;
		Statement stmt=null;
		
		try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			
			
			ResultSet rs =stmt.executeQuery("SELECT * FROM games WHERE task_id='"+task_id+"';");
			
			while(rs.next()==true) {
				Game game=new Game();
				game.setGameID(rs.getString("game_id"));
				game.setCompletionTime(rs.getInt("completion_time"));
				game.setStartingTime(rs.getTimestamp("starting_time"));
				game.setTaskID(rs.getString("task_id"));
				game.setRounds(rs.getInt("rounds"));
				game.setCategory(rs.getString("category"));
				game.setAttackerUsername(rs.getString("attacker_username"));
				game.setDefenderUsername(rs.getString("defender_username"));
				game.setAttackerPoints(rs.getInt("attacker_points"));
				game.setDefenderPoints(rs.getInt("defender_points"));
				game.setOngoing(rs.getBoolean("ongoing"));
				game.setTagsCount(rs.getInt("tags_count"));
				game.setFinished(rs.getBoolean("finished"));
				games.add(game);
			}
			rs.close();
			
			
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			ProjectDB.closeConnection(con, stmt);
		}
		
		return games;
	}
	
	
	public static Task getTask(String task_id) {
		Task task=null;
		Connection con=null;
		Statement stmt=null;
		
		try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			
			
			ResultSet rs =stmt.executeQuery("SELECT * FROM tasks WHERE task_id='"+task_id+"';");
			
			if(rs.next()) {
				task=new Task();
				task.setTaskID(rs.getString("task_id"));
				task.setTaskName(rs.getString("task_name"));
				task.setTaskDescription(rs.getString("description"));
				task.setCategory(rs.getString("category"));
				task.setAttackerHints(rs.getString("attacker_hints"));
				task.setDefenderHints(rs.getString("defender_hints"));
				task.setAttackersDescription(rs.getString("attacker_description"));
				task.setDefendersDescription(rs.getString("defender_description"));
				task.setMaxMessages(rs.getInt("max_messages"));
				task.setTimestamp(rs.getTimestamp("timestamp"));
				task.setTaskCreator(rs.getString("task_creator"));
				task.setActive(rs.getBoolean("active"));
			}
			
			
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			ProjectDB.closeConnection(con, stmt);
		}
		
		return task;
	}
	
	public static void addTask(Task task) {
		Connection con=null;
		Statement stmt=null;
		
		try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			Date date = new Date();
			Timestamp timestamp = new Timestamp(date.getTime());
			task.setTimestamp(timestamp);
			task.setActive(true);
			
			task.setTaskID(ProjectDB.IDgenerator());
			
			stmt.executeUpdate("INSERT INTO tasks(task_id,task_name,description,category,attacker_hints,defender_hints,attacker_description,defender_description,max_messages,timestamp,task_creator,active) VALUES('"+task.getTaskID()+"','"+task.getTaskName()+"','"+task.getTaskDescription()+"','"+task.getCategory()+"','"+task.getAttackerHints()+"','"+task.getDefenderHints()+"','"+task.getAttackersDescription()+"','"+task.getDefendersDescription()+"','"+task.getMaxMessages()+"','"+task.getTimestamp()+"','"+task.getTaskCreator()+"','"+ task.getActive()+"');");
			System.out.println("Task "+task.getTaskID()+"was successfully added!");
			
		} catch (ClassNotFoundException | SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			ProjectDB.closeConnection(con, stmt);
		}
	}
	
	public static boolean checkTaskName(String taskName) {
		Statement stmt = null;
	    Connection con = null;
	    
	    try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			if(taskName==null) {
				return false;
			}
			
			ResultSet rs=stmt.executeQuery("SELECT task_name FROM tasks WHERE task_name='"+taskName+"';");
			
			if(rs.next()==true) {
				System.out.println("#DB: The task already exists");
				return false;
			}else {
				return true;
			}
			 
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			ProjectDB.closeConnection(con, stmt);
		}
	   
	    return true;
	    
	}
	
	public static void deleteTask(String task_id) {
		Connection con=null;
		Statement stmt=null;
		
		try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			stmt.executeUpdate("DELETE FROM tasks WHERE task_id='"+task_id+"';");
			System.out.println("Task "+task_id+"was successfully deleted!");
			
		} catch (ClassNotFoundException | SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			ProjectDB.closeConnection(con, stmt);
		}
		
	}
	public static void deactivateTask(String task_id) {
		Connection con=null;
		Statement stmt=null;
		
		try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			stmt.executeUpdate("UPDATE tasks SET active='"+false+"' WHERE task_id='"+task_id+"';");
			System.out.println("Task "+task_id+"was successfully updated!");
			
		} catch (ClassNotFoundException | SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			ProjectDB.closeConnection(con, stmt);
		}
		
	}
	
}
