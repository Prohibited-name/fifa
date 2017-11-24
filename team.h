#include<string> 
#include<iostream>
#include<vector>
using namespace std;

 struct Pts{
	int W,D,L,GF,GA,GD;
	show(){
		cout << W << "  " << D << "  " << L << "  " << GF << "  " << GA << "  " << GD << endl;
	}
};

struct Member
{
	string name;
	string role;
	int number;
	int ifcaptain;
	int goal;
	void show(){
		cout << "#" << number << ", " << name << ", " << role;
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
	//
};
