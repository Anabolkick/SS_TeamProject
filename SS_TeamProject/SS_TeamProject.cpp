#include <filesystem>
#include <iomanip>
#include <iostream>
#include <string> 
#include <vector>
#include <taglib/fileref.h>

using namespace std;
namespace fs = std::filesystem;

void ShowAllFiles(string path_str);
vector<const char*> FindMP3(string path_str);
void PrintTags(vector<TagLib::FileRef> files, int num);

int main()
{
	string path_str;

	cout << "Enter path to the folder:" << endl;
	getline(cin, path_str);

	//ShowAllFiles(path_str);
	vector<const char*> paths(FindMP3(path_str));
	vector<TagLib::FileRef> files(paths.size());
	for (int i=0; i < files.size(); ++i)
		files[i].create(paths[i]);
	for (int i = 0; i < files.size(); ++i)
		PrintTags(files, files.size());
}

//������� ��� �����
void ShowAllFiles(string path_str)
{
	try
	{
		fs::directory_iterator it(path_str);

		for (; !it._At_end(); it++)
		{
			string file_name;
			fs::path path = it->path();
			file_name = path.string();

			//���� ����� ����� � ����� (�:/ ), ����� (�:// ) � ����������� ������ ������ 
			if(path_str.length() >= 4)   { file_name.erase(0, path_str.length() + 1);}
			else { file_name.erase(0, path_str.length()); }


			cout << file_name << endl;
		}
	}
	catch (exception ex)
	{
		//cout << "Error. Try other path!!" << endl;
		//ShowAllFiles(path_str);
	}
}

vector<const char*> FindMP3(string path_str)
{
	vector<const char*> paths;
	try
	{
		fs::directory_iterator it(path_str);

		for (; !it._At_end(); it++)
		{
			string file_name;
			fs::path path = it->path();
			file_name = path.string();

			//���� ����� ����� � ����� (�:/ ), ����� (�:// ) � ����������� ������ ������ 
			if (file_name.find(".mp3") != string::npos)
			{
				paths.push_back(file_name.c_str());

				//cout << file_name << endl;   //For debug
			}
		}
	}
	catch (exception ex)
	{
		cout << "Error. Try other path!!" << endl;	//TODO Change text
		//ShowAllFiles(path_str);
	}

	return paths;
}

void PrintTags(vector<TagLib::FileRef> files, int num) {
	cout << "______________________________________________" << endl;
	cout << "Title: \t\t" << files[num].tag()->title() << endl;
	cout << "Artist: \t\t" << files[num].tag()->artist() << endl;
	cout << "Album: \t" << files[num].tag()->album() << endl;
	cout << "Year:" << files[num].tag()->year() << endl;
	cout << "Track:" << files[num].tag()->track() << endl;
	cout << "Comment: \t" << files[num].tag()->comment() << endl;
	cout << "Genre: \t\t" << files[num].tag()->genre() << endl;
}