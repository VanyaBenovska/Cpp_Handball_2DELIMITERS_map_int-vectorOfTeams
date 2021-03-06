// Cpp_03_Handball_Statistics_3_Map_of_v.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <functional>
#include <functional>
using namespace std;

class Team {
private:	
	string name;
	int wins;
	vector<string> opponents;

public:
	string getName() {
		return this->name;
	}
	int getWins() {
		return this->wins;
	}
	vector<string> getOpponents() {
		return this->opponents;
	}

	void setWins() {
		this->wins++;
	}
	void setOpponents(string opponent) {
		this->opponents.push_back(opponent);
	}

	Team(string name, string opponent) :
		name(name),
		wins(0),
		opponents(vector<string>({ opponent }))
	{}

	/*string getTeamInfo() {
		sort(this->opponents.begin(), this->opponents.end());
		ostringstream ossOpponents;
		int cnt = 0;
		for (string item : this->opponents)
		{
			ossOpponents << item;
			if (cnt < this->opponents.size() - 1)
			{
				ossOpponents << ", ";
			}
			cnt++;
		}
		string sOrderedOpponents = ossOpponents.str();
		ostringstream info;
		info << this->name << "\n- Wins: " << this->wins << "\n- Opponents: " << sOrderedOpponents << "\n";
		return info.str();
	}*/
};


int StrToInt(string str)
{
	int digit = str[str.length() - 1] - 48;   //!
	int factor = 10;
	for (int i = str.length() - 2; i = 0; i--)
	{
		digit += str[i] * factor;
		factor *= 10;
	}
	return digit;
}

int main()
{
	cin.sync_with_stdio(false);
	map<string, Team> data;
	string input;
	getline(cin, input);

	while (input != "stop")
	{
		string delimiter = " | ";
		input += delimiter;
		size_t pos = 0;
		string token;
		vector<string> vtokens;
		while ((pos = input.find(delimiter)) != std::string::npos) {
			token = input.substr(0, pos);
			vtokens.push_back(token);
			input.erase(0, pos + delimiter.length());
		}
		string team_1 = vtokens[0];
		string team_2 = vtokens[1];
		string scoreFirstMeeting = vtokens[2];
		string scoreSecondMeeting = vtokens[3];
		scoreFirstMeeting += ":";
		scoreSecondMeeting += ":";

		string delimiter2 = ":";
		vector<string> vresultsFirstMeeting, vresultsSecondMeeting;
		while ((pos = scoreFirstMeeting.find(delimiter2)) != std::string::npos) {
			token = scoreFirstMeeting.substr(0, pos);
			vresultsFirstMeeting.push_back(token);
			scoreFirstMeeting.erase(0, pos + delimiter2.length());
		}
		int firstMeeting_ResultTeam01 = StrToInt(vresultsFirstMeeting[0]);
		int firstMeeting_ResultTeam02 = StrToInt(vresultsFirstMeeting[1]);

		while ((pos = scoreSecondMeeting.find(delimiter2)) != std::string::npos) {
			token = scoreSecondMeeting.substr(0, pos);
			vresultsSecondMeeting.push_back(token);
			scoreSecondMeeting.erase(0, pos + delimiter2.length());
		}
		int secondMeeting_ResultTeam02 = StrToInt(vresultsSecondMeeting[0]);
		int secondMeeting_ResultTeam01 = StrToInt(vresultsSecondMeeting[1]);

		int scoreTeam01 = firstMeeting_ResultTeam01 + secondMeeting_ResultTeam01;
		int scoreTeam02 = firstMeeting_ResultTeam02 + secondMeeting_ResultTeam02;
		//**************************************************
		map<string, Team>::iterator foundTeam1 = data.find(team_1);
		if (foundTeam1 != data.end()) {
			//team1 is already in the map
			vector<string> opponentsOfTeam1 = foundTeam1->second.getOpponents();
			auto  it = find(opponentsOfTeam1.begin(), opponentsOfTeam1.end(), team_2);
			if (it != opponentsOfTeam1.end()) {
				//team_2 is already in opponents of team_1
			}
			else {
				foundTeam1->second.setOpponents(team_2);
			}
		}
		else {
			Team team{ team_1, team_2 };
			data.insert({ team_1, team });
		}
		//****************************************************
		map<string, Team>::iterator foundTeam2 = data.find(team_2);
		if (foundTeam2 != data.end()) {
			//team2 is already in the map
			vector<string> opponentsOfTeam2 = foundTeam2->second.getOpponents();
			auto  it = find(opponentsOfTeam2.begin(), opponentsOfTeam2.end(), team_1);
			if (it != opponentsOfTeam2.end()) {
				//team_1 is already in opponents of team_2
			}
			else {
				foundTeam2->second.setOpponents(team_1);
			}
		}
		else {
			Team team{ team_2 , team_1 };
			data.insert({ team_2, team });

		}
		//*****************************************************************************************

		if (scoreTeam01 < scoreTeam02)
		{
			map<string, Team>::iterator foundTeam2 = data.find(team_2);
			foundTeam2->second.setWins();
		}
		else if (scoreTeam01 == scoreTeam02)
		{
			if (secondMeeting_ResultTeam01 + secondMeeting_ResultTeam02 < firstMeeting_ResultTeam01 + firstMeeting_ResultTeam02)
			{
				map<string, Team>::iterator foundTeam2 = data.find(team_2);
				foundTeam2->second.setWins();
			}
			else
			{
				map<string, Team>::iterator foundTeam1 = data.find(team_1);
				foundTeam1->second.setWins();
			}
		}
		else if (scoreTeam01 >= scoreTeam02)
		{
			map<string, Team>::iterator foundTeam1 = data.find(team_1);
			foundTeam1->second.setWins();
		}

		getline(cin, input);
	}

	//RELOADING DATA in MAP of vectors:
	map<int, vector<Team>, greater<int> > dataMapIntVector;
	auto iterator = data.begin();
	Team firsrtTeam = iterator->second;
	int keyFirstTeam = firsrtTeam.getWins();
	vector<Team> vFirst;
	vFirst.push_back(firsrtTeam);
	dataMapIntVector.insert({ keyFirstTeam, vFirst });
	data.erase(iterator);
	for (auto it = data.begin(); it != data.end(); it++)    //data is map<string, Team>
	{
		for (auto ite = dataMapIntVector.begin(); ite != dataMapIntVector.end(); ite++)
		{
			if (it->second.getWins() == ite->first)
			{
				ite->second.push_back(it->second);
			}
			else
			{
				vector<Team> v;
				v.push_back(it->second);
				int key = it->second.getWins();
				dataMapIntVector.insert({ key, v });
			}
		}
	}

	for (auto item : dataMapIntVector)
	{
		vector<Team> dataVEqualWinsTeams = item.second;

		map<string, Team> dataMAPStringTeamsEqualWins;
		int wins = item.first;
		for (int i = 0; i < dataVEqualWinsTeams.size(); i++)
		{
			string teamName = dataVEqualWinsTeams[i].getName();
			dataMAPStringTeamsEqualWins.insert({ teamName, dataVEqualWinsTeams[i] });
		}
		for (auto t : dataMAPStringTeamsEqualWins)
		{
			cout << t.first << endl;
			cout << "- Wins: " << t.second.getWins() << endl;
			vector<string> opponents = t.second.getOpponents();
			sort(opponents.begin(), opponents.end());
			cout << "- Opponents: ";
			int c = 0;
			for (auto v : opponents)
			{
				cout << v;
				if (c < opponents.size() - 1)
				{
					cout << ", ";
				}
				c++;
			}
			cout << endl;
		}
	}
	return 0;
}


