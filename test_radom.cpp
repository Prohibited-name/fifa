#include "team.h"
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<ctime>
using namespace std;
int main(){
	for(int i = 0;i < 100;i++){
		int sum = rand() % 7;
		cout << sum << "  ";
	}
	cout << endl;
}
