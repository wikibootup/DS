#include "BinaryTreeForBST.h"

template < class btElementType >
class BST : public BinaryTree < btElementType > {
public:
   BST();
   virtual void insert(const btElementType & d);
   // Precondition: if d is a left child, then d must be < parent->getData();
   //    if d is a right child, then d must be > parent->getData();
   // Postconditions: T->retrieve(k)->getData() == d
   
virtual BinaryTree < btElementType > * retrieve(const btElementType & d);
   // Precondition: none
   // Postcondition: none
   // Returns: if T contains a node matching d, then
   //    T->retrieve(d)->getData() == d; otherwise, T->isEmpty()
};

template < class btElementType >
void
BST < btElementType >
:: insert(const btElementType & d)
{
   if (nullTree) {
      nullTree = false;
      leftTree = new BST;
      rightTree = new BST;
      treeData = d;
   }
   else if (d == treeData)
      treeData = d;
   else if (d < treeData)
      leftTree->insert(d);
   else
      rightTree->insert(d);
}
template < class btElementType >
BinaryTree < btElementType > *
BST < btElementType >
:: retrieve(const btElementType & d)
{
   if (nullTree || d == treeData)
      return this;
   else if (d < treeData)
      return ((BST <btElementType> *) leftTree) ->retrieve(d);
   else
      return ((BST <btElementType> *) rightTree) ->retrieve(d);
}
template < class btElementType >
BST < btElementType >
:: BST() : BinaryTree < btElementType >() 
{
}

