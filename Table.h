#include <assert.h>

// for an array implementation, need a max table size
const int MAX_TABLE = 1001;

template < class tableKeyType, class tableDataType >

class Table
{
public:
   Table(); // Table constructor
   bool lookup(tableKeyType lookupKey, tableDataType & data);
   void insert(tableKeyType insertKey, tableDataType insertData);
   void deleteKey(tableKeyType deleteKey);
private:
   // implementation via an unordered array of structs
   
struct item {
      tableKeyType key;
      tableDataType data;
   };
   item T[MAX_TABLE]; // stores the items in the table
   int entries;  // keep track of number of entries in table
   int search(tableKeyType key); // an internal routine for searching table
};

template < class tableKeyType, class tableDataType >
int
Table < tableKeyType, tableDataType >
::search(tableKeyType key)
{
   // internal routine for implementation --
   // searches in table for the key --
    // if found, returns its position;
   // else it returns the current value of
   // "entries" -- which is the index 1 past the
   // last item in the table
   int pos;
   for (pos = 0; pos < entries && T[pos].key != key; pos++) 
	;
   return pos;
}
template < class tableKeyType, class tableDataType >
Table < tableKeyType, tableDataType >::Table()
{
   entries = 0;
}
											
template < class tableKeyType, class tableDataType >
void
Table < tableKeyType, tableDataType >
::insert(tableKeyType key, tableDataType data)
{
   assert(entries < MAX_TABLE);
   int pos(search(key)); // set pos to search results
   if (pos == entries) // new key
      entries++;
   T[pos].key = key;
   T[pos].data = data;
}
template < class tableKeyType, class tableDataType >
bool
Table < tableKeyType, tableDataType >
::lookup(tableKeyType key, tableDataType &data)
{
   int pos(search(key)); // set pos to search results
   if (pos == entries) // not found
      return false;
   else {
      data = T[pos].data;
      return true;
   }
}
template < class tableKeyType, class tableDataType >
void Table < tableKeyType, tableDataType >
::deleteKey(tableKeyType key)
{
   int pos(search(key)); // set pos to search results
   if (pos < entries)  { // otherwise, it wasn't found, so do nothing
      // copy last entry into this position
      --entries;
      T[pos] = T[entries];
   }
}


