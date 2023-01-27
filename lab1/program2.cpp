#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

int main(){
	string in;
	cout<<"Please enter 10 digits(with no spaces): ";
	cin>>in;
	string str = in;
	//Checks to see if there is a string of 10 digits no more no less, prints error and aborts if not 10 digits
	if(in.length() != 10){
		cout<<"Error, please enter a 10 digit number\n";
		cout<<"You entered: ";
		abort;
	}
	
	//Reverses the 2nd copy of the input
	reverse(str.begin(), str.end());
	cout<<in<<"\n"<<"\n";
	//Keeps track of a spacer to space out each line correctly
	int spacer = 0;
	//Prints out the original string and reversed string on each line indenting each line by 2 spaces
	for(int i = 0; i < 5; i++){
		cout<<setw(5+spacer)<<' '<<in;
		cout<<setw(10)<<' ';
		cout<<str<<"\n";
		spacer+=2;
	}
	return 0;
}
