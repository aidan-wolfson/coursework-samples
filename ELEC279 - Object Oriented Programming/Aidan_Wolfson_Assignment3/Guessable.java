// Aidan Wolfson 20147339
package com.assignment1;

public interface Guessable extends Comparable<Person> {
	
	public String startMessage();
	
	public String closingMessage();
	
	public int getAwardedPointNumber();
	
}
