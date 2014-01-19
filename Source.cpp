#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main (int argc, char* argv[]) 
{
	srand (time(NULL));

	const char* fname = "myfile1.txt";
	string outStr = "This is a trial line to be written to the file (çğıöşüÇĞİÖŞÜ)";
	stringstream tempStringStream(ios_base::in | ios_base::out | ios_base::app);	//ios::app is implementation dependent

	ofstream myOutFile(fname, ios_base::trunc);
	if(!myOutFile.is_open()) {
		throw invalid_argument("File could not be opened!!!");
	}

	for(int i = 0, randLine = rand() % 10 + 10; i < randLine; i++) {
		int tempLength = rand() % 20;
		myOutFile << outStr.substr(0, outStr.size() - tempLength) << endl;
	}
	myOutFile.close();

	ifstream myInFile(fname);	//ios_base::in
	if(!myInFile.good()) {
		throw (std::exception("File could not be opened!!!"));
	}
	streampos pos = myInFile.tellg();
	cout << "acilan dosyada son pozisyon: " << pos << endl;
	myInFile.seekg((streamoff)0, ios_base::end);
	pos = myInFile.tellg();
	cout << "acilan dosyada son pozisyon: " << pos << endl;
	myInFile.seekg(0, ios_base::beg);

	string tempLine;
	getline(myInFile, tempLine);										//bir satır okuyoruz
	pos = myInFile.tellg();												//streamdeki karakter pozisyonumuz
	cout << "tek satir okunduktan sonra pozisyon: " << pos << endl;		//şu anda ikinci satırın ilk karakteri pozisyonundayız
	myInFile.seekg(-3, ios_base::cur);									//ikinci satırın başından birinci satırın sonuna gidiyoruz (CR|LF iki karakter)
	char c = myInFile.get();											//ilk satırın son karakteri
	cout << "siradaki karakter: [" << c << "]" << endl;
	myInFile.seekg(0, ios_base::beg);									//tekrardan en başa döndük

	unsigned int count = 0, lastSize;
	while(getline(myInFile, tempLine)) {
		lastSize = tempLine.size();
		count += lastSize;
		tempStringStream << tempLine << " [" << lastSize << " bytes]" << endl;
	}
	myInFile.close();

	ofstream myOutFile2("myfile2.txt", ios_base::trunc);
	if(myOutFile2.is_open() && tempStringStream.good()) {
		myOutFile2 << tempStringStream.rdbuf();				//recommended way for STRINGSTREAM to OFSTREAM
		for(int i = 0; i < lastSize; i++) {
			myOutFile2 << "-";
		}
		myOutFile2 << "\nTotal size: " << count << " bytes." << endl;

		myOutFile2.close();
	}


	/*ifstream myfile("example2.txt", ios::binary);
	if(myfile.is_open()) {
		string line;
		unsigned count = 0;

		while(getline(myfile, line)) {
			cout << ++count << "\t" << line << endl;
		}
		
		myfile.close();
	}

	cout << "dosya okundu" << endl;

	ifstream ifstreamBinaryRead("example2.txt", ios_base::binary | ios_base::ate);
	if(ifstreamBinaryRead.is_open()) {
		streampos boyut = ifstreamBinaryRead.tellg();
		char* blok = new char[boyut];
		ifstreamBinaryRead.seekg(0, ios_base::beg);
		ifstreamBinaryRead.read(blok, boyut);		//fastest read(&content[0],)
		ifstreamBinaryRead.close();

		cout << "file is: " << boyut << " bytes." << endl;
	}
	else {
		cout << "hata oluştu" << endl;	
	}*/

	system("PAUSE");

  return 0;
}