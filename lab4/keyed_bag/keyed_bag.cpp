// FILE: keyed_bag.cpp
// CLASS IMPLEMENTED keyed_bag
//
// Jonathan Stock

#include <iostream>
#include <cassert>
#include "keyed_bag.h"

using namespace std;

namespace coen79_lab4{
	
	// constructor that initializes the keyed bag to 0
	keyed_bag::keyed_bag(){
		int i;
		// for loop to set each entry to 0
		for(i = 0; i < CAPACITY; ++i){
			keys[i] = ' ';
			data[i] = 0;
		}
		bag_count = 0;
	};

	// erases all the entries in the keys and data arrays
	void keyed_bag::erase(){
		int i;

		// for loop to set each entry to 0
		for(i = 0; i < CAPACITY; ++i){
			keys[i] = ' ';
			data[i] = 0;
		}
		bag_count = 0;
	}

	// erases a specific item associated with the key given
	// returns true if removed else returns false 
	bool keyed_bag::erase(const key_type& key){
		int i;
		// for loop to search through the keys array
		if(has_key(key) == true){
			for(i = 0; i < size(); ++i){
				if(keys[i] == key){
					keys[i] = ' ';
					data[i] = 0;
					for(i; i < size(); ++i){
						data[i] = data[i+1];
						keys[i] = keys[i+1];
					}
					--bag_count;
				}
			}	
			return true;
		}
		else{
			return false;
		}	
	}
	
	// inserts a new entry at the end of the array if the key does not exist already 
	void keyed_bag::insert(const keyed_bag::value_type& entry, const key_type& key){
		assert(size() < CAPACITY && !has_key(key));
		data[size()] = entry;
		keys[size()] = key;
		++bag_count;
	}

	// adds two keyed_bag objects together
	void keyed_bag::operator +=(const keyed_bag& addend){
		assert(size() + addend.size() <= CAPACITY);
		assert(hasDuplicateKey(addend) != true);
		// loops through the addend arrays and adds each to the initial object 
		int i;
		for(i = 0; i < addend.size(); ++i){
			insert(addend.data[i], addend.keys[i]);
		}
	}

	// determines whether the given key is in the keyed_bag's array of keys
	bool keyed_bag::has_key(const keyed_bag::key_type& key) const{
		int i;
		for(i = 0; i < size(); ++i){
			if(keys[i] == key){
				return true;
			}
		}
		return false;
	}
	
	// returns the data value corresponding to the given key 
	keyed_bag::value_type keyed_bag::get(const keyed_bag::key_type& key) const{
		assert(has_key(key) == true);
		int i;
		for(i = 0; i < CAPACITY; ++i){
			if(keys[i] == key){
				return data[i];
			}
		}
	}

	// returns the number of items in the keyed_bag
	keyed_bag::size_type keyed_bag::size() const{
		return bag_count;
	}

	// returns the number of times the target is in the keyed_bag
	keyed_bag::size_type keyed_bag::count(const keyed_bag::value_type& target) const{
		int counter=0;
		int i;
		// loops through the data array, increments counter if target is found
		for(i = 0; i < CAPACITY; ++i){
			if(data[i] == target){
				++counter;
			}
		}
		return counter;
	}

	// returns true if there are duplicate keys otherwise returns false
	bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const{
		// loops through both keys arrays to check if they're equal
		for(int i = 0; i < CAPACITY; ++i){
			if(has_key(otherBag.keys[i])){
				return true;
			}
		}
		return false;
	}

	// adds one keyed_bag to another keyed_bag and returns a new keyed_bag
	keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2){
		assert(b1.size() + b2.size() <= keyed_bag::CAPACITY);
		assert(b1.hasDuplicateKey(b2) == false);

		keyed_bag k;
		k += b1;
		k += b2;

		return k;
	}
};
