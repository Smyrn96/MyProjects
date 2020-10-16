package com.myProject.Model;

import java.sql.Timestamp;

public class Rating {

	
	private String rating_id;
	private String annotation_id;
	private int stars;
	private String message_id;
	private Timestamp timestamp;
	
	public Rating(){}
	
	public void setRatingID(String rating_id) {
		this.rating_id=rating_id;
	}
	public void setMessageID(String message_id) {
		this.message_id=message_id;
	}
	public void setAnnotationID(String annotation_id) {
		this.annotation_id=annotation_id;
	}
	public void setStars(int stars) {
		this.stars=stars;
	}
	public void setTimestamp(Timestamp timestamp) {
		this.timestamp=timestamp;
	}
	
	public String getMessageID() {
		return this.message_id;
	}
	
	public String getRatingID() {
		return this.rating_id;
	}
	public String getAnnotationID() {
		return this.annotation_id;
	}
	public int getStars() {
		return this.stars;
	}
	public Timestamp getTimestamp() {
		return this.timestamp;
	}
	
	
}
