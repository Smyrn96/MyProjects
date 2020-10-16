package com.myProject.DB;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.Date;

import com.myProject.Model.Message;

public class MessageDB {

	public static ArrayList<Message> getAllMessages(String gameid) throws SQLException{
		Connection con=null;
		Statement stmt=null;
		ArrayList<Message> messages=new ArrayList<Message>();
		
		try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			ResultSet rs=stmt.executeQuery("SELECT * FROM messages WHERE game_id="+"'"+gameid+"'");
			
			while(rs.next()) {
				Message message=new Message();
				message.setGameID(rs.getString("game_id"));
				message.setMessageID(rs.getString("message_id"));
				message.setUserID(rs.getString("user_id"));
				message.setContext(rs.getString("context"));
				message.setTimestamp(rs.getTimestamp("timestamp"));
				messages.add(message);
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
		
		return messages;
		
	}
	
	public static void addMessage(Message message) throws SQLException {
		Connection con=null;
		Statement stmt=null;
		
		try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			Date date = new Date();
			Timestamp timestamp = new Timestamp(date.getTime());
			
			message.setTimestamp(timestamp);
			message.setMessageID(ProjectDB.IDgenerator());
			
			stmt.executeUpdate("INSERT INTO messages(message_id,game_id,context,timestamp,user_id) VALUES('"+message.getMessageID()+"','"+message.getGameID()+"','"+message.getContext()+"','"+message.getTimestamp()+"','"+message.getUserID()+"');");
			System.out.println("#DB: The message "+message.getMessageID()+" from game "+ message.getGameID()+" was successfully updated. "+timestamp);
			
			
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
	
	public static Message getMessage(String message_id) throws SQLException {
		Connection con=null;
		Statement stmt=null;
		Message message=null;
		
		try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			ResultSet rs=stmt.executeQuery("SELECT * FROM messages WHERE message_id="+"'"+message_id+"';");
			if(rs.next()) {
				message=new Message();
				message.setMessageID(rs.getString("message_id"));
				message.setGameID(rs.getString("game_id"));
				message.setUserID(rs.getString("user_id"));
				message.setContext(rs.getString("context"));
				message.setTimestamp(rs.getTimestamp("timestamp"));
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			ProjectDB.closeConnection(con, stmt);
		}
		return message;
		
	}
	
	public static ArrayList<Message> getUsersMessages(String user_id) {
		ArrayList<Message>messages=null;
		Connection con=null;
		Statement stmt=null;
		
		try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			ResultSet rs=stmt.executeQuery("SELECT * FROM messages WHERE user_id="+"'"+user_id+"';");
			
			while(rs.next()) {
				Message message=new Message();
				message.setMessageID(rs.getString("message_id"));
				message.setGameID(rs.getString("game_id"));
				message.setUserID(rs.getString("user_id"));
				message.setContext(rs.getString("context"));
				message.setTimestamp(rs.getTimestamp("timestamp"));
				messages.add(message);
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
		return messages;
	}
	
}
