#pragma once
#include"song.h"
//node of Stack class
class stack_node{
	public:
		stack_node* next;
		song* data;
		stack_node(song* d, stack_node* temp = NULL){
			next = temp;
			data=d;
		}
	};

class Stack
{
private:
	
	stack_node* top;
	int count;
public:
	Stack();
	void push( song* d);
	song* search(int n);
	string display(int min,int max);//returns string of song names inbetween the place min and max
	song* pop(); //pops the song in top node
	song* peek(); //returns the song in top node
	int get_count(); 
	bool isEmpty();

};