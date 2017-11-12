#include<string> 
using std::string;

struct Pts{
	int W,D,L,GF,GA,GD;
};

struct Member
{
	string name;
	string role;
	int number;
	int ifcaptain;
	//int goal;
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
	Team();
	string & get_nation()const;
	stirng & get_area()const;
	string get_group();
	int get_WR();
	Pts & get_pts()const;
	vector<Member> & get_members()const;
	void set_nation(string nation_);
	void set_area(string area_);
	void set_group(string group_);
	void set_WR(int WR_);
	void set_pts(const Pts & pts_);
	void set_members(const vector<Member> members_);
	//
};
