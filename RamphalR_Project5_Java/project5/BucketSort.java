package project5;

import java.io.*;
import java.util.Scanner;

public class BucketSort {
	private int minData;
	private int maxData;
	private int bucketSize;
	private int offset;
	private int[] bucketAry;
	
	public BucketSort(Scanner inFile){
		int[] minmax = new int[2];
		findMinMax(inFile, minmax);
		minData = minmax[0];
		maxData = minmax[1];
		bucketSize = maxData - minData + 1;
		offset = minData;
		bucketAry = new int[bucketSize];
		for(int index = 0; index < bucketSize; index++){
			bucketAry[index] = 0;
		}
	}
	
	public void findMinMax(Scanner inFile, int[] minmax){
		int data;
		data = inFile.nextInt();
		minmax[0] = data;
		minmax[1] = data;
		
		while(inFile.hasNextInt()){
			data = inFile.nextInt();
			if(data < minmax[0]) minmax[0] = data;
			if(data > minmax[1]) minmax[1] = data;
		}
	}
	
	public int getIndex(int data){
		return data - offset;
	}
	
	public int getValue(int index){
		return index + offset;
	}
	
	void printBucketAry(PrintWriter debugFile){
		debugFile.print("Indices:  ");
		for(int index = 0; index < 19; ++index){
			debugFile.printf("%-5s", index);
		}
		debugFile.println();
		debugFile.print("Values:   ");
		for(int index = 0; index < 19; ++index){
			debugFile.printf("%-5s", bucketAry[index]);
		}
	}
	
	void printSortedData(PrintWriter outFile){
		for(int index = 0; index < bucketSize; ++index){
			while(bucketAry[index] > 0){
				outFile.println(index + offset + " ");
				--bucketAry[index];
			}
		}
	}
	
	public static void main(String[] args) throws FileNotFoundException{
		Scanner inFile = new Scanner(new FileReader(args[0]));
		
		PrintWriter debugFile = new PrintWriter(
				new BufferedWriter(
						new OutputStreamWriter(
								new FileOutputStream(args[2]))));
		
		PrintWriter outFile = new PrintWriter(
				new BufferedWriter(
						new OutputStreamWriter(
								new FileOutputStream(args[1]))));
		
		BucketSort buckets = new BucketSort(inFile);
		inFile.close();
		
		inFile = new Scanner(new FileReader(args[0]));
		int data;
		while(inFile.hasNextInt()){
			data = inFile.nextInt();
			++buckets.bucketAry[buckets.getIndex(data)];
			debugFile.println("Index " + buckets.getIndex(data) + ", Data: " + data);
		}
		buckets.printBucketAry(debugFile);
		buckets.printSortedData(outFile);
		inFile.close();
		outFile.close();
		debugFile.close();		
	}
}
