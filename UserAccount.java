package edu.sinclair;

import java.io.Serializable;

public abstract class UserAccount implements Serializable {
	
	private static final long serialVersionUID = -7687530926191311692L;
	private String username;
	private String password;
	
	public UserAccount(String username, String password) {
		super();
		this.username = username;
		this.password = password;
	}
	public String getUsername() {
		return username;
	}
	public boolean isPasswordCorrect(String password) {
		return this.password == null ? false : this.password.equals(password);
	}
	@Override
	public String toString() {
		System.out.print(username);
		return username;
	}
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((username == null) ? 0 : username.hashCode());
		return result;
	}
	@Override
	public boolean equals(Object o) {
		if (this == o)
			return true;
		if (o == null)
			return false;
		if (getClass() != o.getClass())
			return false;
		UserAccount other = (UserAccount) o;
		if (username == null) {
			if (other.username != null)
				return false;
		} 
		if (!username.equals(other.username)) {
			return false;
		}		
		return true;		
	}
	
	public abstract void setType(String type);
}
