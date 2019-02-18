#pragma once

#include"song.h"

class llist_node{
public:

	song* data;
	llist_node* next;
	llist_node(song* a = 0, llist_node* ptr = NULL) :data(a), next(ptr){}
	song* get_data(){ return data; }
};


class List
{
public:
	virtual void append(song* a) = 0;
};


class LList :public List
{
private:
	llist_node* curr;
	int count;

public:
	llist_node* ptr;
	LList();//constructor for the linked list
	void append(song* a);//appends a song in the linked list
	string display_list(int min,int max);//displays list of song along with their numbers between places min and max.
	bool isempty();//returns true if the list is empty
	int get_count();//returns number of songs in the list
	song* get_data();//returns song from current node
	void next();//move to next song
	void move_to_start();//moves to the first song
	song* search(int a);//search songs according to their numbers
	bool find(song* a);//returns true if the song name matches
	bool _delete(song* a);//deletes song and returns true otherwise false.

};

