#include <iostream>
#include "mystring.h"
#include <cstdlib>  // Provides size_t
#include <string>
#include <cstring>
#include <cassert>

using namespace std;

namespace coen79_lab5
{
    // constructor that creates a string from the character array provided and updates private variables
    string::string(const char str[ ])
    {
        current_length = strlen(str);
        allocated = current_length + 1;
        characters = new char[allocated];
        strncpy(characters, str, allocated);
    }
    // constructor that creates a string from the character provided and updates private variables
    string::string(char c)
    {
        current_length = 1;
        allocated = current_length +1;
        characters = new char[allocated];
        characters[length()-1] = c;
        characters[length()] = '\0';   
    } 
    // constructor that creates a string from the string provided and updates private variables                
    string::string(const string& source)
    {
        characters = new char[source.current_length];
        strncpy(characters, source.characters, source.current_length);
        allocated = source.allocated;
        current_length = source.current_length;

    }

    // destroys string
    string::~string( )
    {
        delete[] characters;
        allocated = 0;
        current_length = 0;
    }
    
    // += operater for strings
    void string::operator +=(const string& addend)
    {
        size_t length = current_length + addend.current_length;
        allocated = length + 1;
        reserve(allocated);
        strncat(characters, addend.characters, addend.current_length);
        current_length = length;
    }

    // += operater for string and character array
    void string::operator +=(const char addend[ ])
    {
        size_t length = current_length + strlen(addend);
        allocated = length + 1;
        reserve(allocated);
        for(int i=current_length; i < length; i++)
        {
            characters[i] = addend[i - current_length];
        }
        current_length = length;
    }

    // adds character to string
    void string::operator +=(char addend)
    {
        size_t length = current_length + 1;
        allocated = length + 1;
        reserve(allocated);
        characters[current_length] = addend;
        current_length = length;
    }

    // reserves space for the string and assigns values
    void string::reserve(size_t n)
    {
        char* new_array = new char[n];
        if(characters != NULL){
            strncpy(new_array, characters, current_length);
            delete [] characters;
        }
        characters = new_array;
        allocated = n;

    }

    // = op to set equal
    string& string::operator =(const string& source)
    {
        this->dlt(0, current_length);
		if(current_length != source.current_length)
        {
            allocated = source.allocated;
			reserve(allocated);
        }
        strncpy(characters, source.characters, source.current_length);
		current_length = source.current_length;
		return *this;
    }
    void string::insert(const string& source, unsigned int position)
    {
        assert(position <= length());
        
        // assigns values
        size_t length = current_length + source.length();
        allocated = length + 1;
        reserve(allocated);

        // loop to move characters length of source positions
        for(int i=current_length-1; i >= position; i--)
        {
            characters[i+source.length()] = characters[i];
        }

        // assigns source characters to the open spaces
        for (int i=0; i < source.length(); i++)
        {
            characters[position + i] = source[i];
        }
        current_length = length;       
    }

    // deletes num amount of characters in the string starting at position 
    void string::dlt(unsigned int position, unsigned int num)
    {
        assert((position + num) <= length());
        for(int i = position; i < length(); i++)
        {
            characters[i] = characters[i + num];
        }
        current_length -= num;
    }

    // replaces character at index position
    void string::replace(char c, unsigned int position)
    {
        assert(position < length());

        characters[position] = c;
    }

    // replaces string starting at index position
    void string::replace(const string& source, unsigned int position)
    {
        assert((position + source.length()) <= length());
        for(int i = 0; i < source.length(); i++)
        {
            characters[position + i] = source[i];
        }
    }
    
    // index operator 
    char string::operator [ ](size_t position) const
    {
        assert(position < length());
		return characters[position];
        
    }
    int string::search(char c) const
    {
        // loops through characters and returns index if char is found
        for(int i=0; i < length(); i++)
        {
            if(characters[i] == c){return i;}
        }
        return -1;
    }
    int string::search(const string& substring) const
    {
        int index = -1;
        bool flag = false;
        int j;
        // traverses characters
        for(int i=0; i < current_length; i++)
        {
            // traverses the next characters that match the substring - breaks out of loop if not equal
            for(j=0; j < substring.length(); j++)
            {
                if(characters[i+j] == substring.characters[j])
                {
                    flag = true;
                }
                else
                {
                    flag = false;
                    break;
                }
            }
            // returns starting index
            if(j==substring.length() && flag)
            {
                return i;
            }
        }
        return -1;
    }
    unsigned int string::count(char c) const
    {
        int temp = 0;

        // loops through characters and adds to temp if chars match
        for(int i=0; i < length(); i++)
        {
            if(characters[i] == c){temp++;}
        }
        return temp;
    }
    
    // cout << string
    std::ostream& operator <<(std::ostream& outs, const string& source)
    {
        outs << source.characters;
    	return outs;
    }

    // tests all types of comparisons

    bool operator ==(const string& s1, const string& s2)
    {
        return (strcmp(s1.characters, s2.characters) == 0);
    }
    bool operator !=(const string& s1, const string& s2)
    {
        return (strcmp(s1.characters, s2.characters) != 0);
    }
    bool operator > (const string& s1, const string& s2)
    {
        return (strcmp(s1.characters, s2.characters) > 0);
    }
    bool operator < (const string& s1, const string& s2)
    {
        return (strcmp(s1.characters, s2.characters) < 0);
    }
    bool operator >=(const string& s1, const string& s2)
    {
        return ((s1 > s2) || (s1 == s2));
    }
    bool operator <=(const string& s1, const string& s2)
    {
        return ((s1 < s2) || (s1 == s2));
    }

    // adds two strings together and returns a new string
    string operator +(const string& s1, const string& s2)
    {
        string final;
        final.reserve(s1.length() + s2.length() + 1);
        final += s1;
        final += s2;
        return final;
    }

    // adds string and character array and returns a new string
    string operator +(const string& s1, const char addend[ ])
    {
        string final;
        final.reserve(s1.length() + strlen(addend) + 1);
        final += s1;
        final += addend;
        return final;
    }

    // cin >> string
    std::istream& operator >> (std::istream& ins, string& target)
    {
        char temp[100];
        ins >> temp;
        target.dlt(0, target.length());
        target += temp;
    	return ins;
    }
}