#include"Queue.h"

Queue::Queue()
{
	head = NULL;
	tail = NULL;
}
bool Queue::isEmpty()
{
	return tail == NULL && head == NULL;
}

void Queue::enqueue(song* a)
{
	q_node* q= new q_node(a,NULL); 
	if (tail == NULL)
	{
		head = q;
		tail = q;
	}
	else
		tail->next = q;
	tail = q;
}

song* Queue:: dequeue()
{
	song* a;
	if (isEmpty())
	{
		//cout << "Empty" << endl;
		return NULL;
	}
	if (head == tail)
	{
		a= head->data;
		q_node*p = head;
		head = NULL;
		tail = NULL;
		delete p;
	}
	else
	{
		a = head->data;
		q_node*p = head;
		head = head->next;

		delete p;
	}
	return a;

}
