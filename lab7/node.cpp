
#ifndef ITEM_CPP
#define ITEM_CPP

#include "node.h"

namespace coen79_lab7
{
    // creates node
    node::node(const std::string &itemName, const float &newPrice, node *nextNode) {
        name = itemName;
        price = newPrice;
        link = nextNode;
    }

    // sets name
    void node::setName(const std::string &newName) {
        name = newName;
    }
    
    // sets price
    void node::setPrice(const float &newPrice) {
        price = newPrice;
    }
    
    // sets link
    void node::setLink(node *new_next) {
        link = new_next;
    }
    
    // gets link
    node* node::getLink() {
        return link;
    }
    
    // gets link
    const node* node::getLink() const {
        return link;
    }
    
    // gets name
    std::string node::getName() const{
        return name;
    }
    
    // gets price
    float node::getPrice() const {
        return price;
    }
    
    
    // initializes list
    void list_init(node*& head, node*& tail, const std::string& newName, const float& newPrice) {
        head = new node(newName, newPrice, NULL);
        tail = head;
    }
    
    // inserts a node at the tail
    void list_tail_insert(node*& tail, const std::string &newName, const float &newPrice) {

        // COMPLETE THE IMPLEMENTATION...
        tail->setLink(new node(newName, newPrice, NULL));
        tail = tail->getLink();
    }
    
    // clears the list starting from head
    void list_clear(node*& head) 
    {
        while (head != NULL)
    	    list_head_remove(head);
    }
    
    // copies the list
    void list_copy(const node *old_head, node* &new_head, node* &new_tail) {
        new_head = NULL;
        new_tail = new_head;
        
        const node *cur = old_head;
        // loops through list and copies unless head == NULL 
        while (cur != NULL) {

            if (new_head == NULL) {
                new_head = new node(cur->getName(), cur->getPrice());
                new_tail = new_head;
            }
            else {
                new_tail->setLink(new node(cur->getName(), cur->getPrice()));
                new_tail = new_tail->getLink();
            }
            cur=cur->getLink();
        }
    }
    
    // removes the node at the head
    void list_head_remove(node*& head) {
        // COMPLETE THE IMPLEMENTATION...
        node* temp = head;
        head = head->getLink();
        delete temp;
    }
    
    // prints the list 
    void list_print(node *head) {
        node *cur = head;
        while (cur != NULL) {
            std::cout << "- " << cur->getName() << ", where the price is $" << cur->getPrice() << std::endl;
            cur = cur->getLink();
        }
    }
    
    // checks if the list contains the item
    bool list_contains_item(node *head_ptr, const std::string& newName) {
        return (list_search(head_ptr, newName) != NULL);
    }
    
    // searches in the list for the target given
    node* list_search(node* head_ptr, const std::string& target)
    {
        node *cursor;
        
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->getLink( ))
            if (target == cursor->getName( ))
                return cursor;
        return NULL;
    }
    
    // searches in the list for the target given
    const node* list_search(const node* head_ptr, const std::string & target)
    {
        const node *cursor;
        
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->getLink( ))
            if (target == cursor->getName( ))
                return cursor;
        return NULL;
    }
    
}

#endif
