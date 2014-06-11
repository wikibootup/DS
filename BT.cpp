#include <iostream>
#include "BinaryTree.h"

using namespace std;

int main()
{
   typedef BinaryTree < char > charTree;
   typedef charTree * charTreePtr;

   charTreePtr bt1(new charTree);
   bt1->insert('A');

   charTreePtr bt2(new charTree);
   bt2->insert('B');

   charTreePtr bt3(new charTree);
   bt3->insert('E');
   bt3->makeLeft(bt1);
   bt3->makeRight(bt2);

   charTreePtr bt4(new charTree);
   bt4->insert('C');

   charTreePtr bt5(new charTree);
   bt5->insert('D');

   charTreePtr bt6(new charTree);
   bt6->insert('F');
   bt6->makeLeft(bt4);
   bt6->makeRight(bt5);

   charTreePtr bt7(new charTree);
   bt7->insert('G');
   bt7->makeLeft(bt3);
   bt7->makeRight(bt6);

   //// print out the root
   cout << "Root contains: " << bt7->getData() << endl;

   // print out root of left subtree
   cout << "Left subtree root: " << bt7->left()->getData() << endl;

   // print out root of right subtree
   cout << "Right subtree root: " << bt7->right()->getData() << endl;

   // print out leftmost child in tree
   cout << "Leftmost child is: " <<
      bt7->left()->left()->getData() << endl;

   cout << "Left subtree's rigthchild is: " <<
      bt7->left()->right()->getData() << endl;


   // print out right subtree's left child in tree
   cout << "right subtree's left child is: " <<
      bt7->right()->left()->getData() << endl;

   // print out rightmost child in tree
   cout << "Rightmost child is: " <<
      bt7->right()->right()->getData() << endl;

   return 0;
}

