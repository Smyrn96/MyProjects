package com.myProject.DB;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;

import com.myProject.Model.Challenge;
import com.myProject.Model.User;

public class ChallengeDB {

	public static ArrayList<Challenge> getChallenges(String userID) throws ClassNotFoundException, SQLException {
		ArrayList<Challenge> challenges=new ArrayList<Challenge>();
		
		Connection c=null;
		Statement stmt = null;
		
		try {
			c=ProjectDB.getConnection();
			stmt=c.createStatement();
			
			
			ResultSet rs=stmt.executeQuery("SELECT * FROM challenges WHERE user_id='"+userID+"';");
			
			while(rs.next()==true) {
				Challenge challenge=new Challenge();
				challenge.setUserID(rs.getString("user_id"));
				challenge.setChallengeID(rs.getString("challenge_id"));
				challenge.setDescription(rs.getString("description"));
				challenge.setProgress(rs.getFloat("progress"));
				challenge.setMaxProgress(rs.getFloat("max_progress"));
				challenge.setBadgeReward(rs.getString("badge_id"));
				challenge.setRewardPoints(rs.getInt("reward_points"));
				challenge.setDaily(rs.getBoolean("daily"));
				challenge.setCategory(rs.getString("category"));
				challenges.add(challenge);
			}
			rs.close();
			
		}catch(SQLException ex) {
			
		}finally {
			ProjectDB.closeConnection(c, stmt);
		}
		return challenges;
	}
	
	
	
	public static Challenge getChallenge(String challenge_id) throws SQLException {
		Challenge challenge=null;
		Statement stmt = null;
	    Connection con = null;
	    
	    try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			ResultSet rs=stmt.executeQuery("SELECT * FROM challenges WHERE challenge_id="+"'"+challenge_id+"';");
			
			if(rs.next()) {
				challenge=new Challenge();
				challenge.setChallengeID(rs.getString("challenge_id"));
				challenge.setDescription(rs.getString("description"));
				challenge.setProgress(rs.getFloat("progress"));
				challenge.setMaxProgress(rs.getFloat("max_progress"));
				challenge.setBadgeReward(rs.getString("badge_id"));
				challenge.setDaily(rs.getBoolean("daily"));
				challenge.setRewardPoints(rs.getInt("reward_points"));
				challenge.setCategory(rs.getString("category"));
				
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
	    return challenge;
	}
	
	public static void addChallenge(Challenge challenge) throws SQLException {
		
		Statement stmt = null;
	    Connection con = null;
	    
	    try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			challenge.setChallengeID(ProjectDB.IDgenerator());
			System.out.println(challenge.getChallengeID());
			
			stmt.executeUpdate("INSERT INTO challenges(challenge_id,description,progress,max_progress,badge_id,reward_points,user_id,daily,category) VALUES ('"+challenge.getChallengeID()+"','"+challenge.getDescription()+"','"+challenge.getProgress()+"','"+challenge.getMaxProgress()+"','"+challenge.getBadgeReward()+"','"+ challenge.getRewardPoints()+"','"+challenge.getUserID()+"','"+challenge.isDaily()+"','"+ challenge.getCategory()+"');");
			System.out.println("#DB: The member"+challenge.getChallengeID()+" was successfully added in the database.");
			
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
	
	public static void updateChallenge(Challenge challenge) throws SQLException {
		Statement stmt = null;
	    Connection con = null;
	    
	 
	    try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			stmt.executeUpdate("UPDATE challenges SET progress='"+challenge.getProgress()+"' WHERE challenge_id='"+challenge.getChallengeID()+"';");
			System.out.println("#DB: The challenge "+challenge.getChallengeID()+" was successfully updated.");
			
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
	
	public static void deleteChallenge(String challenge_id) throws SQLException {
		Statement stmt = null;
	    Connection con = null;
	    
	 
	    try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			stmt.executeUpdate("DELETE FROM challenges WHERE challenge_id='"+challenge_id+"';");
			System.out.println("#DB: The member "+challenge_id+" was successfully deleted.");
			
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
