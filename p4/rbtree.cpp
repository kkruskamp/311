// rbtree.cpp 

/* @author Kyle Kruskamp
 * @date April 28th 2016
 *
 * SOURCES: Cormen Textbook (one recommended for class)
 *          Class Notes website (Binary Search Tree && RBT)
 *          http://www.cs.yorku.ca/~aaw/Sotirios/RedBlackTreeAlgorithm.html
 */

#include <iostream>
#include <iomanip>
#include "rbtree.h"

using std::cout;
using std::setw;
using std::endl;

RBTree :: RBTree()
{
   nil = new Node();
   root = nil;
}

//Node Destructer
RBTree :: Node :: ~Node()
{
   delete this->key;
   delete this->value;
} 

RBTree :: ~RBTree()
{
   //Dont need this because myRBT is created statically in rbapp.h.
}

/* @brief
 * Delete function checks if node is null by searching for a value
 * if node is null break loop
 * else if check for duplicates, if found set temp node and delete
 * else checks subtrees and looks for duplicates to delete.
 */

void RBTree :: rbDelete(const string &key, const string &value)
{
   Node *temp = nil;
   temp = rbTreeSearch(root, key);

   if (temp == nil)
   {
      return;
   }

   else
   {
      if ( *(temp->value) == value)
      {
         Node *dNode = temp;
         rbDelete(dNode);
         rbDelete(key, value);
         return;
      }

      else
      {
         Node *succ;
         Node *tempSucc = temp;
         succ = rbTreeSuccessor(tempSucc);

         /* @brief
          * while temp node has a succ and its keys and values are matching
          * delete temp node then reset node to nil
          else set succ node to be the new successor
          */
         while (succ != nil && *(succ->key) == key)
         {
            if ( *(succ->value) == value)
            {
               rbDelete(succ);
               rbDelete(key, value);
               succ = nil;
            }

            else
            {
               tempSucc = succ;
               succ = rbTreeSuccessor(tempSucc);
            }
         }

         Node *pNode;
         Node *tempPred = temp;
         pNode = rbTreePredecessor(tempPred);

         /*
          * Same process as above except we find the pred
          */
         while (pNode != nil && *(pNode->key) == key)
         {
            if ( *(pNode->value) == value)
            {
               rbDelete(pNode);
               rbDelete(key, value);
               pNode = nil;
            }

            else
            {
               tempPred = pNode;
               pNode = rbTreePredecessor(tempPred);
            }
         }
      }
   }
}

/*
 * delete pseudo code from book, deletes nodes using fixup and transplant
 */
void RBTree :: rbDelete(Node *z)
{
   Node *y;
   Node *x;
   char oColor;
   y = z;
   oColor = y->color;

   if (z->left == nil)
   {
      x = z->right;
      rbTransplant(z, z->right);
   }

   else if (z->right == nil)
   {
      x = z->left;
      rbTransplant(z, z->left);
   }

   else
   {
      y = rbTreeMaximum(z->left);
      oColor = y->color;
      x = y->left;

      if (y->parent == z)
      {
         x->parent = y;
      }
      else
      {
         rbTransplant(y, y->left);
         y->left = z->left;
         y->left->parent = y;
      }

      rbTransplant(z, y);
      y->right = z->right;
      y->right->parent = y;
      y->color = z->color;
   }

   if (oColor == 'B')
   {
      rbDeleteFixup(x);
   }

   delete z;
}

/*
 * Adapted again from the Cormen textbook pg. 326 uses left and right rotate along with color to allocate nodes after deletion.
 */
void RBTree :: rbDeleteFixup(Node *z)
{
   Node *y;

   while(z != root && z->color == 'B')
   {
      if (z == z->parent->left)
      {
         y = z->parent->right;

         if (y->color == 'R')
         {
            y->color = 'B';
            z->parent->color = 'R';
            leftRotate(z->parent);
            y = z->parent->right;
         }

         if (y->left->color == 'B' && y->right->color == 'B')
         {
            y->color = 'R';
            z = z->parent;
         }

         else
         {
            if (y->right->color == 'B')
            {
               y->left->color = 'B';
               y->color = 'R';
               rightRotate(y);
               y = z->parent->right;
            }

            y->color = z->parent->color;
            z->parent->color = 'B';
            y->right->color = 'B';
            leftRotate(z->parent);
            z = root;
         }
      }

      else
      {
         y = z->parent->left;

         if (y->color == 'R')
         {
            y->color = 'B';
            z->parent->color = 'R';
            rightRotate(z->parent);
            y = z->parent->left;
         }

         if (y->right->color == 'B' && y->left->color == 'B')
         {
            y->color = 'R';
            z = z->parent;
         }

         else
         {
            if (y->left->color == 'B')
            {
               y->right->color = 'B';
               y->color = 'R';
               leftRotate(y);
               y = z->parent->left;
            }

            y->color = z->parent->color;
            z->parent->color = 'B';
            y->left->color = 'B';
            rightRotate(z->parent);
            z = root;
         }
      }
   }

   z->color = 'B';
}

//sudo code provided from book and source
RBTree :: Node *RBTree :: rbTreeMinimum(Node *x)
{
   while (x->left != nil)
   {
      x = x->left;
   }

   return x;
} 

//sudo code providied from book and source
RBTree :: Node *RBTree :: rbTreeMaximum(Node *x)
{
   while (x->right != nil)
   {
      x = x->right;
   }

   return x;
}

/* @brief
 * if tree has right return minimum of the right tree
 */
RBTree :: Node *RBTree :: rbTreeSuccessor(Node *x)
{
   Node *y;

   if (x->right != nil)
   {
      return rbTreeMinimum(x->right);
   }

   y = x->parent;

   while (y != nil && x == y->right)
   {
      x = y;
      y = y->parent;
   }

   return y;
}

/* @brief
 * same as above but opposite
 */
RBTree :: Node* RBTree :: rbTreePredecessor(Node *x) 
{
   Node *y;

   if (x->left != nil) 
   {
      return rbTreeMaximum(x->left);
   }

   y = x->parent;

   while (y != nil && x == y->left) 
   {
      x = y;
      y = y->parent;
   }

   return y;
}

//Constructor sets
RBTree :: Node :: Node()
{
   left = nullptr;
   right = nullptr;
   parent = nullptr;
   key = nullptr;
   value = nullptr;
   color = 'B';
}

//Constructor part 2
RBTree :: Node :: Node(const string& key_new, const string& value_new, Node* nil)
{
   key = new string(key_new);
   value = new string(value_new);
   left = nil;
   right = nil;
   parent = nil;
}

/* @brief
 * if x parent is nil set y node as root
 * else if x's parents has a left node, set that node to y
 * else if x's parent has a right node set that to y
 * else set both parents equal
 */
void RBTree :: rbTransplant(Node *x, Node *y)
{
   if (x->parent == nil)
   {
      root = y;
   }

   else if (x == x->parent->left)
   {
      x->parent->left = y;
   }

   else
   {
      x->parent->right = y;
   }

   y->parent = x->parent;
}

//Given function passes in root and depth
void RBTree :: rbPrintTree()
{
   reverseInOrderPrint(root, 0);
}

//Given function
void RBTree :: reverseInOrderPrint(Node *x, int depth) 
{
   if ( x != nil ) 
   {
      reverseInOrderPrint(x->right, depth+1);
      cout << setw(depth*4+4) << x->color << " ";
      cout << *(x->key) << " " << *(x->value) << endl;
      reverseInOrderPrint(x->left, depth+1);
   }
}

/*@brief
 * if passed in node is nil or has a dupe
 * else if recursively search through left subs
 * else recursively search right
 */
RBTree :: Node* RBTree :: rbTreeSearch(Node *x, const string &key)
{
   if ((x == nil) || (key == *(x->key)))
   {
      return x;
   }

   if (key < *(x->key))
   {
      return rbTreeSearch(x->left, key);
   }

   else
   {
      return rbTreeSearch(x->right, key);
   }
}

/* This method uses the rbTreeSearch, rbTreeSuccessor, and
 * rbTreePredecessor functions to find the matches.
 */
vector<const string*> RBTree :: rbFind(const string& key)
{
   vector<const string*> word;
   Node* find = nil;
   find = rbTreeSearch(root,key);

   if (find != nil && (*(find->key) == key))
   {
      word.push_back(find->value);
      Node *succ;
      Node *succNode = find;
      succ = rbTreeSuccessor(succNode);

      while (succ != nil && *(succ->key) == key)
      {
         word.push_back(succ->value);
         succNode = succ;
         succ = rbTreeSuccessor(succNode);
      }

      Node* pred;
      Node* predNode = find;
      pred = rbTreePredecessor(predNode);

      while(pred != nil && *(pred->key) == key)
      {
         word.push_back(pred->value);
         predNode = pred;
         pred = rbTreePredecessor(predNode);
      }
   }
   return word;
}

/* @brief
 * right rotate assumes left child is not nil
 * right pivots and makes y the new root of the sub
 */
void RBTree :: rightRotate(Node *x)
{
   Node *y = x->left;
   x->left = y->right;

   if (y->right != nil)
   {
      y->right->parent = x;
   }

   y->parent = x->parent;

   if (x->parent == nil)
   {
      root = y;
   }

   else if (x == x->parent->right)
   {
      x->parent->right = y;
   }

   else
   {
      x->parent->left = y;
   }

   y->right = x;
   x->parent = y;
}

/* @brief
 * left rotate assumes right child is not nil
 * left pivots and makes y the new root of the sub
 * same as right but opposite
 */
void RBTree :: leftRotate(Node *x)
{
   Node *y = x->right;
   x->right = y->left;

   if (y->left != nil)
   {
      y->left->parent = x;
   }

   y->parent = x->parent;

   if (x->parent == nil)
   {
      root = y;
   }

   else if (x == x->parent->left)
   {
      x->parent->left = y;
   }

   else
   {
      x->parent->right = y;
   }

   y->left = x;
   x->parent = y;   
}

//Adapted from class notes given, rebalances RBT after new nodes are inserted
//uses left and right rotate along with parent location to allocate new nodes
void RBTree :: rbInsertFixup(Node *z)
{
   Node *y;

   while (z->parent->color == 'R')
   {
      if (z->parent == z->parent->parent->left)
      {
         y = z->parent->parent->right;

         if (y->color == 'R')
         {
            z->parent->color = 'B';
            y->color = 'B';
            z->parent->parent->color = 'R';
            z = z->parent->parent;
         }

         else if (z == z->parent->right)
         {
            z = z->parent;
            leftRotate(z);
         }

         else
         {
            z->parent->color = 'B';
            z->parent->parent->color = 'R';
            rightRotate(z->parent->parent);
         }
      }

      else
      { 
         y = z->parent->parent->left;

         if (y->color == 'R')
         {
            z->parent->color = 'B';
            y->color = 'B';
            z->parent->parent->color = 'R';
            z = y->parent->parent;
         }

         else if (z == z->parent->left)
         {
            z = z->parent;
            rightRotate(z);
         }

         else
         {
            z->parent->color = 'B';
            z->parent->parent->color = 'R';
            leftRotate(z->parent->parent);
         }
      }
   }

   root->color = 'B';
}

/* @Brief 
 * Sudo code straight from the source
 * ended up not using private helper insert function 
 * included new node and other nodes in this function instead
 */
void RBTree :: rbInsert(const string& key, const string& value)
{
   Node *y = new Node(key, value, nil);
   Node *z = nil;
   Node *x = root;
   while(x != nil)
   {
      z = x;

      if(*(y->key) < *(x->key))
      {
         x = x->left;
      }

      else
      {
         x = x->right;
      }
   }

   y->parent = z;

   if(z == nil)
   {
      root = y;
   }
   else if(*(y->key) < *(z->key))
   {
      z->left = y; 
   }
   else 
   {
      z->right = y;
   }
   y->left = nil;
   y->right = nil;
   y->color = 'R';
   rbInsertFixup(y);
}
