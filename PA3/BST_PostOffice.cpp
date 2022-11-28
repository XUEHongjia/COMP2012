//
// Created by Yigit Sen on 27/10/2022.
//

#include "BST_PostOffice.h"

// TODO: Constructors and Destructors

//TIP: root will be nullptr at first, and we'll add a node once we try to add a mail object.
BST_PostOffice::BST_PostOffice()
{
}

BST_PostOffice_Node::BST_PostOffice_Node(Mail *mail):
district( mail->getDistrict() )
{
    this->left = NULL;
    this->right = NULL;
    this->mailman[ mail->getAddressHash() ].addMail( mail );
}

BST_PostOffice::~BST_PostOffice()
{
    delete root;
}

BST_PostOffice_Node::~BST_PostOffice_Node()
{
    delete left;
    delete right;
}

// TODO: Accessor functions.
BST_PostOffice * BST_PostOffice_Node::getLeftBST() const
{
    return left;
}

BST_PostOffice * BST_PostOffice_Node::getRightBST() const
{
    return right;
}

District BST_PostOffice_Node::getDistrict() const
{
    return district;
}


//TODO: Given a district, id and street name, find the mail object.
Mail *BST_PostOffice::find(District dist, int id, std::string streetName)
{
    if ( this->root == NULL )
    {
        return NULL;
    }

    else
    {
        if ( this->root->district == dist )
        {
            return this->root->find( id, streetName );
        }

        else if ( this->root->district < dist )
        {
            if ( this->root->right )
            {
                return this->root->right->find( dist, id, streetName );
            }

            else
            {
                return NULL;
            }
            
        }

        else if ( this->root->district > dist )
        {
            if ( this->root->left )
            {
                return this->root->left->find( dist, id, streetName );
            }

            else
            {
                return NULL;
            }
            
        }
    }
    
}

Mail *BST_PostOffice_Node::find(int id, std::string streetName)
{
    Mail* target_mail = NULL;
    for ( int i = 0; i < HASH_MODULO; i++ )
    {
        target_mail = this->mailman[i].find( id, streetName );
        if ( target_mail != NULL )
        {
            return target_mail;
        }
    }

    if ( target_mail == NULL )  
    {
        return NULL;
    }
}


// TODO: Given a district, id and street name, remove the mail object from the
// system.
bool BST_PostOffice::remove(District dist, int id, std::string streetName)
{
    if ( this->root == NULL )
    {
        return false;
    }

    else
    {
        if ( this->root->district == dist )
        {
            return this->root->remove( id, streetName );
        }

        else if ( this->root->district < dist )
        {
            if ( this->root->right )
            {
                return this->root->right->remove( dist, id, streetName );
            }

            else
            {
                return false;
            }
            
        }

        else if ( this->root->district > dist )
        {
            if ( this->root->left )
            {
                return this->root->left->remove( dist, id, streetName );
            }
            
            else
            {
                return false;
            }
            
        }
    }
    
}

bool BST_PostOffice_Node::remove(int id, std::string streetName)
{
    // to be added
    bool find = false;
    for ( int i = 0; i < HASH_MODULO; i++ )
    {
        find = this->mailman[i].remove( id, streetName );
        if ( find )
        { return find; }
    }

    if ( !find )
    { return false; }
}

// TODO: Add mail to the system
void BST_PostOffice::addMail(Mail *mail)
{
    if ( this->root == NULL )
    {
        this->root = new BST_PostOffice_Node( mail );
    }

    else
    {
        this->root->addMail( mail );
    }
    
}

void BST_PostOffice_Node::addMail(Mail *mail)
{
    if ( this->district == mail->getDistrict() )
    {
        this->mailman[ mail->getAddressHash() ].addMail( mail );
    }

    else if ( this->district < mail->getDistrict() )
    {
        if ( this->right )
        {
            this->right->addMail( mail );
        }

        else
        {
            this->right = new BST_PostOffice;
            this->right->addMail( mail );
        }
        
    }

    else if ( this->district > mail->getDistrict() )
    {
        if ( this->left )
        {
            this->left->addMail( mail );
        }

        else
        {
            this->left = new BST_PostOffice;
            this->left->addMail( mail );
        }
        
    }
}

// TODO: Given a district, print all of the data in it.
// TIP: Print style depends on type.
void BST_PostOffice::printDistrict(District dist, printType type) const
{
    if ( this->root == NULL )
    {
        return;
    }

    else
    {
        if ( this->root->district == dist )
        {
            this->root->print( type );
        }

        else if( this->root->district < dist )
        {
            if ( this->root->right )
            {
                this->root->right->printDistrict( dist, type );
            }

            else
            {
                return;
            }
            
        }

        else if( this->root->district < dist )
        {
            if ( this->root->left )
            {
                this->root->left->printDistrict( dist, type );
            }

            else
            {
                return;
            }
        }
    }
    
}

void BST_PostOffice_Node::print(printType type) const
{
    std::cout << "The District Mail Report for district " << this->district << std::endl;
    for ( int i = 0; i < HASH_MODULO; i++ )
    {
        std::cout << "For Mailman " << i << std::endl;
        if ( type == 1 )
        {
            this->mailman[i].printInOrder();
        }
        else if ( type == 2 )
        {
            this->mailman[i].printPreOrder();
        }
        else if ( type == 3 )
        {
            this->mailman[i].printPostOrder();
        }
        
    }
}

// TODO: Given a district and ID of the mailman, print all mail in it
// TIP: Print style depends on type - see the header file
void BST_PostOffice::printMailman(District district, int i, printType type) const
{
    if ( this->root == NULL )
    {
        return;
    }

    else
    {
        if ( this->root->district == district )
        {
            this->root->printMailman( i, type );
        }

        else if ( this->root->district < district )
        {
            if ( this->root->right )
            {
                this->root->right->printMailman( district, i, type );
            }
            else
            {
                return;
            }
            
        }

        else if( this->root->district > district )
        {
            if ( this->root->left )
            {
                this->root->left->printMailman( district, i, type );
            }
            else
            {
                return;
            }
            
        }
    }
}

void BST_PostOffice_Node::printMailman(int i, printType type) const
{
    if ( type == 1 )
    {
        this->mailman[i].printInOrder();
    }

    else if ( type == 2 )
    {
        this->mailman[i].printPostOrder();
    }

    else if ( type == 3 )
    {
        this->mailman[i].printPreOrder();
    }
}

// TODO: Other print functions.
void BST_PostOffice::printInOrder() const
{
    if ( this->root == NULL )
    {
        return;
    }

    else
    {
        if ( this->root->left )
        {
            this->root->left->printInOrder();
        }

        //this->root->print( inorder );
        std::cout<<"BST Node for District: " << this->root->district << std::endl;
        for ( int i = 0; i < 10; i++ )
        {
            this->root->mailman[i].printInOrder();
        }

        if ( this->root->right )
        {
            this->root->right->printInOrder();
        }
    }
    
}

void BST_PostOffice::printPostOrder() const
{
    if ( this->root == NULL )
    {
        return;
    }

    else
    {
        if ( this->root->left )
        {
            this->root->left->printPostOrder();
        }
        
        if ( this->root->right )
        {
            this->root->right->printPostOrder();
        }

        //this->root->print( postorder );
        std::cout<<"BST Node for District: " << this->root->district << std::endl;
        for ( int i = 0; i < HASH_MODULO; i++ )
        {
            this->root->mailman[i].printPostOrder();
        }
    }
    
}

void BST_PostOffice::printPreOrder() const
{
    if ( this->root == NULL )
    {
        return;
    }

    else
    {
        //this->root->print( preorder );
        std::cout<<"BST Node for District: " << this->root->district << std::endl;
        for ( int i = 0; i < HASH_MODULO; i++ )
        {
            this->root->mailman[i].printPreOrder();
        }

        if ( this->root->left )
        {
            this->root->left->printPreOrder();
        }
        
        if ( this->root->right )
        {
            this->root->right->printPreOrder();
        }
    }
    
}