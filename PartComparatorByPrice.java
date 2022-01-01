package edu.sinclair;

import java.util.Comparator;

public class PartComparatorByPrice implements Comparator<Part> {

	@Override
	public int compare(Part part1, Part part2) {
		if (part1.getPrice() < part2.getPrice()) {
			return 1;
		} if (part1.getPrice() == part2.getPrice()) {
			return 0;
		} if (part1.getPrice() > part2.getPrice()) {
			return -1;
		}
		return 0;
	}

}
