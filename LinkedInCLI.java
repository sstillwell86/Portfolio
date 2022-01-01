package edu.sinclair;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.Stack;

public class LinkedInCLI {
	
	private List<LinkedInUser> ignore = new ArrayList<>();
	private List<LinkedInUser> path = new ArrayList<>();
	private List<LinkedInUser> users;
	private Stack<String> actionHistory = new Stack<String>();
	private Stack<LinkedInUser> actionHistoryTarget = new Stack<LinkedInUser>();
	private LinkedInUser loggedInUser;
	private static final String PATH = System.getProperty("user.home") + File.separator + "sinclair" + File.separator;
	private static final String FILE_NAME = "LinkedInUsers.dat";
	
	public LinkedInCLI() {
		users = new ArrayList<>();
	}
	
	@SuppressWarnings("unchecked")
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		LinkedInCLI linkedInCLI = new LinkedInCLI();
		File file = new File (PATH + FILE_NAME);
		if (file.exists()) {
			try (
					FileInputStream fis = new FileInputStream(file);
					ObjectInputStream objectInput = new ObjectInputStream(fis);
					) {
					  do {
						  linkedInCLI.users = (List<LinkedInUser>)objectInput.readObject();					   
					  } while (objectInput.available() > 0);				  
					} catch (ClassNotFoundException e) {
						e.printStackTrace();
					} catch (IOException e) {
						e.printStackTrace();
					}	
		}
		int menuChoice = linkedInCLI.getMenuChoice(input);
		do {
			if (menuChoice < 1 || menuChoice > 16) {
				System.out.print("Please enter a valid menu choice.");
				menuChoice = linkedInCLI.getMenuChoice(input);
			}
			if (menuChoice == 1) {
				linkedInCLI.listUsers();
				menuChoice = linkedInCLI.getMenuChoice(input);
			}
			if (menuChoice == 2) {
				linkedInCLI.sortByConnections();
				menuChoice = linkedInCLI.getMenuChoice(input);
			}
			if (menuChoice == 3) {
				linkedInCLI.sortByType();
				menuChoice = linkedInCLI.getMenuChoice(input);
			}
			if (menuChoice == 4) {
				linkedInCLI.addUser(input, linkedInCLI);
				menuChoice = linkedInCLI.getMenuChoice(input);
			}
			if (menuChoice == 5) {
				linkedInCLI.deleteUser(input, linkedInCLI);
				menuChoice = linkedInCLI.getMenuChoice(input);
			}
			if (menuChoice == 6) {
				linkedInCLI.whoAmI();
				menuChoice = linkedInCLI.getMenuChoice(input);
			}
			if (menuChoice == 7) {
				linkedInCLI.listConnections();
				menuChoice = linkedInCLI.getMenuChoice(input);
			}
			if (menuChoice == 8) {
				linkedInCLI.addConnection(input, linkedInCLI);
				menuChoice = linkedInCLI.getMenuChoice(input);
			}
			if (menuChoice == 9) {
				linkedInCLI.removeConnection(input, linkedInCLI);
				menuChoice = linkedInCLI.getMenuChoice(input);
			}
			if (menuChoice == 10) {
				if (linkedInCLI.loggedInUser.getConnections().isEmpty()) {
					System.out.print("\nYou are not connected to any users.\n");
				} else {
					System.out.print("\nEnter a username:\n");
					String username = input.nextLine();
					if (linkedInCLI.findUser(username).equals(linkedInCLI.loggedInUser)) {
						System.out.print("\nYOU are " + username + ".\n");
					} else {
						int degreeOfSeparation = linkedInCLI.degreeOfSeparation(linkedInCLI.ignore, linkedInCLI.loggedInUser, username, linkedInCLI.path);
						degreeOfSeparation--;
						if (degreeOfSeparation == -1) {
							System.out.print("\nNo connections were found to that user.\n");
						} else {
							System.out.print("\nThere is " + degreeOfSeparation + " degrees of separation between you and " + username + "\n");
							System.out.print(linkedInCLI.loggedInUser.getUsername());
							for (int i = 0; i < linkedInCLI.path.size(); i++) {
								System.out.print(" -> " + linkedInCLI.path.get(i).getUsername());
							}
							System.out.print("\n");
							linkedInCLI.path.clear();
						}
					}			
				}
				menuChoice = linkedInCLI.getMenuChoice(input);
			}
			if (menuChoice == 11) {
				linkedInCLI.addSkill(input);
				menuChoice = linkedInCLI.getMenuChoice(input);
			}
			if (menuChoice == 12) {
				linkedInCLI.removeSkill(input);
				menuChoice = linkedInCLI.getMenuChoice(input);
			}
			if (menuChoice == 13) {
				linkedInCLI.listSkills();
				menuChoice = linkedInCLI.getMenuChoice(input);
			}
			if (menuChoice == 14) {
				linkedInCLI.undo(input, linkedInCLI);
				menuChoice = linkedInCLI.getMenuChoice(input);
			}
			if (menuChoice == 15) {
				linkedInCLI.signOff();
				menuChoice = linkedInCLI.getMenuChoice(input);
			}
			if (menuChoice == 16) {
				input.close();
				linkedInCLI.quit();
			}			
		} while (menuChoice != 16);
	}
	// EXPLANATION
	// I used two stacks, one to hold the action performed and one to hold the linkedInUser object it was performed on 
	//(since I'm not comfortable searching a string for a specific word). Stacks seemed the most efficient since I'm only concerned with the last value added,
	//and I can simply pop the stack the last time I need the value in the stack returned, saving a line of code.
	private void undo(Scanner input, LinkedInCLI linkedInCLI) {
		if (actionHistory.isEmpty()) {
			System.out.print("\nThere are no actions to undo.");
		} else {
			System.out.print("\nThe last menu option selected was " + actionHistory.get(actionHistory.size()-1) + " involving " +
		actionHistoryTarget.get(actionHistoryTarget.size()-1) + ". Undo(Y/N)\n");
			String undo = input.nextLine();
			if (undo.equals("Y")) {
				if (actionHistory.peek().equals("Sign up a New User")) {
					System.out.print(actionHistoryTarget.peek() + " was removed from users.\n");
					users.remove(actionHistoryTarget.pop());
				}
				if (actionHistory.peek().equals("Delete a User")) {
					System.out.print(actionHistoryTarget.peek() + " was added to users.\n");
					users.add(actionHistoryTarget.pop());
				}
				if (actionHistory.peek().equals("Add Connection")) {
					System.out.print(actionHistoryTarget.peek() + " was removed from connections.\n");
					try {
						loggedInUser.removeConnection(actionHistoryTarget.pop());
					} catch (LinkedInException e) {
						e.printStackTrace();
					}
				}
				if (actionHistory.peek().equals("Remove Connection")) {
					System.out.print(actionHistoryTarget.peek() + " was added to connections.\n");
					try {
						loggedInUser.addConnection(actionHistoryTarget.pop());
					} catch (LinkedInException e) {
						e.printStackTrace();
					}
				}
				actionHistory.pop();
			}
		}		
	}

	private void listSkills() {
		System.out.print("\n");
		for (String string : loggedInUser.getSkillset()) {
			System.out.println(string);
		}
		
	}

	private void removeSkill(Scanner input) {
		System.out.print("Enter the skill to remove: ");
		String skill = input.nextLine();
		try {
			loggedInUser.removeSkill(skill);
		} catch (LinkedInException e) {
			e.printStackTrace();
		}
	}

	private void addSkill(Scanner input) {
		System.out.print("Enter the skill to add: ");
		String skill = input.nextLine();
		loggedInUser.addSkill(skill);
	}

	private void sortByConnections() {
		LinkedInUserComparatorByConnections connectionsComparator = new LinkedInUserComparatorByConnections();
		users.sort(connectionsComparator);
		System.out.print("\n");
		for (int i = 0; i < users.size(); i++) {
			System.out.print(users.get(i).getUsername() + "; connection size = " + users.get(i).getConnections().size() + "\n");
		}	
	}

	private void sortByType() {
		LinkedInUserComparatorByType typeComparator = new LinkedInUserComparatorByType();
		users.sort(typeComparator);
		System.out.print("\n");
		for (int i = 0; i < users.size(); i++) {
			System.out.print(users.get(i).getUsername() + "; type = " + users.get(i).getType() + "\n");
		}		
	}

	private int degreeOfSeparation(List<LinkedInUser> ignore, LinkedInUser user, String username, List<LinkedInUser> path) {
		int separationDegree = 0;
		if (user.getConnections().isEmpty()) {
			path.remove(user);
			return separationDegree;
		}
		if (user.getConnections().contains(findUser(username))) {
			path.add(findUser(username));
			separationDegree++;
			return separationDegree;
		}
		for (int i = 0; i < user.getConnections().size(); i++) {
			if (ignore.contains(user.getConnections().get(i))) {
				continue;
			} else {
				ignore.add(user.getConnections().get(i));
				path.add(user.getConnections().get(i));
				separationDegree++;
				if (user.getConnections().contains(findUser(username))) {
					return separationDegree;
				} else {
					separationDegree = separationDegree + degreeOfSeparation(ignore, user.getConnections().get(i), username, path);
					return separationDegree;
				}
			}		
		}
		return separationDegree;		
	}
	
	private void listConnections() {
		if (loggedInUser.getConnections().isEmpty()) {
			System.out.print("\nYou are not connected to any users.\n");
		} else {
			System.out.print("\n");
			for (int i = 0; i < loggedInUser.getConnections().size(); i++) {
				System.out.print(loggedInUser.getConnections().get(i).getUsername() + "\n");
			}
		}		
	}
	
	private void removeConnection(Scanner input, LinkedInCLI linkedInCLI) {
		if (loggedInUser.getConnections().isEmpty()) {
			System.out.print("\nYou are not connected to any users.\n");
		}
		System.out.print("\nEnter the username of the connection to be removed:\n");
		String username = input.nextLine();
		if (findUser(username) == null) {
			System.out.print("User does not exist.");
		}
		if (loggedInUser.getConnections().indexOf(new LinkedInUser(username, "")) < 0) {
			System.out.print("\nYou are not connected to that user.\n");
		} else {
			try {
				loggedInUser.removeConnection(new LinkedInUser(username, ""));
				actionHistory.add("Remove Connection");
				actionHistoryTarget.add(linkedInCLI.findUser(username));
			} catch (LinkedInException e) {
				e.printStackTrace();
			}
		}
	}
	
	private void addConnection(Scanner input, LinkedInCLI linkedInCLI) {
		System.out.print("\nEnter the user's name:\n");
		String username = input.nextLine();
		if (findUser(username) == null) {
			System.out.print("User does not exist.\n");
		} else {
			try {
				loggedInUser.addConnection(findUser(username));
				actionHistory.add("Add Connection");
				actionHistoryTarget.add(linkedInCLI.findUser(username));
			} catch (LinkedInException e) {
				e.printStackTrace();
			}
		}
	}
	
	private void signOff() {
		loggedInUser = null;
		actionHistory.removeAllElements();
		actionHistoryTarget.removeAllElements();
		System.out.print("\n");
	}

	private void whoAmI() {
		System.out.print("\n" + loggedInUser.getUsername() + "\n" + loggedInUser.getType() + "\n");
	}

	private LinkedInUser findUser(String username) {
		int idx = users.indexOf(new LinkedInUser(username, ""));
		final LinkedInUser user;
		if (idx < 0) {
			user = null;
		} else {
			user = this.users.get(idx);
		}
		return user;
	}
	
	private void deleteUser(Scanner input, LinkedInCLI linkedInCLI) {
		System.out.print("\nEnter the name of user to delete\n");
		String username = input.nextLine();
		if (findUser(username) != null) {
			System.out.print("\nEnter the user's password\n");
			String password = input.nextLine();
			if (findUser(username).isPasswordCorrect(password)) {
				users.remove(findUser(username));
				actionHistory.add("Delete a User");
				actionHistoryTarget.add(linkedInCLI.findUser(username));
				if (findUser(username).equals(loggedInUser)) {
					loggedInUser = null;
				}
			} else {
				System.out.print("\nIncorrect password.\n");
			}
		} else {
			System.out.print("\nUser does not exist.\n");
		}
	}

	private void addUser(Scanner input, LinkedInCLI linkedInCLI) {
		System.out.print("\nEnter a username\n");
		String username = input.nextLine();
		if (findUser(username) == null) {
			System.out.print("\nEnter a password\n");
			String password = input.nextLine();
			System.out.print("\nEnter the type of user (P or S)\n");
			String type = input.nextLine();
			while (type.equals("P") != true && type.equals("S") != true) {
				System.out.print("\n\nPlease enter a valid type.\nEnter the type of user (P or S)\n");
				type = input.nextLine();
			}
			LinkedInUser user = new LinkedInUser(username, password);
			user.setType(type);
			users.add(user);
			actionHistory.add("Sign up a New User");
			actionHistoryTarget.add(linkedInCLI.findUser(username));
		} else {
			System.out.print("\nUser already exists.\n");
		}		
	}

	private void listUsers() {
		users.sort(null);
		System.out.print("\n");
		for (int i = 0; i < users.size(); i++) {
			System.out.print(users.get(i).getUsername() + "\n");
		}
	}

	public int getMenuChoice(Scanner input) {	
		if (users.size() == 0) {	
			System.out.print("There are no users in the system. Please establish a root user and password\n\nUsername:\n");
			String username = input.nextLine();
			System.out.print("\nPassword:\n");
			String password = input.nextLine();
			loggedInUser = new LinkedInUser(username, password);
			loggedInUser.setType("P");
			setLoggedInUser(loggedInUser);
			users.add(getLoggedInUser());	
		} else while (loggedInUser == null) {		
			System.out.print("Please login to continue\n\nuser name:\n");
			String username = input.nextLine();
			System.out.print("\npassword:\n");
			String password = input.nextLine();
			if (findUser(username) == null) {
				System.out.print("\n\nThere is no user with that user name.\n\n");	
			} else {
				if (findUser(username).isPasswordCorrect(password)) {
					setLoggedInUser(findUser(username));
					showMenu();
					String menuChoice = input.nextLine();
					try {
						return Integer.parseInt(menuChoice);
					} catch (NumberFormatException nfe) {
						return 0;
					}
					
				} else {
					System.out.print("\n\nPassword mismatch\n\n");
				}	
			}
		}
		showMenu();
		String menuChoice = input.nextLine();
		try {
			return Integer.parseInt(menuChoice);
		} catch (NumberFormatException nfe) {
			return 0;
		}
	}
	
	public void showMenu() {
		System.out.print("\nWelcome " + loggedInUser.getUsername() + "\n1. List all Users Alphabetically\n2. List Users by Number of Connections"
				+ "\n3. List Users by Type\n4. Sign up a New User\n5. Delete a User\n6. Who am I"
				+ "\n7. List Connections\n8. Add Connection\n9. Remove Connection\n10. Degree of Separation\n11. Add Skillset\n12. Remove Skillset\n13. List Skillsets"
				+ "\n14. Undo\n15. Sign off\n16. Quit\n" );	
	}
	
	public void quit() {
		File file = new File (PATH + FILE_NAME);
		if (file.exists()) {
			file.delete();
		}
		new File(PATH).mkdirs();
		try (FileOutputStream fos = new FileOutputStream(PATH + FILE_NAME);
				ObjectOutputStream oos = new ObjectOutputStream(fos);){
			oos.writeObject(this.users);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		System.out.print("\nGoodbye");
		System.exit(0);
	}

	public List<LinkedInUser> getUsers() {
		return users;
	}

	public void setUsers(List<LinkedInUser> users) {
		this.users = users;
	}

	public LinkedInUser getLoggedInUser() {
		return loggedInUser;
	}

	public void setLoggedInUser(LinkedInUser loggedInUser) {
		this.loggedInUser = loggedInUser;
	}
}