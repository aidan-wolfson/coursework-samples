// Aidan Wolfson - 20147339
package com.assignment1;

public class Politician extends Person {
	private String party;
	
	public Politician(String name, Date birthday, double difficulty, String party) {
		// Calling the super constructor
		super(name, birthday, difficulty);
		
		this.party = party;
	}
	
	// Copy constructor
	public Politician(Politician politician) {
		super(politician);
		
		this.party = politician.party;
	}
	
	public Politician clone() {
		return new Politician(this);
	}
	
	public String toString() {
		return super.toString() + ". They are a member of the " + party + " party.";
	}
	
	public String personType() {
		return "politician";
	}
}
