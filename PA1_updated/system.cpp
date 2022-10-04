#include <iostream>
#include <cstring>
#include "system.h"
#include "student.h"
#include "course.h"
#include "course_database.h"
#include "student_database.h"
#include "wait_list.h"
#include "swap_list.h"

using namespace std;

/*
The following 3 helper functions may be useful in add/swap/drop function. You may implement them if you find them useful.
If not, you can remove these 3 helper functions as we will NOT set any test case testing these helper functions.
*/

// Helper function: add the Student to the end of the waitlist of the Course.
void join_waitlist(const int student_id, Course* course) {
    // TODO
}

// Helper function: find the index of a course within the enrolled course list of a student.
int search_course_index(const Student* const student, const char* const course_name) {
    // TODO
    int num_enrolled_course = ( *student ).get_num_enrolled_course();
    char** enrolled_course = ( *student ).get_enrolled_courses();
    for ( int i = 0; i < num_enrolled_course; i++ )
    {
        int a = strcmp( enrolled_course[i], course_name );
        if ( a == 0 )
        {
            return i;
        }
        else
        {}
    }
}

// Helper function: find the index of the student_id in the enrolled student list
int search_student_id(const int student_id, const Course* const course) {
    // TODO
    int size = ( *course ).get_size();
    int* studets_enrolled = ( *course ).get_students_enrolled();
    for ( int i = 0; i < size; i++ )
    {
        if ( studets_enrolled[i] == student_id )
        {
            return i;
        }
        else
        {}
        
    }
}


System::System(const int max_num_course, const int max_num_student) {
    course_database = new Course_Database(max_num_course);
    student_database = new Student_Database(max_num_student);
}

System::System(const System& system) {
    this->course_database = new Course_Database(*system.course_database);
    this->student_database = new Student_Database(*system.student_database);
}

System::~System() {
    delete course_database;
    delete student_database;
}

void System::admit(const char* const name, const int student_id, const double gpa) {
    this->student_database->create_entry(name, student_id, gpa);
}

bool System::apply_overload(const int student_id, const int request_credit) {
    // TODO
        Student* student_A = (*(get_student_database())).get_student_by_id(student_id);
        double A_gpa = ( (*student_A ).get_gpa() ) ;
    if( request_credit > 30 )
    {
        return false;
    }
    else if ( request_credit >= 24 && A_gpa < 3.7)
    {
        return false;
    }
    else if( request_credit > 18 && A_gpa < 3.3 )
    {
        return false;
    }
    else
    { 
        (*student_A ).set_max_credit( request_credit );
        return true;
    }
}

bool System::add(const int student_id, const char* const course_name) {
    // TODO
    Student* student_A = (*(get_student_database())).get_student_by_id(student_id);
    Course* course_A = ( *( get_course_database() ) ).get_course_by_name( course_name );
    int credit_course_A = ( *course_A ).get_num_credit();
    int pending_credit_A = ( *student_A ).get_pending_credit();
    int current_credit_A = ( *student_A ).get_curr_credit();
    int max_credit_A = ( *student_A ).get_max_credit();
    if ( ( credit_course_A + current_credit_A + pending_credit_A ) > max_credit_A )
    {
        return false;
    }

    else
    {
        int capacity_A = ( *course_A ).get_capacity();
        int size_A = ( *course_A ).get_size();

        if ( size_A + 1 <= capacity_A ) // there are still seats available, succesfully enrolled
        {
            // update student_A data
            ( *student_A ).set_curr_credit( current_credit_A + credit_course_A );

            int num_enrolled_course_A = ( *student_A ).get_num_enrolled_course();
            // how to update the enrolled_course?
            char** enrolled_courses_A = ( *student_A ).get_enrolled_courses();
            enrolled_courses_A[ num_enrolled_course_A ] = new char[ strlen( course_name )+1 ];
            strcpy( enrolled_courses_A[ num_enrolled_course_A ], course_name );

            ( *student_A ).set_num_enrolled_course( num_enrolled_course_A + 1 );

            // update course_A data
            ( *course_A ).set_size( size_A + 1 );
            // how to update the enrolled_student?
            int* enrolled_students_A = ( *course_A ).get_students_enrolled();
            enrolled_students_A[ size_A ] = student_id; 
        }

        else  // no seats available, student is added to the waitlist
        {
            // update student_A data
            ( *student_A ).set_pending_credit( pending_credit_A + credit_course_A );
            // update course_A data
            Wait_List* waitlist_A = ( *course_A ).get_wait_list();
            Student_ListNode* student_listnode_A = ( *waitlist_A ).get_end();
            if ( student_listnode_A == NULL )
            {
                student_listnode_A = new Student_ListNode( student_id, NULL );
                ( *waitlist_A ).set_head( student_listnode_A );
                ( *waitlist_A ).set_end( student_listnode_A );
            }
            else
            {
                student_listnode_A->next = new Student_ListNode( student_id, NULL );
                ( *waitlist_A ).set_end( student_listnode_A->next );
            }
            
        }

        return true;
    }
}

bool System::swap(const int student_id, const char* const original_course_name, const char* const target_course_name) {
    // TODO
    Student* student_A = (*(get_student_database())).get_student_by_id(student_id);
    Course* original_course_A = ( *( get_course_database() ) ).get_course_by_name( original_course_name );
    Course* target_course_A = ( *( get_course_database() ) ).get_course_by_name( target_course_name );

    int pending_credit_A = ( *student_A ).get_pending_credit();
    int current_credit_A = ( *student_A ).get_curr_credit();
    int max_credit_A = ( *student_A ).get_max_credit();

    int credit_original_course_A = ( *original_course_A ).get_num_credit();
    int credit_target_course_A = ( *target_course_A ).get_num_credit();
    int credit_change = credit_target_course_A - credit_original_course_A;
    int final_change = ( credit_change > 0 ) ?  credit_change : 0;

    if ( current_credit_A + pending_credit_A + final_change > max_credit_A )
    {
        return false;
    }

    else 
    {
        int capacity_target_A = ( *target_course_A ).get_capacity();
        int size_target_A = ( *target_course_A ).get_size();

        if ( size_target_A + 1 <= capacity_target_A )   // there are seats available in the target course
        {
            // requires one add operation and one drop operation
            // add operation ( we should avoid using add )
            ( *student_A ).set_curr_credit( current_credit_A + credit_target_course_A );

            int num_enrolled_course_A = ( *student_A ).get_num_enrolled_course();
            // how to update the enrolled_course?
            char** enrolled_courses_A = ( *student_A ).get_enrolled_courses();
            enrolled_courses_A[ num_enrolled_course_A ] = new char[ strlen( target_course_name )+1 ];
            strcpy( enrolled_courses_A[ num_enrolled_course_A ], target_course_name );

            ( *student_A ).set_num_enrolled_course( num_enrolled_course_A + 1 );

            // update course_A data
            ( *target_course_A ).set_size( size_target_A + 1 );
            int* enrolled_students_A = ( *target_course_A ).get_students_enrolled();
            enrolled_students_A[ size_target_A ] = student_id; 

            // drop the original course
            drop( student_id, original_course_name );
        }

        else // no seats available, student is added to the waitlist
        {
            // update student_A data
            ( *student_A ).set_pending_credit( pending_credit_A + credit_change );
            Swap_List* swap_list_A = ( *student_A ).get_swap_list();
            Swap* swap_head_A = new Swap( original_course_name, target_course_name, (*swap_list_A).get_head() );
            ( *swap_list_A ).set_head( swap_head_A );

            // update target_course_A data
            Wait_List* waitlist_A = ( *target_course_A ).get_wait_list();
            Student_ListNode* student_listnode_A = ( *waitlist_A ).get_end();
            if ( student_listnode_A == NULL )
            {
                student_listnode_A = new Student_ListNode( student_id, NULL );
                ( *waitlist_A ).set_head( student_listnode_A );
                ( *waitlist_A ).set_end( student_listnode_A );
            }
            else
            {
                student_listnode_A->next = new Student_ListNode( student_id, NULL );
                ( *waitlist_A ).set_end( student_listnode_A->next );
            }
        }

        return true;
    }
}

void System::drop(const int student_id, const char* const course_name) {
    // TODO
    // get course and data
    Student* student_A = (*(get_student_database())).get_student_by_id(student_id);
    Course* course_A = ( *( get_course_database() ) ).get_course_by_name( course_name );
    int credit_course_A = ( *course_A ).get_num_credit();
    int current_credit_A = ( *student_A ).get_curr_credit();

    // update student data
    // reset enrolled credit
    (*student_A).set_curr_credit( current_credit_A - credit_course_A );

    int num_enrolled_course_A = ( *student_A ).get_num_enrolled_course();

    // reset enrolled course/number
    char** enrolled_courses_A = ( *student_A ).get_enrolled_courses();
    int index_course = search_course_index( student_A, course_name );
    delete[] enrolled_courses_A[ index_course ];
    enrolled_courses_A[ index_course ] = NULL;

    for ( int i = index_course; i < num_enrolled_course_A-1; i++ )
    {
        enrolled_courses_A[i] = enrolled_courses_A[i+1];
    }
    enrolled_courses_A[ num_enrolled_course_A-1 ] = NULL;
    ( *student_A ).set_num_enrolled_course( num_enrolled_course_A - 1 );


    // update course data
    int size_A = ( *course_A ).get_size();
    int index_student = search_student_id( student_id, course_A );
    int* enrolled_student = ( *course_A ).get_students_enrolled();
    enrolled_student[index_student] = enrolled_student[size_A-1];
    enrolled_student[ size_A-1 ] = 0;

    // check if there are any students on the waitlist
    Wait_List* waitlist_A = ( *course_A ).get_wait_list();
    bool waitlist_empty = ( (*waitlist_A).get_head() == NULL );
    (*course_A).set_size( size_A-1 );

    if ( waitlist_empty )
    {
        return;
    }

    else
    {
        // to be finished since a drop could trigger another add/swap
        
    }
    

}

void System::add_course(const char* const name, const int num_credit, const int course_capacity) {
    this->course_database->create_entry(name, num_credit, course_capacity);
}

void System::print_info() const {
    this->course_database->print_all_course();
    this->student_database->print_all_students();
}

Course_Database* System::get_course_database() const {
    return course_database;
}

Student_Database* System::get_student_database() const {
    return student_database;
}

void System::set_course_database(Course_Database* const course_database) {
    this->course_database = course_database;
}

void System::set_student_database(Student_Database* const student_database) {
    this->student_database = student_database;
}
