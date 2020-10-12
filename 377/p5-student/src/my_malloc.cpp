#include "my_malloc.h"
#include <assert.h>
#include <stdio.h>
#include <sys/mman.h>

// A pointer to the head of the free list.
node_t *head = NULL;

// The heap function returns the head pointer to the free list. If the heap
// has not been allocated yet (head is NULL) it will use mmap to allocate
// a page of memory from the OS and initialize the first free node.
node_t *heap() {
  if (head == NULL) {
    // This allocates the heap and initializes the head node.
    head = (node_t *)mmap(NULL, HEAP_SIZE, PROT_READ | PROT_WRITE,
                          MAP_ANON | MAP_PRIVATE, -1, 0);
    head->size = HEAP_SIZE - sizeof(node_t);
    head->next = NULL;
  }

  return head;
}

// Reallocates the heap.
void reset_heap() {
  if (head != NULL) {
    munmap(head, HEAP_SIZE);
    head = NULL;
    heap();
  }
}

// Returns a pointer to the head of the free list.
node_t *free_list() { return head; }

// Calculates the amount of free memory available in the heap.
size_t available_memory() {
  size_t n = 0;
  node_t *p = heap();
  while (p != NULL) {
    n += p->size;
    p = p->next;
  }
  return n;
}

// Returns the number of nodes on the free list.
int number_of_free_nodes() {
  int count = 0;
  node_t *p = heap();
  while (p != NULL) {
    count++;
    p = p->next;
  }

  return count;
}

// Prints the free list. Useful for debugging purposes.
void print_free_list() {
  node_t *p = heap();
  while (p != NULL) {
    printf("Free(%zd)", p->size);
    p = p->next;
    if (p != NULL) {
      printf("->");
    }
  }
  printf("\n");
}

// Finds a node on the free list that has enough available memory to
// allocate to a calling program. This function uses the "first-fit"
// algorithm to locate a free node.
//
// PARAMETERS:
// size - the number of bytes requested to allocate
//
// RETURNS:
// found - the node found on the free list with enough memory to allocate
// previous - the previous node to the found node
//
void find_free(size_t size, node_t **found, node_t **previous) {

  node_t *last = NULL;
  node_t *curr = heap();

  while(curr != NULL) {
    if(curr->size + sizeof(node_t) >= size + sizeof(header_t)) {
      *found = curr;
      *previous = last;
      // printf("found %p\n", *found);
      return;
    }
    last = curr;
    curr = curr->next;
  }

  *found = NULL;
  *previous = NULL;

}

// Splits a found free node to accommodate an allocation request.
//
// The job of this function is to take a given free_node found from
// `find_free` and split it according to the number of bytes to allocate.
// In doing so, it will adjust the size and next pointer of the `free_block`
// as well as the `previous` node to properly adjust the free list.
//
// PARAMETERS:
// size - the number of bytes requested to allocate
// previous - the previous node to the free block
// free_block - the node on the free list to allocate from
//
// RETURNS:
// allocated - an allocated block to be returned to the calling program
//
void split(size_t size, node_t **previous, node_t **free_block,
           header_t **allocated) {
  assert(*free_block != NULL);

  node_t* save = *free_block;

  size_t shift = size + sizeof(header_t);

  *free_block = (node_t *) ((char *) (*free_block) + shift);
  (*free_block)->size = save->size - shift;
  (*free_block)->next = save->next;

  if(*previous == NULL) {
    head = *free_block;
  } else {
    (*previous)->next = *free_block;
  }

  *allocated = (header_t*) save;
  (*allocated)->size = size;
  (*allocated)->magic = MAGIC;

}

// Returns a pointer to a region of memory having at least the request `size`
// bytes.
//
// PARAMETERS:
// size - the number of bytes requested to allocate
//
// RETURNS:
// A void pointer to the region of allocated memory
//
void *my_malloc(size_t size) {

  node_t* free;
  node_t* previous;
  find_free(size, &free, &previous);

  if(free == NULL) return NULL;

  header_t* allocated;

  split(size, &previous, &free, &allocated);

  return (void *) (allocated + 1);

}

// Merges adjacent nodes on the free list to reduce external fragmentation.
//
// This function will only coalesce nodes starting with `free_block`. It will
// not handle coalescing of previous nodes (we don't have previous pointers!).
//
// PARAMETERS:
// free_block - the starting node on the free list to coalesce
//
void coalesce(node_t *free_block) {

  bool changed = true;

  while(changed && number_of_free_nodes() > 1) {
    changed = false;

    node_t* next = (node_t *) ((char *) free_block + (free_block->size) + sizeof(node_t));

    if(free_block->next == next) {
      changed = true;
      free_block->size += free_block->next->size + sizeof(node_t);
      free_block->next = free_block->next->next;
    }

    
  }
}

// Frees a given region of memory back to the free list.
//
// PARAMETERS:
// allocated - a pointer to a region of memory previously allocated by my_malloc
//
void my_free(void *allocated) {

  allocated = ((header_t *) allocated) - 1;

  assert(((header_t*) allocated)->magic == MAGIC);

  node_t* freedman = (node_t *) allocated;
  freedman->size = ((header_t *) allocated)->size;


  freedman->next = head;
  head = freedman;

  coalesce(head);

}
