package edu.sinclair;

public class PartBomEntry {
	private String partNumber;
	private int quantity;
	
	public String getPartNumber() {
		return partNumber;
	}
	
	public void setPartNumber(String partNumber) {
		this.partNumber = partNumber;
	}
	
	public int getQuantity() {
		return quantity;
	}
	
	public void setQuantity(int quantity) {
		this.quantity = quantity;
	}
	
	@Override
	public String toString() {
		System.out.print(partNumber);
		return partNumber;
	}
	
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((partNumber == null) ? 0 : partNumber.hashCode());
		return result;
	}
	
	@Override
	public boolean equals(Object o) {
		if (o == null)
			return false;
		if (getClass() != o.getClass())
			return false;
		PartBomEntry other = (PartBomEntry) o;
		if (partNumber == null) {
			if (other.partNumber != null)
				return false;
		} 
		if (!partNumber.equals(other.partNumber)) {
			return false;
		}		
		return true;		
	}
}
