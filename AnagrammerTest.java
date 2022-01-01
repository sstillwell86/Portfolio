import java.util.ArrayList;
import java.util.List;

import org.apache.commons.cli.AnagramEvaluatorImpl;
import org.junit.jupiter.api.Test;

import junit.framework.Assert;

@SuppressWarnings("deprecation")
public class AnagrammerTest {
	AnagramEvaluatorImpl anagrammer = new AnagramEvaluatorImpl();
	List<String> permutationList = new ArrayList<>();
	
	@Test
	public void testAnagrammerWords() {
		permutationList = anagrammer.evaluate("DOG", "words");
		Assert.assertTrue(permutationList.size() == 2);
		Assert.assertEquals(permutationList.get(0),  "DOG");
		Assert.assertEquals(permutationList.get(1), "GOD");
	}
	
	@Test
	public void testAnagrammerNoFilter() {
		permutationList = anagrammer.evaluate("DOG", "nf");
		Assert.assertTrue(permutationList.size() == 6);
		Assert.assertEquals(permutationList.get(0), "DGO");
		Assert.assertEquals(permutationList.get(1), "DOG");
		Assert.assertEquals(permutationList.get(2), "GDO");
		Assert.assertEquals(permutationList.get(3), "GOD");
		Assert.assertEquals(permutationList.get(4), "ODG");
		Assert.assertEquals(permutationList.get(5), "OGD");
		
		permutationList = anagrammer.evaluate("GOODS",  "nf");
		Assert.assertTrue(permutationList.size()==60);
		
		permutationList = anagrammer.evaluate("WORKING", "nf");
		Assert.assertTrue(permutationList.size()==5040);
	}
}
