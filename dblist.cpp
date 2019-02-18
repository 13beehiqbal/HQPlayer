#include "dblist.h"


dblist::dblist(){
	start = NULL;
	curr = NULL;
	end=NULL;
}
int dblist::id = 0;
int dblist::count = 0;


bool dblist::has_next(){
	if (curr->next != NULL)
		return true;
	else
		return false;
}

bool dblist::next(){
	if (has_next()){
		curr = curr->next;
		return true;
	}
	else
	{
		cout << "There is no next song" << endl;
		return false;
	}
}

bool dblist::previous(){
	if (curr->prev != NULL){
		curr = curr->prev;
		return true;
	}
	else{
		cout << "There is no previous song" << endl;
		return false;
	}
}

void dblist::move_to_start(){
	curr = start;
}

song* dblist::get_song(){
	return curr->data;
}

node* dblist::get_current(){
	return curr;
}

node* dblist::get_next()
{
	if(has_next())
		return curr->next;
	else 
		return NULL;
}
void dblist::move_to_pos(int a)
{
	if (a >= count)
		cout << "The position does not exists" << endl;
	else{
		move_to_start();
		for (int i = 0; i < a; i++)
			next();
	}
}

void dblist::swap(node* node1, node* node2) {
	song* temp_data = node1->data;
	node1->data = node2->data;
	node2->data = temp_data;

	int temp = node1->index;
	node1->index = node2->index;
	node2->index = temp;
}

node* dblist::get_start(){
	return start;
}

node* dblist::get_end(){
	return end;
}

void dblist::move_to_end(){
	curr=end;
}

string dblist::addnode()          //adding node
{
	id++;
	count++;
	char r;
	song* new_song = new song();
	new_song->new_song();
	cout << "press 's' to add in start,'m' for midd , 'e' for end" << endl;
	cin >> r;
	switch (r)
	{
	case's':                 //add start
		if (start == NULL)
		{
			end=curr=start = new node(new_song, id, NULL, NULL);
		}
		else
		{
			start = start->prev = new node(new_song, id, NULL, start);
		}
		break;
	case'e':               //add end
		if (start == NULL)
		{
			end=curr=start = new node(new_song, id, NULL, NULL);
		}
		else
		{
			end=end->next = new node(new_song, id, end, NULL);
		}
		break;
	case'm':                //add mid
		int num;
		cout << "enter song number after which you want to enter" << endl;
		cin >> num;
		if (num >= count)
		{
			cout << "No song exists at that number" << endl;
			throw -2;
		}
		temp2 = start;
		for (int i = 0; i < num; i++)
		{
			if (start == NULL)
				cout << "given song not found" << endl;
			else
			{
				temp3 = temp2;
				temp2 = temp2->next;

			}
		}

		temp2->prev = temp3->next = new node(new_song, id, temp3, temp2);
		break;
	}
	return new_song->get_name();

}


string dblist::append(song* s)          //adding node
{
	id++;
	count++;
	if (start == NULL)
	{
		end=curr=start = new node(s, id, NULL, NULL);
	}
	else
	{
		end->next = new node(s, id, end, NULL);
		end=end->next;
	}
	return s->get_name();

}
string dblist::display(int min, int max)        //displaying
{
	string listplay;
	if (start == NULL)
		return "No songs in the playlist\n";
	temp3 = start;
	int i = min+1;
	for(int j=1;j<i;j++)
		temp3=temp3->next;
	if(max>count)max=count;
	if (start == NULL)
		listplay= "No songs in the playlist\n";
	else
	{
		for (; i < max;i++)
		{
			listplay +=  song::int_to_char(i);
			listplay+= " - ";
			listplay+=temp3->data->get_name();
			listplay+= "\n";
			temp3 = temp3->next;
		}
		listplay+= song::int_to_char(i) + " - " + temp3->data->get_name() + "\n";
	}
	return listplay;
}

node* dblist::search(int temp)            //searching
{

	temp1 = start;
	for (int i = 1; i < temp; i++)
		temp1 = temp1->next;
	return temp1;

}
void dblist::delnode()           //deleting
{

	char d;
	cout << "press 's' to delete from start,'m' for midd , 'e' for end" << endl;
	cin >> d;
	switch (d)
	{
	case's':               //delete start
		if (start == NULL)
		{
			cout << "no song to delete" << endl;
		}
		else
		{
			temp1 = start;
			start = start->next;
			start->prev = NULL;
			delete temp1;
			count--;
		}
		break;
	case'e':            //delete end
		if (start == NULL)
		{
			cout << "no song to delete" << endl;
		}
		else
		{
			temp1 = start;
			while (temp1->next != NULL)
			{
				temp2 = temp1;
				temp1 = temp1->next;
			}
			delete temp1;
			temp2->next = NULL;
			count--;
		}
		break;
	case'm':               //delete mid
		int num;
		cout << "enter song you want to delete from playlist" << endl;
		cin >> num;
		if (num >= count)
		{
			cout << "No song exists at that number" << endl;
			return;
		}
		temp1 = start;
		for (int i = 1; i < num; i++)
		{
			if (start == NULL)
				cout << "given song does not exist" << endl;
			else
			{
				temp2 = temp1;
				temp1 = temp1->next;
			}
		}
		temp3 = temp1->next;
		temp2->next = temp3;
		temp3->prev = temp2;
		delete temp1;
		break;
	}
}

void dblist::delnode(int num)
{
	if (num >= count)
	{
		cout << "No song exists at that number" << endl;
		return;
	}
	temp1 = start;
	for (int i = 1; i < num; i++)
	{
		if (start == NULL)
			cout << "given song does not exist" << endl;
		else
		{
			temp2 = temp1;
			temp1 = temp1->next;
		}
	}
	temp3 = temp1->next;
	temp2->next = temp3;
	temp3->prev = temp2;
	delete temp1;
}

void dblist::show()               //backward display
{
	cout << "backward display" << endl;
	temp3 = start;
	int i = 0;
	if (start == NULL)
		cout << "no song to display" << endl;
	else
	{
		while (temp3->next != NULL)
		{
			temp3 = temp3->next;
			i++;
		}
		while (temp3->prev != NULL)
		{
			cout << i + 1 << " - " << temp3->data->get_name().c_str() << endl;
			temp3 = temp3->prev;
			i--;
		}
		cout << "1 - " << temp3->data->get_name().c_str() << endl;
	}
}

std::ofstream& operator<< (std::ofstream& stream, const dblist& s)
{
	node* temp=s.start;
	for(int i=0;i<s.count;i++){
		stream<<*(temp->data);
		stream<<temp->index<<endl;
		temp=temp->next;
	}
	return stream;
}
std::ifstream& operator>> (std::ifstream& stream, dblist& s)
{
	s.start = new node();
	stream>>(*(s.start->data));
	stream>>s.start->index;
	stream.ignore();
	dblist::id=s.start->index;
	dblist::count=1;
	node* temp =s.curr= s.start;
	while(!stream.eof())
	{
		temp->next= new node();
		stream>>*(temp->next->data);
		stream>>temp->next->index;
		temp->next->prev=temp;
		stream.ignore();
		dblist::id=temp->next->index;
		dblist::count++;
		if(!stream.eof())
			break;
	}
	return stream;
}