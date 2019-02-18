#include"Heap.h"		
//constructor
Heap::Heap(int n)
{
	count = 0;
	size = n;
	heap = new heapNode[size]();
}
//swap node data of two nodes
void Heap:: swap(heapNode& a, heapNode& b)
{
	song* temp = a.data;
	a.data= b.data;
	b.data = temp;
	bool flag=a.flag;
	a.flag=b.flag;
	b.flag=flag;
}
//reheaps the array given the upper and lower index (Max Heap)
void Heap::ReheapUp(int root, int bottom)
{
	int parent;
	int temp;

	// Check base case in recursive calls.  If bottom's index is greater
	// than the root index we have not finished recursively reheaping.
	if (bottom > root)
	{
		parent = (bottom - 1) / 2;
		if (heap[parent].data->count < heap[bottom].data->count)
		{
			// Swap these two elements
			swap(heap[parent],heap[bottom]);

			if (bottom % 2==0 && heap[bottom - 1].data->count < heap[bottom].data->count)
			{
				// Swap these two elements
				swap(heap[bottom-1],heap[bottom]);
			}
		}
		ReheapUp(root, parent);

	}
}
//bubble sort using flag O(n^2)
void Heap::sort()
{
	int i,j,temp,flag=0;
	//Big O(count) in best case
	for(i=0;i<count;i++)
	{

		flag = 0;
		for(j=0;j<count-1;j++)
		{
			if (heap[j].data->count < heap[j+1].data->count)
			{
				swap(heap[j],heap[j+1]);
				flag = 1;    
			}
		}    
		if(flag==0)
			break;
	}
}
//inserts a song into heap tree BigO(logN)
bool Heap::insert(song* temp)
{
	if (count < size)
	{

		heap[count].data = temp;
		heap[count].flag = true;
		ReheapUp(0, count);
		count++;
		return true;
	}
	else
		return false;
}
//to remove a song from the heap tree
bool Heap::remove(song* temp)
{
	for( int i=0;i<count;i++)
	{
		if(heap[i].data==temp)
		{
			heap[i].flag=false;
			return true;
		}
	}
	return false;

}

//return true if heap is empty
bool Heap::IsEmpty()
{
	if (count == 0)
		return true;
	else
		return false;

}


//searches and returns the song given the index no in the most played list
song* Heap::search(int key)
{
	if(key>count)
		return NULL;
	if(heap[key-1].data->count==0)
		return NULL;
	else
		return heap[key-1].data;

}
//searches and returns the song given the index no in the never played list
song* Heap::neversearch(int key)
{
	if(key>count)
		return NULL;
	if(heap[key-1].data->count!=0)
		return NULL;
	else
		return heap[key-1].data;

}
//returns true if heap is full
bool Heap::IsFull(){
	if (count == size)
		return true;
	else
		return false;
}

//displays the songs present in the heap tree (most played only )
string Heap::display(int min,int max)
{
	string listplay;
	if(max>count)max=count;
	if(IsEmpty())
		return "There is no song in most played list";
	for (int i = min; i < max; i++)
	{
		if(heap[i].flag&&heap[i].data->count!=0)
			listplay+= song::int_to_char(i+1)+" - "+ "(Times= "+song::int_to_char(heap[i].data->count)+") "+heap[i].data->get_name() + "\n";
	}
	return listplay;
}

//displays the songs present in the heap tree (never played only )
string Heap::neverdisplay(int min,int max)
{
	string listplay;
	if(max>count)max=count;
	if(IsEmpty())
		return "There is no song in most played list";
	for (int i = min; i < max; i++)
	{
		if(heap[i].flag&&heap[i].data->count==0)
			listplay+= song::int_to_char(i+1)+" - "+ "(Times= "+song::int_to_char(heap[i].data->count)+") "+heap[i].data->get_name() + "\n";
	}
	return listplay;
}




