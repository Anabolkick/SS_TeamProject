#include <filesystem>
#include <iomanip>
#include <iostream>
#include <string> 

using namespace std;
namespace fs = std::filesystem;

void ShowAllFiles();

int main()
{
	
	ShowAllFiles();

}

//Выводит все файлы
void ShowAllFiles()
{
	string path_str;
	cout << "Enter path to the folder:" << endl;
	getline(cin, path_str);

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
		ShowAllFiles();
	}
}