#pragma once
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

class song{
private:
	string name;
	string directory;
public:
	int count;
	static string int_to_char(int c); //converts integer into corresonding string like (int)5 = "005"(string)
	song(int a,string n, string d);
	song(song* temp);
	song();
	string get_name();
	string get_directory();
	void new_song();
	void play();
	void display();
	
	friend std::ofstream& operator << (std::ofstream& out, const song& s);//friend function writing song class object into file 
	friend std::ifstream& operator >> (std::ifstream& in, song& s);//friend function reading song from a file
};


