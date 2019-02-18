#pragma once

#include"song.h"
class heapNode
{

public:
	song* data;
	bool flag;
	heapNode(){
		data = NULL;
		flag = false;
	}
};

class Heap
{
private:

	int count;
	int size;
	heapNode* heap;
public:

	Heap(int n);

	void sort();

	void swap(heapNode& a, heapNode& b);

	void ReheapUp(int root, int bottom);

	bool insert(song* temp);

	bool remove(song* temp);

	bool IsEmpty();

	song* search(int key);

	song* neversearch(int key);

	bool IsFull();

	string display(int min,int max);

	string neverdisplay(int min,int max);



};

