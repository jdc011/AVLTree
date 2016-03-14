/*=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
                                                      Author: Jeremy Cruz
                                                      
                                                      Date:   2016

                                   Node.h
--------------------------------------------------------------------------------
Purpose: This is the definition of the node class. All members are public 
         the tree is made up of nodes and must know all its values.
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~*/
#ifndef NODE_H
#define NODE_H

template<typename Data> /* define template definition for class below */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name:        Node

Purpose:     Make the tree and holds values that determines the structure of the
             tree.

Data Fields: parent:  top node
             right:   right node
             left:    left node
             entry:   value in node
             height:  how tall is the node
             level:   level of node's address
             width:   width of subtree defined by node
             depth:   depth of node
             balance: right height minus left height of the node

Functions: Node:       constructor
           ~Node:      destructor
           sucessor:   find next node
           print_node: print contents of node
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class Node
{
   public:
      /* data fields */
      Node<Data> * parent; /* parent pointer */
      Node<Data> * right;  /* right pointer */
      Node<Data> * left;   /* left pointer */
      Data entry;          /* entry held via generic */
      unsigned int height, /* height of the node */
                   level,  /* current level where this node resides in the tree
                              */
                   width,  /* how wide the subtree defined by this node is */
                   depth;  /* depth of this node */
      int balance;         /* balance of this node defined by left and right 
                              heights */
  
      /* functions */
      Node(Data); /* constructor for defining a node object of a given entry */
      ~Node(void); /* destructor implementing node deletion */
      Node<Data> * sucessor(Node<Data> *); /* find next node in ascending order 
                                              of entry of the node passed in */
      void print_node(Node<Data> *); /* print the contents of this node */
};

#endif
