#include <iostream>
#include <fstream>
using namespace std;

class BucketSort{
private:
   int minData;
   int maxData;
   int bucketSize;
   int offset;
   int* bucketAry;

public:
   BucketSort(ifstream&);
   ~BucketSort();
   void findMinMax(ifstream&, int&, int&);
   int getIndex(int);
   int getValue(int);
   void incrementBucket(int);
   void decrementBucket(int);
   void printBucketAry(ofstream&); //debugging output
   void printSortedData(ofstream&); //sorted data output
};

BucketSort::BucketSort(ifstream& inFile){
   findMinMax(inFile, minData, maxData);
   bucketSize = maxData - minData + 1;
   offset = minData;
   bucketAry = new int[bucketSize];
   for(int index = 0; index < bucketSize; ++index){
      bucketAry[index] = 0;
   }
}

BucketSort::~BucketSort(){
   if(bucketAry != NULL){
      delete[] bucketAry;
   }
}

void BucketSort::findMinMax(ifstream& inFile, int& min, int& max){
   int data;
   inFile >> data;
   min = data;
   max = data;

   while(inFile >> data){
      if(data < min){
         min = data;
      }
      if(data > max){
         max = data;
      }
   }
}

int BucketSort::getIndex(int data){
   return data - offset;
}

int BucketSort::getValue(int index){
   return index + offset;
}

void BucketSort::incrementBucket(int index){
   ++bucketAry[index];
}

void BucketSort::decrementBucket(int index){
   --bucketAry[index];
}

void BucketSort::printBucketAry(ofstream& debugFile){
   debugFile << "Indices:  ";
   for(int counter = 0; counter < 19; ++counter){
      debugFile << counter;
      debugFile.width(4);
   }
   debugFile << endl << "Contents: ";
   for(int counter = 0; counter < 19; ++counter){
      debugFile << bucketAry[counter];
      debugFile.width(4);
   }
}

void BucketSort::printSortedData(ofstream& debugFile){
   for(int index = 0; index < bucketSize; ++index){
      while(bucketAry[index] > 0){
         debugFile << index + offset << endl;
         decrementBucket(index);
      }
   }
}

int main(int argc, char** argv){
   ifstream inFile;
   inFile.open(argv[1]);
   BucketSort buckets(inFile);

   inFile.close();
   inFile.open(argv[1]);
   ofstream outFile1;
   outFile1.open(argv[2]);
   ofstream outFile2;
   outFile2.open(argv[3]);
   int data;
   while(inFile >> data){
      buckets.incrementBucket(buckets.getIndex(data));
      outFile2 << "Index: " << buckets.getIndex(data) << ", Data: " << data << endl;
   }
   buckets.printBucketAry(outFile2);
   buckets.printSortedData(outFile1);
   inFile.close();
   outFile1.close();
   outFile2.close();
   return 0;
}





















 
