#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cmath>
using namespace std;
class Player{
private:
string _name="",_boardchoice="";
int _strength=0, _stamina=0, _wisdom=0, _pride_points=0, _age=0, _advisor=0;

/*
advisors:
gain Mufasa's spirit from answering a hard question
Lucky you!, you found Mufasa's spirit but a great mind is required to control him
Mufasa's spirit:gives super strength,can choose what to roll from 1-6, 
assoicated event:you barely escaped with your life due to stampeding wildebeests, lose 1k points

1:Rafiki:Invisibility,4-6,
2:Nala:Night vision:1-3
3:Sarabi:Energy manipulation:1-8
4:Zazu:Weather control:0-1
5:Sarafina:Super speed:1 or 6
*/
public:
Player();
Player(string name,int strength, int stamina, int wisdom);
string getName();
int getStrength();
int getStamina();
int getWisdom();
int getPridePoints();
int getAge();
int getAdvisor();
void setName(string name);
void setStrength(int strength);
void setStamina(int stamina);
void setWisdom(int wisdom);
void setPridePoints(int pride_points);
void setAge(int age);
void trainCub(int strength, int stamina, int wisdom);
void trainCub();
void toPrideLands();//goes on the PrideLands part of the board and print stats on it
void toCubTraining();
void printStats(int i);
void printMenu(int);//prints the menu out
void setAdvisor();
int rollDice();//print random number from 1-6 set it to rollValue rolled, then return it
int rollAdvisorDice(int _advisor);//rolls the advisors dice, then set rollValue = srand thing and return it
int move(int rollValue);//move spaces depending on amount rolled,takes in amount rolled
void printAllStats();//used in the secondary layer of printStats to print both player's stats, uses a for loop and calls the printStats
void printIntro();//prints the introduction stuff
void getRidOfPlayersAdvisor();
void printAdvisorStatsIfTheychoseTraining(int);//only ran at the beginning if the person chose to do cub training
bool printAdvisorStats(int);//takes in advisor, then print their stats,then ask if the person wants the use the adivsors dice,if yes, then the player uses it
void setAdvisorEqualToMufasasSpirit();
void endGame();
void printStatsMenu(int);
void increaseWisdom(int);
void increaseStrength(int);
void increaseStamina(int);
void decreaseStamina(int);
void decreaseStrength(int);
void decreaseWisdom(int);
void increasePridePoints(int);
void decreasePridePoints(int);
void setPlayerBoardchoice(string);
string getPlayerBoardchoice();
};
