#include <iostream>
#include <fstream>
using namespace std;

class listNode{
private:
	friend class linkedListStack;
	int data;
	listNode* next;
	
public:
	listNode(int);
	listNode();
	void setNext(listNode*);
	int getData();
	listNode* getNext(); //returns the address of the next node
   ~listNode(); //destructor
};

class linkedListStack{
private:
	listNode* top;

public:
	linkedListStack();
	bool isEmpty();
	void push(int);
	int pop();
   ~linkedListStack();
};

//listNode methods
listNode::listNode(int num){
	data = num;
	next = NULL;
}

listNode::listNode(){
	data = 0;
	next = NULL;
}

void listNode::setNext(listNode* in){
   next = in;
}

int listNode::getData(){
	return data;
}

listNode* listNode::getNext(){
	return next;
}

listNode::~listNode(){
   delete next;
}

//linkedListStack methods
linkedListStack::linkedListStack(){
	top = NULL;
}

bool linkedListStack::isEmpty(){
	return top == NULL;
}

void linkedListStack::push(int num){
   listNode* temp = new listNode(num);
	if(isEmpty()){
		top = temp;
	}
	else{
		temp->setNext(top);
		top = temp;
	}
   cout << "Data: " << top->getData() << ", Next: " << top->getNext();
}

int linkedListStack::pop(){
   if(isEmpty()){
      return 0;
   }
   
   else{
      int temp = top->getData();
      listNode* tempNode = top->getNext();
      delete top;
      top = tempNode;
      return temp;
   }
}

linkedListStack::~linkedListStack(){
   while(top != NULL){
      listNode* temp = top->getNext();
      delete top;
      top = temp;
   }
}

int main(int argc, char** argv){
   linkedListStack stack;
   ifstream infile;
   infile.open(argv[1]);
   int data;
   
   cout << "Input data:\n";
   while(infile >> data){
      stack.push(data); //creates the new listNode and prints out its data and next values
      cout << endl;
   }
   
   infile.close();

   cout  << endl << "Popping from stack:\n";
   while(!stack.isEmpty()){
      cout << stack.pop() << endl;
   }
   
   return 0;
}
