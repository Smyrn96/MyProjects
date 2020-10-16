package com.myProject.DB;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.Date;

import com.myProject.Model.Game;
import com.myProject.Model.Tag;
import com.myProject.Model.User;

public class GameDB {

	public static ArrayList<Game> getGames() throws ClassNotFoundException, SQLException {
		ArrayList<Game> games=new ArrayList<Game>();
		
		Connection c=null;
		Statement stmt = null;
		
		try {
			c=ProjectDB.getConnection();
			stmt=c.createStatement();
			
			
			ResultSet rs=stmt.executeQuery("SELECT * FROM games;");
			
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
			
		}catch(SQLException ex) {
			
		}finally {
			ProjectDB.closeConnection(c, stmt);
		}
		return games;
	}
	
	public static ArrayList<Game> getLiveGames() throws ClassNotFoundException, SQLException {
		ArrayList<Game> liveGames=new ArrayList<Game>();
		
		Connection c=null;
		Statement stmt = null;
		
		try {
			c=ProjectDB.getConnection();
			stmt=c.createStatement();
			
			
			ResultSet rs=stmt.executeQuery("SELECT * FROM games WHERE ongoing=true;");
			
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
				liveGames.add(game);
			}
			rs.close();
			
		}catch(SQLException ex) {
			
		}finally {
			ProjectDB.closeConnection(c, stmt);
		}
		return liveGames;
	}
	
	public static ArrayList<Game> getHomeGames() throws ClassNotFoundException, SQLException {
		ArrayList<Game> homeGames=new ArrayList<Game>();
		
		Connection c=null;
		Statement stmt = null;
		
		try {
			c=ProjectDB.getConnection();
			stmt=c.createStatement();
			
			
			ResultSet rs=stmt.executeQuery("SELECT * FROM games WHERE ongoing=true AND (attacker_id=null OR defender_id=null);");
			
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
				homeGames.add(game);
			}
			rs.close();
			
		}catch(SQLException ex) {
			
		}finally {
			ProjectDB.closeConnection(c, stmt);
		}
		return homeGames;
	}
	
	
	public static Game getGame(String game_id) throws SQLException {
		Game game=null;
		Statement stmt = null;
	    Connection con = null;
	    
	    try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			ResultSet rs=stmt.executeQuery("SELECT * FROM games WHERE game_id="+"'"+game_id+"';");
			
			if(rs.next()) {
				game=new Game();
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
				game.setFinished(rs.getBoolean("finished"));
				game.setTagsCount(rs.getInt("tags_count"));
				
			}else {
				System.out.println("No user with that username");
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
	    return game;
	}
	
	
	public static ArrayList<Tag> getGameUserTags(String game_id,String user_id) throws SQLException {
		ArrayList<Tag> Tags=new ArrayList<Tag>();
		Statement stmt = null;
	    Connection con = null;
	    
	    try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			ResultSet rs=stmt.executeQuery("SELECT * FROM tags WHERE gameid="+"'"+game_id+"' AND user_id='"+user_id+"';");
			
			if(rs.next()) {
				Tag tag=new Tag();
				tag.setMessageID(rs.getString("message_id"));
				tag.setUserID(rs.getString("user_id"));
				tag.setGameID(rs.getString("gameid"));
				tag.setCategory(rs.getString("category"));
				tag.setTagID(rs.getString("tag_id"));
				tag.setTimestamp(rs.getTimestamp("timestamp"));
				Tags.add(tag);

				
			}else {
				System.out.println("No user with that username");
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
	    return Tags;
	}
	
	public static void addGame(Game game) throws SQLException {
		
		Statement stmt = null;
	    Connection con = null;
	    
	    try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			Date date = new Date();
			Timestamp timestamp = new Timestamp(date.getTime());
			System.out.println(timestamp);
			game.setStartingTime(timestamp);
			game.setGameID(ProjectDB.IDgenerator());
			
			stmt.executeUpdate("INSERT INTO games(game_id,completion_time,starting_time,category,task_id,rounds,attacker_username,defender_username,attacker_points,defender_points,ongoing,tags_count,finished) VALUES ('"+game.getGameID()+"','"+game.getCompletionTime()+"','"+game.getStartingTime()+"','"+game.getCategory()+"','"+game.getTaskID()+"','"+game.getRounds()+"','"+game.getAttackerUsername()+"','"+game.getDefenderUsername()+"','"+game.getAttackerPoints()+"','"+game.getDefenderPoints()+"','"+game.isOngoing()+"','"+game.getTagsCount()+"','"+game.isFinished()+"');");
			System.out.println("#DB: The game "+game.getGameID()+" was successfully added in the database.");
			
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			ProjectDB.closeConnection(con, stmt);
		}
	}
	    
	    public static boolean joinGame(String gameID,User user) throws SQLException {
			
			Statement stmt = null;
		    Connection con = null;
		    
		    Game game=null;
		    
		    try {
				con=ProjectDB.getConnection();
				stmt=con.createStatement();
				
				Date date = new Date();
				Timestamp timestamp = new Timestamp(date.getTime());
				System.out.println(timestamp);
				//game.setStartingTime(timestamp);
				
				game=getGame(gameID);
				String role="";
				
				if(game.getAttackerUsername()!=null  && (game.getDefenderUsername()==null || game.getDefenderUsername().equals(""))) {
					role="Defender";
				}else if((game.getAttackerUsername()==null || game.getAttackerUsername().equals("")) && game.getDefenderUsername()!=null) {
					role="Attacker";
				}
				
				if(role.equals("Attacker")) {
					stmt.executeUpdate("UPDATE games SET attacker_username='"+ user.getUsername()+"', attacker_points='"+ user.getScore()+"' WHERE game_id='"+gameID+"';" );
					System.out.println("#DB: The game "+game.getGameID()+" ATTACKER was successfully added in the database.");
				}else if(role.equals("Defender")) {
					stmt.executeUpdate("UPDATE games SET defender_username='"+ user.getUsername()+"', defender_points='"+ user.getScore()+"' WHERE game_id='"+gameID+"';" );
					System.out.println("#DB: The game "+game.getGameID()+" was successfully added in the database.");
				}else {
					stmt.executeUpdate("UPDATE games SET completion_time='"+ game.getCompletionTime()+"', rounds='"+ game.getRounds()+",tags='"+game.getTagsCount()+"',ongoing='"+ game.isOngoing()+"',finished='"+game.isFinished()+"' WHERE game_id='"+gameID+"';" );
				}
				
				return true;
				
				
			} catch (ClassNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}finally {
				ProjectDB.closeConnection(con, stmt);
			}
		    return false;
	}
	    public static boolean editGame(Game game)  throws SQLException{
	    	Statement stmt = null;
		    Connection con = null;
		    
		    
		    try {
				con=ProjectDB.getConnection();
				stmt=con.createStatement();
				
				
				stmt.executeUpdate("UPDATE games SET completion_time='"+ game.getCompletionTime()+"', rounds='"+ game.getRounds()+"',tags_count='"+game.getTagsCount()+"',ongoing='"+ game.isOngoing()+"',finished='"+game.isFinished()+"' WHERE game_id='"+game.getGameID()+"';" );
			
				
				return true;
				
				
			} catch (ClassNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}finally {
				ProjectDB.closeConnection(con, stmt);
			}
		    return false;
	    }
	    public static ArrayList<Tag> getGameTags(String game_id) throws ClassNotFoundException, SQLException {
			ArrayList<Tag> tags=new ArrayList<Tag>();
			
			Connection c=null;
			Statement stmt = null;
			
			try {
				c=ProjectDB.getConnection();
				stmt=c.createStatement();
				
				
				ResultSet rs=stmt.executeQuery("SELECT * FROM tags WHERE gameID='"+game_id+"';");
				
				while(rs.next()==true) {
					Tag tag=new Tag();
					tag.setMessageID(rs.getString("message_id"));
					tag.setUserID(rs.getString("user_id"));
					tag.setGameID(rs.getString("gameid"));
					tag.setCategory(rs.getString("category"));
					tag.setTagID(rs.getString("tag_id"));
					tag.setTimestamp(rs.getTimestamp("timestamp"));
					tags.add(tag);
				}
				rs.close();
				
			}catch(SQLException ex) {
				
			}finally {
				ProjectDB.closeConnection(c, stmt);
			}
			return tags;
		}
	
	
}
