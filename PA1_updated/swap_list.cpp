#include <iostream>
#include <cstring>
#include "swap_list.h"

using namespace std;

Swap::Swap(const char* const original_course_name, const char* const target_course_name, Swap* const next)
{
    // TODO
    this->original_course_name = new char[ strlen( original_course_name )+1 ];
    strcpy( this->original_course_name, original_course_name );

    this->target_course_name = new char[ strlen( target_course_name )+1 ];
    strcpy( this->target_course_name, target_course_name );

    this->next = next;
    // DONE
}


Swap::~Swap() {
    // TODO
    delete [] original_course_name;
    delete [] target_course_name;
}

Swap_List::Swap_List() {
    // TODO
    this->head = NULL;
    // DONE
}

Swap_List::Swap_List(const Swap_List& swap_list) {
    // TODO
    // first we need to check if this is a empty linked list
    if ( swap_list.head == NULL )
    {
        this->head = NULL;
    }
    else
    {
        this->head = new Swap( swap_list.head->original_course_name, swap_list.head->target_course_name, swap_list.head->next );
    }
    
}

Swap_List::~Swap_List() {
    // TODO
    delete head;
    // DONE
}

void Swap_List::print_list() const {
    Swap* temp = this->head;
    int index = 0;
    while(temp) {
        cout << "Swap: " << index++ << endl;
        cout << "Original Course: " << temp->original_course_name << endl;
        cout << "Target Course: " << temp->target_course_name << endl;
        temp = temp->next;
    }
}

Swap* Swap_List::get_head() const {
    return head;
}

void Swap_List::set_head(Swap* const head) {
    this->head = head;
}