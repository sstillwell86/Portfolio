package edu.sinclair;

import java.util.Comparator;

public class LinkedInUserComparatorByConnections implements Comparator<LinkedInUser> {

	@Override
	public int compare(LinkedInUser user1, LinkedInUser user2) {
		if (user1.getConnections().size() < user2.getConnections().size()) {
			return 1;
		} if (user1.getConnections().size() == user2.getConnections().size()) {
			return user1.compareTo(user2);
		} if (user1.getConnections().size() > user2.getConnections().size()) {
			return -1;
		}
		return 0;
	}

}
