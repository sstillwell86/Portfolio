package edu.sinclair;

import java.io.File;
import java.io.FileNotFoundException;
import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import com.google.gson.Gson;

public class PartManagerImpl implements PartManager {
	private List<Part> partStore = new ArrayList<>();
	
	@Override
	public int importPartStore(String filePath) {
		String jsonData = null;
		File file = new File (filePath);
		try {
			Scanner input = new Scanner(file);
			StringBuilder storage = new StringBuilder();
			while (input.hasNextLine()) {
				storage.append(input.nextLine());
			}
			jsonData = storage.toString();
			input.close();
		} catch (FileNotFoundException e1) {
			e1.printStackTrace();
		}	
		Gson gson = new Gson();
		Part[] parts = gson.fromJson(jsonData, Part[].class);
		for (int i = 0; i < parts.length; i++) {
			partStore.add(parts[i]);
		}
		return parts.length;
	}

	@Override
	public Part costPart(String partNumber) {
		float totalPrice = costTotal(partNumber);
		totalPrice = roundForMoney(totalPrice);
		retrievePart(partNumber).setPrice(totalPrice);
		return retrievePart(partNumber);
	}
	
	public float costTotal(String partNumber) {
		Part part = retrievePart(partNumber);
		float totalCost = 0;
		if (part.getPrice() != 0.0F) {
			return retrievePart(partNumber).getPrice();
		}
		else {
			for (int i = 0; i < part.getBillOfMaterial().size(); i++) {
				totalCost += costTotal(part.getBillOfMaterial().get(i).getPartNumber()) * part.getBillOfMaterial().get(i).getQuantity();
			}
			return totalCost;
		}
	}
	
	@SuppressWarnings("deprecation")
	public float roundForMoney(final float value) {   
		return new BigDecimal(value).setScale(2, BigDecimal.ROUND_HALF_UP).floatValue(); 
	} 

	@Override
	public Part retrievePart(String partNumber) {
		int idx = partStore.indexOf(new Part(partNumber));
		final Part part;
		if (idx < 0) {
			part = null;
		} else {
			part = this.partStore.get(idx);
		}
		return part;
	}

	@Override
	public List<Part> getFinalAssemblies() {
		List<Part> finalAssemblies = new ArrayList<>();
		for (int i = 0; i < partStore.size(); i++) {
			if (partStore.get(i).getPartType().equals("ASSEMBLY")) {
				finalAssemblies.add(partStore.get(i));
			}
		}
		return finalAssemblies;
	}

	@Override
	public List<Part> getPurchasePartsByPrice() {
		List<Part> purchaseParts = new ArrayList<>();
		for (int i = 0; i < partStore.size(); i++) {
			if (partStore.get(i).getPartType().equals("PURCHASE")) {
				purchaseParts.add(partStore.get(i));
			}
		}
		PartComparatorByPrice priceComparator = new PartComparatorByPrice();
		purchaseParts.sort(priceComparator);
		return purchaseParts;
	}
}