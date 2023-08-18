// Aidan Wolfson - 20147339
package com.assignment1;

public class Person {
	private String name;
	private Date birthday;
	
	public Person(String name, Date birthday) {
		this.name = name;
		this.birthday = birthday;
	}
	
	// "Shallow Copy" constructor
	public Person(Person person) {
		this.name = person.name;
		this.birthday = person.birthday;
	}
	
	// Accessor Methods
	public String getName() {
		return this.name;
	}
	
	protected Date getBirthday() {
		//Private accessor to prevent privacy leaks 
		return this.birthday;
	}
	
	public String toString(){
		return this.name + ", born on " + birthday.getDay() + ", " + birthday.getMonth() + ", " + birthday.getYear(); 
	}
	
	
	
	
}
