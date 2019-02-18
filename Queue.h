#pragma once
#include"song.h"
//node of queue class
class q_node
{
public:
	song* data;
	q_node* next;
	q_node(song* s=NULL, q_node* n= NULL):next(n)
	{
		if(s==NULL)
			data= new song();
		else
			data=s;
	}
};

class Queue
{
private:
	q_node* head;
	q_node* tail;
public:
	Queue();//constructor
	bool isEmpty();//returns true  if queue is empty
	void enqueue(song* a); //enqueues a song into queue
	song* dequeue(); //returns dequeued song
};