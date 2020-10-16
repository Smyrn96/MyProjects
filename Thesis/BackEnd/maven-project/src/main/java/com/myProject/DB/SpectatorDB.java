package com.myProject.DB;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.Date;

import com.myProject.Model.Spectator;
import com.myProject.Model.User;

public class SpectatorDB {

	public static ArrayList<Spectator> getSpectators() throws ClassNotFoundException, SQLException {
		ArrayList<Spectator> spectators=new ArrayList<Spectator>();
		
		Connection c=null;
		Statement stmt = null;
		
		try {
			c=ProjectDB.getConnection();
			stmt=c.createStatement();
			
			
			ResultSet rs=stmt.executeQuery("SELECT * FROM spectators;");
			
			while(rs.next()==true) {
				Spectator spectator=new Spectator();
				spectator.setSpectatorID(rs.getString("user_id"));
				spectator.setGameID(rs.getString("game_id"));
				spectator.setTimestamp(rs.getTimestamp("spectate_start"));
				spectators.add(spectator);
			}
			rs.close();
			
		}catch(SQLException ex) {
			
		}finally {
			ProjectDB.closeConnection(c, stmt);
		}
		return spectators;
	}
	
	
	public static Spectator getSpectator(String user_id) throws SQLException {
		Spectator spectator=null;
		Statement stmt = null;
	    Connection con = null;
	    
	    try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			ResultSet rs=stmt.executeQuery("SELECT * FROM spectators WHERE user_id="+"'"+user_id+"';");
			
			if(rs.next()) {
				spectator=new Spectator();
				
				spectator.setSpectatorID(rs.getString("user_id"));
				spectator.setGameID(rs.getString("game_id"));
				spectator.setTimestamp(rs.getTimestamp("spectate_start"));
				
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
	    return spectator;
	}
	
	public static String getSpectatorGame(String game_id) throws SQLException {
		Spectator spectator=null;
		Statement stmt = null;
	    Connection con = null;
	    
	    try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			ResultSet rs=stmt.executeQuery("SELECT * FROM spectators WHERE game_id="+"'"+game_id+"';");
			
			if(rs.next()) {
				spectator=new Spectator();
				
				spectator.setSpectatorID(rs.getString("user_id"));
				spectator.setGameID(rs.getString("game_id"));
				spectator.setTimestamp(rs.getTimestamp("spectate_start"));
				
			}else {
				System.out.println("No user with that game_id");
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
	    return spectator.getSpectatorID();
	}
	
public static void addSpectator(Spectator spectator) throws SQLException {
		
		Statement stmt = null;
	    Connection con = null;
	    
	    try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			Date date = new Date();
			Timestamp timestamp = new Timestamp(date.getTime());
			spectator.setTimestamp(timestamp);
			
			
			stmt.executeUpdate("INSERT INTO spectators(user_id,game_id,spectate_start) VALUES ('"+spectator.getSpectatorID()+"','"+spectator.getGameID()+"','"+spectator.getTimestamp()+"');");
			System.out.println("#DB: The member"+spectator.getSpectatorID()+" was successfully added in the database.");
			
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
	
	public static void updateUser(Spectator spectator) throws SQLException {
		Statement stmt = null;
	    Connection con = null;
	    
	 
	    try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			Date date = new Date();
			Timestamp timestamp = new Timestamp(date.getTime());
			
			stmt.executeUpdate("UPDATE spectators SET game_id='"+spectator.getGameID()+"',spectate_start="+spectator.getTimestamp()+" WHERE user_id='"+spectator.getSpectatorID()+"';");
			System.out.println("#DB: The member "+spectator.getSpectatorID()+" was successfully updated. "+timestamp);
			
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
			
			stmt.executeUpdate("DELETE FROM spectators WHERE user_id='"+user_id+"';");
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
}
