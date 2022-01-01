package org.apache.commons.cli;

import java.util.Set;

public interface AnagramDataReader {
	/**  * Returns a Set containing all words read from the anagram data text file.  * 
	 *  * @return the Set or empty Set if no words are found.  */ 
	Set<String> readData();
}
