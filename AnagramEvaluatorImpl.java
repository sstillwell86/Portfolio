package org.apache.commons.cli;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class AnagramEvaluatorImpl implements AnagramEvaluator {

	//from https://introcs.cs.princeton.edu/java/23recursion/Permutations.java.html 
	//recursively adds one letter from the string then the rest, cycling through all combinations
	public void permutation(String prefix, String str, Set<String> permutationSet) {
	    int n = str.length();
	    if (n == 0) permutationSet.add(prefix);
	    else {
	        for (int i = 0; i < n; i++)
	            permutation(prefix + str.charAt(i), str.substring(0, i) + str.substring(i+1, n), permutationSet);
	    }
	} // end of borrowed code
	
	@Override
	public List<String> evaluate(String anagram, String option) {
		
		Set<String> permutationSet = new HashSet<>();
		permutation("", anagram, permutationSet);
		
		List<String> permutationList = new ArrayList<>();
		permutationList.addAll(permutationSet);
		permutationList.sort(null);
		
		if (option.equals("nf")) {
			for (int i=0; i<permutationList.size(); i++) {
				System.out.print(permutationList.get(i) + "\n");
			}
			System.out.print("\n-- " + permutationList.size() + " value(s) found");
			return permutationList;
		}
		
		AnagramDataReaderImpl anagramDataReader = new AnagramDataReaderImpl();
		Set<String> anagramData = anagramDataReader.readData();
		if (option.equals("words")) {
			for (int i =0; i < permutationList.size(); i++) {
				if (anagramData.contains(permutationList.get(i))) {
					System.out.print(permutationList.get(i) + "\n");
				} else {
					permutationList.remove(i);
					i--;
				}
			}
			System.out.print("\n-- " + permutationList.size() + " value(s) found");
			return permutationList;
		}
		return null;
	}
}
