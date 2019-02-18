#pragma once
#include"Llist.h"
#include"trie.h"
#include"Queue.h"
#include"dblist.h"
#include"ofSoundPlayer.h"
#include"Stack.h"
#include"Heap.h"

class HQPlayer
{
private:
	bool pause;
	Queue* queue;
	dblist* playlist;
	LList* favourites;
	Trie* trie;
	bool repeat;
	Stack* recent;
public:
	string current_song;
	ofSoundPlayer* player;
	string play(song* temp); 
	string next();
	string previous();
	void repeat_all();//careful about the display function now
	void repeat_one();//repeats the currently playing song when next or previous is pressed
	void no_repeat(); //playling loop ends with the end of playlist
	void shuffle();//shuffle using fisher yates algorithm
	void add_song(); 
	void delete_song();
	void edit_song();
	string display(int min, int max); //returns string containing songs  between index min and max returned from scroll bar 
	void mark_favourite(song* key); //appends into favourites
	void queue_song(song* key); //queues the song into queue
	void delete_song(int n,song* key); //delete song from the playlist, trie, recent played, never played, mostly played if exists
	void backwards_display();//displays playlist backwards
	void search(); 
	song* search(int); //searches and returns the song by song number in playlist
	song* search(string);//searches and returns the song by song name in playlist
	string get_current_song_name(); //returns current song name 
	void insert_trie(song* key); //inserts to trie
	node* get_next(); //returns next song name
	void mute(); //mutes the player
	string play_from_start(); //plays from start
	dblist* get_playlist(); // retuns playlist
	LList* get_favourites();
	Stack* get_recent();
	Trie* get_trie();
	string display_favourites(int min,int max);
	void set_position(float n); //set track postition  
	void set_volume(float n); //sets volume
	float get_position(); //returns track position
	void set_stop(); //stops the player
	void set_pause(); //pauses the track
	HQPlayer(); //constructor
};