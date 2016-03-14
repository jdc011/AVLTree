/*=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
                                                      Author: Jeremy Cruz
                                                      
                                                      Date:   2016

                                   Node.cpp
--------------------------------------------------------------------------------
Purpose: This contains the definition of a node along with a destructor to allow
         deletion of this node. Node values are set to default. This implements
         finding the sucessor of the node that was passed in. This is also where
         a function to print a node passed in is implemented.
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~*/
#include "Node.h"
#include<iostream>
#include<string>

template<typename Data> /* define template definition for function below */
/*------------------------------------------------------------------------------
Name:       Node 

Purpose:    Constructor for a node object. Data fields are initialized to their
            values of a default state.

Parameters: entry: value held by this node via generic

Return:     none
------------------------------------------------------------------------------*/
Node<Data> :: Node(Data entry)
{
   parent = right = left = 0; /* pointers are null by default */
   height = level = 0; /* height and level are empty */
   width = depth = 1; /* depth if 1 when this node exists */
   balance = 0; /* node starts at perfect balance */
   this->entry = entry; /* data value held by this node via generic */
}

template<typename Data> /* define template definition for function below */
/*------------------------------------------------------------------------------
Name:       ~Node

Purpose:    Node destructor, no defined implementation

Parameters: none

Return:     none
------------------------------------------------------------------------------*/
Node<Data> :: ~Node()
{
   /* no defined implementation for the destructor */  
}

template<typename Data> /* define template definition for function below */
/*------------------------------------------------------------------------------
Name:       sucessor

Purpose:    Given a node passed in, traverse the tree under certain cases to 
            find the suceeding node based on the value it hold. Cases involve
            whether it has a right child.

Parameters: node: find the sucessor of this node

Return:     sucessor_node: sucessor of the node that was passed in
------------------------------------------------------------------------------*/
Node<Data> * Node<Data> :: sucessor(Node<Data> * node)
{
   Node<Data> * sucessor_node = 0; /* sucessor node defaulted to null */

   /* no right child */
   if(!node->right)
   {
      /* no sucessor can be found from a root with no right child */
      if(!node->parent)
         return sucessor_node;

      /* case where current is the left of parent, just go up */
      if(node->parent->left == node)
         sucessor_node = node->parent;
      /* case where current is the right of parent */
      else
      {
         /* keep going up to right nodes */
         while(node->parent && node->parent->right == node)
            node = node->parent;
         
         /* here we hit the root meaning we came from the biggest node, so
            there is no sucessor */
         if(!node->parent)
            return sucessor_node; 

         /* parent is the sucessor */
         sucessor_node = node->parent;
      }
   }
   /* has a right child */
   else 
   {
      /* start right */
      node = node->right;

      /* go fas left as possible */
      while(node->left)
         node = node->left;
      
      /* landed on sucessor after going all the way left as far as psossible */
      sucessor_node = node;
   }
   
   /* current node is the sucessor, return it */
   return sucessor_node;
}

template<typename Data> /* define template definition for function below */
/*------------------------------------------------------------------------------
Name:       print_node

Purpose:    print the contents of the node passed in

Parameters: node: node to have its values printed

Return:     void
------------------------------------------------------------------------------*/
void Node<Data> :: print_node(Node<Data> * node)
{
   /* print data fields of the node */
   std :: cout << node->entry << " ::"
               << " height: " << node->height << " ::"
               << " width: " << node->width << " ::"
               << " level: " << node->level << " ::"
               << " depth: " << node->depth << " ::"
               << " balance: " << node->balance << " ::";

   /* print pointers from this node */
   if(node->parent) 
      std :: cout << " parent: " << node->parent->entry << " ::"; /* parent */
   else
      std :: cout << " parent: " << "NULL " << "::"; /* no parent */

   if(node->right)
      std :: cout << " right: " << node->right->entry << " ::"; /* right */
   else
      std :: cout << " right: " << "NULL " << "::"; /* no right */

   if(node->left)
      std :: cout << " left: " << node->left->entry << std :: endl; /* left */
   else
      std :: cout << " left: " << "NULL" << std :: endl; /* no left */
}

/* define all types for the template class */
template class Node<char>; /* node holding char */
template class Node<short>; /* node holding short */
template class Node<int>; /* node holding int */
template class Node<float>; /* node holding float */
template class Node<double>; /* node holding double */
template class Node<long>; /* node holding long */
template class Node<std :: string>; /* node holding string */
