#include "wolf.h"
#include "sheep.h"
#include "grass.h"
#include "helper.h"

/**
 * TODO: TASK 4
 * 
 * Place a copy of this Wolf onto nextGrid at the specified position.
 * You may implement this similar to Sheep::putSelf().
*/
void Wolf::putSelf(Grid* nextGrid, const int x, const int y) {
    Wolf* wolf0 = new Wolf( *this );
    bool placed = putAnimal( wolf0, nextGrid, x, y );
    if ( placed )
    {
        this->setNextSelf( wolf0 );
    }
}

/**
 * TODO: TASK 4
 * 
 * Place a brand new Wolf onto nextGrid at the specified position.
 * You may implement this similar to Sheep::putClone().
*/
void Wolf::putClone(Grid* nextGrid, const int x, const int y) const {
    Wolf* wolf0 = new Wolf( this->getBoard() );
    bool placed = putAnimal( wolf0, nextGrid, x, y );
}

/**
 * TODO: TASK 4
 * 
 * Implement this function similar to Sheep::eat().
 * The only difference is that Wolf eats Sheep instead of Grass.
*/
void Wolf::eat(Grid* nextGrid) {
    for (int i=0; i<9; ++i) {
        if (i == 4) continue;
        int adjX = getX() + getAdjX(i);
        int adjY = getY() + getAdjY(i);
        Entity* adjEntity = getBoard()->getGrid()->getCell(adjX, adjY);

        if (!adjEntity) {
            // Out of bounds or empty space, ignore
            continue;
        }
        // ?
        if ( adjEntity->toChar() == 'S' && ( adjEntity->isRemoved() == false ) )
        {
            adjEntity->removeSelf( nextGrid );
            
            this->setHungerCounter( this->getHungerCooldown() );
            break;
        }
    }
    return;
}

/**
 * TODO: TASK 4
 * 
 * Implement this function similar to Sheep::breed().
 * The only difference is that Wolf breeds by finding a Wolf instead of Sheep.
*/
void Wolf::breed(Grid* nextGrid) {
    for (int i=0; i<9; ++i) 
    {
        if (i == 4) continue;
        int adjX = getX() + getAdjX(i);
        int adjY = getY() + getAdjY(i);
        Entity* adjEntity = getBoard()->getGrid()->getCell(adjX, adjY);

        if (!adjEntity) {
            // Out of bounds or empty space, ignore
            continue;
        }

        // ?
        if ( adjEntity->toChar() == 'W' )
        {
            int pos = this->getRandomMovementIndex(nextGrid);
            if ( pos != -1 )
            {
                int X = this->getX();
                int Y = this->getY();

                int adjX = X + getAdjX( pos );
                int adjY = Y + getAdjY( pos );

                this->putClone( nextGrid, adjX, adjY );

                this->setBreedCounter( this->getBreedCooldown() );
                break;
            }
        }
    }
    return;
    
}

/**
 * TODO: TASK 4
 * 
 * If there is at least one Sheep on the board, Wolf tries to move towards it.
 * 
 * You should loop over the board in the same order as Board calling update(), 
 * calculate Euclidean distance to each cell containing a Sheep, and keep track of the shortest distance found.
 * Ignore sheeps that have been eaten (removed).
 * No need to keep track of Sheeps with the same distance as shortest one found so far.
 * 
 * If a Sheep is found, move to the adjacent cell closest to that Sheep. If that cell is occupied with another Animal,
 * the Wolf stays at its position.
 * 
 * If no Sheep is found, the Wolf moves randomly like a Sheep.
 * 
 * You may follow the structure below to implement the function.
*/
void Wolf::move(Grid* nextGrid) {
    // First, find a sheep to target
    
    // ?
    bool sheep_found = false;
    int num_sheep = 0;
    int coor_sheep[ 2*10*20 ];
    for (int x=0; x<BOARD_SIZE_W; ++x) 
    {
        for (int y=0; y<BOARD_SIZE_H; ++y) 
        {
            Entity* entity = getBoard()->getGrid()->getCell(x, y);
            if ( !entity )
            {
                continue; // empty entity, ignore
            }
            else
            {
                bool is_sheep = ( entity->toChar() == 'S' ) && ( entity->isRemoved() == false );
                sheep_found = sheep_found || is_sheep ;
                if ( is_sheep )
                {
                    coor_sheep[ 2*num_sheep ] = x;
                    coor_sheep[ 2*num_sheep + 1 ] = y;
                    num_sheep += 1;
                }
            }
            
        }
    }

    if ( sheep_found ) { // Edit this line with the appropriate condition
        // If a sheep with the closest distance is found, try to move towards it
        // ?
        // acquire target position
        int distance = 10*10 + 20*20;
        int coor_target[2];
        int wolf_x = this->getX();
        int wolf_y = this->getY();
        for ( int i = 0; i < num_sheep; i++ ) 
        {
            int tem_dis = ( wolf_x - coor_sheep[ 2*i ] )*( wolf_x - coor_sheep[ 2*i ] ) 
            + ( wolf_y - coor_sheep[ 2*i + 1 ] )*( wolf_y - coor_sheep[ 2*i + 1 ] );
            if ( tem_dis < distance )
            {
                coor_target[0] = coor_sheep[ 2*i ];
                coor_target[1] = coor_sheep[ 2*i + 1 ];
                distance = tem_dis;
            }
        } // postion acquired

        // find the move that can wolf closet to the target
        int move = 0;
        int move_distance = distance;
        for ( int i = 0; i < 9; i++ )
        {
            if ( i==4 ) continue;
            int adjX = wolf_x + getAdjX(i);
            int adjY = wolf_y + getAdjY(i);
            if (nextGrid->outOfBounds(adjX, adjY)) 
            {
                // Out of bounds, ignore
                continue;
            }
            int try_dis = ( coor_target[0] - adjX )*( coor_target[0] - adjX ) 
            + ( coor_target[1] - adjY )*( coor_target[1] - adjY );
            if ( try_dis < move_distance )
            {
                move = i;
                move_distance = try_dis;
            }
        }
        // move found

        // verify if the move is valid( if there it is occupied by animal )
        int adjX = wolf_x + getAdjX(move);
        int adjY = wolf_y + getAdjY(move);
        Entity* adjEntity = getBoard()->getGrid()->getCell(adjX, adjY);
        Entity* adjNextEntity = nextGrid->getCell(adjX, adjY);
        bool is_animal = (dynamic_cast<Animal*>(adjEntity)) || (dynamic_cast<Animal*>(adjNextEntity));
        // if valid, move
        if ( !is_animal )
        {
            this->putSelf( nextGrid, adjX, adjY );
        }
        // if not, stay put
        else
        {
            this->putSelf( nextGrid, this->getX(), this->getY() );
        }
        
        
    }
    else
    {
        // No sheep found, move randomly
        int move = this->getRandomMovementIndex(nextGrid);
        if ( move != -1 )
        {
            int X = this->getX();
            int Y = this->getY();

            int adjX = X + getAdjX( move );
            int adjY = Y + getAdjY( move );

            this->putSelf( nextGrid, adjX, adjY );

        }
        else
        {
            this->putSelf( nextGrid, this->getX(), this->getY() );
        }
        // ?
    }
}