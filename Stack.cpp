#include"Stack.h"

Stack::Stack(){
	top  = NULL;
	count = 0;
}

void Stack::push(song* d){
	if (top == NULL)
		top = new stack_node(d);
	else{
		top = new stack_node(d, top);
	}
	count++;
}

string Stack :: display(int min,int max)
{
	int n=0;
	string listplay;
	if(top==NULL)
	{
		return "There is no song in the recenly played songs";
	}
	else
	{
		stack_node* temp = top;
		int i;
		for(i=0;i<min+1;i++)
			temp=temp->next;

		while(temp!=NULL&&i<max)
		{
			listplay+=song::int_to_char(i++)+" - "+temp->data->get_name()+"\n";
			temp=temp->next;
		}
		return listplay;
	}

}
song* Stack::search(int n)
{
	stack_node* temp=top; 
	if(n>0&&n<=count){
		for(int i=1;i<n;i++)
			temp=temp->next;
		return temp->data;
	}
	else
	{
		cout<<"No song exists of that number"<<endl;
		return NULL;
	}
}
song* Stack::pop()
{
	if (top != NULL){
		song* temp = top->data;
		stack_node* temp2=top;
		top = top->next;
		count--;
		delete temp2;
		return temp;
	}
	else
	{
		cout<<"No song exists to pop"<<endl;
		return NULL;
	}

}
bool Stack::isEmpty(){
	return top == NULL;
}

song* Stack::peek(){
	if (top != NULL)
		return top->data;
	else{
		cout<<"No element exists to peek"<<endl;
		return NULL;
	}
}

int Stack::get_count(){
	return count;
}
