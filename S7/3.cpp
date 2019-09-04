#include <iostream>
using namespace std;
#include <algorithm>
#include <stdio.h>
#include <pthread.h>
#define SIZE 5
int A[SIZE];
struct data{
	int i;
	int stride;
};
void * routine1(void *x){
	struct data *a = (struct data *) x;
	A[a->i] = min(A[a->i], A[a->i + a->stride]);
	pthread_exit((void *)x);
}
int main(){
	cout << "enter array" << endl;
	for (int i = 0; i < SIZE; ++i)
	{
		cin >> A[i];
	}
	
	int stride = SIZE / 2;
	int before = SIZE;
	while(stride != 0){
		pthread_t thread[stride];
		for (int i = 0; i < stride; ++i)
		{
			data * a = new data;
			a->i = i;
			a->stride = stride; 
			pthread_create(&thread[i], NULL, routine1, (void *) a);
		}
		for (int i = 0; i < stride; ++i)
		{
			pthread_join(thread[i], NULL);
		}
		if(before % 2 == 1)
			A[before / 2] = min(A[before - 1], A[before/2]);
		for (int i = 0; i < SIZE; ++i)
		{
			cout << A[i] << "," ;
		}
		cout << endl;
		if(before %2 == 1){
			before = stride + 1;
			stride = before / 2;
		}else{
			before = stride;
			stride /= 2;			
		}
	}
	cout << A[0] << endl;
	return 0;
}