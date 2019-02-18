#include"trie.h"

Trie::Trie(){
	count = 0;
	curr = root = new Trie_node();
}

void Trie::move_to_start(){
	curr = root;

}

int Trie::char_to_index(char c){
	if (c >= 'a'&&c <= 'z')
		return (int)c - 'a';
	else if (c >= 'A' && c <= 'Z')
		return (int)c - 'A';
	else
		return -1;
}

string Trie::remove_spaces(string key)
{
	string temp;
	int j=0;
	for(int i=0;i<key.size();i++)
	{
		if(key[i]!=' ')
			temp.append(1,key[i]);
	}	
	return temp;
}
void Trie::insert(song* key)
{
	string keyName= remove_spaces(key->get_name());
	move_to_start();
	count++;
	for (int i = 0; i < keyName.length()-4; i++){
		int index = char_to_index(keyName[i]);
		if(index==-1)continue;
		if (!curr->children[index])
			curr->children[index] = new Trie_node();
		curr->words->append(key);
		curr = curr->children[index];
	}
	curr->data=key;
}

void Trie::_delete(string key)
{
	key=remove_spaces(key);
	move_to_start();
	count++;
	for (int i = 0; i < key.length(); i++){
		int index = char_to_index(key[i]);
		if (!curr->children[index])
			curr->children[index] = new Trie_node();
		curr = curr->children[index];
	}
	curr->data = NULL;
}

song* Trie::search(string key)
{
	key= remove_spaces(key);
	move_to_start();
	for (int i = 0; i < key.length(); i++){
		int index = char_to_index(key[i]);
		if(index==-1) continue;
		if (!curr->children[index])
			return NULL;
		curr = curr->children[index];
	}
	if (curr != NULL){
		return curr->data;
	}
	else
		return NULL;
}


string Trie::display(string key,int min,int max)
{
	key= remove_spaces(key);
	move_to_start();
	for (int i = 0; i < key.length(); i++){
		int index = char_to_index(key[i]);
		if(index==-1) continue;
		if (!curr->children[index])
			return "\0";
		curr = curr->children[index];
	}
	if (curr != NULL ){
		return curr->words->display_list(min,max);
	}
	else
		return "\0";
}
