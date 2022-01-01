package edu.sinclair;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

import org.junit.Assert;
import org.junit.Test;

public class PartManagerImplTest {
	
	@Test
	public void testImportPartStore() {
		PartManagerImpl manager = new PartManagerImpl();
		Assert.assertTrue(manager.importPartStore(System.getProperty("user.home") + File.separator + "sinclair" + File.separator + "bom.json") > 0);
	}
	
	@Test
	public void testCostPart() {
		PartManagerImpl manager = new PartManagerImpl();
		manager.importPartStore(System.getProperty("user.home") + File.separator + "sinclair" + File.separator + "bom.json");
		System.out.print(manager.costTotal("290B7266J1"));
		manager.costPart("50-0083");
		Assert.assertTrue(manager.retrievePart("50-0083").getPrice() == 1.11F);
		manager.costPart("20-0015");
		Assert.assertTrue(manager.retrievePart("20-0015").getPrice() == 70.46F);
		manager.costPart("20-0001");
		Assert.assertTrue(manager.retrievePart("20-0001").getPrice() == 96.39F);
		manager.costPart("290B7266J6");
		Assert.assertTrue(manager.retrievePart("290B7266J6").getPrice() == 334.10F);
		manager.costPart("290B7266J2");
		Assert.assertTrue(manager.retrievePart("290B7266J2").getPrice() == 532.20F);
		manager.costPart("290B7266J1");
		Assert.assertTrue(manager.retrievePart("290B7266J1").getPrice() == 415.16F);
		
	}
	
	@Test
	public void testCostTotal() {
		PartManagerImpl manager = new PartManagerImpl();
		manager.importPartStore(System.getProperty("user.home") + File.separator + "sinclair" + File.separator + "bom.json");
		Assert.assertTrue(manager.costTotal("50-0083") == 1.11F);
	}	

	
	@Test
	public void testRoundForMoney() {
		PartManagerImpl manager = new PartManagerImpl();
		manager.importPartStore(System.getProperty("user.home") + File.separator + "sinclair" + File.separator + "bom.json");
		Assert.assertTrue(manager.roundForMoney((float) 12.005F) == 12.01F);
		Assert.assertTrue(manager.roundForMoney((float) 12.001F) == 12.00F);
	}
	
	@Test
	public void testRetrievePart() {
		PartManagerImpl manager = new PartManagerImpl();
		manager.importPartStore(System.getProperty("user.home") + File.separator + "sinclair" + File.separator + "bom.json");
		Assert.assertTrue(manager.retrievePart("50-0083").getPartType().equals("PURCHASE"));
		Assert.assertTrue(manager.retrievePart("50-0083").getPrice() == 1.11F);
		Assert.assertTrue(manager.retrievePart("50-0083").getName().equals("Hook & Loop (Velcro), Black, 2\" wide"));
		Assert.assertTrue(manager.retrievePart("38274") == null);
	
	}
	
	@Test
	public void testGetFinalAssemblies() {
		PartManagerImpl manager = new PartManagerImpl();
		manager.importPartStore(System.getProperty("user.home") + File.separator + "sinclair" + File.separator + "bom.json");
		List<Part> finalAssemblies = new ArrayList<>();
		finalAssemblies = manager.getFinalAssemblies();
		boolean isCorrect = true;
		for (int i = 0; i < finalAssemblies.size(); i++) {
			if (!finalAssemblies.get(i).getPartType().equals("ASSEMBLY")) {
				isCorrect = false;
			}	
		}
		Assert.assertTrue(isCorrect);
	}
	
	@Test
	public void testGetPurchasePartsByPrice() {
		PartManagerImpl manager = new PartManagerImpl();
		manager.importPartStore(System.getProperty("user.home") + File.separator + "sinclair" + File.separator + "bom.json");
		List<Part> purchaseParts = new ArrayList<>();
		purchaseParts = manager.getPurchasePartsByPrice();
		boolean isCorrect = true;
		for (int i = 0; i < purchaseParts.size(); i++) {
			if (!purchaseParts.get(i).getPartType().equals("PURCHASE")) {
				isCorrect = false;
			}
		}
		Assert.assertTrue(isCorrect);
		for (int i = 0; i < (purchaseParts.size() - 1); i++) {
			if (purchaseParts.get(i).getPrice() < purchaseParts.get(i+1).getPrice()) {
				isCorrect = false;
			}
		}
		Assert.assertTrue(isCorrect);
	}
}
