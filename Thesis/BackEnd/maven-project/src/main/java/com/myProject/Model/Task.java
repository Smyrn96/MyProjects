package com.myProject.Model;

import java.sql.Timestamp;
import java.util.UUID;

public class Task {
	private String taskCreator;
	private String taskName;
	private String taskID;
	private String taskDescription;
	private String attackers_description;
	private String defenders_description;
	private String category;
	private String attackers_hints;
	private String defenders_hints;
	private int max_messages;
	private Timestamp date;
	private boolean active;
	
	public Task() {
		
	}
	
	public Task(String taskName,String taskDescription,String attackers_description, String defenders_description,String category,String attackers_hints,String defenders_hints,int max_messages) {
		this.taskName=taskName;
		this.taskID=("#" + UUID.randomUUID().toString()).substring(0,7);
		this.taskDescription=taskDescription;
		this.attackers_description=attackers_description;
		this.defenders_description=defenders_description;
		this.category=category;
		this.attackers_hints=attackers_hints;
		this.defenders_hints=defenders_hints;
		this.max_messages=max_messages;
	}
	
	public void setTaskID(String taskID) {
		this.taskID=taskID;
	}
	public void setTaskName(String taskName) {
		this.taskName=taskName;
	}
	public String getTaskName() {
		return this.taskName;
	}
	
	
	public void setTaskCreator(String taskCreator) {
		this.taskCreator=taskCreator;
	}
	public String getTaskCreator() {
		return this.taskCreator;
	}
	public void setTimestamp(Timestamp date) {
		this.date=date;
	}
	public Timestamp getTimestamp() {
		return this.date ;
	}
	
	public String getTaskID() {
		return this.taskID;
	}
	public void setTaskDescription(String taskDescription) {
		this.taskDescription=taskDescription;
	}
	public String getTaskDescription() {
		return this.taskDescription;
	}
	public void setAttackersDescription(String attackers_description) {
		this.attackers_description=attackers_description;
	}
	public String getAttackersDescription() {
		return this.attackers_description;
	}
	public void setDefendersDescription(String defenders_description) {
		this.defenders_description=defenders_description;
	}
	public String getDefendersDescription() {
		return this.defenders_description;
	}
	public void setCategory(String category) {
		this.category=category;
	}
	public String getCategory() {
		return this.category;
	}
	public void setAttackerHints(String attackers_hints) {
		this.attackers_hints=attackers_hints;
	}
	public String getAttackerHints() {
		return this.attackers_hints;
	}
	public void setDefenderHints(String defenders_hints) {
		this.defenders_hints=defenders_hints;
	}
	public String getDefenderHints() {
		return this.defenders_hints;
	}
	public void setMaxMessages(int max_messages) {
		this.max_messages=max_messages;
	}
	public int getMaxMessages() {
		return this.max_messages;
	}
	public void setActive(boolean active) {
		this.active=active;
	}
	public boolean getActive() {
		return this.active;
	}
}
