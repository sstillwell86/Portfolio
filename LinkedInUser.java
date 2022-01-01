package edu.sinclair;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;
import java.util.TreeSet;

public class LinkedInUser extends UserAccount implements Comparable<LinkedInUser>, Serializable {

	private static final long serialVersionUID = -3072603701327940326L;
	private String type;
	private List<LinkedInUser> connections = new ArrayList<>();
	private TreeSet<String> skillset = new TreeSet<>(new TreeSetComparator());
	//EXPLANATION
	//I used a TreeSet to store the skillset since it's elements are automatically sorted according to their natural order.

	
	public LinkedInUser(String username, String password) {
		super(username, password);
	}

	@Override
	public void setType(String type) {	
		this.type = type;
	}
	
	public String getType() {
		return type;
	}
	
	public void addSkill(String skill) {
		skillset.add(skill);
	}	
	
	public void removeSkill(String skill) throws LinkedInException {
		if (skillset.contains(skill)) {
			skillset.remove(skill);
		} else {
			throw new LinkedInException("That skill isn't in your skillset.");
		}
	}
	
	public void addConnection(LinkedInUser user) throws LinkedInException {
		int index = connections.indexOf(user); 
		if (index < 0) {
			connections.add(user);
		}
		else {
			throw new LinkedInException("You are already connected with this user");
		}
	}
	
	public void removeConnection(LinkedInUser user) throws LinkedInException {
		int index = connections.indexOf(user);
		if (index < 0) {
			throw new LinkedInException("You are NOT connected with this user");
		}
		else {
			connections.remove(index);
		}
	}
	
	public List<LinkedInUser> getConnections() {
		return new ArrayList<>(connections);
	}

	@Override
	public int compareTo(LinkedInUser o) {
		String user1 = this.getUsername();
		String user2 = o.getUsername();
		int rc = user1.compareToIgnoreCase(user2);
		return rc;
	}

	public TreeSet<String> getSkillset() {
		return new TreeSet<>(skillset);
	}

	public void setSkillset(TreeSet<String> skillset) {
		this.skillset = skillset;
	}
	
	public void readObject(ObjectInputStream in) throws IOException, ClassNotFoundException {
		this.skillset = new TreeSet<>(new TreeSetComparator());
		in.defaultReadObject();
	}
	
	public String toString() {
		return getUsername();
	}
}
