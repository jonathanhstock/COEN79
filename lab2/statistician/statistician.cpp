// FILE: statistician.cpp
// CLASS IMPLEMENTED: statistician (see stats.h for documentation)

#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include "statistician.h"

using namespace std;

namespace coen79_lab2{

	//constructor to set the private variables equal to the parameter variables
	statistician::statistician(double total, int size, double min, double max, double avg){
		this->total = total;
		this->size = size;
		this->min = min;
		this->max = max;
		this->avg = avg;
	}
	
	//adds a new number to the sequence and updates all the private variables
	void statistician::next(double r){
		total += r;
		size +=1;
		if(min == 0 && max == 0){
			min = r;
			max = r;
		}
		else if(min > r){
			min = r;
		}
		else if(max < r){
			max = r;
		}
		avg = total/size;
	}
	
	//resets all of the private variables to 0
	void statistician::reset(){
		total = 0;
		size = 0;
		min = 0;
		max = 0;
		avg = 0;
	}
	
	//returns the size of the sequence
	int statistician::length() const{
		return size;
	}

	//returns the total sum of the sequence
	double statistician::sum() const{
		return total;
	}
	
	//returns the mean of the sequence
	double statistician::mean() const{
		assert(size > 0);
		return avg;	
	}

	//returns the minimum number in the sequence
	double statistician::minimum() const{
		assert(size > 0);
		return min;
	}

	//returns the maximum number in the sequence
	double statistician::maximum() const{
		assert(size > 0);
		return max;
	}

	//overloading the + operator so we can add the values of 2 different statistician
	//objects
	statistician operator +(const statistician& s1, const statistician& s2){
		double total1 = s1.total + s2.total;
		int size1 = s1.size + s2.size;
		double min1; 
		double max1;
		if(s1.min < s2.min){
			min1 = s1.min;
		}
		else{
			min1 = s2.min;
		}
		if(s1.max > s2.max){
			max1 = s1.max;
		}
		else{
			max1 = s2.max;
		}
		double avg1 = total1/size1;
			
		return statistician(total1, size1, min1, max1, avg1);		
	}
	
	//overloading the * operator so we can multiply each of the statistician
	//object private variables by a scale provided
	statistician operator *(double scale, const statistician& s){
		double total1 = scale*s.total;
		double min1;
		double max1;
		if(scale < 0){
			min1 = scale*s.max;
			max1 = scale*s.min;
		}
		else{
			min1 = scale*s.min;
			max1 = scale*s.max;
		}
		double avg1 = scale*s.avg;
		
		return statistician(total1, s.size, min1, max1, avg1); 
	}
	
	//overloading the == operator so we can check if each of the statistician
	//objects' private variables are equal to each other
	bool operator ==(const statistician& s1, const statistician& s2){
		return ((s1.length() == s2.length()) && (s1.sum() == s2.sum()) && 
				(s1.minimum() == s2.minimum()) && (s1.maximum() == s2.maximum()) 
				&& (s1.mean() == s2.mean())); 
	}		
    
}


