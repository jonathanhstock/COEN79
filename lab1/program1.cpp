#include <iostream>
#include <string>

using namespace std;
	
int main(){
	string str;
	cout<<"Please input some text: ";
	getline(cin,str);
	
	int count_isalnum = 0;
	int count_notalnum = 0;	
	//This for loop iterates through the entire string to check each character
	for (int i = 0; i < str.length(); i++){
		//This if statement checks if the character is a space and moves to the next character
		if(str[i] == ' '){
			continue;
		}
		//This else if statement checks if the character is alphanumeric and increments the alnum counter if it is
		else if (isalnum(str[i])){
			count_isalnum++;
		}
		//This else statement increments the notalnum counter since the character can only be non-alphanumeric
		else{
			count_notalnum++;
		}
	}

	cout<<str<<" has "<<count_isalnum<<" alphanumeric characters and "<<count_notalnum<<" non-alphanumeric characters\n";	
}
