// Aidan Wolfson 20147339
package com.assignment1;

public class GuessablePerson<T extends Person> implements Guessable, Cloneable {
	private T person; 
	private double difficulty;
	
	public GuessablePerson(T person, double difficulty) {
		this.person = person;
		this.difficulty = difficulty;
	}
	
	public int compareTo(Person person) {
		// returns -1 if calling object comes before, 1 if passing object comes before
		if(this.person.getBirthday().compareTo(person.getBirthday()) == -1)
			// this GuessablePerson is younger than the passed person
			return -1;
		else if(this.person.getBirthday().equals(person.getBirthday()) == true)
			if(Integer.parseInt(this.person.getName().substring(0, 0)) <= Integer.parseInt(person.getName().substring(0,0)))
				return -1;
			else
				return 1;
		else
			return 1;
	}
	
	public String startMessage() {
		return "Guess the birthday of the " +person.personType() + " " + person.getName();
	}
	
	public String closingMessage() {
		return "Congratulations!! You were correct, " + person.toString();
	}
	
	public int getAwardedPointNumber() {
		double points = this.difficulty*100;
		return (int) points;
	}
	
	public Date getBirthday() {
		return person.getBirthday();
	}
	
	@SuppressWarnings("unchecked")
	public GuessablePerson<T> clone() {
		try {
			GuessablePerson<T> newPerson = (GuessablePerson<T>) super.clone();
			newPerson.person = (T) person.clone();
			return newPerson;
		} catch(CloneNotSupportedException e) {
			return null;
		}
	}
}
