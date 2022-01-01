import java.util.ArrayList;
import java.util.Arrays;

import org.junit.jupiter.api.Test;

import junit.framework.Assert;

@SuppressWarnings("deprecation")
public class TreeTest {
	
	@Test
	public <E> void testBST() {
		BinarySearchTree<Integer> integerTree = new BinarySearchTree<Integer>();
		integerTree.insert(1);
		integerTree.insert(2);
		integerTree.insert(3);
		integerTree.insert(7);
		integerTree.insert(5);
		integerTree.insert(6);
		integerTree.insert(8);
		
		ArrayList<Integer> list = integerTree.breadthFirstTraversal(integerTree.root);
		ArrayList<Integer> expectedResult = new ArrayList<Integer>(Arrays.asList(1, 2, 3, 7, 5, 8, 6));
		Assert.assertEquals(expectedResult, list);
		
		System.out.print(integerTree.height(integerTree.root));
		
		Assert.assertEquals(integerTree.height(integerTree.root), 5);
		
		System.out.print("\n");
		ArrayList<Integer> inorderList = integerTree.inorderTraversal(integerTree.root);
		ArrayList<Integer> inorderExpectedResult = new ArrayList<Integer>(Arrays.asList(1, 2, 3, 5, 6, 7, 8));
		Assert.assertEquals(inorderExpectedResult, inorderList);
		
		BinarySearchTree<String> stringTree = new BinarySearchTree<String>();
		stringTree.insert("Ed");
		stringTree.insert("Dave");
		stringTree.insert("Frank");
		stringTree.insert("Adam");
		stringTree.insert("Bob");
		stringTree.insert("Carl");
		stringTree.insert("Frank");
		stringTree.insert("George");
		stringTree.insert("Howard");
		
		System.out.print("\n");
		ArrayList<String> stringList = stringTree.breadthFirstTraversal(stringTree.root);
		ArrayList<String> expectedStringList = new ArrayList<String>(Arrays.asList("Ed", "Dave", "Frank", "Adam", "George", "Bob", "Howard", "Carl"));
		Assert.assertEquals(expectedStringList, stringList);
		
		Assert.assertEquals(stringTree.height(stringTree.root), 4);
		
		System.out.print("\n");
		ArrayList<String> inorderStringList = stringTree.inorderTraversal(stringTree.root);
		ArrayList<String> expectedInorderStringList = new ArrayList<String>(Arrays.asList("Adam", "Bob", "Carl", "Dave", "Ed", "Frank", "George", "Howard"));
		Assert.assertEquals(expectedInorderStringList, inorderStringList);
		
	}
}
