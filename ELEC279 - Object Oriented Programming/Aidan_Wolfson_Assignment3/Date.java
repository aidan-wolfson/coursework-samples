// Aidan Wolfson - 20147339
package com.assignment1;

public class Date implements Comparable<Date>, Cloneable{
	
	private static class Months{
		
		private static int getDays(int month) {
			switch(month) {
				case 2:
					return 29;
				case 4:
					return 30;
				case 6:
					return 30;
				case 9:
					return 30;
				case 11:
					return 30;
				default:
					// return 31 days if none of above months are met
					return 31;
			}
		}
	}
	
	private int day;
	private int month;
	private int year;
	
	public Date(int day, int month, int year) {
		this.day = day;
		this.month = month;
		this.year = year;
	}
	
	public Date clone() {
		try {
			Date newDate = (Date) super.clone();
			return newDate;
		} catch(CloneNotSupportedException e) {
			return null;
		}
	}
	
	public Date(String dateString){
		// Extracting int values from passed string to initialize instance variables. Second term forces the base to 10. 
		try {
			// if dateString is too long or short, throw exception
			if(dateString.length() != 10)
				throw new IncorrectDateException(dateString);
			
			// check the year input - if it's less than one, throw exception
			if(Integer.parseInt(dateString.substring(6,10), 10) < 1)
				throw new IncorrectDateException(dateString);
			
			// check the month output
			if(Integer.parseInt(dateString.substring(3,5), 10) < 1 || Integer.parseInt(dateString.substring(3,5), 10) > 12)
				throw new IncorrectDateException(dateString);
			
			// check the day input
			if(Integer.parseInt(dateString.substring(0,2), 10) < 1 || Integer.parseInt(dateString.substring(0,2), 10) > Date.Months.getDays(Integer.parseInt(dateString.substring(3,5), 10)))
				throw new IncorrectDateException(dateString);
			
			// if all is well with the string, initialize
			this.year = Integer.parseInt(dateString.substring(6,10), 10);
			this.month = Integer.parseInt(dateString.substring(3,5), 10);
			this.day = Integer.parseInt(dateString.substring(0,2), 10);
			
		} catch(IncorrectDateException e) {
			this.day = 1;
			this.month = 1;
			this.year = 1;
		}
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
	

	public int checkYearEqual(Date date) {
		// assuming date passed is birthday
		if(date==null) {
			return -2; // guess invalid
		} else if(this.year < date.year) {
			//System.out.println("Incorrect!! Try a later year.");
			return -1; // guess too early
		} else if(this.year > date.year) {
			//System.out.println("Incorrect!! Try an earlier year.");
			return 1; // guess too late
		} else 
			// The years are equal
			return 0;
	}
	
	public int checkMonthEqual(Date date) {
		// assuming date passed is birthday
		if(date==null) {
			return -2;
		} else if(this.month < date.month) {
			//System.out.println("Incorrect!! Try a later month.");
			return -1;
		} else if(this.month > date.month) {
			//System.out.println("Incorrect!! Try an earlier month.");
			return 1;
		} else 
			// The months are equal
			return 0;
	}
	
	public int checkDayEqual(Date date) {
		// assuming date passed is birthday, returns -1 for too early, 1 for too late, and 0 for equal (-2 for invalid)
		if(date==null) {
			return -2;
		} else if(this.day < date.day) {
			//System.out.println("Incorrect!! Try a later day.");
			return -1;
		} else if(this.day > date.day) {
			//System.out.println("Incorrect!! Try an earlier day.");
			return 1;
		} else 
			// The days are equal
			return 0;
	}
	
	public int compareTo(Date otherDate){
		// return -1 if this Date is earlier than otherDate, 1 if Date is later than otherDate, 0 if equal (-2 for error)
		// abandoning the checkDay,Month, and Year functions I used in assignment 2 because they just complicate this approach
		if(otherDate==null)
			return -2;
		// equals case
		else if(this.year == otherDate.year) {
			if(this.month == otherDate.month) {
				if(this.day == otherDate.day) {
					return 0;
				}
			}
		} else if(this.year > otherDate.year)
			return 1;
		else if(this.year == otherDate.year) {
			// Check the months
			if(this.month > otherDate.month) {
				return 1;
			} else if(this.month == otherDate.month){
				// Check the days
				if(this.day > otherDate.day) {
					return 1;
				} else {
					return -1; 	// if this returns false, it's earlier than the passed Date
				}
			} else {
				return -1;
			}
		} else {
			return -1;
		}
		return -2;
	}
}


