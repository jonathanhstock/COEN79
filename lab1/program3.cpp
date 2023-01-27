#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char*argv[]){
	
	//Checks to see if there is a text file given in the command line when running the program
	if(argc != 2){
		cout<< "Error, please enter the name of the text file"<<endl;
		return 0;
	}
	
	ifstream file(argv[1]);
	
	string temp;
	//Loops through the entire file checking to see if there are still words left
	while (file>>temp){	
		
		//Checks to see if temp is bigger then 10 otherwise skips to next word
		if(temp.length()>=10){
			//Loops through each word checking if it has punctuation and removes them, else converts to uppercase
			for(int i=0; i<temp.length(); i++){
				if(ispunct(temp[i])){
					temp.erase(i--,1);
	
				}
				else{
					temp[i]=toupper(temp[i]);
				}
			}
			
			//if the temp's length is still bigger than 10 then print temp
			if(temp.length()>=10){
				cout<<temp<<endl;
			}
		}
	}
	file.close();	
	return 0;
}
