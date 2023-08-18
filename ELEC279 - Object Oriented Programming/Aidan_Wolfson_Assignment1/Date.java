// Aidan Wolfson - 20147339
package com.assignment1;

public class Date {
	private int day;
	private int month;
	private int year;
	
	public Date(int day, int month, int year) {
		this.day = day;
		this.month = month;
		this.year = year;
	}
	
	// "Shallow Copy" constructor
	public Date(Date date) {
		this.day = date.day;
		this.month = date.month;
		this.year = date.year;
	} 
	
	public Date(String dateString){
		// Extracting int values from passed string to initialize instance variables. Second term forces the base to 10. 
		this.day = Integer.parseInt(dateString.substring(0,2), 10);
		this.month = Integer.parseInt(dateString.substring(3,5), 10);
		this.year = Integer.parseInt(dateString.substring(6,10), 10);
	}
	
	// Accessor Methods
	public int getDay() {
		return this.day;
	}
	
	public int getMonth() {
		return this.month;
	}
	
	public int getYear() {
		return this.year;
	}
	
	boolean equals(Date date) {
		// If the passed Date object exists and has values equal to another Date object, then return true
		if(date==null)
			return false;
		else if(this.day == date.day && this.month == date.month && this.year == date.year)
			return true;
		else {
			return false;
		}
	}
	
	
	// Further comparison methods. I'm a little unsure of these, because they weren't necessary for the assignment, but I think having the greater than and less than check in methods is more manageable.
	boolean greaterThan(Date date) {
		// Check to see if this Date object is greater than the passed Date object. Sorry, this method got a little chaotic and I'm a little unsure of it. I think it works, though.
		if(date==null)
			return false;
		else if(this.year > date.year)
			return true;
		else if(this.year == date.year) {
			// Check the months
			if(this.month > date.month) {
				return true;
			} else if(this.month == date.month){
				// Check the days
				if(this.day > date.day) {
					return true;
				} else {
					return false; 	// if this returns false, it's either less than or equal to the passed Date
				}
			} else {
				return false;
			}
		} else {
			return false;
		}
	}
	
	boolean lessThan(Date date) {
		// Check to see if this Date object is less than the passed Date object. 
		if(date==null)
			return false;
		else if(this.year < date.year)
			return true;
		else if(this.year == date.year) {
			// Check the months
			if(this.month < date.month) {
				return true;
			} else if(this.month == date.month){
				// Check the days
				if(this.day < date.day) {
					return true;
				} else {
					return false; 	// if this returns false, it's either greater than or equal to the passed Date
				}
			} else {
				return false;
			}
		} else {
			return false;
		}
	}
}
