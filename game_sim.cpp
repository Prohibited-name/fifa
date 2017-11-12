#include "team.h"
#include<iostream>
using namespace std;
Member choose(vector<Member> &m,int ans);
Member get_a_goal(vector<Member> &m);
bool find_name(vector<Member> &m,string name);
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
		cout << endl;
	}
	cout << team2.get_nation() << endl;
	for(auto ele : t2){
		ele.show();
		cout << endl;
	}
	cout << "Playing..." << endl;
	double z = (double)abs(team1.get_WR() - team2.get_WR()) / (team1.get_WR() + team2.get_WR());
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(4.0,0.8);
	int sum = (int)distribution(generator);
	int score1 = (team1.get_WR() * sum) / (team1.get_WR() + team2.get_WR());
	int score2 = sum - score1;
	int s1 = score1;
	int s2 = score2;
	while(score1 > 0||score2 > 0){
		if(score1 == 0){
			cout << team2.get_nation() << " did a goal, and it was ";
			get_a_goal(t2).show();
			cout << " did the goal." << endl;
			score2--;
			cout << "Now it is " << s1 - score1 << " : " << s2 - score2 << endl;
		}
		else if(score2 == 0){
			cout << team1.get_nation() << " did a goal, and it was ";
			get_a_goal(t1).show();
			cout << "did the goal." << endl;
			score1--;
			cout << "Now it is " << s1 - score1 << " : " << s2 - score2 << endl;
		}
		else{
			int rad = rand() % 2;
			if(rad){
				cout << team2.get_nation() << " did a goal, and it was ";
				get_a_goal(t2).show();
				cout << "did the goal." << endl;
				score2--;
				cout << "Now it is " << s1 - score1 << " : " << s2 - score2 << endl;
			}
			else{
				cout << team1.get_nation() << " did a goal, and it was ";
				get_a_goal(t1).show();
				cout << "did the goal." << endl;
				score1--;
				cout << "Now it is " << s1 - score1 << " : " << s2 - score2 << endl;
			}
		}
	}
	temp1 = team1.get_members();
	for(auto ele : temp1){
		if(!find_name(t1,ele.name)){
			t1.push_back(ele);
		}
	}
	team1.set_members(t1);
	temp2 = team2.get_members();
	for(auto ele : temp2){
		if(!find_name(t2,ele.name)){
			t2.push_back(ele);
		}
	}
	team2.set_members(t2);
	if(s1 > s2){
		cout << team1.get_nation() << " win the game with " << s1 << " : " << s2 << endl;
		Pts temp = team1.get_pts();
		temp.W++;
		temp.GF += s1;
		temp.GA += s2;
		temp.GD = temp.GF - temp.GA;
		team1.set_pts(temp);
		temp = team2.get_pts();
		temp.L++;
		temp.GF += s2;
		temp.GA += s1;
		temp.GD = temp.GF - temp.GA;
		team2.set_pts(temp);
	}
	else if(s1 < s2){
		cout << team2.get_nation() << " win the game with " << s1 << " : " << s2 << endl;
		Pts temp = team2.get_pts();
		temp.W++;
		temp.GF += s1;
		temp.GA += s2;
		temp.GD = temp.GF - temp.GA;
		team2.set_pts(temp);
		temp = team1.get_pts();
		temp.L++;
		temp.GF += s2;
		temp.GA += s1;
		temp.GD = temp.GF - temp.GA;
		team1.set_pts(temp);
	}
	else{
		cout << "It is a draw with " << s1 << " : " << s2 << endl;
		Pts temp = team1.get_pts();
		temp.D++;
		temp.GF += s1;
		temp.GA += s2;
		temp.GD = temp.GF - temp.GA;
		team1.set_pts(temp);
		temp = team2.get_pts();
		temp.D++;
		temp.GF += s2;
		temp.GA += s1;
		temp.GD = temp.GF - temp.GA;
		team2.set_pts(temp);
	}
}

Member choose(vector<Member> &m,int ans){
	auto it = m.begin();
	srand(time(0));
	if(ans == 0){
		int rad = rand() % 3 + 1;
		int cnt = 0;
		while(cnt < rad){
			it++;
			if(it == m.end()){
				it = m.begin();
			}
			if((*it).role == "GK"){
				cnt++;
			}
		}
		return *it;
	}
	else if(ans == 1){
		int rad = rand() % 4 + 1;
		int cnt = 0;
		while(cnt < rad){
			it++;
			if(it == m.end()){
				it = m.begin();
			}
			if((*it).role == "DF"){
				cnt++;
			}
		}
		return *it;
	}
	else if(ans == 2){
		int rad = rand() % 4 + 1;
		int cnt = 0;
		while(cnt < rad){
			it++;
			if(it == m.end()){
				it = m.begin();
			}
			if((*it).role == "MF"){
				cnt++;
			}
		}
		return *it;
	}
	else if(ans == 3){
		int rad = rand() % 5 + 1;
		int cnt = 0;
		while(cnt < rad){
			it++;
			if(it == m.end()){
				it = m.begin();
			}
			if((*it).role == "FW"){
				cnt++;
			}
		}
		return *it;
	}
}


Member get_a_goal(vector<Member> &m){
	srand(time(0));
	int rad = rand() % 20 + 1;
	auto it = m.begin();
	int cnt = 0;
	while(cnt < rad){
		it++;
		if(it == m.end()){
			it = m.begin();
		}
		if((*it).role == "DF"){
			cnt++;
		}
		else if((*it).role != "GK"){
			cnt += 2;
		}
	}
	(*it).goal++;
	return *it;
}


bool find_name(vector<Member> &m,string name){
	for(auto ele : m){
		if(ele.name == name) return true;
	}
	return false;
}