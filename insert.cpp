#include<bits/stdc++.h>
#include"kvStore.cpp"

using namespace std;

kvStore kv(10000000);

Slice *random_key(){
	string letters = "";
	for(char i = 'a';i<='z';i++)letters+=i;
	for(char i = 'A';i<='Z';i++)letters+=i;
	Slice *ret = new Slice;
	ret->size = 64;
	ret->data = (char *)malloc(64*sizeof(char));
	for(int i=0;i<64;i++)
		ret->data[i] = letters[rand()%52];
	return ret;
}

Slice *random_value(){
	string letters = "";
	for(int i = 32;i<=127;i++)letters+=char(i);
	Slice *ret = new Slice;
	ret->size = 255;
	ret->data = (char *)malloc(255*sizeof(char));
	for(int i=0;i<255;i++)
		ret->data[i] = letters[rand()%96];
	return ret;
}

pair <Slice *,Slice *> arr[10000000];

void checktime()
{
	struct timespec ts;
	printf("Running Program\n");
	clock_gettime(CLOCK_MONOTONIC_RAW,&ts);
	long double st=ts.tv_nsec/(1e9)+ts.tv_sec;

	for(int i=0;i<1e7;i++)
	{
		kv.put(*arr[i].first,*arr[i].first);
	}

	clock_gettime(CLOCK_MONOTONIC_RAW,&ts);
	long double en=ts.tv_nsec/(1e9)+ts.tv_sec;
	printf("Program ended\nTime = %Lf\n",en-st);
}

int main(void)
{
	for(int i=0;i<1e7;i++)
	{
		arr[i].first = random_key();
		arr[i].second = random_value();
	}
	cout<<"Done Making\n";
	checktime();
	return 0;
}