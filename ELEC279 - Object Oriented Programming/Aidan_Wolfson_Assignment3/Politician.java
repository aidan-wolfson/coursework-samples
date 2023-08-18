// Aidan Wolfson - 20147339
package com.assignment1;

public class Politician extends Person {
	private String party;
	
	public Politician(String name, Date birthday, String party) {
		// Calling the super constructor
		super(name, birthday);
		
		this.party = party;
	}
	
	public Politician clone() {
		Politician newPolitician = (Politician) super.clone();
		return newPolitician;
	}
	
	public String toString() {
		return super.toString() + ". They are a member of the " + party + " party.";
	}
	
	public String personType() {
		return "politician";
	}
}
