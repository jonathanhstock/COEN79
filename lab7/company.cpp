// FILE: company.cpp
// CLASS implemented: company (see company.h for documentation)


#include <cassert>
#include "company.h"

//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

namespace coen79_lab7
{
    // creates a company
    company::company() {
        this->company_name = "";
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    // creates a company with given name
    company::company(const std::string& company_name) {
        assert(company_name.length() > 0);

        this->company_name = company_name;
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    // copy constructor
    company::company(const company &src) {
        Debug("Company copy constructor..." << std::endl);

        // COMPLETE THE IMPLEMENTATION...
        head_ptr = NULL;
        tail_ptr = NULL;
        *this = src;
    }

    // assignment operator setting this equal to the source
    company& company::operator= (const company &src) {
        Debug("Company assignemnt operator..." << std::endl);

        // COMPLETE THE IMPLEMENTATION...
        if(this == &src)
            return *this;
 
        list_clear(head_ptr);
        
        head_ptr = NULL;
        tail_ptr = NULL;

        list_copy(src.head_ptr, head_ptr, tail_ptr);
        
        company_name = src.company_name;      
        return *this;

    }
    
    // destructor for the list
    company::~company() {
        list_clear(head_ptr);
    }
    
    // gets company name
    std::string company::get_name() const {
        return company_name;
    }
    
    // gets head
    const node *company::get_head() const {
        return head_ptr;
    }
    
    // gets tail
    const node *company::get_tail() const {
        return tail_ptr;
    }
    
    // gets head
    node* company::get_head() {
        return head_ptr;
    }
    
    // gets tail
    node* company::get_tail() {
        return tail_ptr;
    }
    
    // prints all items in the list
    void company::print_items() {
        list_print(head_ptr);
    }
    
    // inserts a node at the end of the list and returns true if success else false
    bool company::insert(const std::string& product_name, const float& price) {
        
        assert(product_name.length() > 0);

        // if list contains duplicate
        if (list_contains_item(head_ptr, product_name)) {
            return false;
        }
        
        // if list is empty 
        if (head_ptr == NULL) {
            list_init(head_ptr, tail_ptr, product_name, price);

        }

        // if list is not empty
        else {
            // COMPLETE THE IMPLEMENTATION...
            list_tail_insert(tail_ptr, product_name, price);
        }
        
        return true;
    }

    // erases the company with the product
    bool company::erase(const std::string& product_name) {
        assert(product_name.length() > 0);

        node *cursor;
        node *temp;

        // if list is empty or has 1 product
        if(head_ptr->getLink() == NULL || head_ptr == NULL)
        {
            if(head_ptr->getName() == product_name)
            {
                head_ptr = NULL;
                return true;
            }
            else {return false;}
        }
        
        // loops to get the product name and reassigns the pointers to skip cursor once reaches product
        temp = head_ptr;
        for (cursor = head_ptr->getLink(); cursor != NULL; cursor = cursor->getLink( ))
        {
            if (product_name == cursor->getName( ))
            {
                temp->setLink(cursor->getLink());
                delete cursor;
                return true;
            }
            temp = temp->getLink();
        }        
        return false;
    }
    
    
}
