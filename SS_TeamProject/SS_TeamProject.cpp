#include <filesystem>
#include <iomanip>
#include <iostream>
#include <string> 
#include <vector>


using namespace std;
namespace fs = std::filesystem;

void ShowAllFiles(string path_str);
vector<const char*> FindMP3(string path_str);

int main()
{
	string path_str;

	cout << "Enter path to the folder:" << endl;
	getline(cin, path_str);

	//ShowAllFiles(path_str);
	FindMP3(path_str);

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
		cout << "Error. Try other path!!" << endl;
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

			//Если поиск сразу в диске (С:/ ), инчае (С:// ) и получаеться лишний символ 
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