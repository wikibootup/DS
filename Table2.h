#include <assert.h>
// Implementing a Table via Hashing

// for an array implementation, need a max table size
const int MAX_TABLE = 11;

template < class tableKeyType, class tableDataType >
class Table
{
public:
   Table(); // Table constructor
   void insert(const tableKeyType & key, const tableDataType & data);
   // Precondition: None
   // Postcondition: data and associated key are stored in the Table,
   //    i.e., lookup(key,data) == true and returns the data
   // Note: If there was already data stored with this key, the insert
   //    call will replace it.
   
bool lookup(const tableKeyType & key, tableDataType & data);
   // Precondition: None
   // Postcondition: if key is in the table, returns true and associated
   //    data is returned; otherwise, false is returned and
   //    data is undefined.
   void deleteKey(const tableKeyType & key);
   // Precondition: None
   // Postcondition: lookup(key,d) returns false
   void dump(); // print the contents of the hash table -- handy!
private:
   // implementation via a hash table
   enum slotType {Empty, Deleted, InUse};

struct slot {
      slotType slotStatus;
      tableKeyType key;
      tableDataType data;
   };
   slot T[MAX_TABLE];    // stores the items in the table
   int entries;          // keep track of number of entries in table
   int hash(const tableKeyType & key);
   // Precondition: none
   // Postcondition: none
   // Returns: the home address for key
   
int probe(const int pos);
   // Precondition: pos is a slot between 0 and MAX_TABLE-1
   // Postcondition: none
   // Returns: the next slot, using wrapping (between 0 and MAX_TABLE-1)
   bool search(int & pos, const tableKeyType & target);
   // Precondition: pos is the hash address of target
   // Postcondition: if target is in the table, pos is set to its actual slot
   // Returns: true if target is in the table, else false
};

////////////////////

template < class tableKeyType, class tableDataType >
int
Table < tableKeyType, tableDataType >
::hash(const tableKeyType & key)
{
   return key % MAX_TABLE;
}
template < class tableKeyType, class tableDataType >
int
Table < tableKeyType, tableDataType >
::probe(const int pos)
{
   if (pos < MAX_TABLE - 1)
      return pos + 1;
   else
      return 0;
}

template < class tableKeyType, class tableDataType >
bool
Table < tableKeyType, tableDataType >
::search(int & pos, const tableKeyType & target)
{
   // search for target, starting at pos
   for ( ; T[pos].slotStatus != Empty; pos = probe(pos))
      if (T[pos].slotStatus == InUse && T[pos].key == target)
         return true;
   return false;
}

template < class tableKeyType, class tableDataType >
Table < tableKeyType, tableDataType >
::Table() // implementation of Table constructor
{
   entries = 0;
   int i;
   for (i = 0; i < MAX_TABLE; i++)
      T[i].slotStatus = Empty;
}

template < class tableKeyType, class tableDataType >
void
Table < tableKeyType, tableDataType >
::insert(const tableKeyType & key, const tableDataType & data)
{
   assert(entries < MAX_TABLE - 1);
   int pos(hash(key)); // find a position to insert the item
   if (!search(pos, key)) { // key was not in the table
      // starting at home address, find first free position
      pos = hash(key);
      while (T[pos].slotStatus == InUse)
         pos = probe(pos);
      entries++; // number of entries goes up
   }
   T[pos].slotStatus = InUse;
   T[pos].key = key;
   T[pos].data = data;
}
template < class tableKeyType, class tableDataType >
bool
Table < tableKeyType, tableDataType >
::lookup(const tableKeyType & key, tableDataType & data)
{
   int pos(hash(key));
   if (search(pos, key)) {
      data = T[pos].data;
      return true;
   }
   else
      return false;
}
template < class tableKeyType, class tableDataType >
void
Table < tableKeyType, tableDataType >::deleteKey(const tableKeyType & key)
{
   int pos(hash(key));
   if (search(pos, key)) {
      T[pos].slotStatus = Deleted;
      entries--;
   }
}

// the following function is handy for debugging
template < class tableKeyType, class tableDataType >
void
Table < tableKeyType, tableDataType >::dump()
{
   int i;
   for (i = 0; i < MAX_TABLE; i++) {
      cout << i << '\t';
      switch(T[i].slotStatus) {
      case InUse: 
         cout << "In Use\t" << T[i].key << endl; 
         break;

      case Deleted: 
         cout << "Deleted\t" << T[i].key << endl; 
         break;
      case Empty: 
         cout << "Empty\t" << endl; 
         break;
      }
   }
   cout << "Entries = " << entries << "\n\n";
}


