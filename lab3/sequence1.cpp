// FILE: sequence1.cpp
// CLASS IMPLEMENTED: sequence

//Jonathan Stock


#include <iostream>
#include <cassert>
#include <cmath>
#include "sequence1.h"

using namespace std;

namespace coen79_lab3{

	//constructor for constructing the sequence objects
	sequence::sequence(){
		//for loop to initialize everything to 0
		for(int i = 0; i < CAPACITY; i++){
			data[i] = 0;
		}
		used = 0;
		current_index = 0;	
	}

	//sets current_index to 0
	void sequence::start(){
		current_index = 0;	
	}

	//sets current_index to the last item in the sequence
	void sequence::end(){
		assert(used>0);
		current_index = used-1;
	}

	//sets current_index to the last space in the array
	void sequence::last(){
		current_index = CAPACITY-1;
	}
	
	//increments current_index if it is less than the amount of items in the sequence
	void sequence::advance(){
		assert(is_item() == true);
		if(current_index < used){
			current_index++;
		}
	}
	
	//decrements the current_index if it is not the first spot in the sequence
	void sequence::retreat(){
		if(current_index != 0){
			current_index--;
		}
	}

	//inserts an entry into the first spot if there are no items
	//otherwise inserts it before the current index
	void sequence::insert(const value_type& entry){
		assert(size() < CAPACITY);
		if(is_item() == false){
			insert_front(entry);
		}
		else{
			//shifts all of the entries up by 1 index
			for(size_type i = size(); i>current_index; i--){
				data[i] = data[i-1];
			}
			data[current_index] = entry;
			used++;
		}

	}

	//attaches an entry at the end of the sequence
	//otherwise attaches it before the current index
	void sequence::attach(const value_type& entry){
		assert(size() < CAPACITY);
		if(is_item() == false){
			attach_back(entry);
		}
		else{
			current_index++;
			//shifts all entries up by 1 index
			for(size_type i = size(); i>current_index; i--){
				data[i]=data[i-1];
			}
			data[current_index] = entry;
			used++;
		}
		
	}

	//removes the entry at the current index
	void sequence::remove_current(){
		assert(is_item() == true);
		//shifts all items after the current index down
		for(size_type i = current_index; i<size(); i++){
			data[i] = data[i+1];
		}
		used--;
	}

	//inserts a new entry at the front of the sequence
	void sequence::insert_front(const value_type& entry){
		assert(size() < CAPACITY);
		//shifts all items up by 1 index
		for(size_type i=size(); i>0; i--){
			data[i] = data[i-1];
		}
		data[0] = entry;
		used++;
		current_index = 0;
	}

	//attaches an entry at the back of the sequence
	void sequence::attach_back(const value_type& entry){
		assert(size() < CAPACITY);
		data[size()] = entry;
		current_index = size();
		used++;
	}

	//removes the first entry in the sequence
	void sequence::remove_front(){
		assert(is_item() == true);
		//shifts all entries down by 1 index
		for(size_type i = 0; i<size(); i++){
			data[i] = data[i+1];
		}
		used--;
		current_index = 0;
	}
	
	//loops through the new sequence and adds each entry to the initial sequence
	void sequence::operator+= (const sequence& rhs){
		for(size_type i=0; i<rhs.size(); i++){
			attach_back(rhs.data[i]);
		}
	}

	//returns the used variable
	sequence::size_type sequence::size() const{
		return used;
	}

	//returns true if there is an item at the index else returns false
	bool sequence::is_item() const{
		return (current_index<used);
	}

	//returns the entry at the current index
	sequence::value_type sequence::current() const{
		assert(is_item() == true);
		return data[current_index];
	}

	//returns the current index of a specific sequence
	sequence::value_type sequence::operator[] (sequence::size_type index) const{
		assert(index<used);
		return data[index];
	}

	//returns the mean of the sequence
	double sequence::mean() const{
		double mean = 0.0;
		double sum = 0.0;
		//loops through the sequence to calculate the sum of all entries
		for(size_type i=0; i<size(); i++){
			sum += data[i];
		}
		mean = sum/size();
		return mean;
	}

	//returns the standard deviation of the sequence
	//https://www.programiz.com/cpp-programming/examples/standard-deviation
	double sequence::standardDeviation() const{
		double standardDeviation = 0.0;
		//loops through to calculate the variance of the sequence
		for(size_type i=0; i<size(); i++){
			standardDeviation += pow(data[i] - mean(), 2);
		}
		return sqrt(standardDeviation/size());
	}

	//adds two sequence objects together and returns a new sequence
	sequence operator+ (const sequence& lhs, const sequence& rhs){
		sequence s1;
		s1 += lhs;
		s1 += rhs;
		return s1;
	}

	//returns the sum of the sequence
	sequence::value_type summation(const sequence& s){
		sequence::value_type sum = 0.0;
		//loops through the sequence to calculate the sum of all the entries
		for(sequence::size_type i = 0; i<s.size(); i++){
			sum += s[i];
		}
		return sum;
	}
}

