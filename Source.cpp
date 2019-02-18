#include<iostream>
using namespace std;
#include<string>
#include"HQPlayer.h"


void Menu()
{
	HQPlayer player;
	char ch;
	do
	{
		char i;
		cout << "Press a to add song" << endl
			<< "Press d to delete" << endl
			<< "Press s for search" << endl
			<< "Press v for display" << endl
			<< "Press e for backward display" << endl
			<< "Press n for Next Song" << endl
			<< "Press p for previous song"<<endl
			<<"Press r for repeat all"<<endl
			<<"Press t for no repeat"<<endl
			<<"Press u for shuffle"<<endl
			<<"Press l for play"<<endl;
		cin >> i;
		switch (i)
		{
		case'a':
			player.add_song();
			break;
		case'd':
			player.delete_song();
			break;
		case'v':
			player.display();
			break;
		case's':
			player.search();
			break;
		case'e':
			player.backwards_display();
			break;
		case'n':
			player.next();
			break;
		case'p':
			player.previous();
			break;
		case'r':
			player.repeat_all();
			break;
		case't':
			player.no_repeat();
			break;
		case'u':
			player.shuffle();
			break;
		case'l':
			player.play_from_start();
		default:
			cout << "Bad input" << endl;
			break;
		}
		cout << "want to process more y/n" << endl;
		cin >> ch;
	} while (ch != 'n');
}
int main()
{
	try{
		Menu();
		cin.get();
		return 0;
	}
	catch (int n){
		if (n == -1){
			cout << "Extension not valid" << endl;
		}
	}
}