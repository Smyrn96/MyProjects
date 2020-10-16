package com.myProject.DB;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.Date;

import com.myProject.Model.Annotation;
import com.myProject.Model.Challenge;
import com.myProject.Model.Rating;

public class AnnotationDB {

	public static ArrayList<Annotation> getAnnotations(String userID) throws ClassNotFoundException, SQLException {
		ArrayList<Annotation> annotations=new ArrayList<Annotation>();
		
		Connection c=null;
		Statement stmt = null;
		
		try {
			c=ProjectDB.getConnection();
			stmt=c.createStatement();
			
			
			ResultSet rs=stmt.executeQuery("SELECT * FROM annotations WHERE user_id='"+userID+"';");
			
			while(rs.next()==true) {
				Annotation annotation=new Annotation();
				annotation.setUserID(rs.getString("user_id"));
				
				annotation.setAnnotationID(rs.getString("annotation_id"));
				annotation.setGameID(rs.getString("game_id"));
				annotation.setCreated(rs.getTimestamp("created"));
				annotations.add(annotation);
			}
			rs.close();
			
		}catch(SQLException ex) {
			
		}finally {
			ProjectDB.closeConnection(c, stmt);
		}
		return annotations;
	}
	
	
	
	public static Annotation getAnnotation(String annotation_id) throws SQLException {
		Annotation annotation=null;
		Statement stmt = null;
	    Connection con = null;
	    
	    try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			ResultSet rs=stmt.executeQuery("SELECT * FROM annotations WHERE annotation_id="+"'"+annotation_id+"';");
			
			if(rs.next()) {
				annotation=new Annotation();
				annotation.setUserID(rs.getString("user_id"));
				annotation.setAnnotationID(rs.getString("annotation_id"));
				annotation.setGameID(rs.getString("game_id"));
				annotation.setCreated(rs.getTimestamp("created"));
				
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
	    return annotation;
	}
	
	public static Annotation addAnnotation(Annotation annotation) throws SQLException {
		
		Statement stmt = null;
	    Connection con = null;
	    
	    try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			annotation.setAnnotationID(ProjectDB.IDgenerator());
			Date date = new Date();
			Timestamp timestamp = new Timestamp(date.getTime());
			
			annotation.setCreated(timestamp);
			
			stmt.executeUpdate("INSERT INTO annotations(annotation_id,user_id,game_id,created) VALUES ('"+annotation.getAnnotationID()+"','"+annotation.getUserID()+"','"+annotation.getGameID()+"','"+annotation.getCreated()+"');");
			System.out.println("#DB: The member"+annotation.getAnnotationID()+" was successfully added in the database.");
			
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			ProjectDB.closeConnection(con, stmt);
		}
	    
		return annotation;
	}



public static ArrayList<Rating> getRatings(String annotation_id) throws ClassNotFoundException, SQLException {
	ArrayList<Rating> ratings=new ArrayList<Rating>();
	
	Connection c=null;
	Statement stmt = null;
	
	try {
		c=ProjectDB.getConnection();
		stmt=c.createStatement();
		
		
		ResultSet rs=stmt.executeQuery("SELECT * FROM ratings WHERE annotation_id='"+annotation_id+"';");
		
		while(rs.next()==true) {
			Rating rating=new Rating();
			rating.setMessageID(rs.getString("message_id"));
			rating.setRatingID(rs.getString("rating_id"));
			rating.setAnnotationID(rs.getString("annotation_id"));
			rating.setStars(rs.getInt("stars"));
			rating.setTimestamp(rs.getTimestamp("timestamp"));
			ratings.add(rating);
		}
		rs.close();
		
	}catch(SQLException ex) {
		
	}finally {
		ProjectDB.closeConnection(c, stmt);
	}
	return ratings;
}


public static Rating getRating(String rating_id) throws SQLException {
	Rating rating=null;
	Statement stmt = null;
    Connection con = null;
    
    try {
		con=ProjectDB.getConnection();
		stmt=con.createStatement();
		
		ResultSet rs=stmt.executeQuery("SELECT * FROM ratings WHERE rating_id="+"'"+rating_id+"';");
		
		if(rs.next()) {
			rating=new Rating();
			rating.setRatingID(rs.getString("rating_id"));
			rating.setMessageID(rs.getString("message_id"));
			rating.setAnnotationID(rs.getString("annotation_id"));
			rating.setStars(rs.getInt("stars"));
			rating.setTimestamp(rs.getTimestamp("timestamp"));
			
			
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
    return rating;
}


public static Rating addRating(Rating rating) throws SQLException {
	
	Statement stmt = null;
    Connection con = null;
    
    try {
		con=ProjectDB.getConnection();
		stmt=con.createStatement();
		
		rating.setRatingID(ProjectDB.IDgenerator());
		Date date = new Date();
		Timestamp timestamp = new Timestamp(date.getTime());
		
		rating.setTimestamp(timestamp);
		
		stmt.executeUpdate("INSERT INTO ratings(annotation_id,rating_id,message_id,stars,timestamp) VALUES ('"+rating.getAnnotationID()+"','"+rating.getRatingID()+"','"+rating.getMessageID()+"','"+rating.getStars()+"','"+rating.getTimestamp()+"');");
		System.out.println("#DB: The member"+rating.getRatingID()+" was successfully added in the database.");
		
	} catch (ClassNotFoundException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	} catch (SQLException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}finally {
		ProjectDB.closeConnection(con, stmt);
	}
    
	return rating;
}




}



