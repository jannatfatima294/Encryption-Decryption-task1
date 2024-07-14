#include<iostream>
#include<cstring>
#include<fstream>
#include<cctype>
#include<limits>
#include<cstdlib>
using namespace std;
string Encrypt(const string& text, int shift){ //function for encryption
	string result= "";
	for (size_t i = 0; i < text.length(); ++i) {
        char c = text[i];
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            result += (c - base + shift) % 26 + base;
        } else {
            result += c;
        }
    }
    return result;
}

string Decrypt(const string& text, int shift){ //function for decryption
	return Encrypt(text, 26-(shift%26));
}
string ReadFile(const string& filename){ // function for reading content
	ifstream file(filename.c_str());
	if (!file){
		cerr<< " Error: file is not opening "<<filename<<endl;
		exit(EXIT_FAILURE);
	}
	string content((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
    file.close();
    return content;
}
void WriteFile(const string& filename, const string& content){// function for writing content
	ofstream file(filename.c_str());
	if (!file){
		cerr<<" Error: file is not opening "<<filename<<endl;
		exit(EXIT_FAILURE);
	}
	file<<content;
	file.close();
}
int ValidShift(){ //function for getting a valid shift value
int shift;
while(true){
	cout<<" Enter value to shift (0-25) :"<<endl;
	cin>>shift;
	if (cin.fail() || shift < 0 || shift > 25) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cerr << "Invalid input. Please enter an integer between 0 and 25." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            return shift;
        }
}
}
int main(){
	string infile, outfile;
	int shift;
	char choice;
	cout<<" Enter 'E' for Encryption and 'D' for Decryption :"<<endl;
	cin>>choice;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	if (choice != 'E' && choice != 'e' && choice != 'D' && choice != 'd') {
        cerr << "Invalid choice! Please enter 'E' for encryption or 'D' for decryption." << endl;
        return 1;
    }
	cout << "Enter the input file name: ";
    getline(cin, infile);

    cout << "Enter the output file name: ";
    getline(cin, outfile);

    shift = ValidShift();

    string content = ReadFile(infile);
    string result;

    if (choice == 'E' || choice == 'e') {
        result = Encrypt(content, shift);
    } else if (choice == 'D' || choice == 'd') {
        result = Decrypt(content, shift);
    }

    WriteFile(outfile, result);

    cout << "Operation completed successfully." << endl;

    return 0;
}
