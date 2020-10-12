#include <string>
#include <fstream>
#include <iostream>
#include <queue>
#include <list>

#include "scheduling.h"

using namespace std;

pqueue_arrival read_workload(string filename)
{
  pqueue_arrival workload;

  ifstream file;

  file.open(filename.c_str());

  if(!file.is_open()) {
    // printf("Didn't open.\n");
    exit(0);
  }

  char buff;
  char curr[30];
  int curi = 0;
  Process p = Process();
  int flag = 0;

  while(!file.eof()) {
    file >> noskipws >> buff;

    if(buff == ' ') {
      curr[curi] = '\0';
      p.arrival = atoi(curr);
      curi = -1;
      flag = 1;
    } else if (buff == '\n' && flag) {
      flag = 0;
      curr[curi] = '\0';
      p.duration = atoi(curr);
      workload.push(p);
      curi = -1;
      p = Process();
    } else {
      curr[curi] = buff;
    }
    curi++;
  }

  file.close();

  return workload;
}

void show_workload(pqueue_arrival workload)
{
  pqueue_arrival xs = workload;
  cout << "Workload:" << endl;
  while (!xs.empty())
  {
    Process p = xs.top();
    cout << '\t' << p.arrival << ' ' << p.duration << endl;
    xs.pop();
  }
}

void show_processes(list<Process> processes)
{
  list<Process> xs = processes;
  cout << "Processes:" << endl;
  while (!xs.empty())
  {
    Process p = xs.front();
    cout << "\tarrival=" << p.arrival << ", duration=" << p.duration
         << ", first_run=" << p.first_run << ", completion=" << p.completion << endl;
    xs.pop_front();
  }
}

list<Process> fifo(pqueue_arrival workload)
{

  list<Process> complete;

  int time = 0;

  while(!workload.empty()) {
    Process curr = workload.top();
    workload.pop();
    curr.first_run = time;
    time += curr.duration;
    curr.completion = time;
    complete.push_back(curr);
  }

  return complete;
}

list<Process> sjf(pqueue_arrival workload)
{

  list<Process> complete;
  pqueue_duration sorted;
  int time = 0;


  while(!workload.empty()) {
    while(workload.top().arrival <= time && !workload.empty()) {
      sorted.push(workload.top());
      workload.pop();
    }
    Process curr = sorted.top();
    sorted.pop();
    curr.first_run = time;
    time += curr.duration;
    curr.completion = time;
    complete.push_back(curr);
    while(!sorted.empty()) {
      workload.push(sorted.top());
      sorted.pop();
    }
  }

  return complete;
}

list<Process> stcf(pqueue_arrival workload)
{
  list<Process> complete;


  pqueue_duration arrived;
  int time = 0;

  while(!workload.empty() || !arrived.empty()) {

    while(!workload.empty() && workload.top().arrival <= time) {
      Process curr = workload.top();
      curr.first_run = -1;
      curr.completion = curr.duration;
      arrived.push(curr);
      workload.pop();
    }

    if(!arrived.empty()) {

      Process curr = arrived.top();
      arrived.pop();

      if(curr.first_run == -1) {
        curr.first_run = time;
      }

      if(curr.duration == 0) {
        curr.duration = curr.completion;
        curr.completion = time;
        complete.push_back(curr);
      } else {
        curr.duration -= 1;
        time++;
        arrived.push(curr);
      }
    } else {
      time++;
    }

  }

  return complete;
}

list<Process> rr(pqueue_arrival workload)
{

  list<Process> complete;
  pqueue_arrival arrived;
  pqueue_arrival doneincycle;

  int time = 0;

  while(!workload.empty() || !arrived.empty()) {


    while(!workload.empty() && workload.top().arrival <= time) {
      Process curr = workload.top();
      curr.first_run = -1;
      curr.completion = curr.duration;
      arrived.push(curr);
      workload.pop();
    }

    if(!arrived.empty()) {

      while(!arrived.empty()) {

        Process curr = arrived.top();
        arrived.pop();

        if(curr.first_run == -1) {
          curr.first_run = time;
        }

        if(curr.duration == 0) {
          curr.duration = curr.completion;
          curr.completion = time - 1;
          complete.push_back(curr);
        } else {
          curr.duration -= 1;
          time++;
          doneincycle.push(curr);
        }
      }

      while(!doneincycle.empty()) {
        Process curr = doneincycle.top();
        doneincycle.pop();
        arrived.push(curr);
      }

    } else {
      time++;
    }

  }

  return complete;
}

float avg_turnaround(list<Process> processes)
{
  float avg_t;
  for(auto it = processes.begin(); it != processes.end(); ++it) {
    avg_t += (float) (it->completion - it->arrival) / processes.size();
  }
  return avg_t;
}

float avg_response(list<Process> processes)
{
  float avg_r;
  for(auto it = processes.begin(); it != processes.end(); ++it) {
    avg_r += (float) (it->first_run - it->arrival) / processes.size();
  }
  return avg_r;
}

void show_metrics(list<Process> processes)
{
  show_processes(processes);
  cout << '\n';
  cout << "Average Turnaround Time: " << avg_turnaround(processes) << endl;
  cout << "Average Response Time:   " << avg_response(processes) << endl;
}
