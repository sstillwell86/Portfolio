package edu.sinclair;

import java.util.Comparator;

public class LinkedInUserComparatorByType implements Comparator<LinkedInUser> {

	@Override
	public int compare(LinkedInUser user1, LinkedInUser user2) {
		if (user1.getType().equals(user2.getType())) {
			return user1.compareTo(user2);
		} else {
			return user1.getType().compareTo(user2.getType());
		}
	}
}
