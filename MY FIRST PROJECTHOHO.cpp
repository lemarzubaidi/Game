#include <iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
void restscreen() {
	system("cls");
	system("color 0F");
}
enum enplayer{player=1,com=2,draw=3};
enum enchoice{rock=1,paper=2,scissors=3};
struct stGameResult {
	short GameRound=0;
	short Player1wintimes=0;
	short Comwintimes=0;
	short Drawwintims=0;
	enplayer GameWinner;
	string Winnername="";


};
struct stRoundInfo {
	short RoundNumber = 0;
	enchoice Player1Choice;
	enchoice Comchoice;
	enplayer Winner;
	string WinnerName;
};
int random(int from,int to) {
	return rand() % (to - from + 1) + from;
	
}
enchoice ReadPlayerChoice() {
	short numberc;
	do {
		cout << "\nyour choice: [1]: rock, [2]: paper, [3]: scssior ?\n";
		cin >> numberc;
	} while (numberc < 1 || numberc>3);
	return (enchoice)numberc;
}
enchoice GetComChoice(){
	return (enchoice)random(1,3);
}
short howtime() {
	short number=1;
	do {
		cout << "How Many Rounds 1 to 10 ?\n";
		cin >> number;

	} while (number < 1 || number > 10);
	return number;
}
enplayer whowintheround(stRoundInfo roundinfo) {
	if (roundinfo.Player1Choice==roundinfo.Comchoice) {
		return enplayer::draw;
	}
	switch (roundinfo.Player1Choice) {
	case enchoice::paper:
		return (roundinfo.Comchoice == enchoice::scissors) ? enplayer::com : enplayer::player;
	case enchoice::rock:
		return (roundinfo.Comchoice == enchoice::paper) ? enplayer::com : enplayer::player;
	case enchoice::scissors:
		return (roundinfo.Comchoice == enchoice::rock) ? enplayer::com : enplayer::player;

	}

}
string winnername(enplayer winner) {
	string arrwinner[3] = { "player","com","Nowinner" };//لازم نفس ترتيب الاينم
	return arrwinner[winner - 1];
}
string choices(enchoice player) {
	string choice[3] = { "rock","paper","scssiors" };
	return choice[player - 1];
}
void printroundinfo(stRoundInfo roundinfo) {
	cout << "\n--------------Round [" << roundinfo.RoundNumber << " ]-------------\n\n";
	cout << "Player1 Choice: " << choices(roundinfo.Player1Choice) << "\n";
	cout << "Computer choice: " << choices(roundinfo.Comchoice) << endl;
	cout << "Round Winner  :[" << roundinfo.WinnerName << "]\n";
	cout << "----------------------------------------------\n";
}
enplayer winnergame(short playerwintimes,short comwin) {
	if (playerwintimes > comwin)
		return  enplayer::player;
	else if (playerwintimes < comwin)
		return enplayer::com;
	else
		return enplayer::draw;
}
stGameResult fillgame(short gameround,short playerwin,short comwin,short drawwin) {
	stGameResult result;
	result.GameRound = gameround;
	result.Player1wintimes = playerwin;
	result.Comwintimes = comwin;
	result.Drawwintims = drawwin;
	result.GameWinner = winnergame(playerwin,comwin);
	result.Winnername = winnername(result.GameWinner);
	return result;

}
stGameResult PlayGame(short round) {
	stRoundInfo roundinfo;
	short playerwintimes=0, comwintimes=0, drawtimes=0;
	for (short i = 1; i <= round; i++)
	{
		cout << "\nRound [" << i << "] begeins:\n";
		roundinfo.RoundNumber = i;
		roundinfo.Player1Choice = ReadPlayerChoice();
		roundinfo.Comchoice = GetComChoice();
		roundinfo.Winner = whowintheround(roundinfo);
		roundinfo.WinnerName = winnername(roundinfo.Winner);
		if (roundinfo.Winner == enplayer::player)
			playerwintimes++;
		else if (roundinfo.Winner == enplayer::com)
			comwintimes++;
		else
			drawtimes++;
		printroundinfo(roundinfo);

	}
	return fillgame(round, playerwintimes, comwintimes, drawtimes);
}
string Tab(short num) {
	string t="";
	for (int i = 0; i <num ; i++)
	{
		t =t+ "\t";
		cout << t;

	}
	return t;
}
void showgameover() {
	cout << Tab(2) << "--------------------------------------------------------------\n\n";
	cout << Tab(2) << "                +++ G a m a e   O v e r +++   \n";
	cout << Tab(2) << "----------------------------------------------------------------\n\n";
}
void setcolor(enplayer win) {
	switch (win) {
	case enplayer::player:
		system("color 2F");
		break;
	case enplayer::com:
		system("color 4F");
		break;
	case enplayer::draw:
		system("color 6F");
		break;
	}
}
void showfinalres(stGameResult res) {
	cout << Tab(2) << "----------------------------[Game Result]-------------------\n\n";
	cout << Tab(2) << "Game Rounds        :" << res.GameRound << endl;
	cout << Tab(2) << "Player1 won times   :" << res.Player1wintimes << endl;
	cout << Tab(2) << "Computer won times    :" << res.Comwintimes << endl;
	cout << Tab(2) << "Draw times   :" << res.Drawwintims << endl;
	cout << Tab(2) << "Final Winner   :" << res.Winnername << endl;
	cout << "------------------------------------------------------------\n";
	setcolor(res.GameWinner);
}
void StartGame() {
	char playagain = 'Y';
	do {
		restscreen();
		stGameResult res = PlayGame(howtime());
		showgameover();
		showfinalres(res);
		cout << "do you want to play again? (Y/N) :\n";
		cin >> playagain;


	} while (playagain == 'Y' || playagain == 'y');
 }
int main()
{
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}
