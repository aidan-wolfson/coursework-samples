// Aidan Wolfson - 20147339
package com.assignment1;

public abstract class Person {
	private String name;
	private Date birthday;
	private double difficulty;
	
	public Person(String name, Date birthday, double difficulty) {
		this.name = name;
		this.birthday = new Date(birthday);
		this.difficulty = difficulty;
	}
	
	// "Shallow Copy" constructor
	public Person(Person person) {
		this.name = person.name;
		this.birthday = person.birthday;
		this.difficulty = person.difficulty;
	}
	
	// Accessor Methods
	public String getName() {
		return this.name;
	}
	
	protected Date getBirthday() {
		// Accessor to prevent privacy leaks 
		return new Date(birthday);
	}
	
	public String toString(){
		return this.name + ", was born on " + birthday.getDay() + ", " + birthday.getMonth() + ", " + birthday.getYear(); 
	}
	
	public int getAwardedPointNumber() {
		double doublePoint = difficulty*100;
		int points = (int)doublePoint;
		return points;
	}
	
	public String startMessage() {
		return "Guess the birthday of the " + personType() + " " + name;
	}
	
	public String closingMessage() {
		return "Congratulations! You were correct, " + toString();
	}
	
	// Abstract methods
	public abstract String personType();
	
	public abstract Person clone();
}
