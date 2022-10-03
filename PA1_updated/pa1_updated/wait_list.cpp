#include <iostream>
#include "wait_list.h"

using namespace std;

Student_ListNode::Student_ListNode(const int student_id, Student_ListNode* const next):
student_id{ student_id }
 {
    // TODO
    this->next = next;
}

Wait_List::Wait_List() {
    // TODO
    this->head = NULL;
    this->end = NULL;
}

Wait_List::Wait_List(const Wait_List& wait_list) {
    // TODO
    // this is the tricky part since it involves linked-list
    this->head = new Student_ListNode( wait_list.head->student_id , NULL );
    Student_ListNode* target_link = this->head;
    for ( Student_ListNode* referencee_link = wait_list.head; referencee_link->next != NULL; referencee_link = referencee_link->next )
    {
        target_link->next = new Student_ListNode( referencee_link->next->student_id, NULL );
        target_link = target_link->next;
    }
    this->end = target_link;
}

Wait_List::~Wait_List() {
    // TODO
    // also very tricky
    Student_ListNode* current = head;
    Student_ListNode* next = NULL;
    while (current != NULL)
    {
       next = current->next;
       delete current;
       current = next;
    }
    head = NULL;
    end = NULL;
}


void Wait_List::print_list() const {
    Student_ListNode* temp = this->head;
    int index = 0;
    while(temp) {
        cout << "Waitlist Number: " << index++ << endl;
        cout << temp->student_id << endl;
        temp = temp->next;
    }
}

Student_ListNode* Wait_List::get_head() const {
    return head;
}

Student_ListNode* Wait_List::get_end() const {
    return end;
}

void Wait_List::set_head(Student_ListNode* const head) {
    this->head = head;
}

void Wait_List::set_end(Student_ListNode* const end) {
    this->end = end;
}