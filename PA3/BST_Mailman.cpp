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
        if ( this->right )
        {
            this->right->addMail( mail );
        }

        else
        {
            this->right = new BST_Mailman;
            this->right->addMail( mail );
        }
        
    }

    else if ( this->streetName > mail->getStreetName() )
    {
        if ( this->left )
        {
            this->left->addMail( mail );
        }

        else
        {
            this->left = new BST_Mailman;
            this->left->addMail( mail );
        }
        
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
            return this->root->remove(id);
        }

        else if ( this->root->getStreetName() > streetName )
        {
            if ( this->root->left )
            {
                return this->root->left->remove( id, streetName );
            }
            else
            {
                return false;
            }
            
        }

        else if ( this->root->getStreetName() < streetName )
        {
            if ( this->root->right )
            {
                return this->root->right->remove( id, streetName );
            }
            else
            {
                return false;
            }
            
        }
    }
    
}

bool BST_Mailman_Node::remove(int id)
{
    bool find = false;
    for ( int i = 0; i < currentMailsStored; i++ )
    {
        if ( mailPtr[i] )
        {
            if ( this->mailPtr[i]->getId() == id )
            {
                delete mailPtr[i];
                mailPtr[i] = NULL;
                find = true;
                break;
            }
        }
    }
    
    return find;
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
            return this->root->find(id);
        }

        else if ( this->root->getStreetName() > streetName )
        {
            if ( this->root->left )
            {
                return this->root->left->find( id, streetName );
            }
            else
            {
                return NULL;
            }
            
        }

        else if ( this->root->getStreetName() < streetName )
        {
            if ( this->root->right )
            {
                return this->root->right->find( id, streetName );
            }

            else
            {
                return NULL;
            }
        }
    }
    
}

Mail *BST_Mailman_Node::find(int id)
{
    Mail* find = NULL;
    for ( int i = 0; i < currentMailsStored; i++ )
    {
        if ( mailPtr[i] )
        {
            if ( mailPtr[i]->getId() == id )
            {
                find =  mailPtr[i];
                break;
            }
        }
    }
    return find;
}


// TODO: Print functions. See example outputs for the necessary formats.
void BST_Mailman::printInOrder() const
{
    if ( this->root == NULL )
    {
        return;
    }

    else
    {
        if ( this->root->left )
        { this->root->left->printInOrder(); }

        this->root->print();

        if( this->root->right )
        { this->root->right->printInOrder(); }
    }
}

void BST_Mailman::printPostOrder() const
{
    if ( this->root )
    {
        if ( this->root->left )
        {
            this->root->left->printPostOrder();
        }
        if( this->root->right )
        {
            this->root->right->printPostOrder();
        }
        this->root->print();
    }
}

void BST_Mailman::printPreOrder() const
{
    if ( this->root )
    {
        this->root->print();

        if ( this->root->left )
        {
            this->root->left->printPreOrder();
        }

        if( this->root->right )
        {
            this->root->right->printPreOrder();
        }
    }
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
