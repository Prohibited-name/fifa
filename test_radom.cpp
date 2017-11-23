#include<iostream>
#include<vector>
using namespace std;
struct test{
	vector<int> val;
	test(){
		val.push_back(1);
		val.push_back(2);
	}
	vector<int> &get(){
		return val;
	}
};
int main(){
	test t;
	cout << (t.get())[1] << endl;
}
