#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <list>
/* Author: Daniel Kim
Class: Data Structures and Algorithms I
Professor: Carl Sable
Date: 04/10/19
This assignment entailed creating a stack and queue data structure.
Both data structures should be able to handle ints, doubles, and strings.
Commands are given through a text file, syntax specified by the assignment
It was assumed that all commands would be valid commands. */

using namespace std;
// Abstract Class
template <class T>
class SimpleLinkedList{
private:
	string name;
protected:
typedef struct {
	T data;
	struct SimpleLinkedList<T>::Node *next;
} Node;
	Node *head, *tail;
public:
	SimpleLinkedList();
	SimpleLinkedList(string initName);
	~SimpleLinkedList();
	void pop(ofstream &outputfile);
	string getName();
	virtual void push(T* input) = 0;
};

// Abstract Class Constructor
template <class T>
SimpleLinkedList<T>::SimpleLinkedList(string initName){
	head = NULL;
	tail = NULL;
	name = initName;
}

// Abstract Class Default Constructor
template <class T>
SimpleLinkedList<T>::SimpleLinkedList(){
	head = NULL;
	tail = NULL;
	name = "TEMP_NAME";
}

// Abstract Class Destructor
template <class T>
SimpleLinkedList<T>::~SimpleLinkedList(){
	delete this;
}

// returns Name
template <class T>
string SimpleLinkedList<T>::getName(){
	return this->name;
}

// Stack Class
template <class T>
class Stack: public SimpleLinkedList<T>{
public:
	Stack(): SimpleLinkedList<T>::SimpleLinkedList(){}
	Stack(string initName): SimpleLinkedList<T>::SimpleLinkedList(initName){}
	void push(T* input);
};

// Queue Class
template <class T>
class Queue: public SimpleLinkedList<T>{
public:
	Queue(): SimpleLinkedList<T>::SimpleLinkedList(){}
	Queue(string initName): SimpleLinkedList<T>::SimpleLinkedList(initName){}
	void push(T* input);
};

// Pop Function
template<class T>
void SimpleLinkedList<T>::pop(ofstream &outputfile){
	if(head == NULL){
		outputfile << "ERROR: This list is empty!" << endl;
	}
	else{
		Node *tmp = this->head;
		outputfile << "Value popped: " << tmp->data << endl;
		this->head = head->next;
	}
	return;
}

// Stack Push Function
template<class T>
void Stack<T>::push(T* input){
	typename SimpleLinkedList<T>::Node *tmp = new typename SimpleLinkedList<T>::Node;
	tmp->data = *input;
	if(this->head == NULL){
		tmp->next = NULL;
		this->head = tmp;
		this->tail = tmp;
	}
	else{
		tmp->next = this->head;
		this->head = tmp;
	}
}

// Queue Push Function
template<class T>
void Queue<T>::push(T* input){
	typename SimpleLinkedList<T>::Node *tmp  = new typename SimpleLinkedList<T>::Node;
	tmp->data = *input;
	tmp->next = NULL;
	if(this->head == NULL){
		this->head = tmp;
		this->tail = tmp;
	}
	else{
		this->tail->next = tmp;
		this->tail = this->tail->next;
	}
}
/* Returns LinkedList pointer with a certain name,
returns NULL if it given name does not exist*/
template<class T> 
SimpleLinkedList<T>* find(list<SimpleLinkedList<T>*> list, string name){
	for (auto it = list.begin(); it != list.end(); it++){
		if ((*it)->getName().compare(name) == 0){
			return *it;
		}
	}
	return NULL;
}

/* Pop Function, attemps to pop the LinkedList with
a certain name. Prints an error if it fails */
template<class T>
void pop(list<SimpleLinkedList<T>*> list, string name, ofstream &outputfile){
	SimpleLinkedList<T>* temp = find(list,name);
	if (temp != NULL){
		(temp)->pop(outputfile);
		return;
	}	
	outputfile << "ERROR: This name does not exist!" << endl;
}

/* Check Function, checks if a LinkedList of a certain
name exists. Returns 0 if the name already exists,
1 if it does not exist*/
template<class T>
bool check(list<SimpleLinkedList<T>*> list, string name, ofstream &outputfile){
	if (find(list, name) != NULL){
		outputfile << "ERROR: This name already exists!" << endl;
		return 0;
	}
	return 1;
}

/* Push Function, attempts to push an input into a LinkedList
with a certain name. Prints an error if it fails */
template<class T>
void push(list<SimpleLinkedList<T>*> list, string name, T* input, ofstream &outputfile){
	SimpleLinkedList<T>* temp = find(list, name);
	if (temp != NULL){
		temp->push(input);
		return;
	}
	outputfile << "ERROR: This name does not exist!" << endl;
}

int main(){
	int tempInt;
	double tempDouble;
	string input, output;
	cout << "Enter Name of input file: ";
	cin >> input;
	cout << "Enter the Name of output file: ";
	cin >> output;
	ifstream inputfile (input);
	ofstream outputfile (output);
	string nextLine, tempName, tempName2;
	list<SimpleLinkedList<int>*> listInt; 
	list<SimpleLinkedList<double>*> listDouble;
	list<SimpleLinkedList<string>*> listString;
	while(getline(inputfile, nextLine)){
		if (!nextLine.empty()){
			bool foundFlag = 0;
			outputfile << "PROCESSING COMMAND: " << nextLine << endl;
			auto it = nextLine.begin();
			if (*it == 'c'){ // Parsing through the text, line by line
				it += 7;
				while(*it != ' '){ // gets next word
					tempName += *(it++);
				}
				it +=1;
				if (tempName.front() == 'i'){ // checks if the name starts with i,d, or s, and then checks if it should be a queue or stack
					if (check(listInt, tempName, outputfile)){
						if (*it == 'q'){
							listInt.push_front(new Queue<int>(tempName));
						}
						else if (*it == 's'){
							listInt.push_front(new Stack<int>(tempName));
						}
					}
				}
				else if (tempName.front() == 'd'){
					if (check(listDouble, tempName, outputfile)){
						if (*it == 'q'){
							listDouble.push_front(new Queue<double>(tempName));
						}
						else if (*it == 's'){
							listDouble.push_front(new Stack<double>(tempName));
						}
					}
				}
				else if (tempName.front() == 's'){
					if (check(listString, tempName, outputfile)){
						if (*it == 'q'){
							listString.push_front(new Queue<string>(tempName));
						}
						else if (*it == 's'){
							listString.push_front(new Stack<string>(tempName));
						}
					}
				}
				tempName.clear();
			}
			else if (*it == 'p'){ // Case if its push or pop
				it++;
				if (*it == 'u'){ // Push Case
					it += 4;
					while(*it != ' '){
						tempName += *(it++);
					}
					it +=1; 
					while(*it != '\0'){ // gets next word
						tempName2 += *(it++);
					}
					switch(tempName.front()){
						case 'i': 
							tempInt = atoi(tempName2.c_str());
							push(listInt, tempName, &tempInt, outputfile);
							break;
						case 'd': 
							tempDouble = stod(tempName2.c_str());
							push(listDouble, tempName, &tempDouble, outputfile);
							break;
						case 's': 
							push(listString, tempName, &tempName2, outputfile);
							break;
					}
					tempName2.clear();											
				}
				else if (*it == 'o'){ // Pop Case
					it += 3;
					while(*it != '\0'){ //gets next word
						tempName += (*it++);
					}
					switch(tempName.front()){
						case 'i': 
							pop(listInt, tempName, outputfile);
							break;
						case 'd': 
							pop(listDouble, tempName, outputfile);
							break;
						case 's':	pop(listString, tempName, outputfile);
							break;
					}
				}
			}
		}
		tempName.clear();
	}
	inputfile.close();
	outputfile.close();
	return 0;
}
