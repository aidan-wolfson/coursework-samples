// Aidan Wolfson - 20147339
package com.assignment1;

public class Singer extends Person {
	private String debutAlbum;
	private Date debutAlbumReleaseDate;
	
	public Singer(String name, Date birthday, double difficulty, String debutAlbum, Date debutAlbumReleaseDate) {
		// Calling the super() constructor
		super(name, birthday, difficulty);
		
		// Initializing instance variables
		this.debutAlbum = debutAlbum;
		this.debutAlbumReleaseDate = new Date(debutAlbumReleaseDate);
	}
	
	// Shallow copy constructor
	public Singer(Singer singer) {
		super(singer);
		
		this.debutAlbum = singer.debutAlbum;
		this.debutAlbumReleaseDate = singer.debutAlbumReleaseDate;
	}
	
	public Singer clone() {
		return new Singer(this);
	}
	
	public String toString() {
		return super.toString() + ". Their debut album was " + debutAlbum + ", and was released on " + debutAlbumReleaseDate.getDay() + " " + debutAlbumReleaseDate.getMonth() + " " + debutAlbumReleaseDate.getYear();
	}
	
	public String personType() {
		return "singer";
	}
	
	
}
