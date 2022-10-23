#include <iostream>
#include "object.h"

const Pair Object::getSize() const
{
    return _size;
}

const Pair Object::getPosition() const  //Task 2
{
    if ( this->_parent == NULL )
    {
        return _position;
    }

    else
    {
        return { _position.x + this->_parent->getPosition().x, _position.y + this->_parent->getPosition().y };
    }
}

const char* Object::getName() const
{
    return _name;
}

void Object::setSize(int x, int y)  //Task 3
{
    if ( x > SCREEN_RESOLUTION.x || y > SCREEN_RESOLUTION.y || x < 0 || y < 0 )
    {
        std::cout << "Invalid size of " << this->_name << endl;
    }

    else
    {
        _size.x = x;
        _size.y = y;
    }
    
}

void Object::setPosition(int x, int y)  //Task 3
{
    if ( x < 0 || y < 0 )
    {
        std::cout << "Invalid position of " << this->_name << endl;
    }
    else
    {
        _position.x = x;
        _position.y = y;
    }
}

void Object::setName(const char*name)
{
    for(int i = 0;i<MAX_NAME_LENGTH; i++)
    {
        _name[i] = name[i];
        if(name[i]=='\0') break;
    }
}

void Object::setParent(Object* parent)
{
    _parent = parent;
}

void Object::displayBasic() const
{
    cout << "\n\tName: ["<< getName()<<"]"; 
    cout <<"\n\tPosition: ("<< getPosition().x << ", "<< getPosition().y<<")";
    cout <<"\n\tSize: (" <<  getSize().x << ", "<< getSize().y<<") ";
}

Object::Object() : _size{0,0}, _position{0,0}, _parent{nullptr}
{
    _name = new char[MAX_NAME_LENGTH];
    _name[0]='\0';
}

Object::~Object()
{
    if (_name != nullptr) 
        delete [] _name;
}