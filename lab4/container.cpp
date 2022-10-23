#include "container.h"
#include <iostream>

void Container::addObject(Object *object)   //Task 1&3
{
    if (_num_object < MAX_OBJECT_NUM && 
    this->getSize().x >= object->getSize().x + object->getPosition().x && 
    this->getSize().y >= object->getSize().y + object->getPosition().y )
    {
        _objects[_num_object++] = object;
        object->setParent(this);
    }

    else 
    {
        cout << "The object "<< object->getName() << " is too large and cannot be added to "<< this->getName() << endl;
    }
    
}

void Container::display() const //Task 1
{
    std::cout << "\nContainer";
    this->displayBasic();
    std::cout <<"\n\t\t";
    if ( _num_object != 0 )
    {
        std::cout << "#objects: " << _num_object << "\n";
        for ( int i = 0; i < _num_object; i++ )
        {
            (*this->_objects[i]).display();
        }
    }

    else
    {
    }
}

Container::Container() 
{
    for (int i = 0; i < MAX_OBJECT_NUM; i++)
        _objects[i] = nullptr;

    _num_object = 0;
}

Container::~Container()  //Task 1
{
    std::cout<<"\nDestructing Container "<<this->getName();
        for (int i = 0; i < _num_object; i++)
        if ( _objects[i] != nullptr)
            delete _objects[i];
}