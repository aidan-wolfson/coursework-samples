// Aidan Wolfson - 20147339
package com.assignment1;
import java.util.Random;
import java.util.Scanner;
import java.util.Arrays;

public class GuessMaster2 {
	private Person[] people;
	private int numPoints;
	private int numPeople;
	
	public GuessMaster2() {
		this.numPoints = 0;
		this.numPeople = 0;
		this.people = new Person[numPeople];
	}
	
	private String getUserInput() {
		@SuppressWarnings("resource") // this is what was recommended to me after it said keyboard was never closed. I'm not sure what the best way to close a keyboard is, so hopefully this is ok!
		Scanner keyboard = new Scanner(System.in);
		System.out.println("Enter your birthday guess here (DD/MM/YYYY): ");
		String input = keyboard.next();
		if(input.equals("quit")) {
			System.exit(0);
		}
		return input;
	}
	
	public void addPerson(Person person) {
		numPeople++;
		people = Arrays.copyOf(people, numPeople);
		people[numPeople-1] = person;
	}
	
	public void startGame() {
		
		
		// Cue Gary the Guess Master. Lights, camera, action!!! You're live, Gary. 
		System.out.println("Greetings, Human!! Welcome to... you guessed it, the second official BIRTHDAY GUESS GAME!! The game where YOU guess a celebrity's birthday!! I'll be your GuessMasterBot for this evening, but you can call me Gary. Now, let's begin the game!!");
		System.out.println("Ok, where are the- oh! Found them. Phewf, almost lost the cards. Classic Gary moment!!");
		System.out.println("*studio audience laughs*");
		
		// The Game Loop
		while(numPoints <= 1000) {
			int i = 0; // simple loop counter
			// Selecting the person at random using the Random class
			Random rand = new Random();
			int personSelector = rand.nextInt(numPeople);
			Person currentPerson = people[personSelector];
			System.out.println(currentPerson.startMessage());
			
			// Guess Loop
			while(i != 1) {
				
				String guessInput = getUserInput();
				Date birthdayGuess = new Date(guessInput);
						
					// Checking player guesses
					if(birthdayGuess.equals(currentPerson.getBirthday()) == true) {
						System.out.println(currentPerson.closingMessage());
						numPoints = numPoints + currentPerson.getAwardedPointNumber();
						System.out.println("You won " + currentPerson.getAwardedPointNumber() + " points in this round. Your total number of points is " + numPoints);
						i++;
					} else if(birthdayGuess.checkYearEqual(currentPerson.getBirthday()) == false) {
						//birthdayGuess.checkYearEqual(currentPerson.getBirthday());
					} else if(birthdayGuess.checkMonthEqual(currentPerson.getBirthday()) == false) {
						//birthdayGuess.checkMonthEqual(currentPerson.getBirthday());
					} else if(birthdayGuess.checkDayEqual(currentPerson.getBirthday()) == false) {
						//birthdayGuess.checkDayEqual(currentPerson.getBirthday());
					}
				}
			}
		System.out.println("W O W ! Congratulations Human!! You made it to 1000 points!! That's amazing!! You won!!");
	}
}
