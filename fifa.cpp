#include "fifa.h"

bool cmp_group(const game &g1,const game &g2){
	return (g1.team1 -> get_group())[0] < (g2.team1 -> get_group())[0] || ((g1.team1 -> get_group())[0] == (g2.team1 -> get_group())[0] && g1.time < g2.time);
}

bool cmp_date(const game &g1,const game &g2){
	return g1.time < g2.time || (g1.time == g2.time && g1.team1 -> get_group() < g2.team1 -> get_group());
}

bool cmp_team(const team &t1,const team &t2){
	return (t1.get_group())[0] < t2.get_group()[0]||((t1.get_group())[0] == t2.get_group()[0] && (t1.get_pts().W * 3 + t1.get_pts().D) < (t2.get_pts().W * 3 + t2.get_pts().D));
}

fifa::fifa(vector<team> teams){
	team32 = teams;
}

void fifa::run_sim(){
	ifstream schedule_in("schedule.txt");
	//stage 1
	vector<game> game32;
	for(int i = 0;i < 48;i++){
		int num;
		game temp;
		schedule_in >> num >> temp.month >> temp.day >> time >> a >> b >> temp.place;
		for(auto it = team32.begin();it != team32.end();it++){
			if(it -> group == a){
				temp.team1 = it;
			}
		}
		for(auto it = team32.begin();it != team32.end();it++){
			if(it -> group == b){
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
		cout << "Group " << (*it).team1.group[0] << endl;
		for(int i = 0;i < 6;i++){
			cout << (*it).team1.get_nation() << " vs " << (*it).team2.get_nation() << ", ";
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
			cout << (*it).team1.nation << " vs " << (*it).team2.nation << ", ";
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
	for(int i = 0;i < 8;i++){
		cout << "Final result for group " << (char)(i + 'A') << endl;
		cout << "Team     W  D  L  GF  GA  GD   Pts" << endl;
		cout << team32[8 * i].get_nation() << "  ";
		team32[8 * i].show();cout << endl;
		cout << team32[8 * i + 1].get_nation() << "  ";
		team32[8 * i + 1].show();cout << endl;
		cout << team32[8 * i + 2].get_nation() << "  ";
		team32[8 * i + 2].show();cout << endl;
		cout << team32[8 * i + 2].get_nation() << "  ";
		team32[8 * i + 2].show();cout << endl;
		team32[8 * i].set_group("")
	}
}