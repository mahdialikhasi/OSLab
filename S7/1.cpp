#include <iostream>
using namespace std;
#include <algorithm>
#include <stdio.h>
#include <pthread.h>
int A[1000][1000];
int B[1000][1000];
int n = 0;
struct data{
	int i;
	int j;
};
void * routine1(void *x){
	int sum = 0;
	struct data *a = (struct data *) x;
	for (int i = 0; i < n; ++i)
	{
		sum += A[a->i][i] * B[i][a->j];
	}

	//cout << a->i << " :: " << a->j << " :: " << sum << endl;
	pthread_exit((void *)sum);
}
int main(){
	cout << "Enter size : " << endl;
	cin >> n;
	cout << "enter A" << endl;
	
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cin >> A[i][j];
		}
	}
	cout << "enter B" << endl;
	
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cin >> B[i][j];
		}
	}
	pthread_t thread[n];
	cout << "dot :: " << endl;
	for (int i = 0; i < n; ++i){
		int sum = 0;
		for (int j = 0; j < n; ++j)
		{
			struct data * a = new data();
			a->i = i;
			a->j = j;
			//cout << a->i << a->j << endl;
			pthread_create(&thread[i], NULL, routine1, (void *) a);
		}
		//cout << i << endl;
		int *retval = new int;
		for (int j = 0; j < n; ++j)
		{
			pthread_join(thread[i], (void **)retval);
			cout << *retval << " ";
		}
		cout << endl;
	}
	return 0;
}