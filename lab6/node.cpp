// FILE: node.cpp
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
//
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include "node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
#include <iostream>

using namespace std;

namespace coen79_lab6
{
    size_t list_length(const node* head_ptr)
    // Library facilities used: cstdlib
    {
	const node *cursor;
	size_t answer;

	answer = 0;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
	    ++answer;

	return answer;
    }

    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
    	head_ptr = new node(entry, head_ptr);
    }

    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
    	node *insert_ptr;

    	insert_ptr = new node(entry, previous_ptr->link( ));
    	previous_ptr->set_link(insert_ptr);
    }

    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	const node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	const node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    void list_head_remove(node*& head_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = head_ptr;
    	head_ptr = head_ptr->link( );
    	delete remove_ptr;
    }

    void list_remove(node* previous_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = previous_ptr->link( );
    	previous_ptr->set_link( remove_ptr->link( ) );
    	delete remove_ptr;
    }

    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
    {
    	while (head_ptr != NULL)
    	    list_head_remove(head_ptr);
    }


    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
    {
    	head_ptr = NULL;
    	tail_ptr = NULL;

    	// Handle the case of the empty list.
    	if (source_ptr == NULL)
    	    return;

    	// Make the head node for the newly created list, and put data in it.
    	list_head_insert(head_ptr, source_ptr->data( ));
    	tail_ptr = head_ptr;

    	// Copy the rest of the nodes one at a time, adding at the tail of new list.
    	source_ptr = source_ptr->link( );
    	while (source_ptr != NULL)
    	{
    	    list_insert(tail_ptr, source_ptr->data( ));
    	    tail_ptr = tail_ptr->link( );
    	    source_ptr = source_ptr->link( );
    	}
    }

	// pieces the list together
	void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr)
	{
		head_ptr = NULL;
        tail_ptr = NULL;

        if(start_ptr == end_ptr || start_ptr == NULL)
            return;

        list_head_insert(head_ptr, start_ptr->data( ));
        start_ptr = start_ptr->link( );
        tail_ptr = head_ptr;

        while (start_ptr != end_ptr)
        {
            list_insert(tail_ptr, start_ptr->data( ));
            tail_ptr = tail_ptr->link( );
            start_ptr = start_ptr->link( );
            
        }
	}

	// counts the occurences of target
    size_t list_occurrences(node* head_ptr, const node::value_type& target)
	{
		// assert(head_ptr == )

		node *cursor;
		int counter = 0;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
		{
    	    if (target == cursor->data())
			{
				counter++;
			}
		}
    	return counter;
	}

	// inserts at position
    void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position)
	{
        assert(position > 0 && position <= list_length(head_ptr)+1);

        if(position == 1)
        {
            list_head_insert(head_ptr, entry);
            return;
        }

        node* ptr = list_locate(head_ptr, position-1);

        if(ptr != NULL)
            list_insert(ptr, entry);
	}

	// removes a value at position
    node::value_type list_remove_at(node*& head_ptr, size_t position)
	{

		assert(position > 0 && position <=list_length(head_ptr));

		
		node::value_type temp = list_locate(head_ptr,position)->data();
		if(position == 1)
		{
			list_head_remove(head_ptr);
			return temp;	
		}
		else
		{
			list_remove(list_locate(head_ptr, position-1));
			return temp;
		}
	}

	// copies the segment
    node* list_copy_segment(node* head_ptr, size_t start, size_t finish)
	{
		assert((1 <= start) && (start <= finish) && (finish <= list_length(head_ptr)));
        
        if(head_ptr == NULL)
            return head_ptr;

		node *new_head = NULL;

        node* ptr = list_locate(head_ptr, start);
        list_head_insert(new_head, ptr->data( ));
		if (start == finish) {return new_head;}
		node* temp = new_head;
        for(++start; start <= finish; ++start)
        {
            ptr = list_locate(head_ptr, start);
            list_insert(temp, ptr->data( ));
			temp = temp->link();
        }
        return new_head;
	}

	// prints out the nodes and places commas in some of them
	void list_print (const node* head_ptr)
	{
		
		if(head_ptr == NULL)
		{
			cout << endl;
            return;
		}
		const node *cursor = head_ptr;
		
		while(cursor != NULL) //&& cursor->link() != NULL)
		{
			if(cursor->link() == NULL) {cout << cursor->data() << endl;}	
    	    else {cout << cursor->data() << ", ";}
			cursor = cursor->link();
		}
		
	}

	// removes the duplicates of the list
    void list_remove_dups(node* head_ptr)
	{
		if(head_ptr == NULL)
            return;
        
        node* ptr1 = head_ptr;
        node* ptr2;

        while(ptr1 != NULL)
        {
            ptr2 = ptr1;

            while(ptr2->link( ) != NULL)
            {
                if(ptr1->data( ) == ptr2->link( )->data( ))
                {
					node* ptr3 = ptr2->link();
					ptr2->set_link(ptr3->link());
					delete ptr3;
				}
                else
                    ptr2 = ptr2->link( );
            }
            ptr1 = ptr1->link( );
        }
	}

	// detects if there is a loop
    node* list_detect_loop (node* head_ptr)
	{
		
        node *slow = head_ptr;
		node*fast = head_ptr;
        
        while(slow != NULL && fast != NULL && fast->link() != NULL) 
		{
            
            slow = slow->link();               //Slow moves by 1 step
            fast = fast->link()->link();        //Fast moves by two steps
            
            if(slow==fast) //If they meet then there is a loop
                break;
        }
        if(fast == NULL || fast->link() == NULL)
		{
			return NULL;
		}

        slow = head_ptr;

		while(slow != fast)
		{
			slow = slow->link();
			fast = fast->link();
		}
		return slow;
	}
}
