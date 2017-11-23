#include "game_sim.h"
int seed = time(0);
int Rank(Member &m){
	if(m.role == "GK"){
		return 0;
	}
	else if(m.role == "DF"){
		return 1;
	}
	else if(m.role == "MF"){
		return 2;
	}
	else{
		return 3;
	}
}
bool cmp(Member &a,Member &b){
	if(Rank(a) == Rank(b)){
		return a.number < b.number;
	}
	return Rank(a) < Rank(b);
}
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
	sort(t1.begin(),t1.end(),cmp);
	sort(t2.begin(),t2.end(),cmp);
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
	//double z = (double)abs(team1.get_WR() - team2.get_WR()) / (team1.get_WR() + team2.get_WR());
	//std::default_random_engine generator;
	//std::normal_distribution<double> distribution(4.0,0.8);
	srand(seed++);
	int sum = rand() % 7;
	int score1 = (team2.get_WR() * sum) / (team1.get_WR() + team2.get_WR());
	int rads = rand() % (team1.get_WR() + team2.get_WR());
	if(rads < team1.get_WR() && rads < team2.get_WR()){
		if(score1 > sum - score1&&score1 > 0){
			score1--;
		}
		else if(sum - score1 > 0){
			score1++;
		}
	}
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
			srand(seed++);
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

int main(){
	Team team1,team2;
	vector<Member> members;
	Member member;
	for(int i = 1;i <= 23;i++){
		member.name = ""; 
		member.name.push_back('a' + i - 1);
		if(i == 1){
			member.ifcaptain = 1;
			member.role = "GK";
		}
		else if(i > 1 && i < 9){
			member.ifcaptain = 0;
			member.role = "DF";
		}
		else if(i > 8 && i < 15){
			member.ifcaptain = 0;
			member.role = "MF";
		}
		else{
			member.ifcaptain = 0;
			member.role = "FW";
		}
		member.number = i;
		members.push_back(member);
	}
	team1.set_members(members);
	team1.set_nation("China");
	team1.set_WR(2);
	for(int i = 1;i <= 23;i++){
		member.name = "";
		member.name.push_back('A' + i - 1);
		if(i == 1){
			member.ifcaptain = 1;
			member.role = "GK";
		}
		else if(i > 1 && i < 9){
			member.ifcaptain = 0;
			member.role = "DF";
		}
		else if(i > 8 && i < 15){
			member.ifcaptain = 0;
			member.role = "MF";
		}
		else{
			member.ifcaptain = 0;
			member.role = "FW";
		}
		member.number = i;
		members.push_back(member);
	}
	team2.set_members(members);
	team2.set_nation("JP");
	team2.set_WR(112);
	for(int i = 0;i < 1000;i++)
		game_sim(team1,team2);
	team1.get_pts().show();
	team2.get_pts().show();
}

Member choose(vector<Member> &m,int ans){
	auto it = m.begin();
	seed++;
	srand(seed);
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
		Member temp = *it;
		m.erase(it);
		return temp;
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
		Member temp = *it;
		m.erase(it);
		return temp;
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
		Member temp = *it;
		m.erase(it);
		return temp;
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
		Member temp = *it;
		m.erase(it);
		return temp;
	}
}


Member get_a_goal(vector<Member> &m){
	seed++;
	srand(seed);
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
