//dblist.h
#pragma once

#include"song.h"

class node
{
public:
	song *data;
	node *next;
	node *prev;
	int index;
	node(song* s = NULL,int i=0, node* p = NULL, node* n = NULL) : next(n), prev(p),index(i)
	{
		if(s==NULL)
			data= new song();
		else
			data=s;
	}
	void display(){
		cout << "Song name: " << data->get_name().c_str() << endl
			<< "Directory: " << data->get_directory().c_str() << endl;
	}
};
class dblist{
public:
	string addnode();//adds node into dblist
	string append(song* s); //appends song into doubly liinked list
	void delnode(); //delete nodes from double linked list
	void delnode(int num); //deletes node at the place num
	string display(int min, int max); //returns string containing song names between index min and max
	void show(); //displays the linked list in console
	node* search(int p); //searches and returns the searched node at place p if exists
	bool has_next(); //return true if curr->next!=NULL
	bool next(); 
	bool previous();
	void move_to_start(); //moves current pointer to the start
	song* get_song(); 
	node* get_current();
	void move_to_end();
	void move_to_pos(int a);
	void swap(node* node1, node* node2); //swaps two nodes
	node* get_start();
	node* get_end();
	dblist();
	static int count;
	node* temp1;
	node* curr;
	node* end;
	node* get_next();
private:
	node *start, *temp2, *temp3;
	static int id;

	friend std::ofstream& operator<< (std::ofstream& stream, const dblist& s);//writing doubly linked list node into file
	friend std::ifstream& operator>> (std::ifstream& stream, dblist& s);//reading doubly linked list node into file
};
