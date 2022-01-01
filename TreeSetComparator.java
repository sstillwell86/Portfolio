package edu.sinclair;

import java.io.Serializable;
import java.util.Comparator;

public class TreeSetComparator implements Comparator<String>, Serializable {
	private static final long serialVersionUID = -5603518161263484796L;

	@Override
	public int compare(String o1, String o2) {
		if (o1.equals(null)) {
			return 0;
		} 
		if (o2.equals(null)) {
			return 0;
		} else {
			return o1.compareTo(o2);
		}
	}
}
