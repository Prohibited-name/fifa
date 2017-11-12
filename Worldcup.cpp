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
};

class Team{
private:
	string nation;
	string area;
	Pts pts;
	vector<Member> member;
	char group;
public:
	string & get_nation()const;
	stirng & get_area()const;
	Pts & get_pts()const;
	vector<Member> & get_member()const;
	char get_group();
};


