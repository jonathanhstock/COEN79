// FILE: database.cpp
// CLASS implemented: database (see database.h for documentation)

// INVARIANT for the database ADT:
//   1. The items in the database are stored in a dynamic array, where each entry of the array includes
//      a company name, a pointer to the head of the linked list of products, and a
//      a pointer to the tail of the linked list of products
//   2. The number of slots in the array of companies is stored in member varibale aloc_slots
//   3. The number of used slots of the array of companies is stored in member varibale used_slots


#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "database.h"


//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif


namespace coen79_lab7
{
    // creates a database with initial capacity
    database::database(const size_type& initial_capacity) {
        used_slots = 0;
        aloc_slots = initial_capacity;
        company_array = new company[aloc_slots];
    }
    
    // copy constructor
    database::database(const database &src) {
        Debug("Copy constructor..." << std::endl);

        // COMPLETE THE IMPLEMENTATION...
        company_array = NULL;
        *this = src;
        
    }
    
    // assignment operator setting this equal to rhs
    database& database::operator= (const database &rhs) {
        Debug("Assignment operator..." << std::endl);
        std::cout << "copying elements of database..." ;

        // COMPLETE THE IMPLEMENTATION...
        if(this == &rhs)
            return *this;

        delete [] company_array;
        company_array = new company[rhs.aloc_slots];
        std::copy(rhs.company_array, rhs.company_array + rhs.used_slots, company_array);
        used_slots = rhs.used_slots;
        aloc_slots = rhs.aloc_slots;
        return *this;        
        
    }
    
    // destructor
    database::~database() {
        // COMPLETE THE IMPLEMENTATION...
        delete [] company_array;
        aloc_slots = 0;
        used_slots = 0;
    }
    
    // reserves database with new capacity
    void database::reserve(size_type new_capacity) {
        Debug("Reserve..." << std::endl);

        
        if (new_capacity == aloc_slots)
            return; // The allocated memory is already the right size.
        
        if (new_capacity < used_slots)
            new_capacity = used_slots; // Cannot allocate less than we are using.
        
        // COMPLETE THE IMPLEMENTATION...
        aloc_slots = new_capacity;

        // creates a new array and copies old array into new array and reassigns
        company *newArray = new company[aloc_slots]; 

        
        std::copy(company_array, company_array + used_slots, newArray);
        delete [] company_array;
        
        company_array = newArray;
        
        
    }
    
    // inserts a company at the end of the array
    bool database::insert_company(const std::string &entry) {
        
        Debug("Insert company..." << std::endl);

        assert(entry.length() > 0);
        
        size_type pos = search_company(entry);
        
        // If you find a company that is false, because there are duplicates
        if (pos != COMPANY_NOT_FOUND) {
            return false;
        }

        // COMPLETE THE IMPLEMENTATION...
        // if array is full then double capacity 
        if(used_slots == aloc_slots)
        {

            reserve(2*aloc_slots);
        }
        company *array = new company(entry);
        company_array[used_slots] = *array;
        ++used_slots;
        return true;
    }
    
    // inserts a product at the given company
    bool database::insert_item(const std::string &company, const std::string &product_name, const float &price) {
        Debug("Insert item..." << std::endl);

        assert(company.length() > 0 && product_name.length() > 0);

        // COMPLETE THE IMPLEMENTATION...
        size_type index = search_company(company);
        if(index == COMPANY_NOT_FOUND) {return false;}

        // if company exists
        else
        {
            company_array[index].insert(product_name, price);
            return true;
        }
        
    }
    
    // erases a company
    bool database::erase_company(const std::string &company) {
        
        size_type company_index = search_company(company);
        
        // COMPLETE THE IMPLEMENTATION...
        // loops through to shift down each company and overwrites given company
        for(int i = company_index; i < used_slots; ++i)
        {
            company_array[i] = company_array[i+1];
        }
        --used_slots;
        return true;
    }
    
    // erases a product for a given company
    bool database::erase_item(const std::string& cName, const std::string& pName) {
        
        assert(cName.length() > 0 && pName.length() > 0);

        // COMPLETE THE IMPLEMENTATION...
        size_type index = search_company(cName);
        if(index == COMPANY_NOT_FOUND) {return false;}

        // if company exists erase product
        else
        {
            company_array[index].erase(pName);
            return true;
        }
        
        
    }

    // searches for a given company and returns index
    database::size_type database::search_company(const std::string& company) {
        assert(company.length() > 0);

        // COMPLETE THE IMPLEMENTATION...
        // loops through to get the name of each company and checks with given company name
        for(size_type i = 0; i < used_slots; ++i)
        {
            if(company_array[i].get_name() == company)
            {
                return i;
            }
            
        }
        return COMPANY_NOT_FOUND;
            
    }
    
    // prints each companies items
    bool database::print_items_by_company(const std::string& cName) {
        assert(cName.length() > 0);

        size_type c_index = search_company(cName);
        
        if (c_index == COMPANY_NOT_FOUND) {
            return false;
        }
        
        std::cout << "Printing the products of " << cName << ":"<< std::endl;
        company_array[c_index].print_items();
        std::cout << std::endl;
        
        return true;
    }
    
    // prints each company
    void database::print_companies() {
        
        std::cout << "Company List" << std::endl;
        for (int i = 0; i < used_slots; i++) {
            std::cout << "- " << company_array[i].get_name() << std::endl;
        }
    }
}

#endif
