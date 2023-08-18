// Aidan Wolfson 20147339
package com.assignment1;


import java.util.Scanner;
import java.util.HashSet;
import java.util.Iterator;
import java.io.FileInputStream;
import java.io.FileNotFoundException;

public class GuessMaster3 {
	private HashSet<GuessablePerson<?>> people;
	private int numPoints;
	
	public GuessMaster3() {
		this.numPoints = 0;
		this.people = new HashSet<GuessablePerson<?>>(0);
	}

	private String getUserInput(Scanner keyboard) {
		// this is what was recommended to me after it said keyboard was never closed. I'm not sure what the best way to close a keyboard is, so hopefully this is ok!
		while(keyboard.hasNextLine()) {
			System.out.println("Enter your birthday guess here (DD/MM/YYYY): ");
			String input = keyboard.nextLine();
			if(input.equals("quit")) {
				System.exit(0);
			}
			return input;
		}
		return null;
	}

	public <M extends Person> void addPerson(M person, double difficulty) {
		GuessablePerson<Person> newGuessablePerson = new GuessablePerson<Person>(person,difficulty);
		people.add(newGuessablePerson);
	}
	
	public HashSet<GuessablePerson<?>> getPeople(){
		return people;
	}
	
	public void startGame() {
		
		
		// Cue Gary the Guess Master. Lights, camera, action!!! You're live, Gary. 
		System.out.println("Greetings, Human!! Welcome to... you guessed it, the second official BIRTHDAY GUESS GAME!! The game where YOU guess a celebrity's birthday!! I'll be your GuessMasterBot for this evening, but you can call me Gary. Now, let's begin the game!!");
		System.out.println("Ok, where are the- oh! Found them. Phewf, almost lost the cards. Classic Gary moment!!");
		System.out.println("*studio audience laughs*");
		
		// The Game Loop
		
		Iterator<GuessablePerson<? extends Person>> peopleIterator = people.iterator();
				
		while(peopleIterator.hasNext()) {
			int i = 0; // simple loop counter
			GuessablePerson<? extends Person> currentPerson = peopleIterator.next();
			try {
				Scanner keyboard = new Scanner(new FileInputStream("C:\\Users\\aidan\\eclipse-workspace\\ELEC279\\GuessMaster\\src\test.txt"));
			
			System.out.println(currentPerson.startMessage());

			
			// Guess Loop
			while(i != 1) {
				
				System.out.println("If you would like to exit at any time, type 'quit'");
				String guessInput = getUserInput(keyboard);
				try {
				Date birthdayGuess = new Date(guessInput);
				
					// Checking player guesses
					if(birthdayGuess.compareTo(currentPerson.getBirthday()) == 0) {
						System.out.println(currentPerson.closingMessage());
						numPoints = numPoints + currentPerson.getAwardedPointNumber();
						System.out.println("You won " + currentPerson.getAwardedPointNumber() + " points in this round. Your total number of points is " + numPoints);
						i++;
					} else if(birthdayGuess.compareTo(currentPerson.getBirthday()) == 1) {
						System.out.println("Incorrect!! Try an earlier date.");
					} else if(birthdayGuess.compareTo(currentPerson.getBirthday()) == -1) {
						System.out.println("Incorrect!! Try a later date.");
					} else {
						System.out.println("Whoops!! Look like there was an error somewhere. Try again!");
					}
				}
				catch(IncorrectDateException e) {

				}
			}
			} catch (FileNotFoundException e) {
				
			}
		}
		System.out.println("Game finished!!");
	}
}
