// Aidan Wolfson - 20147339
package com.assignment1;
import java.util.Scanner;

public class GuessMaster {
	private int currentPerson;
	private Person person1;
	private Person person2;
	private Person person3;
	
	public GuessMaster(Person person1, Person person2, Person person3) {
		this.currentPerson = 1;
		this.person1 = person1;
		this.person2 = person2;
		this.person3 = person3;
	}
	
	// Player Input Method
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
	
	public void startGame() {
		// Cue Gary the Guess Master. Lights, camera, action!!! You're live, Gary. 
		System.out.println("Greetings, Human!! Welcome to... you guessed it, BIRTHDAY GUESS!! The game where YOU guess a celebrity's birthday!! I'll be your GuessMasterBot for this evening, but you can call me Gary. Now, let's begin the game!!");
		System.out.println("Ok, where are the- oh! Found them. Phewf, almost lost the cards. Classic Gary moment!!");
		System.out.println("*studio audience laughs*");
		
		// Full Game Loop
		for(int i = 0; i < 3; i++) {
			if(currentPerson == 1) {
				// Using person1
				System.out.println("Alright, let's begin the game!! It looks like the person who YOU'LL be guessing the birthday of is... *Gary shuffles the cards as the audience waits in anticipation*");
				System.out.println(person1.getName() + "!!!");
			
				// Loop
				while(currentPerson == 1) {
					// Player guess is stored in a Date object
					String guessInput = getUserInput();		
					Date birthdayGuess = new Date(guessInput);
			
					// Check if birthday is correct. If it is, end game. If it's too big, say so, and restart loop. If it's too small, say so, and restart Loop.
					if(birthdayGuess.equals(person1.getBirthday()) == true) {
						System.out.println("CORRECT!! " + person1.toString() + ". Incredible!! Audience, give it up for our friend, Human!! I'll move onto the next person now!! Magnificent. Truly magnificent.");
						currentPerson++;
					} else if(birthdayGuess.greaterThan(person1.getBirthday()) == true) {
						System.out.println("Ohhhh not quite!! Let's take a closer look... Ah, try an earlier date!!");
					} else {
						System.out.println("Incorrect!! Maybe try a later date!!");
					}
				}
			
			} else if(currentPerson == 2) {
				// Using person2
				System.out.println("Ok!! Round 2!! Next up, you'll be guessing the birthday of... *Gary shuffles the cards as the audience waits in anticipation*");
				System.out.println(person2.getName() + "!!!");
			
				// Loop
				while(currentPerson == 2) {
					// Player guess is stored in a Date object
					String guessInput = getUserInput();	
					Date birthdayGuess = new Date(guessInput);
				
				
					// Check if birthday is correct. If it is, end game. If it's too big, say so, and restart loop. If it's too small, say so, and restart Loop.
					if(birthdayGuess.equals(person2.getBirthday()) == true) {
						System.out.println("CORRECT!! " + person2.toString() + ". Wow. Human, you are REALLY good at this. I am impressed. Onto our final round!!");
						currentPerson++;
					} else if(birthdayGuess.greaterThan(person2.getBirthday()) == true) {
						System.out.println("Ohhhh not quite!! Let's take a closer look... Ah, try an earlier date!!");
					} else {
						System.out.println("Incorrect!! Maybe try a later date!!");
					}
				}
			
			} else if(currentPerson == 3) {
				// Using person3
				System.out.println("Well folks, this is the moment you've all been waiting for. Human will be attempting the final round of Birthday Guess. Will they guess correctly? I guess we'll find out. *Gary shuffles the cards once more*");
				System.out.println("*the tension is palpable*");
				System.out.println("You will be guessing the birthday of " + person3.getName() + ".");
				System.out.println("Here we go. *intense music plays in the background*");
			
				// Loop
				while(currentPerson == 3) {
					// Player guess is stored in a Date object
					String guessInput = getUserInput();			
					Date birthdayGuess = new Date(guessInput);
				
				
					// Check if birthday is correct. If it is, end game. If it's too big, say so, and restart loop. If it's too small, say so, and restart Loop.
					if(birthdayGuess.equals(person3.getBirthday()) == true) {
						System.out.println("CORRECT!!!!! " + person3.toString() + ". THEY DID IT!!! HUMAN DID IT!!! EVERYONE, THIS HAS BEEN BIRTHDAY GUESS. LET'S GIVE A HUGE ROUND OF APPLAUSE FOR OUR PLAYER, HUMAN. WE'LL SEE YOU ALL NEXT WEEK!!");
						currentPerson++;
						return;
					} else if(birthdayGuess.greaterThan(person3.getBirthday()) == true) {
						System.out.println("Not quite.. try an earlier date. *the crowd tenses up*");
					} else {
						System.out.println("Incorrect. Maybe try a later date. *the crowd gasps a little*");
					}
				}
			}
		}
	}
}
