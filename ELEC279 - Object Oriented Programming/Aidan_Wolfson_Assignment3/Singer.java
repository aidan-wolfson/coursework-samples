// Aidan Wolfson - 20147339
package com.assignment1;

public class Singer extends Person {
	private String debutAlbum;
	private Date debutAlbumReleaseDate;
	
	public Singer(String name, Date birthday, String debutAlbum, Date debutAlbumReleaseDate) {
		// Calling the super() constructor
		super(name, birthday);
		
		// Initializing instance variables
		this.debutAlbum = debutAlbum;
		this.debutAlbumReleaseDate = debutAlbumReleaseDate.clone();
	}
	
	public Singer clone() {
			Singer newSinger = (Singer) super.clone();
			newSinger.debutAlbumReleaseDate = debutAlbumReleaseDate.clone();
			return newSinger;
	}
	
	public String toString() {
		return super.toString() + ". Their debut album was " + debutAlbum + ", and was released on " + debutAlbumReleaseDate.getDay() + " " + debutAlbumReleaseDate.getMonth() + " " + debutAlbumReleaseDate.getYear();
	}
	
	public String personType() {
		return "singer";
	}
	
	
}
