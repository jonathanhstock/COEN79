#include <iostream>
#include <cassert>
#include "random.h"

using namespace std;

namespace coen79_lab2{
	
	//constructor to set the class's private variables equal to the parameter variables
	rand_gen::rand_gen(int seed, int multiplier, int increment, int modulus){
		this->seed = seed;
		this->multiplier = multiplier;
		this->increment = increment;
		this->modulus = modulus;	
	}

	//sets the class's private variable seed equal to the parameter newSeed
	void rand_gen::set_seed(int newSeed){
		seed = newSeed;
	}
	
	//creates a temp seed and calculates the value of it given private variables 
	//and sets the value of the class seed equal to the temp seed
	int rand_gen::next(){
		int newSeed;
		newSeed = ((multiplier*seed+increment)%modulus);
		seed = newSeed;
		return seed;
	}

	//prints each private variable from the class
	void rand_gen::print_info(){
		cout<<"Seed: "<<seed<<endl;
		cout<<"Multiplier: "<<multiplier<<endl;
		cout<<"Increment: "<<increment<<endl;
		cout<<"Modulus: "<<modulus<<endl;
	}
}
