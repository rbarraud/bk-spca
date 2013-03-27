#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include "TimeStamp.hh"
using namespace std;

const int nthreads = 2;
void (*fnlist[nthreads-1])(void *);
void *arglist[nthreads-1];
int workflag[nthreads-1];
pthread_mutex_t mtx[nthreads-1];
pthread_t pthrd[nthreads-1];

void addone(void *arg){
	long *p = (long *)(arg);
	*p += 1;
}

void addtwo(void *arg){
	long *p = (long *)(arg);
	*p += 2;
}

void exitfn(void *arg){
	int tid = *((int *) arg);
	pthread_mutex_unlock(mtx+tid-1);
	pthread_exit(NULL);
}

void *worker(void *arg){
	int tid = *((int *) arg);
	while(1){
		pthread_mutex_lock(mtx+tid-1);
		if(workflag[tid-1]==1){
			(*(fnlist[tid-1]))(arglist[tid-1]);
			workflag[tid-1] = 0;
		}
		pthread_mutex_unlock(mtx+tid-1);
	}
	return NULL;
}

void spawn_workers(){
	static int tidlist[nthreads-1];
	for(int i=0; i < nthreads-1; i++){
		pthread_mutex_init(mtx+i, NULL);
		workflag[i] = 0;
		tidlist[i] = i+1;
		pthread_create(pthrd+i, NULL, worker, (void *)(tidlist+i));
	}
}

void shutdown_workers(){
	static int tidlist[nthreads-1];
	for(int i=0; i < nthreads-1; i++){
		while(1){
			pthread_mutex_lock(mtx+i);
			if(workflag[i]==0){
				fnlist[i] = exitfn;
				tidlist[i] = i+1;
				arglist[i] = tidlist+i;
				workflag[i] = 1;
				pthread_mutex_unlock(mtx+i);
				break;
			}
			pthread_mutex_unlock(mtx+i);
		}
		pthread_join(pthrd[i], NULL);
		pthread_mutex_destroy(mtx+i);
	}
}

void assignwork(int i, int tid, long *list){
	int j = tid-1;
	while(1){
		pthread_mutex_lock(mtx+j);
		if(workflag[j]==0){
			fnlist[j] = (i%2==0)?addone:addtwo;
			arglist[j] = (void *)(list+tid);
			workflag[j]=1;
			pthread_mutex_unlock(mtx+j);
			return;
		}
		pthread_mutex_unlock(mtx+j);
	}
}

void manager(long *list, int count){
	spawn_workers();
	for(int i=0; i < count; i++){
		for(int tid=1; tid < nthreads; tid++)
			assignwork(i, tid, list);
		if(i%2==0)
			addone((void *)list);
		else
			addtwo((void *)list);
	}
	shutdown_workers();
}

int main(){
	long list[nthreads];
	for(int i=0; i < nthreads; i++)
		list[i] = 0;
	int count = 1000*1000; 
	TimeStamp clk;
	clk.tic();
	manager(list, count);
	double cycles = clk.toc();
	cout<<"average per parallel region = "<<cycles/count<<endl;
	for(int i=0; i < nthreads; i++)
		cout<<list[i]<<endl;
}
