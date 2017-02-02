#include <iostream>
#include <fstream>
using namespace std;

class HeapSort{
private:
   int* heapAry;
   int capacity;

   void bubbleUp(int);
   void bubbleDown();

public:
   HeapSort(int);
   ~HeapSort();
   void buildHeap(char*, char*);
   void deleteHeap(char*, char*);
   void insertOneDataItem(int);
   int deleteRoot();
   bool isHeapEmpty();
   bool isHeapFull();
   void printHeap(ofstream&);
};

void HeapSort::bubbleUp(int index){
   int currentIndex = index;
   while(heapAry[currentIndex] < heapAry[currentIndex/2] && currentIndex != 1){
      int temp = heapAry[currentIndex/2];
      heapAry[currentIndex/2]=heapAry[currentIndex];
      heapAry[currentIndex] = temp;
      currentIndex /= 2;
   }
}

void HeapSort::bubbleDown(){
   int currentIndex = 1; //start at the root
   int lChild = 2; //start at root's left child
   int rChild = 3; //start at root's right child
 
   while(lChild < heapAry[0] && heapAry[currentIndex] > min(heapAry[lChild], heapAry[rChild])){
      //while the left child is part of the current used space and data>smaller of its kids
      int temp = heapAry[currentIndex];
      heapAry[currentIndex] = min(heapAry[lChild],heapAry[rChild]);
      int smallIndex = (min(heapAry[lChild],heapAry[rChild]) == heapAry[lChild]) ? lChild : rChild; //smallIndex holds index of child with smaller data
      if(smallIndex == rChild && smallIndex > heapAry[0]) break; //do not do swap with right child index if it is not currently included in the heap as decided by heapAry[0]
      heapAry[smallIndex] = temp;
      //set to new values for next iteration of while loop:
      currentIndex = smallIndex;
      lChild = smallIndex * 2;
      rChild = lChild + 1;
   }
}

HeapSort::HeapSort(int size){
   heapAry = new int[size];
   capacity = size;
   heapAry[0] = 0;
}

HeapSort::~HeapSort(){
   if(heapAry != NULL) delete [] heapAry;
}

void HeapSort::buildHeap(char* input, char* debug){
   int data;
   ifstream inFile;
   inFile.open(input);
   ofstream debugFile;
   debugFile.open(debug);
   while(inFile >> data && !isHeapFull()){
      insertOneDataItem(data);
      bubbleUp(heapAry[0]);
      printHeap(debugFile);
   }
   inFile.close(); //segmentation fault here!!! WHY?????
   debugFile.close();
}

void HeapSort::deleteHeap(char* debug, char* output){
   ofstream debugFile;
   debugFile.open(debug);
   ofstream outFile;
   outFile.open(output);
   while(!isHeapEmpty()){
      outFile << deleteRoot() << ' ';
      bubbleDown();
      printHeap(debugFile);
   }
   debugFile.close();
   outFile.close();
}

void HeapSort::insertOneDataItem(int data){
   heapAry[0]++;
   heapAry[heapAry[0]] = data;
   bubbleUp(heapAry[0]);
}

int HeapSort::deleteRoot(){
   int temp = heapAry[1];
   heapAry[1] = heapAry[heapAry[0]];
   heapAry[0]--;
   return temp;
}

bool HeapSort::isHeapEmpty(){
   return heapAry[0] == 0;
}

bool HeapSort::isHeapFull(){
   return heapAry[0] == capacity;
}

void HeapSort::printHeap(ofstream& debugFile){
   int counter = 0;
   while(counter < 11 && counter < heapAry[0]){
      debugFile << heapAry[counter] << ' ';
      counter++;
   }
   debugFile << endl;
}


int main(int argc, char** argv){
   ifstream inFile;
   inFile.open(argv[1]);

   int counter = 0;
   int data;
   while(inFile >> data) ++counter;
   inFile.close();

   HeapSort heap(counter+1);
   heap.buildHeap(argv[1], argv[2]); //call buildHeap, passing input file and debug file names as arguments (to be opened and handled within the method)
   heap.deleteHeap(argv[2], argv[3]); //call deleteHeap, passing debug file and output file names as arguments (to be opened and handled within the method)
   return 0;
}
