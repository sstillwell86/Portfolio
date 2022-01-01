package edu.sinclair;

import java.util.ArrayList;
import java.util.Collections;

public class QuickSort {
	public static <T extends Comparable<T>> void quickSort(T[] list) {
		quickSort(list, 0, list.length - 1);
	}

	private static <T extends Comparable<T>> void quickSort(T[] list, int first, int last) {
		if (last > first) {
			//finds pivot based on median of first three array values, partitions them with lower values on left higher on right, and returns index of pivot
			int pivotIndex = partition(list, first, last);
			quickSort(list, first, pivotIndex - 1);
			quickSort(list, pivotIndex + 1, last);
		}
	}

	private static <T extends Comparable<T>> int partition(T[] list, int first, int last) {
		T pivot = null;
		System.out.print("\nList: ");
		for (int i = 0; i < last - first +1; i++) {
			System.out.print(list[first + i] + " ");
		}
		//if list has two elements or less, switch two elements if right element is less than left, no further logic needed, return
		if (last - first + 1 < 3) {
			pivot = list[first];
		} else {
			ArrayList<T> medianList = new ArrayList<T>();
			medianList.add(0, list[first]);
			medianList.add(1, list[first +1]);
			medianList.add(2, list[first +2]);
			Collections.sort(medianList);
			pivot = medianList.get(1);
		}
	    int low = first;
	    int high = last;

		while (high > low) {
			//looks at all values in array and compares them to pivot, moves to next if value is already lower than pivot
			while (low <= high && list[low].compareTo(pivot) < 0) {
				low++;
			}
			//looks at all values to the right of the new low value and finds one lower than the pivot
			while (low <= high && list[high].compareTo(pivot) > 0) {
				high--;
			}
			//switches the high and low value if they are out of order (low value is higher than pivot, high value is lower than pivot)
			if (high > low) {
				T temp = list[high];
				list[high] = list[low];
				list[low] = temp;
			}
		}
		//looks at all values of array from the right, moves on if already higher than pivot
		while (high > first && list[high].compareTo(pivot) > 0) {
			high--;
		}
			
		if (pivot.compareTo(list[high]) >= 0) {
			System.out.print("\nPivot: " + list[high]);
			return high;
		} else {
			System.out.print("\nPivot: " + list[first]);
			return first;
		}
	}
}