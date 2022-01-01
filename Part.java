package edu.sinclair;

import java.util.List;

public class Part {
	private String partNumber;
	private String name;
	private String partType;
	private float price;
	private List<PartBomEntry> billOfMaterial;
	

	public Part(String partNumber2) {
		this.partNumber = partNumber2;
	}

	public String getPartNumber() {
		return partNumber;
	}
	
	public void setPartNumber(String partNumber) {
		this.partNumber = partNumber;
	}
	
	public String getName() {
		return name;
	}
	
	public void setName(String name) {
		this.name = name;
	}
	
	public String getPartType() {
		return partType;
	}
	
	public void setPartType(String partType) {
		this.partType = partType;
	}
	
	public float getPrice() {
		return price;
	}
	
	public void setPrice(float price) {
		this.price = price;
	}
	
	public List<PartBomEntry> getBillOfMaterial() {
		return billOfMaterial;
	}
	
	public void setBillOfMaterial(List<PartBomEntry> billOfMaterial) {
		this.billOfMaterial = billOfMaterial;
	}
	
	@Override
	public boolean equals(Object o) {
		if (o == null)
			return false;
		if (getClass() != o.getClass())
			return false;
		Part other = (Part) o;
		if (partNumber == null) {
			if (other.partNumber != null)
				return false;
		} 
		if (!partNumber.equals(other.partNumber)) {
			return false;
		}		
		return true;		
	}
	
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((partNumber == null) ? 0 : partNumber.hashCode());
		return result;
	}
	
	@Override
	public String toString() {
		System.out.print(partNumber);
		return partNumber;
	}
}
