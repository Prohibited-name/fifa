#include "team.h"
#include "game_sim.h"
struct game
{
	vector<team>::iterator team1,team2;
	int month,day;
	int time;
	string time;
	string place;	
};

class fifa{
	private:
		vector<team> team32;
	public:
		fifa(vector<team> teams);
		void run_sim();
}