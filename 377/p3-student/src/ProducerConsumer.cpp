#include "ProducerConsumer.h"

// TODO: add BoundedBuffer, locks and any global variables here
BoundedBuffer* buff;

int produced;
pthread_mutex_t produced_lock;
pthread_mutex_t output_lock;

int _items;
int _psleep;
int _csleep;

ofstream _output;

void InitProducerConsumer(int p, int c, int psleep, int csleep, int items) {
  //TODO: constructor to initialize variables declared
  //also see instruction for implementation
  
  _output.open("output.txt");

  buff = new BoundedBuffer(items);

  produced = 0;
  _items = items;
  _psleep = psleep;
  _csleep = csleep;

  pthread_t ptids[p];
  pthread_t ctids[c];

  int pids[p];
  int cids[c];

  for(int i = 0; i < p; i++) {
    pids[i] = i;
    pthread_create(ptids + i, NULL, producer, pids + i);
  }

  for(int i = 0; i < c; i++) {
    cids[i] = i;
    pthread_create(ctids + i, NULL, consumer, cids + i);
  }

  for(int i = 0; i < p; i++) {
    pthread_join(ptids[i], NULL);
  }

  for(int i = 0; i < c; i++) {
    pthread_join(ctids[i], NULL);
  }

  _output.close();

}

void* producer(void* threadID) {
  //TODO: producer thread, see instruction for implementation

  while(produced != _items) {

    pthread_mutex_lock(&produced_lock);

    buff->append(0);
    produced++;

    pthread_mutex_lock(&output_lock);

    _output << "Producer #" << *((int *) threadID) << ", time = " << time(NULL) << ", producing data item #" << produced << ", item value = 0\n";
    
    pthread_mutex_unlock(&output_lock);
    pthread_mutex_unlock(&produced_lock);

    usleep(_psleep);
  }

  return NULL;

}

void* consumer(void* threadID) {
  //TODO: consumer thread, see instruction for implementation

  while(produced != _items || !buff->isEmpty()) {

    buff->remove();

    pthread_mutex_lock(&output_lock);

    _output << "Consumer #" << *((int *) threadID) << ", time = " << time(NULL) << ", comsuming data item with value = 0\n";

    pthread_mutex_unlock(&output_lock);

    usleep(_csleep);

  }

  return NULL;

}
