package com.myProject.DB;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;

import com.myProject.Model.Badge;
import com.myProject.Model.Game;

public class BadgeDB {

	public static Badge getBadge(String description) throws SQLException, IOException {
		Badge badge=null;
		Connection con=null;
		Statement stmt=null;
		InputStream imageStream = null;
		File file=null;
		OutputStream out=null;
		
		try {
			con=ProjectDB.getConnection();
			stmt=con.createStatement();
			
			ResultSet rs=stmt.executeQuery("SELECT * FROM badges WHERE alternative="+"'"+description+"';");
			
			if(rs.next()) {
				badge=new Badge();
				imageStream = rs.getBinaryStream(1);
				file=new File("C:\\Users\\MANOSPC\\Documents\\myproject\\public\\"+description+".png"); //path oxi hardcoded
				out = new FileOutputStream(file);
				int c = 0;
                //write the contents from the input stream to the output stream
				while ((c = imageStream.read()) != -1) {
					out.write(c);
				}
				badge.setPath(file);
				badge.setAlternative(rs.getString("alternative"));
				badge.setBadgeID(rs.getString("badge_id"));
			}
			
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			ProjectDB.closeConnection(con, stmt);
			imageStream.close();
			out.close();
		}
		return badge;
	}
	
	public static void addBadge(Badge badge) throws ClassNotFoundException, SQLException, IOException {
		Connection con=null;
		PreparedStatement statement = null;
		FileInputStream imageInputStream = null;
		
		try {
			badge.setBadgeID(ProjectDB.IDgenerator());
			con=ProjectDB.getConnection();
			statement = con.prepareStatement("INSERT INTO badges(path,badge_id,alternative) VALUES(?,'"+badge.getBadgeID()+"','"+badge.getAlternative()+"');");
			imageInputStream = new FileInputStream(badge.getPath());
			statement.setBinaryStream(1, imageInputStream);
			statement.execute();
			System.out.println("#DB: The badge"+badge.getAlternative()+" was successfully added in the database.");
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			ProjectDB.closeConnection(con, statement);
	        imageInputStream.close();
		}
		
	}
	
	
	

}

