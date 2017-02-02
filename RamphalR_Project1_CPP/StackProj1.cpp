//Ryan Ramphal
//CSCI323/33

#include <iostream>
#include <fstream>
using namespace std;

class stack{
private:
   int* array;
   int top;

public:
   int pop();
   void push(int);
   bool isEmpty();

   stack(int);
   ~stack();
};

int stack::pop(){
   if(isEmpty()){
      return NULL;
   }
   top -= 1;
   return array[top + 1];
}

void stack::push(int n){
   top += 1;
   array[top] = n;
}

bool stack::isEmpty(){
   if(top == -1) return true;
   return false;
}

stack::stack(int size){
   array = new int[size];
   top = -1;
}

stack::~stack(){
   delete array;
}

int main(int argc, char** argv){
   ifstream infile;
   infile.open(argv[1]);
   int data;
   int count = 0;
   
   cout << "Counting:\n";
   while(infile >> data){
      count++;
      cout << data << endl;
   }

   cout << endl << endl;

   infile.close();
   infile.open(argv[1]);

   stack s(count);
   while(infile >> data){
      s.push(data);
   }

   cout << "Popping from stack:\n";
   
   while(!s.isEmpty()){
      cout << s.pop() << endl;
   }

   cout << endl;
   return 0;
}
