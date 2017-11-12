#include "team.h"
#include<iostream>
using namespace std;
void game_sim(Team &team1,Team &team2){
	vector<Member> t1;
	vector<Member> t2;
	vector<Member> temp1 = team1.get_members();
	vector<Member> temp2 = team2.get_members();
	t1.push_back(choose(temp1,0));
	t2.push_back(choose(temp2,0));
	for(int i = 0;i < 3;i++){
		t1.push_back(choose(temp1,1));
		t2.push_back(choose(temp2,1));
		t1.push_back(choose(temp1,2));
		t2.push_back(choose(temp2,2));
	}
	for(int i = 0;i < 4;i++){
		t1.push_back(choose(temp1,3));
		t2.push_back(choose(temp2,3));
	}
	sort(t1,cmp);
	sort(t2,cmp);
	cout << "Group stage:" << endl;
	cout << team1.get_nation() << " vs " << team2.get_nation() << endl;
	cout << team1.get_nation() << endl;
	for(auto ele : t1){
		ele.show();
	}
	cout << team2.get_nation() << endl;
	for(auto ele : t2){
		ele.show();
	}
	cout << "Playing..." << endl;
	double z = (double)abs(team1.get_WR() - team2.get_WR()) / (team1.get_WR() + team2.get_WR());
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(4.0,0.8);
	int sum = (int)distribution(generator);
	int score1 = (team1.get_WR() * sum) / (team1.get_WR() + team2.get_WR());
	int score2 = sum - score1;
	
}