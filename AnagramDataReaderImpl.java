package org.apache.commons.cli;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class AnagramDataReaderImpl implements AnagramDataReader {
	Set<String> anagramData = new HashSet<String>();
	@Override
	public Set<String> readData() {
		
		File file = new File (System.getProperty("user.home") + File.separator + "sinclair" + File.separator + "anagram_data.txt");
		try {
			Scanner input = new Scanner(file);
			
			while (input.hasNextLine()) {
				anagramData.add(input.nextLine());
			}
			input.close();
		} catch (FileNotFoundException e1) {
			e1.printStackTrace();
		}
		return anagramData;
	}

}
