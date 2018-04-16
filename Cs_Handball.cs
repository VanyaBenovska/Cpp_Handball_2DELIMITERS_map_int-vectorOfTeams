using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Cs_03_Handball_Statistics
{
    class Team
    {
        public string Name { get; set; }
        public int Wins { get; set; }
        public List<string> Opponents { get; set; }

        public Team(string name)
        {
            this.Name = name;
            this.Wins = 0;
            this.Opponents = new List<string>();
        }
        public override String ToString()
        {
            this.Opponents.Sort();
            string opponentsToString = string.Join(", ", Opponents).ToString();
            // return String.Format($"{Name}\n- Wins: {Wins}\n- Opponents: {opponentsToString}");
            return String.Format($"{Name}{Environment.NewLine}- Wins: {Wins}{Environment.NewLine}- Opponents: {opponentsToString}");
        }

    }
    class Program
    {
        static void Main(string[] args)
        {
            Dictionary<string, Team> data = new Dictionary<string, Team>();
            string input = Console.ReadLine();
            while (input != "stop")
            {
                string[] tokens = input.Split(new string[] { " | " }, StringSplitOptions.RemoveEmptyEntries).ToArray();
                string team_1 = tokens[0];
                string team_2 = tokens[1];
                string scoreFirstMeeting = tokens[2];
                string scoreSecondMeeting = tokens[3];
                string[] tokensScoreFirstMeeting = scoreFirstMeeting.Split(new char[] { ':' }, StringSplitOptions.RemoveEmptyEntries).ToArray();
                string[] tokensScoreSecondMeeting = scoreSecondMeeting.Split(new char[] { ':' }, StringSplitOptions.RemoveEmptyEntries).ToArray();
                int firstMeeting_ResultTeam01 = int.Parse(tokensScoreFirstMeeting[0]);
                int firstMeeting_ResultTeam02 = int.Parse(tokensScoreFirstMeeting[1]);
                int secondMeeting_ResultTeam02 = int.Parse(tokensScoreSecondMeeting[0]);
                int secondMeeting_ResultTeam01 = int.Parse(tokensScoreSecondMeeting[1]);
                int scoreTeam01 = firstMeeting_ResultTeam01 + secondMeeting_ResultTeam01;
                int scoreTeam02 = firstMeeting_ResultTeam02 + secondMeeting_ResultTeam02;

                //CHECK:
                //Console.WriteLine(firstMeeting_ResultTeam01);
                //Console.WriteLine(firstMeeting_ResultTeam02);
                //Console.WriteLine(secondMeeting_ResultTeam01);
                //Console.WriteLine(secondMeeting_ResultTeam02);

                if (!data.ContainsKey(team_1))
                {
                    Team team = new Team(team_1);
                    //data.Add(team_1, team);
                    data[team_1] = team;
                    data[team_1].Opponents.Add(team_2);
                }

                if (!data.ContainsKey(team_2))
                {
                    Team team = new Team(team_2);
                    //data.Add(team_2, team);
                    data[team_2] = team;
                    data[team_2].Opponents.Add(team_1);
                }

                if (!data[team_1].Opponents.Contains(team_2))
                {
                    data[team_1].Opponents.Add(team_2);
                }

                if (!data[team_2].Opponents.Contains(team_1))
                {
                    data[team_2].Opponents.Add(team_1);
                }



                if (scoreTeam01 < scoreTeam02)
                {
                    data[team_2].Wins++;
                }
                else if (scoreTeam01 == scoreTeam02)
                {
                    if (secondMeeting_ResultTeam01 + secondMeeting_ResultTeam02 <
                        firstMeeting_ResultTeam01 + firstMeeting_ResultTeam02)
                    {
                        data[team_2].Wins++;
                    }
                    else
                    {
                        data[team_1].Wins++;
                    }
                }
                else if (scoreTeam01 > scoreTeam02)
                {
                    data[team_1].Wins++;
                }

                input = Console.ReadLine();
            }

            var orderedInDescendingData = data.OrderByDescending(x => x.Value.Wins)
                .ThenBy(x => x.Value.Name);
            foreach (var item in orderedInDescendingData)
            {
                Team team = item.Value;
                Console.WriteLine($"{team}");
            }
        }
    }
}
