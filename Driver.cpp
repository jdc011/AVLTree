/*=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
                                                      Author: Jeremy Cruz
                                                      
                                                      Date:   2016

                                   Driver.cpp
--------------------------------------------------------------------------------
Purpose: This driver will test our tree by taking a file of data as a 
         command line input. This will test a tree of strings.
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~*/
#include "Tree.h"
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

/*------------------------------------------------------------------------------
Name:      main

Purpose:   Test the tree by inserting strings from an input file from the 
           command line.

Parameters: name of input file

Return:     exit code
------------------------------------------------------------------------------*/
int main(int argc, char * argv[])
{
   ifstream fio; /* input file object */
   fio.open(argv[1], ios :: binary); /* open file in binary mode */

   /* invalid command line input */
   if(argc != 2)
   {
      cerr << "Usage: ./main <filename of data file>" << endl;
      return 1; /* failure */
   }

   /* file not found */
   if(!fio.is_open())
   {
      cerr << "File not found!" << endl;
      return 1; /* failure */
   }

   /* adjust file pointers to test emptiness */
   fio.seekg(0, ios_base :: end);
   unsigned int file_length = fio.tellg();

   /* file is empty */
   if(file_length == 0)
   {
      cerr << "File is empty!" << endl;
      return 1; /* failure */
   }

   /* update file pointer to beginning after all tests passed */
   fio.seekg(0, ios_base :: beg);

   Tree<string> tree; /* tree of strings */
   string data; /* to be inserted to the tree */

   /* insert all file contents into tree */
   while(getline(fio, data))
      tree.insert(data);
   
   /*close the file and print the tree contents */
   fio.close();
   tree.print_tree();

   return 0; /* sucess */
}
