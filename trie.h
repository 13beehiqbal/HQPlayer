#pragma once
#include"Llist.h"
const int ALPHABET_SIZE = 26;

class Trie_node
{
public:
	LList* words;
	song* data;
	Trie_node* children[ALPHABET_SIZE];
	Trie_node(){
		data = NULL;
		for (int i = 0; i < ALPHABET_SIZE; i++)
			children[i] = NULL;
		words = new LList();
	}
};


class Trie
{
private:
	Trie_node* root;
	Trie_node* curr;
	int count;
public:
	Trie(); //constructor
	int char_to_index(char c); //gives ascii value 
	void move_to_start(); //moves current pointer to start
	void insert(song* key); //inserts song into trie
	void _delete(string key); //deletes a song from trie
	song* search(string key);  //searches a song and returns it 
	string remove_spaces(string key); //remove spaces from a string ( used in inserting song name containing spaces)
	string display(string key, int min, int max); 
	//returns a string consisting of all song names (in response to string entered by user i.e auto suggestion..entered between min and max index no)
};