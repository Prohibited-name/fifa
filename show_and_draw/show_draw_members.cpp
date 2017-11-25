#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<vector>
#include<cstdlib>
#include<map>
using namespace std;
 
 struct Pts{
	int W,D,L,GF,GA,GD;
};

struct Member
{
	string name;
	string role;
	int number;
	int ifcaptain;
	int goal;
	void show(){
		cout << "#" << number << ", "<< name << ", " << role << endl;
	}
};

class Team{
private:
	string nation;
	string area;
	string group;
	int WR;
	Pts pts;
	vector<Member> members;
public:
	Team(){
		WR=0;
		pts.W = pts.L = pts.D = pts.GA = pts.GD = pts.GF = 0; 
	}
	string & get_nation(){
		return nation;
	}
	string & get_area(){
		return area;
	}
	string & get_group(){
		return group;
	}
	int & get_WR(){
		return WR;
	}
	Pts & get_pts(){
		return pts;
	}
	vector<Member> & get_members(){
		return members;
	}
	void set_nation(string nation_){
		nation = nation_;
	}
	void set_area(string area_){
		area = area_;
	}
	void set_group(string group_){
		group = group_;
	}
	void set_WR(int WR_){
		WR = WR_;
	}
	void set_pts(const Pts & pts_){
		pts = pts_;
	}
	void set_members(const vector<Member> & members_){
		members = members_;
	}
};
 
 
 
 
 
//part 1:show teams
void show_teams(){
	ifstream fin("team32.txt");
	if(!fin.is_open()){
		cout << "Fail to open the file." << endl;
	}
	else{
		for(int i=0; i<5; i++){
			string area;
			getline(fin, area);
			cout << area << endl;
			string temp = area.substr(area.find("(")+1);
			int n = atoi(temp.c_str());
			area.erase(area.find("("));
			//push team into teams;
			for(int j=0; j<n; j++){
				string nation;
				getline(fin,nation);
				cout << nation << endl;
				temp = nation.substr(nation.find("(")+1);
				int rank = atoi(temp.c_str());
				nation.erase(0,2);
				nation.erase(nation.find(" ("));
				Team team;
				team.set_area(area);
				team.set_nation(nation);
				team.set_WR(rank);
				teams.push_back(team);
			}	
		} 
		fin.close();
	}
}





//part 2:draw and divide into 8 groups
struct Group{
	map<string, int> area_num;
	Team gteams[4];
	char gname;
	int count;
};



void draw(){
	cout << "All teams are allocated according to the procedures for the Final Draw" << endl
	     << "that the committee approved on 14 September 2017, as follow: " << endl
	     << "1. All teams will be allocated to pots 1 to 4 based on sporting principles" << endl
		 << "with each pot containing eight teams." << endl
		 << "2. This means that the October 2017 edition of the FIFA World Ranking will be used to allocate" << endl 
		 << "all qualified teams to the four pots according to their ranking in descending order, with the" << endl
		 << "best seven teams along with hosts Russia in pot 1." << endl;
	vector<Team> pot[4];
	Group groups[8];
	for(int i=0; i<8; i++){
		groups[i].area_num.insert(make_pair("AFC",0));
		groups[i].area_num.insert(make_pair("CAF",0));
		groups[i].area_num.insert(make_pair("UEFA",0));
		groups[i].area_num.insert(make_pair("CONCACAF",0));
		groups[i].area_num.insert(make_pair("CONMEBOL",0));
		groups[i].gname=i+65;
		groups[i].count = 0;
	}
	//allocate into 4 pots, pot[0][0] 不一定是 Russia 
	for(int i=0; i<32; i++){
		if(teams[i].get_WR()==65){
			pot[0].push_back(teams[i]);
		}
		else{
			if(teams[i].get_WR()>=1&&teams[i].get_WR()<=7){
				pot[0].push_back(teams[i]);
			}
			else if(teams[i].get_WR()>=8&&teams[i].get_WR()<=18){
				pot[1].push_back(teams[i]);
			}
			else if(teams[i].get_WR()>=19&&teams[i].get_WR()<=34){
				pot[2].push_back(teams[i]);
			}
			else{
				pot[3].push_back(teams[i]);
			}
		}
	}
	ofstream fout("finalDraw.txt");
	if(!fout.is_open()){
		cout << "Fail to open the file." << endl;
	}
	cout << "First stage" << endl;
	fout << "First stage" << endl;
	for(int i=0; i<4; i++){
		cout << "pot" << (i+1) << endl;
		fout << "pot" << (i+1) << endl;
		for(int j=0 ;j<8; j++){
			if(i==0&&j==0){
				cout << " " << pot[i][j].get_nation() << "(hosts)" << endl;
				fout << " " << pot[i][j].get_nation() << "(hosts)" << endl;
			}
			else{
				cout << " " << pot[i][j].get_nation() << endl;
				fout << " " << pot[i][j].get_nation() << endl;
			}
		}
	}
	cout << "Next, eight groups of four teams will be labelled A to H: the four pots will be emptied" << endl
		 << "by allocating one of their eight teams to each of the eight groups." << endl
		 << "The principle of drawing the teams into the groups will remain unchanged. Hence, no teams" << endl
		 << "from the same confederation, with the exception of UEFA, which could have up to two teams" << endl
		 << "in the same group, will be drawn into the same group." << endl;
	//draw in every pot
	//pot 1
    for(int j=0; j<8; j++){
	    int n = pot[0].size();
		int r = rand()%n;
		//set group
		if(j==0){
			r = 0;
		}
	    groups[j].gteams[0] = pot[0][r];
		string str = pot[0][r].get_area();
		groups[j].area_num[str]++;
		groups[j].count++;
		//set team's group
		for(int p=0; p<32; p++){
			if(teams[p].get_nation()==pot[0][r].get_nation()){
				string str;
				str.push_back(groups[j].gname);
				str.push_back(49);
				teams[p].set_group(str);
			}
		}
		pot[0].erase(pot[0].begin()+r);
	}

	//pot 2 avoid CONMEBOL first

	for(auto it=pot[1].begin(); it!=pot[1].end();){
		if(it->get_area()=="CONMEBOL"){
			for(int j=0; j<8; j++){
				if(groups[j].area_num["CONMEBOL"]==0){
					groups[j].gteams[1]=*(it);
					groups[j].area_num["CONMEBOL"]++;
					groups[j].count++;
			        for(int p=0; p<32; p++){
						if(teams[p].get_nation()==it->get_nation()){
							string str;
				            str.push_back(groups[j].gname);
				            str.push_back(50);
			            	teams[p].set_group(str);
						}
					}
					break;
				}
			}
			it = pot[1].erase(it);
		}else{
			it++;
		}
	}
	for(int j=0; j<8; j++){
		if(groups[j].count==1){
			int n = pot[1].size();
		    int r = rand()%n;
		    groups[j].gteams[1] = pot[1][r];
		    string str = pot[1][r].get_area();
			groups[j].area_num[str]++;
			groups[j].count++;
			//set team's group
			for(int p=0; p<32; p++){
				if(teams[p].get_nation()==pot[1][r].get_nation()){
					string str;
				    str.push_back(groups[j].gname);
				    str.push_back(50);
				    teams[p].set_group(str);
				}
			}
			pot[1].erase(pot[1].begin()+r);
		}
	}

	//pot 3 avoid UEFA and  CONCACAF
	for(auto it=pot[2].begin(); it!=pot[2].end();){
		if(it->get_area()=="UEFA"){
			for(int j=0; j<8; j++){
				if(groups[j].area_num["UEFA"]<=1){
					groups[j].gteams[2]=*(it);
					groups[j].area_num["UEFA"]++;
					groups[j].count++;
					for(int p=0; p<32; p++){
						if(teams[p].get_nation()==it->get_nation()){
							string str;
				            str.push_back(groups[j].gname);
				            str.push_back(51);
				            teams[p].set_group(str);
						}
					}
			        break;
				}
			}
			it = pot[2].erase(it);
		}
		else{
			it++;
		}
	}

	int quit = 0;
	for(auto it=pot[2].begin(); it!=pot[2].end();){
		if(it->get_area()=="CONCACAF"){
			for(int j=0; j<8; j++){
				if(groups[j].count==2){
					if(groups[j].area_num["CONCACAF"]==0){
						groups[j].gteams[2]=*(it);
						groups[j].area_num["CONCACAF"]++;
						groups[j].count++;
						for(int p=0; p<32; p++){
							if(teams[p].get_nation()==it->get_nation()){
								string str;
					            str.push_back(groups[j].gname);
					            str.push_back(51);
					            teams[p].set_group(str);
							}
						}
			            pot[2].erase(it);
			            quit = 1;
			            break;
					}
				}
			}
			if(quit){
				break;
			}
		}
		else{
			it++;
		}
	}
	for(int j=0; j<8; j++){
		if(groups[j].count==2){
			int n = pot[2].size();
			int r = rand()%n;
			groups[j].gteams[2] = pot[2][r];
			string str = pot[2][r].get_area();
			groups[j].area_num[str]++;
			groups[j].count++;
			//set team's group
			for(int p=0; p<32; p++){
				if(teams[p].get_nation()==pot[2][r].get_nation()){
					string str;
				    str.push_back(groups[j].gname);
				    str.push_back(51);
				    teams[p].set_group(str);
				}
			}
			pot[2].erase(pot[2].begin()+r);
		}
	}

	//pot 4 avoid UEFA-> CONCACAF -> AFC -> CAF
    quit = 0;
	for(auto it=pot[3].begin(); it!=pot[3].end();){
		if(it->get_area()=="UEFA"){
			for(int j=0; j<8; j++){
				if(groups[j].area_num["UEFA"]<=1){
					groups[j].gteams[3]=*(it);
					groups[j].area_num["UEFA"]++;
					groups[j].count++;
				    for(int p=0; p<32; p++){
						if(teams[p].get_nation()==it->get_nation()){
							string str;
				            str.push_back(groups[j].gname);
				            str.push_back(52);
				            teams[p].set_group(str);
						}
					}
			        pot[3].erase(it);
			        quit = 1;
			        break;
				}
			}
			if(quit){
				break;
			}
		}
		else{
			it++;
		}
	}
	quit = 0;
	for(auto it=pot[3].begin(); it!=pot[3].end();){
		if(it->get_area()=="CONCACAF"){
			for(int j=0; j<8; j++){
				if(groups[j].count==3){
					if(groups[j].area_num["CONCACAF"]==0){
						groups[j].gteams[3]=*(it);
						groups[j].area_num["CONCACAF"]++;
						groups[j].count++;
					    for(int p=0; p<32; p++){
							if(teams[p].get_nation()==it->get_nation()){
								string str;
				                str.push_back(groups[j].gname);
				                str.push_back(52);
				                teams[p].set_group(str);
							}
						}
				        pot[3].erase(it);
				        quit = 1;
				        break;
					}
				}
			}
			if(quit){
				break;
			}
		}
		else{
			it++;
		}
	}
	for(int j=0; j<8; j++){
		if(groups[j].count==3){
			if(groups[j].area_num["CAF"]==1){
				for(auto it=pot[3].begin(); it!=pot[3].end();){
					if(it->get_area()=="AFC"){
						groups[j].gteams[3]=*(it);
						groups[j].area_num["AFC"]++;
						groups[j].count++;
					    for(int p=0; p<32; p++){
							if(teams[p].get_nation()==it->get_nation()){
								string str;
				                str.push_back(groups[j].gname);
				                str.push_back(52);
				                teams[p].set_group(str);
							}
						}
						pot[3].erase(it);
						break;
					}
					else{
						it++;
					}
				}
			}
		}
	}
	quit = 0;
	for(auto it=pot[3].begin(); it!=pot[3].end();){
		if(it->get_area()=="AFC"){
			for(int j=0; j<8; j++){
				if(groups[j].count==3){
					if(groups[j].area_num["AFC"]==0){
						groups[j].gteams[3]=*(it);
						groups[j].area_num["AFC"]++;
						groups[j].count++;
					    for(int p=0; p<32; p++){
							if(teams[p].get_nation()==it->get_nation()){
								string str;
				                str.push_back(groups[j].gname);
				                str.push_back(52);
				                teams[p].set_group(str);
							}
						}
				        pot[3].erase(it);
				        quit = 1;
				        break;
					}
				}
			}
			if(quit){
				break;
			}
		}
		else{
			it++;
		}
	}
	for(auto it=pot[3].begin(); it!=pot[3].end();){
		for(int j=0; j<8; j++){
			if(groups[j].count==3){
				string str = it->get_area();
				if(groups[j].area_num[str]==0){
					groups[j].gteams[3]=*(it);
					groups[j].area_num[str]++;
					groups[j].count++;
					for(int p=0; p<32; p++){
						if(teams[p].get_nation()==it->get_nation()){
							string str;
				            str.push_back(groups[j].gname);
				            str.push_back(52);
				            teams[p].set_group(str);
						}
					}
				    it = pot[3].erase(it);
				    break;
			    }
		    }
    	}
	}
	cout << "The Final Draw" << endl;
	fout << endl;
	fout << "The Final Draw" << endl;
	for(int i=0; i<8; i++){
		cout << "group " << groups[i].gname << endl;
		fout << "group " << groups[i].gname << endl;
		for(int j=0; j<4; j++){
			if(i==0&&j==0){
				cout << " " << groups[0].gteams[0].get_nation() << " (hosts)" << endl;
				fout << " " << groups[0].gteams[0].get_nation() << " (hosts)" << endl;
				
			}
			else{
				cout << " " << groups[i].gteams[j].get_nation() << endl;
				fout << " " << groups[i].gteams[j].get_nation() << endl;
			}
		}
	}
	fout.close();
}












//part 3: initialize every group's members
/*struct Member
{
	string name;
	string role;
	int number;
	int ifcaptain;
	int goal;
	void show(){
		cout << "#" << number << ", " << name << ", " << role << endl;
	}
};*/
void initialize_members(){
	ifstream fin("members.txt");
	if(!fin.is_open()){
		cout << "Fail to open the file." << endl;
	}
	else{
		for(int p=0; p<32; p++){
			string tname,nstr;
			Member temp;
			vector<Member> tmembers;
			getline(fin,tname);
			for(int j=0; j<23; j++){
				fin >> temp.number >> temp.ifcaptain;
				fin.get();
				getline(fin,temp.name);
				getline(fin,temp.role);
				temp.goal=0;
				tmembers.push_back(temp); 
			}
			for(int i=0; i<32; i++){
				if(teams[i].get_nation()==tname){
					teams[i].set_members(tmembers);
					break;
				}
			}
			getline(fin,nstr);
		}
		fin.close();
	}

}


