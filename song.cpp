#include"song.h"

song::song(int a,string n, string d) :name(n), directory(d),count(a){}
string song::get_name(){
	return name;
}

string song::get_directory(){
	return directory;
}

string song::int_to_char(int c)
{
	char unit = 48+ c%10;
	char ten= 48+ (c/10)%10;
	char hundred=48 + (c/100)%10;
	string tem;
	tem+=hundred;
	tem+=ten;
	tem+=unit;
	return tem;
}

void song::display(){
	cout<<"Song Name: "<<name<<endl
		<<"Directory: "<<directory<<endl;
}

song::song()
{
	name=" ";
	directory=" ";
	count=0;

}

void song::new_song()
{
	string filename, extension;
	cout << "Enter the directory of the song:";
	fflush(stdin);
	getline(cin, filename);

	//to ensure that user only enters the mp3 files
	for (int i = filename.size() - 4; i < filename.size(); i++){
		extension += filename[i];
	}
	if (extension != ".mp3")
		throw - 1;

	//to get the name of the song for searching
	int i = filename.size() - 4;
	for (; filename[i] != '\\'; i--);i++;
	name="";
	for (; i < filename.size() - 4; i++)
		name += filename[i];
	directory = filename;
}
void song::play(){
	system(directory.c_str());
}

song::song(song* temp)
{
	name=temp->name;
	directory=temp->directory;
	count=temp->count;
}

std::ofstream& operator << (std::ofstream& out, const song& s)
{
	out<<s.name<<endl;
	out<<s.directory<<endl;
	out<<s.count<<endl;
	return out;
}
std::ifstream& operator >> (std::ifstream& in, song& s)
{
	string n,d,line;
	int c;
	getline(in,n);
	getline(in,d);
	in>>c;
	std::getline(in,line);
	s.directory=d;
	s.name=n;
	s.count=c;
	return in;
}
