package edu.sinclair;

import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import org.junit.Assert;

public class SortTest {
	Integer[] intList = {2,-3, 0, -4, 1};
	String[] stringList = {"doug", "adam", "nate", "steve", "jeff"};
	LinkedInUser[] userList = {new LinkedInUser("han", null), new LinkedInUser("luke", null), new LinkedInUser("leia", null), new LinkedInUser("chewie", null),
			new LinkedInUser("picard", null)};
	
	@Test
	public void testInsertionSort() {
		InsertionSort.<Integer>insertionSort(intList);
		Assert.assertTrue(intList[0] == -4 && intList[1] == -3 && intList[2] == 0 && intList[3] == 1 && intList[4] == 2);
		InsertionSort.<String>insertionSort(stringList);
		Assert.assertTrue(stringList[0].equals("adam") && stringList[1].equals("doug") && stringList[2].equals("jeff") && stringList[3].equals("nate") && stringList[4].equals("steve"));
		InsertionSort.<LinkedInUser>insertionSort(userList);
		Assert.assertTrue(userList[0].equals(new LinkedInUser("chewie", null)) && userList[1].equals(new LinkedInUser("han", null)) && 
				userList[2].equals(new LinkedInUser("leia", null)) && userList[3].equals(new LinkedInUser("luke", null)));
	}
	
	@Test
	public <T extends Comparable<T>> void testQuickSort() {
		List<Integer> intShuffle = new ArrayList<>();
		for (int i = 0; i < intList.length; i++) {
			intShuffle.add(intList[i]);
		}
		Collections.shuffle(intShuffle);
		for (int i = 0; i < intList.length; i++) {
			intList[i] = intShuffle.get(i);
		}
		System.out.print("\nQuickSort Integer Test:");
		QuickSort.<Integer>quickSort(intList);
		Assert.assertTrue(intList[0] == -4 && intList[1] == -3 && intList[2] == 0 && intList[3] == 1 && intList[4] == 2);
		
		List<String> stringShuffle = new ArrayList<>();
		for (int i = 0; i < stringList.length; i++) {
			stringShuffle.add(stringList[i]);
		}
		Collections.shuffle(stringShuffle);
		for (int i = 0; i < stringList.length; i++) {
			stringList[i] = stringShuffle.get(i);
		}
		System.out.print("\n\nQuickSort String Test:\n");
		QuickSort.<String>quickSort(stringList);
		Assert.assertTrue(stringList[0].equals("adam") && stringList[1].equals("doug") && stringList[2].equals("jeff") && stringList[3].equals("nate") && stringList[4].equals("steve"));
		
		List<LinkedInUser> userShuffle = new ArrayList<>();
		for (int i = 0; i < userList.length; i++) {
			userShuffle.add(userList[i]);
		}
		Collections.shuffle(userShuffle);
		for (int i = 0; i < userList.length; i++) {
			userList[i] = userShuffle.get(i);
		}
		System.out.print("\n\nQuickSort LinkedInUser Test:\n");
		QuickSort.<LinkedInUser>quickSort(userList);
		Assert.assertTrue(userList[0].equals(new LinkedInUser("chewie", null)) && userList[1].equals(new LinkedInUser("han", null)) && 
				userList[2].equals(new LinkedInUser("leia", null)) && userList[3].equals(new LinkedInUser("luke", null)));
	}
}
