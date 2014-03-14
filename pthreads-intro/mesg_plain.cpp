/*
 * Copyright Divakar Viswanath, 2009-2014
 */

/*     
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of version 2 of the GNU General Public License as 
 * published by the Free Software Foundation.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "mesg.hh"
#include <pthread.h>
#include <cstdio>
#include <cstring>

void *print_message(void *arg){
	char *s = (char *)arg;
	char ss[400];
	int l = strlen(s);
	for(int i=0; i < l; i++){
		ss[2*i] = s[i];
		ss[2*i+1] = (s[i]==' ')?' ':'_';
	}
	ss[2*l] ='\0';
	printf("%s",s);
	printf("\n");
	printf("%s", ss);
	printf("\n");
	printf("ss = %p \n\n", (void *)ss);
	return NULL;
}


void fork_pthreads(){
	pthread_t thread1, thread2, thread3;
	char s[600];
	sprintf(s, "Message for thread1");
	sprintf(s+200, "Message for thread2");
	sprintf(s+400, "Message for thread3");
	pthread_create(&thread1, NULL, print_message, (void *)s);
	pthread_create(&thread2, NULL, print_message, (void *)(s+200));
	pthread_create(&thread3, NULL, print_message, (void *)(s+400));
	void *result;
	pthread_join(thread1, &result);
	pthread_join(thread2, &result);
	pthread_join(thread3, &result);
}
