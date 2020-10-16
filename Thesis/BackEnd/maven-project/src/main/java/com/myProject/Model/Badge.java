package com.myProject.Model;

import java.io.File;
import java.sql.Blob;
import java.util.UUID;

public class Badge {
	private File path;
	private String alternative;
	private String badgeID;
	
	public Badge() {
		this.badgeID=(UUID.randomUUID().toString()).substring(0,7);
	}
	
	public Badge(File path,String alternative) {
		this.path=path;
		this.alternative=alternative;
		this.badgeID=( UUID.randomUUID().toString()).substring(0,7);
	}
	
	public void setPath(File path) {
		this.path=path;
	}
	public File getPath() {
		return this.path;
	}
	public void setAlternative(String alternative) {
		this.alternative=alternative;
	}
	public String getAlternative() {
		return this.alternative;
	}
	public void setBadgeID(String badgeID) {
		this.badgeID=badgeID;
	}
	public String getBadgeID() {
		return this.badgeID;
	}
	
}
