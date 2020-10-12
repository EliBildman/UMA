#include "BoundedBuffer.h"

BoundedBuffer::BoundedBuffer(int N) {
  //TODO: constructor to initiliaze all the varibales declared in BoundedBuffer.h
  buffer_size = N;
  buffer = new int[buffer_size];
  buffer_cnt = 0;
  buffer_first = 0;
  buffer_last = -1;
  buffer_lock = PTHREAD_MUTEX_INITIALIZER;
  buffer_not_empty = PTHREAD_COND_INITIALIZER;
  buffer_not_full = PTHREAD_COND_INITIALIZER;
}

BoundedBuffer::~BoundedBuffer() {
  //TODO: destructor to clean up anything necessary
  delete buffer;
}

void BoundedBuffer::append(int data) {
  //TODO: append a data item to the circular buffer
  pthread_mutex_lock(&buffer_lock);

  if(buffer_size == buffer_cnt) pthread_cond_wait(&buffer_not_full, &buffer_lock);

  buffer_last = (buffer_last + 1) % buffer_size;
  buffer[buffer_last] = data;
  if(buffer_cnt == 0) pthread_cond_signal(&buffer_not_empty);
  buffer_cnt++;

  pthread_mutex_unlock(&buffer_lock);
}

int BoundedBuffer::remove() {
  //TODO: remove and return a data item from the circular buffer
  pthread_mutex_lock(&buffer_lock);

  if(isEmpty()) pthread_cond_wait(&buffer_not_empty, &buffer_lock);

  int data = buffer[buffer_first];
  buffer_first = (buffer_first + 1) % buffer_size;
  buffer_cnt--;
  if(buffer_cnt == buffer_size) pthread_cond_signal(&buffer_not_full);
  
  pthread_mutex_unlock(&buffer_lock);
  return data;
}

bool BoundedBuffer::isEmpty() {
  //TODO: check is the buffer is empty
  return buffer_cnt == 0;
}
