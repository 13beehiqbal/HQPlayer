#include"Llist.h"


LList::LList(){
	ptr = NULL;
	curr = NULL;
	count = 0;
}

void LList::append(song* a){
	if (ptr == NULL){
		curr = ptr = new llist_node(a, NULL);
	}
	else {
		llist_node* temp = ptr;
		while (temp->next != NULL){
			temp = temp->next;
		}
		temp->next = new llist_node(a, NULL);
	}
	count++;
}

song* LList::search(int n)
{
	llist_node* temp=ptr; 
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


bool LList::_delete(song* a)
{
	llist_node* temp = ptr;
	if (ptr == NULL){
		cout << "No element exists" << endl;
		return false;
	}

	if ((ptr->get_data()->get_directory() == a->get_directory())){
		llist_node* itemp = ptr;
		cout << "Deleted element " << a->get_name().c_str() << " from the playlist" << endl;
		if (ptr->next != NULL)
			ptr = ptr->next;

		else
			ptr = NULL;
		delete itemp;
		count--;
		return true;
	}

	else {
		temp = ptr;
		while (temp->next != NULL){
			if ((temp->next->data->get_directory() == a->get_directory())
				&& (temp->next->data->get_name() == a->get_name())){
					llist_node* itemp = temp->next;
					temp->next = temp->next->next;
					delete itemp;
					cout << "Deleted element " << a->get_name().c_str() << " from the playlist" << endl;
					count--;
					return true;
			}
			else if (temp->next != NULL)
				temp = temp->next;
			else
				return false;
		}
	}

}
bool LList::find(song* a)
{
	llist_node* temp = ptr;
	if (ptr == NULL){
		cout << "No element exists" << endl;
		return false;
	}

	if ((ptr->get_data()->get_directory() == a->get_directory())){
		return true;
	}

	else {
		temp = ptr;
		while (temp->next != NULL){
			if ((temp->next->data->get_directory() == a->get_directory())
				&& (temp->next->data->get_name() == a->get_name())){
					return true;
			}
			else if (temp->next != NULL)
				temp = temp->next;
			else
				return false;
		}
	}
	return false;

}
string LList::display_list(int min,int max){
	llist_node* temp = ptr;
	string listplay;
	int i=1;
	if(max>count)max=count;
	if(min>count) min=0;
	for(;i<min+1;i++)
		temp=temp->next;
	if(max>count)max=count;
	cout << endl << endl;
	if (ptr == NULL)
		return "No song exists to display" ;
	else{
		while (temp != NULL&& i<=max){
			listplay+= song::int_to_char(i++)+" - "+ temp->data->get_name()+ "\n";
			temp = temp->next;
		}
		return listplay;

	}
}
bool LList::isempty(){
	if (ptr == NULL)
		return true;
	else
		return false;

}

int LList::get_count(){
	return count;
}

song* LList::get_data()
{
	return curr->data;
}
void LList::next(){
	if (curr->next != NULL)
		curr = curr->next;
}
void LList::move_to_start(){
	curr = ptr;
}

