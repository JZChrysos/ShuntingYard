#include <iostream>
#include <cstring>
using namespace std;
//Node
struct Node{
	Node* next;
	char data;
};
//Stack: the stack is a data structure which has an order, and allows the user to access the most recently added node (top).
void push(char c, Node*& top){
	Node * newtop = new Node();
	newtop->data = c;
	newtop->next = top;
	top = newtop;	
}
void pop(Node*& top){ //simply removes the top node and assigns the next one to be top.
	Node * temp = top;
	if(temp != NULL){
		top = top->next;
		delete temp;
	}
}
char peek(Node*& top){
	return top->data;
}
//Queue: the queue allows nodes to be added to the back, and retrieved from the front. Front points backwards to the back, weirdly.
void enqueue(char c, Node*& front, Node*& back){
	Node * newback = new Node();
	newback->data = c;
	if(back == NULL){// when the first thing is added, it is both the front and back.
		front = newback;
		back = newback;
	}
	else{
		back->next = newback;
		back = newback;
	}
}
void dequeue(Node*& front, Node*& back){
	if(front == NULL){
		return;
	}
	else{
	front = front->next;
	if(front == NULL){
		back = NULL;
	}
	}
}
void readqueue(char output[], Node* &front, Node* &back){
	Node* current = front;
	int i = 0;
	while(current != NULL){
		output[i] = current->data;
		i++;
		current = current->next;
		dequeue(front, back);
	}
	output[i] = '\0';
}
//Shunting yard algorithm!
int pres(char c){
	if(c == '+' || c == '-') return 2;
	else if(c == 'x' || c == '/') return 3;
	else if(c =='^') return 4;
	else return 0;
}
void intopost(char* input, Node*& top, Node*& front, Node*& back){
	for(int i=0; input[i] != '\0'; i++){
		char c = input[i];
		// if c is + - * / ^
		if(c =='+' || c == '-' || c == '*' || c == '/' || c == '^'){
			while(top != NULL){
				if(peek(top) != '(' && (pres(c) > pres(peek(top)) || (pres(c) == pres(peek(top)) && c != '^'))){
					enqueue(peek(top), front, back);
					pop(top);
				}
				else{
					break;
				}
			}
			push(c, top);
		}
		// if c is ( )
		else if(c == '(') push(c, top);
		else if(c == ')'){
			while(peek(top) != '('){
				enqueue(peek(top), front, back);
				pop(top);
			}
			pop(top); // discards (
		}
		// if c is a digit (or anything else)
		else{
			enqueue(c, front, back);
		}
	}
}
int main(){
	//initialize stack and queue
	Node * top = NULL;
	Node * front = NULL;
	Node * back = NULL;

	//prompt user for infix
	cout << "This is my Shanty Bard algorithm. Please enter an integer expression with the operations {+,-,*,/,^} in infix without spaces:" << endl;
	char* input;
	char output[100];
	cin.getline(input,100,'\n');
	cout << "got input" << endl;
	intopost(input, top, front, back);
	cout << "did intopost" << endl;
	readqueue(output, front, back);
	cout << "did readqueue" << endl;
	cout << output;
	return 0;
}
