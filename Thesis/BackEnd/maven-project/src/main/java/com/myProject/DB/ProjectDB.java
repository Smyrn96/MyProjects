package com.myProject.DB;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.UUID;

public class ProjectDB {

	public static final String Url="jdbc:postgresql://localhost";
	private static final String DB = "PlatformDataBase";
    private static final int Port = 5432;
    
    private static final String Username = "postgres"; // Share your repo to give you the credentials
    private static final String Password = "Manosmyrn96";  // Share your repo to give you the credentials

    private static final String getConnectionString=Url + ":"+ Port + "/"+ DB;
    
    public static Connection getConnection() throws ClassNotFoundException, SQLException {
    	Class.forName("org.postgresql.Driver");
    	System.out.println("Opened database successfully");
    	return DriverManager.getConnection(getConnectionString,Username,Password);
    	//return DriverManager.getConnection("jdbc:postgresql://localhost:5432/PlatformDataBase","postgres", "Manosmyrn96");
    }
    public static void closeConnection(Connection con, Statement stmt) {
		if(con!=null) {
			try {
				con.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		if(stmt!=null) {
			try {
				stmt.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
    public static String IDgenerator() {
		return (UUID.randomUUID().toString()).substring(0,7);
	}
}
