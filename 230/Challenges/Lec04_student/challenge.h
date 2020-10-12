#include <stdio.h>
#include <string.h>

#ifndef CH_HEAD
#define CH_HEAD

struct BSTNode
{
  struct BSTNode* left;
  char* name;
  struct BSTNode* right;
};

// Getters for global variables in challenge.c

struct BSTNode get_apple();
struct BSTNode get_banana();
struct BSTNode get_mango();
struct BSTNode get_nectarine();
struct BSTNode get_orange();
struct BSTNode get_peach();
struct BSTNode get_pear();

struct BSTNode* get_apple_ptr();
struct BSTNode* get_banana_ptr();
struct BSTNode* get_mango_ptr();
struct BSTNode* get_nectarine_ptr();
struct BSTNode* get_orange_ptr();
struct BSTNode* get_peach_ptr();
struct BSTNode* get_pear_ptr();

char* get_print_buf();

// Struct field getters
// These are arguably no longer necessary,
//  since I've decided not to have students design the struct internals.
// But I'm doing these myself and keeping them on principal

struct BSTNode* get_left(struct BSTNode node);
struct BSTNode* get_right(struct BSTNode node);
char* get_name(struct BSTNode node);

// goal: resets the "print buffer"
void reset_print();

// goal: piece together a tree like the one below
/*
              banana                    
             /      \                   
            /        \                  
           /          \                 
      apple            pear             
                      /                 
                     /                  
                    /                   
           nectarine                    
          /         \                   
         /           \                  
        /             \                 
   mango               orange           
                             \          
                              \         
                               \        
                                peach   
*/
void build_tree();

// goal: fill print_buf with a new-line-delineated in-order-traversal of the trees's nodes' names
// param node: the root of the tree to "print"
// assumptions:
//   parameter node does not have NULL as its name field
//   reset_print has been called directly before this
//   (feel free to guard against these issues though)
void prep_print(struct BSTNode node);

#endif