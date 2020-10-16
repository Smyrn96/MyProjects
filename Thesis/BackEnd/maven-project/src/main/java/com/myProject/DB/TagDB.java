package com.myProject.DB;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.Date;

import com.myProject.Model.Message;
import com.myProject.Model.Tag;
import com.myProject.Model.User;

public class TagDB {

	public static Tag getTag(String tag_id) {
		Connection con=null;
		Statement stmt=null;
		Tag tag=null;
		
		try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			ResultSet rs=stmt.executeQuery("SELECT * FROM tags WHERE tag_id='"+tag_id+"';");
			
			if(rs.next()) {
				tag=new Tag();
				tag.setTagID(rs.getString("tag_id"));
				tag.setMessageID(rs.getString("message_id"));
				tag.setUserID(rs.getString("user_id"));
				tag.setCategory(rs.getString("category"));
				tag.setContext(rs.getString("context"));
				tag.setTimestamp(rs.getTimestamp("timestamp"));
			}
			
			
		} catch (ClassNotFoundException | SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			ProjectDB.closeConnection(con, stmt);
		}
		
		return tag;
	}
	
	public static void addTag(Tag tag) {
		Connection con=null;
		Statement stmt=null;
		
		try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			Date date = new Date();
			Timestamp timestamp = new Timestamp(date.getTime());
			tag.setTimestamp(timestamp);
			tag.setTagID(ProjectDB.IDgenerator());
			
			stmt.executeUpdate("INSERT INTO tags(tag_id,user_id,message_id,context,category,timestamp,gameid) VALUES('"+tag.getTagID()+"','"+tag.getUserID()+"','"+tag.getMessageID()+"','"+tag.getTagContext()+"','"+tag.getCategory()+"','"+tag.getTimestamp()+"','"+tag.getGameID()+"');");
			System.out.println("Tag "+tag.getTagID()+" has been added succesfully");
			
		} catch (ClassNotFoundException | SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			ProjectDB.closeConnection(con, stmt);
		}
	}
	
	public static void updateTag(Tag tag) {
		Connection con=null;
		Statement stmt=null;
		
		try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			stmt.executeUpdate("UPDATE tags SET context='"+tag.getTagContext()+"', category='"+tag.getCategory()+"' WHERE tag_id='"+tag.getTagID()+"';");
			System.out.println("Tag "+tag.getTagID()+" has been updated succesfully");
			
		} catch (ClassNotFoundException | SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			ProjectDB.closeConnection(con, stmt);
		}
	
	}
	
	public static void deleteTag(String tag_id) {
		Connection con=null;
		Statement stmt=null;
		
		try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			stmt.executeUpdate("DELETE FROM tags WHERE tag_id='"+tag_id+"';");
			System.out.println("Tag "+tag_id+" has been removed succesfully");
			
		} catch (ClassNotFoundException | SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			ProjectDB.closeConnection(con, stmt);
		}
	
	}
	public static ArrayList<Tag> getMessageTags(String message_id){
		ArrayList<Tag> tags=new ArrayList<Tag>();
		Connection con=null;
		Statement stmt=null;
		
		try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			ResultSet rs=stmt.executeQuery("SELECT * FROM tags WHERE message_id='"+message_id+"';");
			while(rs.next()) {
				Tag tag=new Tag();
				tag.setTagID(rs.getString("tag_id"));
				tag.setUserID(rs.getString("user_id"));
				tag.setMessageID(rs.getString("message_id"));
				tag.setContext(rs.getString("context"));
				tag.setCategory(rs.getString("category"));
				tag.setTimestamp(rs.getTimestamp("timestamp"));
				tags.add(tag);
			}
			
		} catch (ClassNotFoundException | SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			ProjectDB.closeConnection(con, stmt);
		}
		
		return tags;
	}
	
	public static ArrayList<Tag> getUserTags(User user ){
		ArrayList<Tag> tags=new ArrayList<Tag>();
		Connection con=null;
		Statement stmt=null;
		
		try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			ResultSet rs=stmt.executeQuery("SELECT * FROM tags WHERE user_id='"+user.getUserID()+"';");
			while(rs.next()) {
				Tag tag=new Tag();
				tag.setTagID(rs.getString("tag_id"));
				tag.setUserID(rs.getString("user_id"));
				tag.setMessageID("message_id");
				tag.setContext(rs.getString("context"));
				tag.setCategory(rs.getString("category"));
				tag.setTimestamp(rs.getTimestamp("timestamp"));
				tags.add(tag);
			}
			
		} catch (ClassNotFoundException | SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			ProjectDB.closeConnection(con, stmt);
		}
		
		return tags;
	}
}
