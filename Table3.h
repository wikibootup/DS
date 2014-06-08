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
   //   i.e., lookup(key,data) == true and returns the data
   //   Note: If there was already data stored with this key, the insert
   //         call will replace it.
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
   struct Slot;
   typedef Slot * Link;
   struct Slot {
      tableKeyType key;
      tableDataType data;
      Link next;
   };
   Link T[MAX_TABLE]; // table is an array of pointers to slots
   int hash(const tableKeyType & key);
   // Precondition: none
   // Postcondition: none
   // Returns: the home address for key

   bool search(Link & slotPointer, const tableKeyType & target);
   // Precondition: slotPointer points to the start of the chain for
   //    target's hash address
   // Postcondition: if target is in the chain, slotPointer points to it
   // Returns: true if target is in the table, else false
};

//////////////////
template < class tableKeyType, class tableDataType >
int
Table < tableKeyType, tableDataType >
::hash(const tableKeyType & key)
{
   return key % MAX_TABLE;
}

template < class tableKeyType, class tableDataType >
bool
Table < tableKeyType, tableDataType >
::search(Link & slotPointer, const tableKeyType & target)
{
   // search for target, starting at slotPointer
   for ( ; slotPointer; slotPointer = slotPointer -> next)
      if (slotPointer->key == target)
         return true;
   return false;
}
template < class tableKeyType, class tableDataType >
Table < tableKeyType, tableDataType >
::Table() // implementation of Table constructor
{
   int i;
   for (i = 0; i < MAX_TABLE; i++)
      T[i] = 0;
}
template < class tableKeyType, class tableDataType >
void
Table < tableKeyType, tableDataType >
::insert(const tableKeyType & key, const tableDataType & data)
{
   int pos(hash(key)); // find a position to insert the item
   Link sp(T[pos]);
   if (!search(sp, key)) { // key was not in the table
      // insert new item at beginning of list
      Link insertedSlot = new Slot;
      insertedSlot->key = key;
      insertedSlot->data = data;
      insertedSlot->next = T[pos];
      T[pos] = insertedSlot;
   }
   else  // found old record -- update the data
      sp->data = data;
}
template < class tableKeyType, class tableDataType >
bool
Table < tableKeyType, tableDataType >
::lookup(const tableKeyType & key, tableDataType & data)
{
   int pos(hash(key));
   Link sp(T[pos]);
   if (search(sp, key)) {
      data = sp->data;
      return true;
   }
   else
      return false;
}
template < class tableKeyType, class tableDataType >
void
Table < tableKeyType, tableDataType >::deleteKey(const tableKeyType & key)
{
   // need to find pointer to item preceding the slot to delete
   int pos(hash(key));
   Link p;
   if (0 == T[pos]) // there's nothing here
      return;
   if (T[pos]->key == key) { // special case, for first item in chain
      Link deleteSlot(T[pos]);
      T[pos] = T[pos]->next;
      delete deleteSlot;
   }

   else
      for (p = T[pos]; p->next; p = p->next)
         if (p->next->key == key) {
            Link deleteSlot = p->next;
            p->next = p->next->next;
            delete deleteSlot;
            break;
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
      Link p;
      for (p = T[i]; p; p = p->next)
         cout << p->key << '\t';
      cout << '\n';
   }
    cout << '\n';
}
