#include <filesystem>
#include <iomanip>
#include <iostream>
#include <string> 
#include <vector>
#include <taglib/fileref.h>

using namespace std;
namespace fs = std::filesystem;

void ShowAllFiles(string path_str);
vector<string> FindMP3(string path_str);
void PrintTags(TagLib::FileRef file);

int main()
{
	string path_str;

	cout << "Enter path to the folder:" << endl;
	getline(cin, path_str);

	//ShowAllFiles(path_str);

	vector<string> paths(FindMP3(path_str));

	vector<TagLib::FileRef> files;

	for (int i = 0; i < paths.size(); i++)	 //PATHES.SIZE ????
	{
		const char* temp = paths[i].c_str();
		TagLib::FileRef f(temp);
		files.push_back(f);
	}

	for (int i = 0; i < files.size(); i++)
	{
		PrintTags(files[i]);
	}
		 
}

//Выводит все файлы
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

			//Если поиск сразу в диске (С:/ ), инчае (С:// ) и получаеться лишний символ 
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

vector<string> FindMP3(string path_str)
{
	vector<string> paths;
	try
	{
		fs::directory_iterator it(path_str);

		for (; !it._At_end(); it++)
		{
			string file_name;
			fs::path path = it->path();
			file_name = path.string();

			//Если поиск сразу в диске (С:/ ), инчае (С:// ) и получаеться лишний символ 
			if (file_name.find(".mp3") != string::npos)
			{
				paths.push_back(file_name);

				cout << file_name << endl;   //For debug
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

void PrintTags(TagLib::FileRef file) {
	cout << "______________________________________________" << endl;
	cout << "Title: \t\t" << file.tag()->title() << endl;
	cout << "Artist: \t\t" << file.tag()->artist() << endl;
	cout << "Album: \t" << file.tag()->album() << endl;
	cout << "Year:" << file.tag()->year() << endl;
	cout << "Track:" << file.tag()->track() << endl;
	cout << "Comment: \t" << file.tag()->comment() << endl;
	cout << "Genre: \t\t" << file.tag()->genre() << endl;
}