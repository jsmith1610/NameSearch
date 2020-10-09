//-----------------------------------------------------------
//  Purpose:    Implementation of BinaryTree class.
//  Author:     Jake Smith
//-----------------------------------------------------------
#include "tree.h"
#include <stdlib.h>

//-----------------------------------------------------------
// Constructor function.
//-----------------------------------------------------------
BinaryTree::BinaryTree()
{
   Root = NULL;
}

//-----------------------------------------------------------
// Destructor function helper function.
//-----------------------------------------------------------
void BinaryTree::DestroyHelper(Node * Tree)
{
   // Delete node and it's children
   if (Tree != NULL)
   {
      DestroyHelper(Tree->Left);
      DestroyHelper(Tree->Right);
      delete Tree;
   }
}

//-----------------------------------------------------------
// Destructor function.
//-----------------------------------------------------------
BinaryTree::~BinaryTree()
{
   // Call tree destroy function
   DestroyHelper(Root);
}

//-----------------------------------------------------------
// Search helper function.
//-----------------------------------------------------------
bool BinaryTree::SearchHelper(string Name, Node * Tree)
{
   // Data value not found 
   if (Tree == NULL){
       cout << "Name not found" << endl; 
      return false;
   }
   // Data value found 
   else if (Tree->Name == Name){
       cout << "Name found!" << endl;
       cout << "Name: " << Tree->Name << " Count: " << Tree->Count << " Percent: " << Tree->Percent << " Rank: " << Tree->Rank << endl;
      return true;
   }
   // Recursively search for data value
   else if (Tree->Name > Name)
      return (SearchHelper(Name, Tree->Left));
   else 
      return (SearchHelper(Name, Tree->Right));
}

//-----------------------------------------------------------
// Search for data in the binary tree.
//-----------------------------------------------------------
bool BinaryTree::Search(string Name)
{
   // Call tree searching function
   return (SearchHelper(Name, Root));
}

//-----------------------------------------------------------
// Insert helper function.
//-----------------------------------------------------------
bool BinaryTree::InsertHelper(string Name, int Count, float Percent, int Rank, Node * &Tree)
{
   // Insert data into the tree
   if (Tree == NULL)
   {
      Tree = new Node;
      Tree->Name = Name;
      Tree->Count = Count;
      Tree->Percent = Percent;
      Tree->Rank = Rank;
      
      Tree->Left = NULL;
      Tree->Right = NULL;
      return true;
   }

   // Recursively search for insertion position
   else if (Tree->Name > Name)
      return (InsertHelper(Name, Count, Percent, Rank, Tree->Left));
   else 
      return (InsertHelper(Name, Count, Percent, Rank, Tree->Right));
}

//-----------------------------------------------------------
// Insert data into the binary tree.
//-----------------------------------------------------------
bool BinaryTree::Insert(string Name, int Count, float Percent, int Rank)
{
   // Call tree insertion function
   return (InsertHelper(Name, Count, Percent, Rank, Root));
}

//-----------------------------------------------------------
// Delete a single node from the binary tree.
//-----------------------------------------------------------
bool BinaryTree::DeleteNode(Node * &Tree)
{
   Node *Temp = Tree;

   // Node has 0 children
   if ((Tree->Left == NULL) && (Tree->Right == NULL))
      Tree = NULL;

   // Node has 1 child
   else if (Tree->Left == NULL)
      Tree = Tree->Right;
   else if (Tree->Right == NULL)
      Tree = Tree->Left;


   // Node has 2 children
   else
   {
      // Find leftmost node in right subtree
      Node *Parent = Tree;
      Temp = Tree->Right;
      while (Temp->Left != NULL)
      {
	 Parent = Temp;
	 Temp = Parent->Left;
      }

      // Replace deleted data with leftmost value
      if (Parent == Tree)
	 Parent->Right = Temp->Right;
      else
	 Parent->Left = Temp->Right;
      Tree->Name = Temp->Name;
   }

   // Delete node
   delete Temp;
   return true;
}

//-----------------------------------------------------------
// Delete helper function.
//-----------------------------------------------------------
bool BinaryTree::DeleteHelper(string Name, Node * &Tree)
{
   // Data value not found
   if (Tree == NULL)
      return false;

   // Data value found and deleted
   else if (Tree->Name == Name)
      return (DeleteNode(Tree));

   // Recursively search for node to delete
   else if (Tree->Name > Name)
      return (DeleteHelper(Name, Tree->Left));
   else 
      return (DeleteHelper(Name, Tree->Right));
}

//-----------------------------------------------------------
// Delete data from the binary tree.
//-----------------------------------------------------------
bool BinaryTree::Delete(string Name)
{
   // Call tree deletion function
   return (DeleteHelper(Name, Root));
}

//-----------------------------------------------------------
// Print helper function.
//-----------------------------------------------------------
void BinaryTree::PrintHelper(Node * Tree)
{
   // Check terminating condition
   if (Tree != NULL)
   {
      // Print left subtree
      PrintHelper(Tree->Left);

      // Print node value
      cout << Tree->Name << " " << Tree->Count << " " << Tree->Percent << " " << Tree->Rank << " " << "|| ";

      // Print right subtree
      PrintHelper(Tree->Right);
   }
}

//-----------------------------------------------------------
// Print all records in the binary tree.
//-----------------------------------------------------------
void BinaryTree::Print()
{
   // Call tree printing function
   PrintHelper(Root);
   cout << endl;
}
int main(){
    BinaryTree tree;
    ifstream din;
    string filename;
    din.open("male.txt");
   if (din.fail()){
      cout << "File not found\n";
      return 0;
   } 
    string str;
    string name;
    int count;
    float percent;
    int rank;
    
   while (din>>name>>count>>percent>>rank){
       //For the time being only inserts first names of males and  their count 
        tree.Insert(name,count,percent,rank);
    }
     din.close();
     string choice = "yes";
     string searchName;
     cout << "Welcome to the popular name searcher!" << endl;
     cout << "Make sure to capitalize the name for it to work" << endl;
     while(choice == "yes"){
         cout << "What name would you like to search: ";
         cin >> searchName;
         tree.Search(searchName);
         cout << "Would you like to search another name (yes/no): ";
         cin >> choice;
         while (choice != "yes" && choice !="no"){
             cout << "Wrong input!" << endl;
             cout << "Would you like to search another name (yes/no): ";
                     cin >> choice;
         }
     }
     tree.Print();
    system("pause");
    return 0;
}



