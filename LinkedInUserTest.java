package edu.sinclair;

import static org.junit.jupiter.api.Assertions.assertThrows;

import java.util.List;

import org.junit.Assert;
import org.junit.Test;

public class LinkedInUserTest {
	
	@Test
	public void testConnections() throws LinkedInException {
		LinkedInUser user1 = new LinkedInUser("han", null);
		LinkedInUser user2 = new LinkedInUser("luke", null);
		LinkedInUser user3 = new LinkedInUser("leia", null);
		user1.addConnection(user2);
		user1.addConnection(user3);
		Assert.assertEquals(user1.getConnections().size(), 2);
		Assert.assertTrue(user1.getConnections().contains(user2));
		Assert.assertTrue(user1.getConnections().contains(user3));
		user1.removeConnection(user2);
		Assert.assertEquals(user1.getConnections().size(), 1);
		Assert.assertTrue(user1.getConnections().contains(user3));
	}
	
	@Test
	public void testType() {
		LinkedInUser user1 = new LinkedInUser("Chewie", null);
		user1.setType("P");
		Assert.assertEquals(user1.getType(), "P");
	}
	
	@Test
	public void testAddConnection() throws LinkedInException {
		LinkedInUser user1 = new LinkedInUser("han", null);
		LinkedInUser user2 = new LinkedInUser("luke", null);
		user1.addConnection(user2);
		LinkedInException exception = assertThrows(LinkedInException.class, () -> user1.addConnection(user2));
		Assert.assertEquals("You are already connected with this user", exception.getMessage());
	}
	
	@Test
	public void testRemoveConnection() throws LinkedInException {
		LinkedInUser user1 = new LinkedInUser("han", null);
		LinkedInUser user2 = new LinkedInUser("luke", null);
		LinkedInUser user3 = new LinkedInUser("leia", null);
		user1.addConnection(user2);
		LinkedInException exception = assertThrows(LinkedInException.class, () -> user1.removeConnection(user3));
		Assert.assertEquals("You are NOT connected with this user", exception.getMessage());
	}
	
	@Test
	public void testSort() throws LinkedInException {
		LinkedInUser user1 = new LinkedInUser("Han", null);
		LinkedInUser user2 = new LinkedInUser("LUKE", null);
		LinkedInUser user3 = new LinkedInUser("leia", null);
		user1.addConnection(user2);
		user1.addConnection(user3);
		List<LinkedInUser> connections = user1.getConnections();
		java.util.Collections.sort(connections);
		Assert.assertEquals(connections.get(0), user3);
		Assert.assertEquals(connections.get(1), user2);
	}
}
