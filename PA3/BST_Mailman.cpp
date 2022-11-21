//
// Created by Yigit Sen on 27/10/2022.
//

#include "BST_Mailman.h"

// TODO: Constructors and Destructors
BST_Mailman::BST_Mailman()
{
    this->root = NULL;
}

BST_Mailman_Node::BST_Mailman_Node(Mail *mail):
streetName( mail->getStreetName() )
{
    this->mailPtr[currentMailsStored] = mail;
    this->currentMailsStored += 1;
    this->left = NULL;
    this->right = NULL;
}

BST_Mailman::~BST_Mailman()
{
    delete root;
}

BST_Mailman_Node::~BST_Mailman_Node()
{
    for ( int i = 0; i < currentMailsStored; i++ )
    {
        delete mailPtr[i];
    }
    delete right;
    delete left;
}

// TODO: Getters
std::string BST_Mailman_Node::getStreetName() const
{
    return streetName;
}

BST_Mailman * BST_Mailman_Node::getRightBST() const
{
    return right;
}

BST_Mailman * BST_Mailman_Node::getLeftBST() const
{
    return left;
}


// TODO add mail to the array mailPtr[] - NOTE: WE WILL NEVER ASK YOU TO
//  PUT TOO MANY MAILS. (a max of MAX_NUM_MAILS add_mail calls)
void BST_Mailman::addMail(Mail *mail)
{
    if ( this->root == NULL )
    {
        this->root = new BST_Mailman_Node( mail );
    }

    else
    {
        this->root->addMail( mail );
    }
    
}

void BST_Mailman_Node::addMail(Mail *mail)
{
    if ( this->streetName == mail->getStreetName() )
    {
        this->mailPtr[ currentMailsStored ] = mail;
        currentMailsStored += 1;
    }

    else if ( this->streetName < mail->getStreetName() )
    {
        this->right->addMail( mail );
    }

    else if ( this->streetName > mail->getStreetName() )
    {
        this->left->addMail( mail );
    }
}

// TODO: Remove a mail, given its street name and ID
bool BST_Mailman::remove(int id, std::string streetName)
{
    if ( this->root == NULL )
    {
        return false;
    }

    else
    {
        if ( this->root->getStreetName() == streetName )
        {
            this->root->remove(id);
        }

        else if ( this->root->getStreetName() > streetName )
        {
            this->root->left->remove( id, streetName );
        }

        else if ( this->root->getStreetName() < streetName )
        {
            this->root->right->remove( id, streetName );
        }
    }
    
}

bool BST_Mailman_Node::remove(int id)
{
    bool find = false;
    for ( int i = 0; i < currentMailsStored; i++ )
    {
        if ( this->mailPtr[i]->getId() == id )
        {
            delete mailPtr[i];
            mailPtr[i] = NULL;
            find = true;
            return true;
        }
    }
    
    if ( !find )
    { return false; }
}

// TODO: Find a mail item, given its street name and ID
Mail * BST_Mailman::find(int id, std::string streetName)
{
    if ( this->root == NULL )
    {
        return NULL;
    }

    else
    {
        if ( this->root->getStreetName() == streetName )
        {
            this->root->find(id);
        }

        else if ( this->root->getStreetName() > streetName )
        {
            this->root->left->find( id, streetName );
        }

        else if ( this->root->getStreetName() < streetName )
        {
            this->root->right->find( id, streetName );
        }
    }
    
}

Mail *BST_Mailman_Node::find(int id)
{
    bool find = false;
    for ( int i = 0; i < currentMailsStored; i++ )
    {
        if ( this->mailPtr[i]->getId() == id )
        {
            find = true;
            return mailPtr[i];
        }
    }
    
    if ( !find )
    { return NULL; }
}


// TODO: Print functions. See example outputs for the necessary formats.
void BST_Mailman::printInOrder() const
{
    this->root->left->printInOrder();
    this->root->print();
    this->root->right->printInOrder();
}

void BST_Mailman::printPostOrder() const
{
    this->root->left->printPostOrder();
    this->root->right->printPostOrder();
    this->root->print();
}

void BST_Mailman::printPreOrder() const
{
    this->root->print();
    this->root->left->printPreOrder();
    this->root->right->printPreOrder();
}

void BST_Mailman_Node::print() const
{
    std::cout << "BST Node for Street: " << streetName << std::endl;
    for (int i = 0; i < currentMailsStored; ++i) {
        if(mailPtr[i] != nullptr)
        {
            mailPtr[i]->printMail();
        }
    }
}
