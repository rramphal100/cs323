//Ryan Ramphal
//CSCI323_33 Project 4 Java

package project4;

import java.util.*;
import java.io.*;

public class HeapSort {
	private int[] heapAry;
	
	private void bubbleUp(int index){
		int currentIndex = index;
		while(heapAry[currentIndex] < heapAry[currentIndex/2] && currentIndex > 1){
			int temp = heapAry[currentIndex/2];
			heapAry[currentIndex/2]=heapAry[currentIndex];
			heapAry[currentIndex] = temp;
			currentIndex /= 2;
		}
	}
	
	private void bubbleDown(){
		int currentIndex = 1; //start at the root
		int lChild = 2; //start at root's left child
		int rChild = 3; //start at root's right child

		while(lChild < heapAry[0] && heapAry[currentIndex] > Integer.min(heapAry[lChild], heapAry[rChild])){
			//while the left child is part of the current used space and data>smaller of its kids
			int temp = heapAry[currentIndex];
			heapAry[currentIndex] = Integer.min(heapAry[lChild],heapAry[rChild]);
			int smallIndex = (Integer.min(heapAry[lChild],heapAry[rChild]) == heapAry[lChild]) ? lChild : rChild; //smallIndex holds index of child with smaller data
			if(smallIndex == rChild && smallIndex > heapAry[0]) break; //do not do swap with right child index if it is not currently included in the heap as decided by heapAry[0]
			heapAry[smallIndex] = temp;
			//set to new values for next iteration of while loop:
			currentIndex = smallIndex;
			lChild = smallIndex * 2;
			rChild = lChild + 1;
		}
	}
	
	public HeapSort(int size){
		heapAry = new int[size];
		heapAry[0] = 0;
	}
	
	public void buildHeap(String input, String debug) throws FileNotFoundException{
		Scanner inFile = new Scanner(new FileReader(input));
		PrintWriter debugFile = new PrintWriter(
				new BufferedWriter(
						new OutputStreamWriter(
								new FileOutputStream(debug))));
		
		while(inFile.hasNext() && !isHeapFull()){
			insertOneDataItem(inFile.nextInt());
			bubbleUp(heapAry[0]);
			printHeap(debugFile);
		}
		debugFile.flush();
		inFile.close();
		debugFile.close();
	}
	
	public void deleteHeap(String debug, String output) throws FileNotFoundException{
		PrintWriter debugFile = new PrintWriter(
				new BufferedWriter(
						new OutputStreamWriter(
								new FileOutputStream(debug))));
		
		PrintWriter outFile = new PrintWriter(
				new BufferedWriter(
						new OutputStreamWriter(
								new FileOutputStream(output))));
		
		while(!isHeapEmpty()){
			outFile.print(Integer.toString(deleteRoot()) + ' ');
			bubbleDown();
			printHeap(debugFile);
		}
		debugFile.flush();
		outFile.flush();
		debugFile.close();
		outFile.close();
	}
	
	public void insertOneDataItem(int data){
		heapAry[0]++;
		heapAry[heapAry[0]] = data;
		bubbleUp(heapAry[0]);
	}
	
	public int deleteRoot(){
		int temp = heapAry[1];
		heapAry[1] = heapAry[heapAry[0]];
		heapAry[0]--;
		return temp;
	}
	
	public boolean isHeapEmpty(){
		return heapAry[0] == 0;
	}
	
	public boolean isHeapFull(){
		return heapAry[0] == heapAry.length;
	}
	
	public void printHeap(PrintWriter outFile){
		int counter = 0;
		while(counter < 11 && counter < heapAry[0]){
			outFile.print(Integer.toString(heapAry[counter]) + ' ');
			++counter;
		}
		outFile.println();
	}
	
	public static void main(String[] args) throws FileNotFoundException{
		Scanner inFile = new Scanner(new FileReader(args[0]));
		int data, counter = 0;
		while(inFile.hasNext()){
			data = inFile.nextInt();
			++counter;
		}
		inFile.close();
		HeapSort heap = new HeapSort(counter+1);
		heap.buildHeap(args[0], args[1]);
		heap.deleteHeap(args[1], args[2]);
	}
}
