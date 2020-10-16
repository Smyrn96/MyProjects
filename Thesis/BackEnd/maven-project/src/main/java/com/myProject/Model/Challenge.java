package com.myProject.Model;

public class Challenge {
	
	private String challengeID;
	private String description;
	private float progress;
	private float max_progress;
	private String badge_id;
	private int reward_points;
	private String user_id;
	private boolean daily;
	private String category;
	
	public Challenge(){}
	
	public Challenge(String description,int progress,int max_progress,String badge_id,int reward_points){
		this.description=description;
		this.progress=progress;
		this.max_progress=max_progress;
		this.badge_id=badge_id;
		this.reward_points=reward_points;
	}
	
	public void setUserID(String user_id) {
		this.user_id=user_id;
	}
	
	public String getUserID() {
		return this.user_id;
	}
	
	public void setCategory(String category) {
		this.category=category;
	}
	
	public String getCategory() {
		return this.category;
	}
	
	
	public void setChallengeID(String challengeID) {
		this.challengeID=challengeID;
	}
	
	public String getChallengeID() {
		return this.challengeID;
	}
	
	public void setDescription(String description) {
		this.description=description;
	}
	
	public String getDescription() {
		return this.description;
	}
	
	public void setProgress(float f) {
		this.progress=f;
	}
	
	public float getProgress() {
		return this.progress;
	}
	
	public void setMaxProgress(float max_progress){
		this.max_progress=max_progress;
	}
	
	public float getMaxProgress() {
		return this.max_progress;
	}
	
	public void setBadgeReward(String badge_id) {
		this.badge_id=badge_id;
	}
	
	public String getBadgeReward() {
		return this.badge_id;
	}

	public void setRewardPoints(int reward_points) {
		this.reward_points=reward_points;
	}
	
	public int getRewardPoints() {
		return this.reward_points;
	}
	
	public boolean isDaily(){
		return this.daily;
	}
	
	public void setDaily(boolean daily) {
		this.daily=daily;
	}
	
	
}

