#include <filesystem>
#include <iomanip>
#include <iostream>
#include <string> 
#include <vector>
#include <taglib/fileref.h>

using namespace std;
namespace fs = std::filesystem;

void SelectFile(string& path_str);
void ShowAllFiles(string path_str);
void PrintTags(TagLib::FileRef& file);
void SetAll(TagLib::FileRef& file);
void SetOne(TagLib::FileRef& file, int tag);
int CheckInput(int size);
vector<string> FindMP3(string path_str);
void SelectPath(string & path_str);



int main()
{
	string path_str, scan;
	int f_size = 0, value = -1;
	vector<TagLib::FileRef> files;

	SelectPath(path_str);

	ShowAllFiles(path_str);


	vector<string> paths(FindMP3(path_str));

	// Заполняем paths
	for (int i = 0; i < paths.size(); i++)
	{
		const char* temp = paths[i].c_str();
		TagLib::FileRef f(temp);
		files.push_back(f);
	}

	f_size = files.size();

	//menu
	/*while (value != 0) {
		int value_prn = -1, value_set = -1, prn_file = -1, set_file = -1, tag = -1;
		cout << "\nChoose the operation:\n 1-Print tags\n 2-Set tags\n 0-Exit" << endl;
		cin >> value;
		switch (value) {
		case 1:
			cout << "\nChoose the operation:\n 1-Print tags for all files\n 2-Print tags for one file\n 0-Back" << endl;
			cin >> value_prn;
			getline(cin, scan);
			switch (value_prn) {
			case 1:
				for (int i = 0; i < f_size; i++)
				{
					PrintTags(files[i]);
				}
				break;
			case 2:
				prn_file = CheckInput(f_size);
				PrintTags(files[prn_file]);
			}
			break;
		case 2:
			cout << "\nChoose the operation:\n 1-Set all tags for all files\t 3-Set all tags for one file\n 2-Set one tag for all files\t 4-Set one tags for one file\n 0-Back" << endl;
			cin >> value_set;
			getline(cin, scan);
			switch (value_set) {
			case 1:
				for (int i = 0; i < f_size; i++)
				{
					cout << "\n--------Input for file " << i + 1 << "--------" << endl;
					SetAll(files[i]);
				}
				break;
			case 2:
				cout << "\nChoose the tag:\n 1-Title\t 5-Track\n 2-Artist\t 6-Comment\n 3-Album\t 7-Genre\n 4-Year" << endl;
				tag = CheckInput(7);
				for (int i = 0; i < f_size; i++)
				{
					cout << "\n--------Input for file " << i + 1 << "--------" << endl;
					SetOne(files[i], tag);
				}
				break;
			case 3:
				set_file = CheckInput(f_size);
				cout << "\n--------Input for file " << set_file + 1 << "--------" << endl;
				SetAll(files[set_file]);
				break;
			case 4:
				set_file = CheckInput(f_size);
				cout << "\nChoose the tag:\n 1-Title\t 5-Track\n 2-Artist\t 6-Comment\n 3-Album\t 7-Genre\n 4-Year" << endl;
				tag = CheckInput(7);
				cout << "Input for file " << set_file << endl;
				SetOne(files[set_file], tag);
			}
		}
	}*/

	for (int i = 0; i < files.size(); i++)
	{
		files[i].save();
	}
}

void SelectPath(string & path_str)
{
	cout << "Enter path to the folder:" << endl;
	getline(cin, path_str);
	try
	{
		fs::directory_iterator it(path_str);
		
	}
	catch (exception ex)
	{
		cout << "Pleace, try to enter path again" << endl;
		SelectPath(path_str);
	}
}
//Выводит все файлы
void ShowAllFiles(string path_str)
{
	fs::directory_iterator it(path_str);

	for (; !it._At_end(); it++)
	{
		string file_name;
		fs::path path = it->path();
		file_name = path.string();

		//Если поиск сразу в диске (С:/ ), инчае (С:// ) и получаеться лишний символ 
		if (path_str.length() >= 4) { file_name.erase(0, path_str.length() + 1); }
		else { file_name.erase(0, path_str.length()); }

		if (file_name.find(".mp3") != string::npos)
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 10);
			cout << char(254) << " ";
			SetConsoleTextAttribute(hConsole, 7);
		}
		else if (it->is_directory())
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 9);
			cout << char(254) << " ";
			SetConsoleTextAttribute(hConsole, 7);
		}
		else
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 12);
			cout << char(254) << " ";
			SetConsoleTextAttribute(hConsole, 7);
		}

		cout << file_name << endl;
	}

	SelectFile(path_str);
}

vector<string> FindMP3(string path_str)
{
	vector<string> paths;

	fs::directory_iterator it(path_str);

	for (; !it._At_end(); it++)
	{
		string file_name;
		fs::path path = it->path();
		file_name = path.string();

		//Если поиск сразу в диске (С:/ ), инчае (С:// ) и получается лишний символ 
		if (file_name.find(".mp3") != string::npos)
		{
			paths.push_back(file_name);

			//	cout << file_name << endl;   //For debug
		}
	}



	return paths;
}

void PrintTags(TagLib::FileRef& file) {
	cout << "______________________________________________" << endl;
	cout << "Title: \t\t" << file.tag()->title() << endl;
	cout << "Artist: \t" << file.tag()->artist() << endl;
	cout << "Album: \t\t" << file.tag()->album() << endl;
	cout << "Year: \t\t" << file.tag()->year() << endl;
	cout << "Track: \t\t" << file.tag()->track() << endl;
	cout << "Comment: \t" << file.tag()->comment() << endl;
	cout << "Genre: \t\t" << file.tag()->genre() << endl;
}

void SetAll(TagLib::FileRef& file) {
	string scan;
	cout << "\nTitle: "; getline(cin, scan); file.tag()->setTitle(scan);
	cout << "Artist: "; getline(cin, scan); file.tag()->setArtist(scan);
	cout << "Album: "; getline(cin, scan); file.tag()->setAlbum(scan);
	cout << "Year: "; getline(cin, scan); file.tag()->setYear(stoi(scan));
	cout << "Track: "; getline(cin, scan); file.tag()->setTrack(stoi(scan));
	cout << "Comment: "; getline(cin, scan); file.tag()->setComment(scan);
	cout << "Genre: "; getline(cin, scan); file.tag()->setGenre(scan);
}

void SetOne(TagLib::FileRef& file, int tag) {
	string scan;
	switch (tag) {
	case 0:
		cout << "\nTitle: "; getline(cin, scan); file.tag()->setTitle(scan);
		break;
	case 1:
		cout << "\nArtist: "; getline(cin, scan); file.tag()->setArtist(scan);
		break;
	case 2:
		cout << "\nAlbum: "; getline(cin, scan); file.tag()->setAlbum(scan);
		break;
	case 3:
		cout << "\nYear: "; getline(cin, scan); file.tag()->setYear(stoi(scan));
		break;
	case 4:
		cout << "\nTrack: "; getline(cin, scan); file.tag()->setTrack(stoi(scan));
		break;
	case 5:
		cout << "\nComment: "; getline(cin, scan); file.tag()->setComment(scan);
		break;
	case 6:
		cout << "\nGenre: "; getline(cin, scan); file.tag()->setGenre(scan);
	}
}

int CheckInput(int size) {
	int file = -1;
	string scan = " ";
	cout << "\nWrite a number of the file/tag: "; //how to write more universal?
	cin >> file;
	getline(cin, scan);
	try {
		if (file < 1 || file > size) {
			throw "Incorrect input! ";
		}
		return file - 1;
	}
	catch (string warn) {
		cout << warn << "Enter number between 1 and " << size << "!";
		CheckInput(size);
	}
}

void SelectFile(string& path_str)
{
	string file_name;
	cout << "Enter name or file of folder" << endl;
	getline(cin, file_name);

	fs::directory_iterator it(path_str);

	string new_path = path_str;
	string temp;

	if (new_path.length() >= 4)
	{
		temp = "\\" + file_name;
	}
	else
	{
		temp = file_name;
	}
	
	
	new_path.append(temp);

	for (; !it._At_end(); it++)
	{
		fs::path path = it->path();
		string path_str = path.string();


		if (path_str == new_path && path_str.find(".mp3") != string::npos)
		{
			const char* temp = path_str.c_str();
			TagLib::FileRef f(temp);
			
			PrintTags(f); // TODO 	 выбор выводить или изменять
			break;
		}
		else if (path_str == new_path &&  it->is_directory())
		{
			ShowAllFiles(new_path);
			break;
		}

	}
}
