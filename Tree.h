/*=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
                                                      Author: Jeremy Cruz
                                                      
                                                      Date:   2016

                                   Tree.h
--------------------------------------------------------------------------------
Purpose: This is the definition of the tree class. It is made up of nodes. Along
         with data values of the structure itself, the tree class contains 
         functions for what can be done to a tree based on a proposed node to
         perform that function on.
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~*/
#ifndef TREE_H
#define TREE_H
#include "Node.h"

template<typename Data> /* define template definiation for class below */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name:        Tree

Purpose:     Data structure made up of nodes to be formed in a binary structure

Data Fields: occupancy: amount of nodes in tree
             height:    how tall the tree is
             depth:     amount of levels in the tree
             width:     width of overall tree
             root:      top node in the tree

Functions: Tree:         constructor
           ~Tree:        destructor
           insert:       add nodes
           remove:       take out nodes
           find:         look for a node
           delete_nodes: delete tree node by node
           rotate:       balance nodes
           first_node:   return node carrying smallest value
           print_tree:   print tree attributes and all the nodes it is composed
                         of
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class Tree
{
   private:
      /* data fields */
      unsigned int occupancy, /* nodes in tree */
                   height,    /* how tall the tree is */
                   depth,     /* amount of levels */
                   width;     /* tree's left and right height plus the root */

      Node<Data> * root;      /* first node in the tree */

   public:
      /* functions */
      Tree(void); /* constructor for defining a tree */
      ~Tree(void); /* destructor that deletes the tree by nodes */
      bool insert(Data); /* add nodes */
      bool remove(Data); /* take out nodes */
      bool find(Data); /* look for nodes */
      void delete_nodes(Node<Data> *); /* delete all the nodes in the tree */
      void rotate(Node<Data> *); /* balance nodes */
      Node<Data> * first_node(Tree<Data> *); /* return node of smallest entry */
      void print_tree(void); /* print tree attributes and all its nodes */
};

#endif
