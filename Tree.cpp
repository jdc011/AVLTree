/*=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
                                                      Author: Jeremy Cruz
                                                      
                                                      Date:   2016

                                   Tree.cpp
--------------------------------------------------------------------------------
Purpose: This file contains all the functions of a binary tree including a
         balancing feature found in an avl tree. The tree is made up of nodes
         which are defined in Node.h each having left, right, and parent
         pointers to strcture the entire tree. Nodes can be inserted by less 
         than and greater than properties. Duplicate insert is not allowed.
         Nodes can also be searched for and removed. The destructor implements
         an iterative deletion process of each individual node. Upon insert and
         remove, node members are updated along with the datafields of the tree.
         Rotation is implemented upon insert if a node falls outside of the
         balance threshold. This is where nodes are removed and inserted again.
         The tree can also be printed node by node. It does this iteratively by
         starting at a defined first node by the tree and constantly calling
         the sucessor node implemented in Node.cpp.
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~*/
#include "Tree.h"
#include<iostream>

static const unsigned int BALANCE_THRESHOLD = 2; /* balance factor allowed by 
                                                    this tree */

template<typename Data> /* define template definition for function below */
/*------------------------------------------------------------------------------
Name:       Tree

Purpose:    Tree constructor for this object

Parameters: none
 
Return:     none
------------------------------------------------------------------------------*/
Tree<Data> :: Tree()
{
   /* all data values of tree default to 0 */
   occupancy = height = depth = width = 0;
}

template<typename Data> /* define template definition for function below */
/*------------------------------------------------------------------------------
Name:       ~Tree

Purpose:    destructor for this tree, calls delete_nodes to delete this tree 
            node by node starting from the root

Parameters: none

Return:     none
------------------------------------------------------------------------------*/
Tree<Data> :: ~Tree()
{
   /* delegate to function that deletes the nodes of this tree */
   delete_nodes(root);
}

template<typename Data> /* define template definition for function below */
/*------------------------------------------------------------------------------
Name:       insert

Purpose:    Nodes are inserted to the binary tree based on less than or greater
            than properties of the entry compared to the entry of other nodes
            already in the tree. This takes care of node and tree data values
            as inserting modifies the tree. Rotate is called upon an unbalanced
            node. Duplicate insert is not allowed and will cause this function 
            to return false.

Parameters: entry: the data value via generic to be held by the node attempting 
                   to be inserted

Return:     inserted: sucess or failure of insertion of a node with the given
                      entry
------------------------------------------------------------------------------*/
bool Tree<Data> :: insert(Data entry)
{
   Node<Data> * current; /* current node as insertion traverses tree */
   Node<Data> * new_node = 0; /* node to be assigned once and if inserted */
   bool inserted = false; /* return status of insertion */
   unsigned int traversals = 0; /* amount of levels traversed into the tree */

   /* case for empty tree, assign the root to be node inserted */
   if(occupancy == 0)
   {
      root = new Node<Data>(entry);
      current = root;
      current->width = 1;
      ++occupancy;
      ++depth;
      ++width;
      inserted = true; 
   }
   /* start at already defined root if tree is not null */
   else
      current = root;

   /* continue traversing tree until inserted, should be inserted at bottom */
   while(!inserted)
   {
      /* node with entry was found so loop terminates with insertion set to
         failed */
      if(current->entry == entry)
         break;

      /* increment amount of traversals going down the tree */
      ++traversals;

      /* go right if entry to be inserted is greater than entry where current 
         points to */
      if(current->entry < entry)
      {
         /* null spot not found, keep going right */
         if(current->right)
            current = current->right;
         /* place in new node and initialize its datafields, increment
            occupancy, inserted is true */
         else
         {
            current->right = new Node<Data>(entry);
            current->right->parent = current;
            current = current->right;
            current->level = traversals;
            ++occupancy;
            inserted = true;
         } 
      }
      /* go left if entry to be inserted is less than entry where current points
         to */
      else if(current->entry > entry)
      {
         /* null spot not found, keep going left */
         if(current->left)
            current = current->left;
         /* place in new node and initialize its datafields, increment 
            occupancy, inserted is true */
         else
         {
            current->left = new Node<Data>(entry);
            current->left->parent = current;
            current = current->left;
            current->level = traversals;
            ++occupancy;
            inserted = true;
         }
      }

   }

   /* case where current height and depth have to be incremented because 
      traversal went further down than previous version of this tree */
   if(height < traversals)
   {
      height = traversals;
      depth = height + 1;
   }

   new_node = current; /* save node just inserted */
   unsigned int up_traversals = 0; /* we have up traversals to update fields of
                                      parent nodes of node just inserted */

   /* traverse up the tree to update fields of above nodes since they were all 
      affected */
   do
   {
      /* go up the tree using parent pointers to u pdate current node in up 
         traversals */
      if(current->parent)
      {
         current = current->parent;
         ++up_traversals;
      }
      /* all parent are already taken care of */
      else
         break;
      
      /* case to having to increment height and depth since up traversal is 
         greater than current height and depth*/
      if(up_traversals > current->height)
      {
         ++current->height;
         ++current->depth;

      }

      /* update balances of each node, 3 cases are valid depending on children,
         balance = right's height - left's height */
      if(!current->right && current->left) /* only left child */
         current->balance = (-1 * current->left->height) - 1;
      else if(current->right && !current->left) /* only right child */
         current->balance = current->right->height + 1;
      else if(current->right && current->left) /* 2 children present */
         current->balance = current->right->height - current->left->height;
   }
   while(true);

   /* return status of sucessful insertion */
   return inserted;
}

template<typename Data> /* define template definition for function below */
/*------------------------------------------------------------------------------
Name:       remove

Purpose:    Remove a node given an entry. This modifies tree structure therefore
            data fields of this tree and any surrounding nodes are affected and
            must be updated as such. Remooval will fail if the given entry is
            not in the tree.

Parameters: entry: the data value via generic of the node looking for removal
                   from this tree

Return:     removed: status of whether a node was removed
------------------------------------------------------------------------------*/
bool Tree<Data> :: remove(Data entry)
{
   Node<Data> * current; /* current node being pointed to during traversal of 
                            this tree */
   bool removed = false; /* status of node being removed */

   /* empty tree or node not in the tree causes a failure to be returned */
   if(occupancy == 0 || !find(entry))
      return removed;
   /* set the current node to the root and search for the node to remove from 
      here */
   else
      current = root;

   /* search the tree until the node with the given entry is found */
   while(current->entry != entry)
   {
      /* current entry is bigger */
      if(current->entry > entry)
         current = current->left;
      /* current entry is smaller */
      else if(current->entry < entry)
         current = current->right;
   }

   /* edge case where the root is being removed; specialized to avoid seg 
      faulting the tree due to an empty root */
   if(current == root)
   {
      /* root is a leaf node */
      if(!current->left && !current->right)
         root = NULL;
      /* root only has a right child */
      else if(!current->left && current->right)
         root = current->right;
      /* root only has a left child */
      else if(!current->right && current->left)
         root = current->left;
      /* root has 2 children */
      else if(current->left && current->right)
      {
         /* look for sucessor to replace node to be removed */
         current = current->left;

         while(current->right)
            current = current->right;

         /* only entry is updated since the node is actually in the same place
            only having a different entry, more efficient than deleting the node
            to be removed */
         root->entry = current->entry;

         /* adjust pointers of the sucessor node after swapping nodes */
         if(current->parent->right == current)
            current->parent->right = NULL;
         if(current->parent->left == current)
            current->parent->left = NULL;
      }
   }
   /* node removal does not target the root */
   /* leaf node */
   else if(!current->left && !current->right)
   {
      if(current->parent->right == current)
         current->parent->right = NULL;
      else if(current->parent->left == current)
         current->parent->left = NULL;
   }
   /* has a right child */
   else if(current->right && !current->left)
   {
      /* right parent pointer adjustment */
      if(current->parent->right == current)
      {
         current->parent->right = current->right;
         current->right->parent = current->parent;
      }
      /* left parent pointer adjustment */
      else if(current->parent->left == current)
      {
         current->parent->left = current->right;
         current->right->parent = current->parent;
      }
   }
   /* has a left child */
   else if(!current->right && current->left)
   {
      /* right parent pointer adjustment */
      if(current->parent->right == current)
      {
         current->parent->right = current->left;
         current->left->parent = current->parent;
      }
      /* left parent pointer adjustment */
      else if(current->parent->left == current)
      
      {
         current->parent->left = current->left;
         current->left->parent = current->parent;
      }
   }
   /* has both children */
   else if(current->right && current->left)
   {
      Node<Data> * original = current; /* node to be removed and swapped */
      current = current->left;

      /* find sucessor node to swap with original node */
      while(current->right)
         current = current->right;

      /* update only the entry since the node is in the same place with only a
         different name but with same numerical fields */
      original->entry = current->entry;

      /* adjust pointers of sucessor after swapping */
      if(current->parent->right == current)
         current->parent->right = NULL;
      else if(current->parent->left == current)
         current->parent->left = NULL;
   }

   delete current; /* delete node that has been removed */
   --occupancy; /* decrement occupancy */
   removed = true; /* set removed to true */
   
   /* return status of removal */
   return removed;
}

template<typename Data> /* define template definition for function below */
/*------------------------------------------------------------------------------
Name:       find

Purpose:    search for a node in this tree to see whether or not it exists

Parameters: entry: node carrying this entry to be searched for

Return:     found: status of whether node with the given entry is in the tree
------------------------------------------------------------------------------*/
bool Tree<Data> :: find(Data entry)
{
   Node<Data> * current; /* current node in traversal of tree */
   bool found = false; /* status of whether the node containing the entry was 
                          found */

   /* empty tree, nothing can be found */
   if(occupancy == 0)
      return found;

   /* start searching from the root */
   current = root;

   /* continue this loop while the node is not found */
   while(!found)
   {
      /* node was found */
      if(current->entry == entry)
         found = true;

      /* go right if the current entry is too small */
      else if(current->entry < entry)
      {
         /* break at a leaf node, find fails */
         if(!current->right)
            break;
         else
            current = current->right;
      }
      
      /* go left if the current entry is too big */
      else if(current->entry > entry)
      {
         /* break at a leaf node, find fails */
         if(!current->left)
            break;
         else
            current = current->left;
      }
   }

   /* return status of whether node with the given entry is in the tree */
   return found;
}

template<typename Data> /* define template definition for function below */
/*------------------------------------------------------------------------------
Name:       delete_nodes

Purpose:    Recursive post order deletion of all nodes in the tree.

Parameters: node: should be the root node for all nodes to be sucessfully freed
                  from the tree

Return:     void
------------------------------------------------------------------------------*/
void Tree<Data> :: delete_nodes(Node<Data> * node)
{
   /* return if the tree is already empty */
   if(!node)
      return;

   /* post order deletion, left, right, then delete */
   delete_nodes(node->left);
   delete_nodes(node->right);
   delete node;
}

template<typename Data> /* define template definition for function below */
/*------------------------------------------------------------------------------
Name:       rotate

Purpose:    This is called when the node is unbalanced in order to keep the 
            tree balanced. Going outside the interval of the balance threshold
            will trigger execution of this function.

Parameters: node: node to be rotated from

Return:     void
------------------------------------------------------------------------------*/
void Tree<Data> :: rotate(Node<Data> * node)
{
   /* TODO */
}

template<typename Data> /* define template definition for function below */
/*------------------------------------------------------------------------------
Name:       first_node

Purpose:    Return the node of the tree containing the smallest entry among
            other nodes. Start from root and go as far left from there as 
            possible.

Parameters: tree: this tree

Return:     node: the node of the smallest entry in the tree    
------------------------------------------------------------------------------*/
Node<Data> * Tree<Data> :: first_node(Tree<Data> * tree)
{
   Node<Data> * node = 0; /* node to return defaulted to 0 incase of a null tree
                             */

   /* tree is null, return default node */
   if(occupancy == 0)
      return node;

   /* start at the root */
   node = tree->root;

   /* go as left as possible */
   while(node->left)
      node = node->left;

   /* return the smallest node */
   return node;
}

template<typename Data> /* define template definition for function below */
/*------------------------------------------------------------------------------
Name:       print_tree

Purpose:    Print all nodes of the tree in ascending order of entry along with
            datafields of each node and the tree itself.

Parameters: none

Return:     void
------------------------------------------------------------------------------*/
void Tree<Data> :: print_tree()
{
   Tree<Data> * tree = this; /* printing nodes of this tree */
   Node<Data> * node = tree->first_node(tree); /* start at the first node by 
                                                  delegating to the function 
                                                  that returns it*/
   unsigned int count = 1; /* starting count */

   /* print tree datafileds */
   std :: cout << "Tree attributes :: occupancy: " << occupancy 
               << " :: height: " << height << " :: depth: " << depth 
               << " :: width: " << width << '\n' << std :: endl;

   /* if tree is empty, say so and terminate */
   if(occupancy == 0)
   {
      std :: cout << "The tree is empty!" << std :: endl;
      return;
   }

   /* this will print all nodes in the tree using the sucessor of the current 
      node during the listing iteration */
   while(node->sucessor(node))
   {
      std :: cout << count << ". ";
      node->print_node(node); /* call print_node passing in the current node */
      node = node->sucessor(node); /* update node */
      ++count; /* update count */
   }
 
   /* print the final node */
   std :: cout << count << ". ";
   node->print_node(node);
}

/* define all types for the template class */
template class Tree<char>; /* tree of chars */
template class Tree<short>; /* tree of shorts */
template class Tree<int>; /* tree of ints */
template class Tree<float>; /* tree of floats */
template class Tree<double>; /* tree of doubles */
template class Tree<long>; /* tree of longs */
template class Tree<std :: string>; /* tree of strings */
