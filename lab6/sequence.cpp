//FILE: sequence.cpp
//CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
//INVARIANT for the sequence class
//  1. The number of items in the sequence is stored in the member variable "many_nodes"
//
//  2. For an empty sequence, we do not care what is stored in any of data and head_ptr
//      and tail_ptr point to NULL; for a non-empty sequence, the items stored in the
//      sequence can be accessed using head_ptr and tail_ptr and we don't care what is
//      stored in the rest of the data.
//
//  3. If there is a current item, then it lies in *cursor; if there is no
//     current item, then cursor* equals NULL.
//
//  4. If there is a previous item, then it lies in precursor*.  If there is no previous
//       item, then precursor equals NULL.


#include <iostream>
#include <algorithm> //provides copy function
#include <cassert> //for assert function
#include "sequence.h" //header file for class
#include "node.h" // provides node class

using namespace std; //For copy function

namespace coen79_lab6
{
    // Default private member variable initialization function.
    void sequence::init()
    {
        //Initializing pointers to NULL
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        //Initializiing many_nodes (or our counter) to 0
        many_nodes = 0;
    }

    //CONSTRUCTOR IMPLEMENTATION for default constructor
    sequence :: sequence ()
    {
        init();
    }

    //Copy Constructor
    sequence :: sequence(const sequence& source)
    {
        init();
        *this = source;
    }

    // destructor
    sequence::~sequence( ) 
    {
        list_clear(head_ptr);
        many_nodes = 0;
    }
        
    // sets cursor to the start of the sequence
    void sequence::start( )
    {
        if(many_nodes > 0)
        {
            cursor = head_ptr;
            precursor = NULL;
        }
        else
        {
            cursor = NULL;
            precursor = NULL;
        }
    }

    // sets cursor to the end
    void sequence::end()
    {
        // initial condition
        cursor = tail_ptr;

        // sets it to NULL if 0
        if(many_nodes == 0)
        {
            cursor = NULL;
            precursor = NULL;
            return;
        }

        // sets precursor to null
        if(many_nodes == 1)
        {
            precursor = NULL;
        }
        else
        {
            precursor = head_ptr;
            while(precursor->link() != cursor)
            {
                precursor = precursor->link();
            }
        }

    }

    // advance the cursor one to the right
    void sequence::advance( )
    {
        assert(is_item());
        
        // cursor advances to null if at tail
        if (cursor == tail_ptr)
        {
            cursor = NULL;
            precursor = tail_ptr;
            return;
        }
        precursor = cursor;
        cursor = cursor->link();
    }

    // insert value in front of the current
    void sequence::insert(const value_type& entry)
    {
        //inserts in empty list
        if(head_ptr == NULL)
        {
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            precursor = NULL;
            tail_ptr = head_ptr;
            ++many_nodes;
        }
        //inserts if current at head
        else if(cursor == head_ptr)
        {
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            precursor = NULL;
            ++many_nodes;
        }
        //inserts if current not at head
        else if(cursor != head_ptr)
        {
            if (cursor == NULL)
            {
                list_head_insert(head_ptr, entry);
                cursor = head_ptr;
                precursor = NULL;
                if(many_nodes == 0) {tail_ptr = cursor;}
                ++many_nodes;
                return;
            }
            list_insert(precursor, entry);
            cursor = precursor->link();
            ++many_nodes;
        }     
    
    }

    // attaches value behind the current
    void sequence::attach(const value_type& entry)
    {
        //inserts in empty list
        if(head_ptr == NULL)
        {
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            precursor = NULL;
            tail_ptr = head_ptr;
            ++many_nodes;
            
        }
        //inserts if current at head // diff
        else if(cursor == head_ptr)
        {
            list_insert(head_ptr, entry);
            cursor = head_ptr->link();
            if(cursor->link() == NULL) {tail_ptr = cursor;}
            precursor = head_ptr;
            ++many_nodes;
        }
        //inserts if current not at head
        else if(cursor != head_ptr)
        {
            if(cursor == NULL)
            {
                list_insert(tail_ptr, entry);
                tail_ptr = tail_ptr->link();
                cursor = tail_ptr;

                node *temp = head_ptr;
                while(temp != NULL)
                {
                    if(temp->link() == cursor)
                    {
                        precursor = temp;
                        break;
                    }
                    temp = temp->link();
                }
                ++many_nodes;
                return;
            }
            
            if(cursor == tail_ptr)
            {
                list_insert(tail_ptr, entry);
                precursor = cursor;
                cursor = cursor->link();
                tail_ptr = cursor;
                //precursor = precursor->link();
                ++many_nodes;
                return;
            }
            list_insert(cursor, entry);
            cursor = cursor->link();
            precursor = precursor->link();
            ++many_nodes;
        }

    }

    // = operater
    void sequence::operator =(const sequence& source)
    {
        if(this == &source)
            return;
        list_clear(head_ptr);
        many_nodes = 0;
        list_copy(source.head_ptr, head_ptr, tail_ptr);
        cursor = head_ptr;
        

        node* temp = source.head_ptr;
        if(source.cursor == NULL){
            cursor = NULL;
            precursor = tail_ptr;
        }
        else
        {
            precursor = head_ptr;
            while(temp != source.precursor)
            {
                temp = temp->link();
                precursor = precursor->link();
            }
            if(precursor != NULL)
            {
                cursor = precursor->link();
            }
            
        }
        many_nodes = source.many_nodes;

    }
    
    // removes value at the current
    void sequence::remove_current( )
    {
        if(many_nodes == 0)
        {
            return;            
        }
        //deletes if current at head // diff
        else if(cursor == head_ptr)
        {
            if(cursor->link() != NULL)
            {
                cursor = cursor->link();
                list_head_remove(head_ptr); 
                precursor = NULL;
            }
            else
            {
                list_head_remove(head_ptr);
                tail_ptr = NULL;
                cursor = NULL;
                precursor = NULL;
            }
            
            --many_nodes;
        }
        //deletes if current not at head
        else if(cursor != head_ptr)
        {
            if(cursor == NULL) {return;}
            if(cursor == tail_ptr)
            {
                
                list_remove(precursor);
                cursor = NULL;
                tail_ptr = precursor;
                --many_nodes;
                return;
            }

            cursor = cursor->link();
            list_remove(precursor);
            --many_nodes;
        }    
    }
    
    // CONSTANT MEMBER FUNCTIONS

    // returns many_nodes
    sequence::size_type sequence::size( ) const
    {
        return many_nodes;
    }

    // tests if it is an item
    bool sequence::is_item( ) const
    {
        if(cursor != NULL){return true;}
        else {return false;}
    }

    // returns data at current
    sequence::value_type sequence::current( ) const
    {
        assert(is_item() == true);
        return cursor->data();
    }
    
}
