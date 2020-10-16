package com.myProject.DB;

import java.sql.Timestamp;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.Date;

import com.myProject.Model.User;

public class UserDB {

	public static ArrayList<User> getUsers() throws ClassNotFoundException, SQLException {
		ArrayList<User> users=new ArrayList<User>();
		
		Connection c=null;
		Statement stmt = null;
		
		try {
			c=ProjectDB.getConnection();
			stmt=c.createStatement();
			
			
			ResultSet rs=stmt.executeQuery("SELECT * FROM users;");
			
			while(rs.next()==true) {
				User user=new User();
				user.setUsername(rs.getString("USERNAME"));
				user.setPassword(rs.getString("PASSWORD"));
				user.setUserID(rs.getString("USER_ID"));
				user.setGamesPlayed(rs.getInt("games_played"));
				user.setScore(rs.getInt("POINTS"));
				users.add(user);
			}
			rs.close();
			
		}catch(SQLException ex) {
			
		}finally {
			ProjectDB.closeConnection(c, stmt);
		}
		return users;
	}
	
	
	public static ArrayList<User> getTopUsers() throws ClassNotFoundException, SQLException {
		ArrayList<User> users=new ArrayList<User>();
		
		Connection c=null;
		Statement stmt = null;
		
		try {
			c=ProjectDB.getConnection();
			stmt=c.createStatement();
			
			
			ResultSet rs=stmt.executeQuery("SELECT * FROM users ORDER BY points DESC;");
			
			while(rs.next()==true) {
				User user=new User();
				user.setUsername(rs.getString("USERNAME"));
				user.setPassword(rs.getString("PASSWORD"));
				user.setUserID(rs.getString("USER_ID"));
				user.setGamesPlayed(rs.getInt("games_played"));
				user.setScore(rs.getInt("POINTS"));
				users.add(user);
			}
			rs.close();
			
		}catch(SQLException ex) {
			
		}finally {
			ProjectDB.closeConnection(c, stmt);
		}
		return users;
	}
	
	
	public static ArrayList<String> getUserNames(String username) throws ClassNotFoundException, SQLException{
		ArrayList<String> names=new ArrayList<String>();
		
		 Statement stmt = null;
	     Connection con = null;

	     try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			     
			ResultSet rs=stmt.executeQuery("SELECT "+username +"FROM users");
			
			while(rs.next()) {
				names.add(rs.getString("username"));
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
	     
	     return names;
		
	}
	
	
	public static User getUser(String user_id) throws SQLException {
		User user=null;
		Statement stmt = null;
	    Connection con = null;
	    
	    try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			ResultSet rs=stmt.executeQuery("SELECT * FROM users WHERE user_id="+"'"+user_id+"';");
			
			if(rs.next()) {
				user=new User();
				
				user.setUsername(rs.getString("username"));
				user.setUserID(rs.getString("user_id"));
				user.setGamesPlayed(rs.getInt("games_played"));
				user.setPassword(rs.getString("password"));
				user.setScore(rs.getInt("points"));
				
			}else {
				System.out.println("No user with that id");
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
	    return user;
	}
	public static User getUserByUsername(String username) throws SQLException {
		User user=null;
		Statement stmt = null;
	    Connection con = null;
	    
	    try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			ResultSet rs=stmt.executeQuery("SELECT * FROM users WHERE username="+"'"+username+"';");
			
			System.out.println(username);
			
			if(rs.next()) {
				user=new User();
				
				user.setUsername(rs.getString("username"));
				user.setUserID(rs.getString("user_id"));
				user.setGamesPlayed(rs.getInt("games_played"));
				user.setPassword(rs.getString("password"));
				user.setScore(rs.getInt("points"));
				
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
	    return user;
	}
	
	public static void addUser(User user) throws SQLException {
		
		Statement stmt = null;
	    Connection con = null;
	    
	    try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			Date date = new Date();
			Timestamp timestamp = new Timestamp(date.getTime());
			user.setDate(timestamp);
			user.setUserID(ProjectDB.IDgenerator());
			
			stmt.executeUpdate("INSERT INTO users(user_id,username,password,points,registered_since,games_played) VALUES ('"+user.getUserID()+"','"+user.getUsername()+"','"+user.getPassword()+"','"+user.getScore()+"','"+user.getDate()+"','"+user.getGamesPlayed()+"');");
			System.out.println("#DB: The member"+user.getUsername()+" was successfully added in the database.");
			
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
	
	public static void updateUser(User user) throws SQLException {
		Statement stmt = null;
	    Connection con = null;
	    
	 
	    try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			Date date = new Date();
			Timestamp timestamp = new Timestamp(date.getTime());
			
			stmt.executeUpdate("UPDATE users SET points='"+user.getScore()+"',games_played='"+user.getGamesPlayed()+"' WHERE user_id='"+user.getUserID()+"';");
			System.out.println("#DB: The member "+user.getUsername()+" was successfully updated. "+timestamp);
			
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
	
	public static void deleteUser(String user_id) throws SQLException {
		Statement stmt = null;
	    Connection con = null;
	    
	 
	    try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			Date date = new Date();
			Timestamp timestamp = new Timestamp(date.getTime());
			
			stmt.executeUpdate("DELETE FROM users WHERE user_id='"+user_id+"';");
			System.out.println("#DB: The member "+user_id+" was successfully deleted. "+timestamp);
			
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
	
	public static boolean checkUsername(String username) {
		Statement stmt = null;
	    Connection con = null;
	    
	    try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			if(username==null) {
				return false;
			}
			
			ResultSet rs=stmt.executeQuery("SELECT username FROM users WHERE username='"+username+"';");
			
			if(rs.next()==true) {
				System.out.println("#DB: The member already exists");
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
	
	public static boolean checkPassword(String password) {
		Statement stmt = null;
	    Connection con = null;
	    
	    try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			if(password==null) {
				return false;
			}
			
			ResultSet rs=stmt.executeQuery("SELECT password FROM users WHERE password='"+password+"';");
			
			if(rs.next()==true) {
				System.out.println("#DB: The member already exists");
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
	
	public static boolean checkLogin(String username,String password) {
		Statement stmt = null;
	    Connection con = null;
	    
	    try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			if(password==null || username==null) {
				return false;
			}
			
			ResultSet rs=stmt.executeQuery("SELECT username,password FROM users WHERE password='"+password+"' AND username='"+username+"';");
			
			if(rs.next()==true) {
				System.out.println("#DB: The member exists");
				return true;
			}else {
				return false;
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
	
	
	public static String toString(ArrayList<User> users) {
		int i=0;
		String build="";
		while(i<users.size()) {
			build=build+"User: "+users.get(i).getUsername()+" UserID: " +users.get(i).getUserID()+" Score: "+users.get(i).getScore()+"\n";
			i++;
		}
		return build;
	}

}
