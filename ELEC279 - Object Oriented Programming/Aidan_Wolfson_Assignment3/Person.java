// Aidan Wolfson - 20147339
package com.assignment1;

public abstract class Person implements Cloneable {
	private String name;
	private Date birthday;
	
	public Person(String name, Date birthday) {
		this.name = name;
		this.birthday = birthday.clone();
	}
	
	public Person clone() {
		try {
			Person newPerson = (Person) super.clone();
			newPerson.birthday = birthday.clone();
			return newPerson;
		} catch(CloneNotSupportedException e) {
			return null;
		}
	}
	// Accessor Methods
	public String getName() {
		return this.name;
	}
	
	public Date getBirthday() {
		// Accessor to prevent privacy leaks 
		return birthday.clone();
	}
	
	public String toString(){
		return this.name + ", was born on " + birthday.getDay() + ", " + birthday.getMonth() + ", " + birthday.getYear(); 
	}
	
	// Abstract methods
	public abstract String personType();
}
