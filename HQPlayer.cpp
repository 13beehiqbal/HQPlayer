#include"HQPlayer.h"
#include<time.h>

string HQPlayer::play(song* temp){
	if(temp==NULL) return "\0";
	player->loadSound(temp->get_directory());
	player->play();
	recent->push(temp);
	temp->count++;
	return current_song=temp->get_name();
}


void HQPlayer::set_position(float n)
{
	player->setPosition(n);
}

float HQPlayer::get_position()
{
	return player->getPosition();
}
void HQPlayer::set_volume(float n)
{
	player->setVolume(n);
}

node* HQPlayer:: get_next()
{
	return playlist->curr->next;

}
string HQPlayer::next(){
	if(repeat==true)
	{
		player->play();
		recent->peek()->count++;
		return recent->peek()->get_name();
	}
	if(!queue->isEmpty()){
		song* temp =queue->dequeue();
		return current_song=play(temp);
	}
	if (playlist->next()){
		return current_song=play(playlist->get_song());
	}
	return current_song="No Song Loaded";
}

string HQPlayer::get_current_song_name()
{
	return current_song=playlist->get_song()->get_name();
}
string HQPlayer::previous(){
	if(repeat==true)
	{
		player->play();
		recent->peek()->count++;
		return recent->peek()->get_name();
	}

	if (playlist->previous())
		return current_song=play(playlist->get_song());
	return current_song="No song loaded";
}

void HQPlayer::repeat_all()
{
	repeat=false;
	playlist->get_end()->next = playlist->get_start();
	playlist->get_start()->prev=playlist->get_end();
}

void HQPlayer::no_repeat()
{
	repeat=false;
	playlist->get_start()->prev = NULL;
	playlist->get_end()->next = NULL;
}


void HQPlayer::repeat_one()
{
	repeat=true;
	player->setLoop(true);

}
void HQPlayer::shuffle(){
	srand(time(NULL));
	for (int i = playlist->count - 1; i > 0; i--)
	{
		int j = rand() % i;
		playlist->move_to_pos(i);
		node* temp1 = playlist->get_current();
		playlist->move_to_pos(j);
		node* temp2 = playlist->get_current();
		playlist->swap(temp1, temp2);
	}
}


void HQPlayer::insert_trie(song* key)
{
	trie->insert(key);
}



void HQPlayer::delete_song(){
	playlist->delnode();//delete from trie
}


void HQPlayer::mute()
{
	player->setVolume(0.0);
}

string HQPlayer::display(int min, int max)
{
	return playlist->display(min,max);
}

dblist* HQPlayer::get_playlist(){
	return playlist;
}

Stack* HQPlayer::get_recent()
{
	return recent;
}


void HQPlayer::backwards_display(){
	playlist->show();
}
song* HQPlayer::search(int n)
{
	if (n <= 0 ||n > playlist->count)
	{
		cout<<"Invalid input!"<<endl;
		return NULL;
	}
	return playlist->search(n)->data;
}

song* HQPlayer::search(string key)
{
	song* keySong = trie->search(key);
	if (keySong == NULL)
	{
		cout << "No song exists of that name" << endl;
		return NULL;
	}
	else 
		return keySong;
}

string HQPlayer::play_from_start(){
	if (playlist->get_start() != NULL)
		return play(playlist->get_start()->data);
	else
		cout << "There is no song in the playlist" << endl;
}


LList* HQPlayer::get_favourites()
{
	return favourites;
}
Trie* HQPlayer::get_trie()
{
	return trie;
}

void HQPlayer::set_pause(){
	if(pause==true)
	{
		pause=false;
		player->setPaused(pause);
	}
	else
	{
		pause=true;
		player->setPaused(pause);
	}
}

void HQPlayer::set_stop()
{
	player->stop();
}

string HQPlayer::display_favourites(int min, int max){
	if (favourites->ptr != NULL)
		return favourites->display_list(min,max);
	else
		return "There is no song in favourites";
}
HQPlayer::HQPlayer()
{
	repeat=false;
	playlist = new dblist();
	trie = new Trie();
	favourites = new LList();
	player= new ofSoundPlayer();
	pause=false;
	queue= new Queue();
	recent= new Stack();
	current_song="\0";
}

void HQPlayer::mark_favourite(song* key)
{
	if(key==NULL) return;
	else if (!favourites->find(key))
		favourites->append(key);
	else 
		return;
}

void HQPlayer::queue_song(song* key)
{
	if(key==NULL) return;
	queue->enqueue(key);

}

void HQPlayer::delete_song(int n,song* key)
{
	if(key==NULL) return;
	else if(key==playlist->curr->data) return;
	trie->_delete(key->get_name());
	favourites->_delete(key);
	playlist->delnode(n);

}

