//Ryan Ramphal
//CS323-33
//Project 3 - C++

#include <iostream>
#include <fstream>
using namespace std;

class ListNode{
private:
   friend class LinkedList;
   int data;
   ListNode* next;

public:
   ListNode(int);
   ListNode(int, ListNode*);
   ~ListNode();
   int getData();
   ListNode* getNext();
   void setNext(ListNode*);
};

ListNode::ListNode(int num){
   data = num;
   next = NULL;
}

ListNode::ListNode(int num, ListNode* newNode){
   data = num;
   next = newNode;
}

ListNode::~ListNode(){
   next = NULL;
}

int ListNode::getData(){
   return data;
}

ListNode* ListNode::getNext(){
   return next;
}

void ListNode::setNext(ListNode* newNext){
   next = newNext;
}

class LinkedList{
private:
   ListNode* listHead;
   ListNode* findSpot(int);

public:
   LinkedList();
   bool isEmpty();
   void listInsert(int, ofstream&);
   //void listDelete(int, ofstream&);
   void printList(ofstream&);
};

ListNode* LinkedList::findSpot(int input){
   if(isEmpty()){
      return listHead;
   }
   ListNode* temp = listHead;
   while(temp->getNext() != NULL && temp->getNext()->getData() < input){
      temp = temp->getNext();
   }
   return temp;
}

LinkedList::LinkedList(){
   ListNode* temp = new ListNode(-9999);
   listHead = temp;
}

bool LinkedList::isEmpty(){
   return listHead->getNext() == NULL;
}

void LinkedList::listInsert(int input, ofstream& out){
   ListNode* spot = findSpot(input);
   if(spot->getNext() != NULL){
      if(spot->getNext()->getData() == input){
         out << input << " is already in the list." << endl;
         return;
      }
   }
   ListNode* temp = new ListNode(input, spot->next);
   spot->next = temp;
   printList(out);
}

void LinkedList::printList(ofstream& out){
   out << "ListHead --> (" << listHead->getData() << ", " << listHead->getNext() << ") ";
   ListNode* temp = listHead->getNext();
   while(temp != NULL){
      out << "--> (" << temp->getData() << ", " << temp->getNext() << ") ";
      temp = temp->getNext();
   }
   out << endl;
}


int main(int argc, char* argv[]){
   ifstream inFile;
   inFile.open(argv[1]);
   ofstream outFile;
   outFile.open(argv[2]);

   LinkedList list;
   int data;
   while(inFile >> data){
      outFile << "Insert data " << data << ": ";
      list.listInsert(data, outFile);
   }

   inFile.close();
   outFile.close();

   return 0;
}
