//Ryan Ramphal
//CS323-33

import java.io.*;
import java.util.*;

public class RamphalR_Project2_Java {
	public static void main(String[] args) throws FileNotFoundException{
		LinkedListStack stack = new LinkedListStack();
		Scanner inFile = new Scanner(new FileReader(args[0]));
		int datum = -1;
		System.out.println("Pushing to stack:");
		while(inFile.hasNext()){ //while there is still more stuff in the input file to read
			datum = inFile.nextInt(); //get the next integer in the input file
			stack.push(datum); //create new ListNode w/ the new data and push it to the stack
		}

		inFile.close(); //close the input file

		System.out.println("\nPopping from stack:");
		while(!stack.isEmpty()){
			System.out.println("Popped: " + stack.pop());
		}
	}
}

