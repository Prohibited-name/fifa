#include "game_sim.h"
struct game
{
	string num;
	vector<Team>::iterator team1,team2;
	int month,day;
	int time;
	string place;	
};

class fifa{
	private:
		vector<Team> team32;
		void show_info(string s);
		void update_info(vector<Team> teams);
		void save_result(vector<Team> teams,string s);
		void show_final();
	public:
		fifa(vector<Team> teams);
		void run_sim();
};
