# CSCI-220-AVL-Tree-Project
Final project for my Data Structures And Algorithms class. 
Reads in a file and then constructs an AVL Tree out of it.
The tree keeps track of a county code, population, and the name of the county.
User is then able to search for records, insert records, delete records, and list all records.

Project Handout
----------------
CSCI 220 -- Project 4 (AVL Trees)
Due Tuesday, 12/03/2019 (TTh Section)
Due Monday, 12/02/2019 (MW Section)

This project is designed to help you understand tree structure, its implementation, and its
usage. You will implement a population database for California counties using an AVL
Search Tree to store the database records. Define and implement an AVLTree class that
supports standard map operations using county/state code as a key for each record (no
duplicate keys). Your AVLTree class handles binary search tree of population records
and your application performs the tasks below via a menu using this binary search
tree. Your AVLTree class must be a regular class that can handle specified data,
county/state code, population, and county/state name (3 fields) and it cannot be a
C++ class template or a Java generic class. You must follow the specified interface
below for your class:

Class AVLTree
// constructor accepts file name and construct AVL tree
AVLTree(string filename)
// public operations
// print appropriate message and data if found
// print number of nodes examined
 void find(int code)
// print appropriate message and insert node if not found
// replace data if found; print number of nodes examined
void insert(int code, int pop, string countyState)
// print appropriate message and erase node if found
// print number of nodes examined
void erase(int code)
// print one record per line using an in-order traversal
void print()
// draw a reasonable tree with just code
void draw() // extra credit only

Feel free to add additional classes (Entry, BinaryTree, BST, etc.), or use existing classes
from your text book. Your class(es) must also use the ideas outline in the book such as
proper binary tree and tri-node restructuring so it is highly recommended that you
use/modify the code from the book. For erase operation, replace a node with two
internal children with an in-order successor. Do not use code from other sources.
Download the data file p4small.txt, containing a list of a few population records –
county/state code, population in million, and county with state abbreviation (3 fields
separated by commas). Build an AVL search tree from the records of the input data file
by inserting one record at a time to the tree (do not output anything when constructing the
tree). It then provides the following menu: 

1. Search for a record
2. Insert a record
3. Delete a record
4. List all records
5. Exit

Your program will continue until the user wants to exit this program. For option 1, user
will be prompted for the county/state code; if the record is found, display complete
record. For option 2, user will be prompted to enter the population record on one line:
county/state code, population, and county/state name. For option 3, user will be
prompted for the county/state code. For option 4, you need to perform an in-order
traversal and display one record per line (order by county/state code). In addition, your
program must display number of nodes examined for options 1 to 3. Make sure to search,
insert, and remove records for, to, and from different points of the tree (root, left, and
right node) to show that your implementation is working properly.
Run the following test cases after the tree is constructed:

1. List all records
2. Search for 6037
3. Search for 6000
4. Insert 6066, 1, “New County, CA”
5. Insert 6065, 2000, “Riverside, CA”
6. Delete 6999
7. Delete 6075
8. Delete 6055
9. List all records

Team Project: It is not required but it is recommended that you work in a team of
two. You must sign up by Wednesday, 11/13/19, for MW class or Thursday, 11/14/19,
for TTh class if it is going to be a team project. Make sure to split the responsibilities
equally and work together. You do need to provide a short description on who did what
and your experience as a team project. It is possible that all team members may not
receive the same score. If it is a team project, you need to also process the larger data
file, p4Medium.txt, and compare results with regular BST implementation (number of
nodes examined for applicable operations for the required test cases). Set up class BST
that has the same interface as class AVLTree. Your team can earn 4 extra points for
implementing the other extra feature.

Extra Credit: You can earn up to 4 additional points if you allow a hidden debugging
feature that draws a current tree using county/state code for each node (use menu option 0
and select that option right after the tree is constructed from the data file). Provide a
reasonable drawing with just the county/state code in each node. Show that it is working
correctly with a few records in the tree. For an individual project, you can also perform a
comparison of regular BST vs. AVL Tree as mentioned under team project for extra
credit.

© by T. Vo 
