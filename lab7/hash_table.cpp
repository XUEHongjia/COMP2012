#include "hash_table.h"
#include <cmath>
#include <iostream>

int HashTable::hashFunction(const std::string &name, int base, int table_size) {
  int res = 0;
  for (unsigned int i = 0; i < name.size(); i++) {
    res = (base*res + name[i] - 'a') % table_size;
  }
  return res;
}

int HashTable::getNextHashTableSize(int now_hash_table_size) {
  int res = now_hash_table_size*2;
  bool is_prime = false;
  while (true) {
    is_prime = true;
    int sq = sqrt(res);
    for (int i = 2; i <= sq; i++) {
      if (res % i == 0) {
        is_prime = false;
        break;
      }
    }
    if (is_prime)
      break;
    res++;
  }
  return res;
}

HashTable::HashTable(int init_size, int maximum_probe_num, ProbeMode probe_mode):
base_1_{ 37 },
base_2_{ 41 },
hash_table_size_{ init_size },
maximum_probe_num_{ maximum_probe_num },
probe_mode_{ probe_mode }
{  // Task 1

  // initialize table and its cells
  table_ = new HashCell[ init_size ];
  for ( int i = 0; i < init_size; i++ )
  {
    table_[i].state = HashCellState::Empty;
    table_[i].student = NULL;
  }

  // inittialize a lamda function?
  if ( probe_mode_ == ProbeMode::DoubleHash )
  {
    probe_func_ =  []( int hash_value1, int hash_value2, int num_probe, int hash_table_size )->int
    {
      int p = ( hash_value1 + num_probe*hash_value2 ) % hash_table_size;
      std::cout << "Probing for the position: " << p << std::endl;
      return p ;
    } ;
  }

  else if ( probe_mode_ == ProbeMode::Linear )
  {
    probe_func_ =  []( int hash_value1, int hash_value2, int num_probe, int hash_table_size )->int
    {
      int p = ( hash_value1 + num_probe ) % hash_table_size;
      std::cout << "Probing for the position: " << p << std::endl;
      return p;
    } ;
  }

  else if ( probe_mode_ == ProbeMode::Quadratic )
  {
    probe_func_ =  []( int hash_value1, int hash_value2, int num_probe, int hash_table_size )->int
    {
      int p = ( hash_value1 + num_probe*num_probe ) % hash_table_size ;
      std::cout << "Probing for the position: " << p << std::endl;
      return p;
    } ;
  }
}

HashTable::~HashTable() {  // Task 1
  delete [] table_;
  table_ = NULL;
}

bool HashTable::add(const std::string &name, int score) {  // Task 2 & 5

  int hash_value1 = hashFunction( name, base_1_, hash_table_size_ );
  int hash_value2 = hashFunction( name, base_2_, hash_table_size_ );
  if ( hash_value2 == 0 )
  {
    hash_value2 = 1;
  }

  bool pos_found = false;
  for ( int num_probe = 0; num_probe < maximum_probe_num_; num_probe++ )
  {
    int hik = probe_func_( hash_value1, hash_value2, num_probe, hash_table_size_ );
    
    if ( table_[ hik ].state == HashCellState::Active &&  name == table_[ hik ].student->name() )
    {
      return false;
    }

    else if ( table_[ hik ].state == HashCellState::Empty || table_[ hik ].state == HashCellState::Deleted )
    {
      table_[ hik ].state = HashCellState::Active;
      table_[ hik ].student = new Student( name, score );
      pos_found = true;
      return true;
    }

  }

  if( ! pos_found ) 
  {
    bool insert_after_rehash = false;
    while( !insert_after_rehash )
    {
      this->reHashUntilSuccess();
      int hash_value1 = hashFunction( name, base_1_, hash_table_size_ );
      int hash_value2 = hashFunction( name, base_2_, hash_table_size_ );
      if ( hash_value2 == 0 )
      {hash_value2 = 1;}

      for ( int num_probe = 0; num_probe < maximum_probe_num_; num_probe++ )
      {
        int hik = probe_func_( hash_value1, hash_value2, num_probe, hash_table_size_ );
    
        if ( table_[ hik ].state == HashCellState::Empty )
        {
          table_[ hik ].state = HashCellState::Active;
          table_[ hik ].student = new Student( name, score );
          insert_after_rehash = true;
          break;
        }
      }

    }
    return true;
  }

}

int HashTable::search(const std::string &name) const {  // Task 3
  int hash_value1 = hashFunction( name, base_1_, hash_table_size_ );
  int hash_value2 = hashFunction( name, base_2_, hash_table_size_ );
  if ( hash_value2 == 0 )
  {
    hash_value2 = 1;
  }

  bool student_found = false;
    for ( int num_probe = 0; num_probe < hash_table_size_; num_probe++ )
    {
      int hik = probe_func_( hash_value1, hash_value2, num_probe, hash_table_size_ );
      if ( table_[ hik ].state == HashCellState::Deleted )
      {
        continue;
      }

      else if ( table_[ hik ].state == HashCellState::Active )
      {
        if ( name == table_[hik].student->name() )
        {
          student_found = true;
          return table_[hik].student->score();
        }
      }

      else if ( table_[ hik ].state == HashCellState::Empty )
      {
        return -1;
      }

    }

    if ( !student_found )
    {
      return -1;
    }
}

bool HashTable::remove(const std::string &name) {  // Task 4
  int hash_value1 = hashFunction( name, base_1_, hash_table_size_ );
  int hash_value2 = hashFunction( name, base_2_, hash_table_size_ );
  if ( hash_value2 == 0 )
  {
    hash_value2 = 1;
  }

  bool student_found = false;
    for ( int num_probe = 0; num_probe < hash_table_size_; num_probe++ )
    {
      int hik = probe_func_( hash_value1, hash_value2, num_probe, hash_table_size_ );
      if ( table_[ hik ].state == HashCellState::Deleted )
      {
        continue;
      }

      else if ( table_[ hik ].state == HashCellState::Active )
      {
        if ( name == table_[hik].student->name() )
        {
          student_found = true;
          delete table_[ hik ].student;
          table_[ hik ].student = NULL;
          table_[ hik ].state = HashCellState::Deleted;
          return true;
        }
      }

      else if ( table_[ hik ].state == HashCellState::Empty )
      {
        return false;
      }

    }

    if ( !student_found )
    {
      return false;
    }
}

void HashTable::reHashUntilSuccess() {
  int next_hash_table_size = getNextHashTableSize(hash_table_size_);
  while (true) {
    if (reHash(next_hash_table_size)) {
      return;
    }
    next_hash_table_size = getNextHashTableSize(next_hash_table_size);
  }
}

bool HashTable::reHash(int rehash_table_size) {  // Task 5

  //allocate new memory
  HashCell * rehash_table = new HashCell[ rehash_table_size ];
    for ( int i = 0; i < rehash_table_size; i++ )
  {
    rehash_table[i].state = HashCellState::Empty;
    rehash_table[i].student = NULL;
  }

  // copy
    for ( int i = 0; i < hash_table_size_; i++ )
  {

    if ( table_[i].state == HashCellState::Deleted || table_[i].state == HashCellState::Empty )  
    {
      continue;
    }

    else if ( table_[i].state == HashCellState::Active )
    {
      // prepare the data needed
      std::string name1 = table_[i].student->name();
      int hash_value1 = hashFunction( name1, base_1_, rehash_table_size );
      int hash_value2 = hashFunction( name1, base_2_, rehash_table_size );
      if ( hash_value2 == 0 )
      {
          hash_value2 = 1;
      }
      bool pos_found = false;
      // try with maximum_probe_number
      for ( int num_probe = 0; num_probe < maximum_probe_num_; num_probe++ )
      {
        int hik = probe_func_( hash_value1, hash_value2, num_probe, rehash_table_size );
    
        if ( rehash_table[ hik ].state == HashCellState::Active )
        {
          continue;
        }

        else if ( rehash_table[ hik ].state == HashCellState::Empty  )
        {
          pos_found = true;
          rehash_table[ hik ].state = HashCellState::Active;
          rehash_table[ hik ].student = new Student( *(this->table_[i].student) );
          break;
        }

      }// for loop for maximum probe number

      if ( !pos_found )
      { 
        delete [] rehash_table;
        rehash_table = NULL;
        return false; 
      }

    } // if the cell is active

  }// for loop of orginal hash-table size
  delete [] this->table_;
  this->table_ = rehash_table;
  this->hash_table_size_ = rehash_table_size;
  return true;

} // end of rehash

void HashTable::print() const {
  std::cout << "hash_table_size:" << hash_table_size_ << std::endl;
  for (int i = 0; i < hash_table_size_; i++) {
    std::cout << i << ": state = ";
    if (table_[i].state == HashCellState::Empty) {
      std::cout << "Empty" << std::endl;
    } 
    else if (table_[i].state == HashCellState::Deleted) {
      std::cout << "Deleted" << std::endl;
    } 
    else if (table_[i].state == HashCellState::Active) {
      std::cout << "Active ";
      std::cout << "Student = (" << table_[i].student->name() << ", "
                << table_[i].student->score() << ")" << std::endl;
    }
  }
}

