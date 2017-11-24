#include "fifa.h"
#include<fstream>
using namespace std;
bool cmp_group(const game &g1,const game &g2){
	return (g1.team1 -> get_group())[0] < (g2.team1 -> get_group())[0] || ((g1.team1 -> get_group())[0] == (g2.team1 -> get_group())[0] && g1.time < g2.time);
}

bool cmp_date(const game &g1,const game &g2){
	return g1.time < g2.time || (g1.time == g2.time && g1.team1 -> get_group() < g2.team1 -> get_group());
}

bool cmp_team(Team &t1,Team &t2){
	return ((t1.get_group())[0] < t2.get_group()[0])||((t1.get_group())[0] == t2.get_group()[0] && (t1.get_pts().W * 3 + t1.get_pts().D) < (t2.get_pts().W * 3 + t2.get_pts().D));
}

fifa::fifa(vector<Team> teams){
	team32 = teams;
}

void fifa::run_sim(){
	ifstream schedule_in("schedule.txt");
	//stage 1
	vector<game> game32;
	for(int i = 0;i < 48;i++){
		string a,b,time;
		game temp;
		schedule_in >> temp.num >> temp.month >> temp.day >> time >> a >> b >> temp.place;
		for(auto it = team32.begin();it != team32.end();it++){
			if(it -> get_group() == a){
				temp.team1 = it;
			}
		}
		for(auto it = team32.begin();it != team32.end();it++){
			if(it -> get_group() == b){
				temp.team2 = it;
			}
		}
		temp.time = temp.month * 31 + temp.day;
		game32.push_back(temp);
	}
	sort(game32.begin(),game32.end(),cmp_group);
	auto it = game32.begin();
	int cnt = 0;
	cout << "Matches by squads" << endl;
	while(it != game32.end()){
		cout << "Group " << (*it).team1 -> get_group()[0] << endl;
		for(int i = 0;i < 6;i++){
			cout << (*it).team1 -> get_nation() << " vs " << (*it).team2 -> get_nation() << ", ";
			cout << (*it).place << ", " << (*it).month << "," << (*it).day << endl;
			it++;
		}
	}
	cout << endl;
	cout << "Matches by date" << endl;
	sort(game32.begin(),game32.end(),cmp_date);
	it = game32.begin();
	int pre_date = (*it).time;
	cout << (*it).month << "," << (*it).day << endl;
	while(it != game32.end()){
		if((*it).time == pre_date){
			cout << (*it).team1 -> get_nation() << " vs " << (*it).team2 -> get_nation() << ", ";
			cout << (*it).place << endl;
			it++;
		}
		else{
			pre_date = (*it).time;
		}
	}
	//game start!!!
	for(auto game : game32){
		game_sim(*(game.team1),*(game.team2));
	}
	sort(team32.begin(),team32.end(),cmp_team);
	vector<Team> team16;
	for(int i = 0;i < 8;i++){
		string temp;
		temp.push_back(i + 'A');
		temp += "1";
		team16.push_back(team32[4 * i]);
		team16[2 * i].set_group(temp);
		temp = "";
		temp.push_back(i + 'A');
		temp += "2";
		team16.push_back(team32[4 * i + 1]);
		team16[2 * i + 1].set_group(temp);
	}
	save_result(team16,"team16");
	show_info("Result16");
	//16
	vector<game> game16;
	cout << "Qualified for round of 16: " << endl;
	for(auto team : team16){
		cout << team.get_nation() << endl;
	}
	cout << "Schedule for round of 16: " << endl;
	for(int i = 0;i < 8;i++){
		game temp;
		string time,a,b;
		schedule_in >> temp.num >> temp.month >> temp.day >> time >> a >> b >> temp.place;
		for(auto it = team16.begin();it != team16.end();it++){
			if(it -> get_group() == a){
				temp.team1 = it;
			}
		}
		for(auto it = team16.begin();it != team16.end();it++){
			if(it -> get_group() == b){
				temp.team2 = it;
			}
		}
		temp.time = temp.month * 31 + temp.day;
		game16.push_back(temp);
	}
	it = game16.begin();
	pre_date = (*it).time;
	cout << (*it).month << "," << (*it).day << endl;
	while(it != game16.end()){
		if((*it).time == pre_date){
			cout << (*it).team1 -> get_nation() << " vs " << (*it).team2 -> get_nation() << ", ";
			cout << (*it).place << endl;
			it++;
		}
		else{
			pre_date = (*it).time;
		}
	}
	vector<Team> team8;
	for(auto game : game16){
		Team temp;
		game_sim_2(*(game.team1),*(game.team2),temp);
		temp.set_group(game.num);
		team8.push_back(temp);
	}
	update_info(team16);
	save_result(team8,"team8");
	show_info("Result8");
	//8
	vector<game> game8;
	cout << "Qualified for round of 8: " << endl;
	for(auto team : team8){
		cout << team.get_nation() << endl;
	}
	cout << "Schedule for round of 8: " << endl;
	for(int i = 0;i < 4;i++){
		string time,a,b;
		game temp;
		schedule_in >> temp.num >> temp.month >> temp.day >> time >> a >> b >> temp.place;
		for(auto it = team8.begin();it != team8.end();it++){
			if(it -> get_group() == a){
				temp.team1 = it;
			}
		}
		for(auto it = team8.begin();it != team8.end();it++){
			if(it -> get_group() == b){
				temp.team2 = it;
			}
		}
		temp.time = temp.month * 31 + temp.day;
		game8.push_back(temp);
	}
	it = game8.begin();
	pre_date = (*it).time;
	cout << (*it).month << "," << (*it).day << endl;
	while(it != game8.end()){
		if((*it).time == pre_date){
			cout << (*it).team1 -> get_nation() << " vs " << (*it).team2 -> get_nation() << ", ";
			cout << (*it).place << endl;
			it++;
		}
		else{
			pre_date = (*it).time;
		}
	}
	vector<Team> team4;
	for(auto game : game8){
		Team temp;
		game_sim_2(*(game.team1),*(game.team2),temp);
		temp.set_group(game.num);
		team4.push_back(temp);
	}
	update_info(team8);
	save_result(team4,"team4");
	show_info("Result4");
	//4
	vector<game> game4;
	cout << "Qualified for round of 4: " << endl;
	for(auto team : team4){
		cout << team.get_nation() << endl;
	}
	cout << "Schedule for round of 4: " << endl;
	for(int i = 0;i < 2;i++){
		game temp;
		string time,a,b;
		schedule_in >> temp.num >> temp.month >> temp.day >> time >> a >> b >> temp.place;
		for(auto it = team4.begin();it != team4.end();it++){
			if(it -> get_group() == a){
				temp.team1 = it;
			}
		}
		for(auto it = team4.begin();it != team4.end();it++){
			if(it -> get_group() == b){
				temp.team2 = it;
			}
		}
		temp.time = temp.month * 31 + temp.day;
		game4.push_back(temp);
	}
	it = game4.begin();
	pre_date = (*it).time;
	cout << (*it).month << "," << (*it).day << endl;
	while(it != game4.end()){
		if((*it).time == pre_date){
			cout << (*it).team1 -> get_nation() << " vs " << (*it).team2 -> get_nation() << ", ";
			cout << (*it).place << endl;
			it++;
		}
		else{
			pre_date = (*it).time;
		}
	}
	vector<Team> team2_1,team2_2;
	for(auto game : game4){
		Team temp;
		game_sim_2(*(game.team1),*(game.team2),temp);
		team2_1.push_back(temp);
	}
	for(auto team : team4){
		if(team.get_nation() != team2_1[0].get_nation() && team.get_nation() != team2_1[1].get_nation()){
			team2_2.push_back(team);
		}
	}
	update_info(team4);
	save_result(team2_1,"team2");
	show_info("Result2");
	//3-4
	game game2_1;
	cout << "Qualified for round of 3-4: " << endl;
	for(auto team : team2_2){
		cout << team.get_nation() << endl;
	}
	cout << "Schedule for round of 3-4: " << endl;
	string time,a,b;
	schedule_in >> game2_1.num >> game2_1.month >> game2_1.day >> time >> a >> b >> game2_1.place;
	auto it_1 = team2_2.begin();
	game2_1.team1 = it_1++;
	game2_1.team2 = it_1;
	game2_1.time = game2_1.month * 31 + game2_1.day;
	cout << game2_1.month << "," << game2_1.day << endl;
	{
		Team temp;
		game_sim_2(*(game2_1.team1),*(game2_1.team2),temp);
		team2_1.push_back(temp);
	}
	update_info(team2_2);
	//final
	game game2_2;
	cout << "Qualified for round of final: " << endl;
	for(auto team : team2_1){
		cout << team.get_nation() << endl;
	}
	cout << "Schedule for round of final: " << endl;
	schedule_in >> game2_2.num >> game2_2.month >> game2_2.day >> time >> a >> b >> game2_2.place;
	auto it_2 = team2_1.begin();
	game2_2.team1 = it_2++;
	game2_2.team2 = it_2;
	game2_2.time = game2_2.month * 31 + game2_2.day;
	cout << game2_2.month << "," << game2_2.day << endl;
	vector<Team> winner;
	{
		Team temp;
		game_sim_2(*(game2_2.team1),*(game2_2.team2),temp);
		winner.push_back(temp);
	}
	update_info(team2_1);
	save_result(winner,"team1");
	show_info("Result1");
	//end
	schedule_in.close();
	show_final();
}

void fifa::update_info(vector<Team> teams){
	for(auto team : teams){
		for(auto update_team : team32){
			if(team.get_nation() == update_team.get_nation()){
				update_team.set_WR(team.get_WR());
				update_team.set_pts(team.get_pts());
				update_team.set_members(team.get_members());
			}
		}
	}
}

void fifa::show_info(string s){
	ofstream out(s+".txt");
	for(int i = 0;i < 8;i++){
		out << "Final result for group " << (char)(i + 'A') << endl;
		out << "Team     W  D  L  GF  GA  GD   Pts" << endl;
		out << team32[8 * i].get_nation() << "  ";
		out << team32[4 * i].show() << endl;
		out << team32[8 * i + 1].get_nation() << "  ";
		out << team32[4 * i + 1].show() << endl;
		out << team32[8 * i + 2].get_nation() << "  ";
		out << team32[4 * i + 2].show() << endl;
		out << team32[8 * i + 2].get_nation() << "  ";
		out << team32[4 * i + 3].show() << endl;
	}
	out.close();
}

void fifa::save_result(vector<Team> teams,string s){
	ofstream out(s + ".txt");
	out << "Qualified for round of " << teams.size();
	for(auto team : teams){
		out << team.get_nation() << endl;
	}
	out.close();
}


void fifa::show_final(){}
