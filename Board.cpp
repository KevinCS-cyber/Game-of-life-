#include "Board.h"
#define RED "\033[48;2;230;10;10m"
#define GREEN "\033[48;2;34;139;34m" /* Grassy Green (34,139,34) */
#define BLUE "\033[48;2;10;10;230m"
#define PINK "\033[48;2;255;105;180m"
#define BROWN "\033[48;2;139;69;19m"
#define PURPLE "\033[48;2;128;0;128m"
#define ORANGE "\033[48;2;230;115;0m" /* Orange (230,115,0) */
#define GREY "\033[48;2;128;128;128m" /* Grey (128,128,128) */
#define RESET "\033[0m"
#include<vector>
int split(const string input_string, char separator, string arr[], const int ARR_SIZE);
//playerIndexToMoveBack is to have the correct index to call getters and setters so it would be correct
void Board::TileEffects(int player_index, int player_position,int amountPlayerMovedDuringTurn,int playerIndexToMoveBack)
{
    string TileColor = getPlayerColor(player_index, player_position);
    int PlayerNum = player_index + 1;
    int purpleLinesToRead = 0;
    int pinkAdvisorID = 0;
    int greenAdvisorID=0;
    int GreenRandom = 0;
    int greenAdvisorForBadEffects=0;
    int greenRandomLine = 0;
    string greenline = "";
    string greenArray[5];
    int pridepointsgained=0;
    string didPlayerUseAdvisor="";
    string pinkChoice = "";
    string purpleArray[2];
    string line = "", answer = "";
    if(playerIndexToMoveBack==1){
        PlayerNum=2;
    }
    else{
        PlayerNum=1;
    }
    cout << "Player " << PlayerNum << ". You landed on a " << TileColor << " tile!" << endl;
    if (TileColor == "Blue")
    {
        cout << "you landed on a oasis tile!" << endl;
        cout << "the oasis tile allows you to roll again and you gain 200 on all leadership traits!" << endl;
        lions[playerIndexToMoveBack].increaseStamina(200);
        lions[playerIndexToMoveBack].increaseStrength(200);
        lions[playerIndexToMoveBack].increaseWisdom(200);
        cout << "player " << PlayerNum << ", your new stamina points is " << lions[playerIndexToMoveBack].getStamina()<<endl;
        cout << "player " << PlayerNum << ", your new strength points is " << lions[playerIndexToMoveBack].getStrength()<<endl; 
        cout << "player " << PlayerNum << ", your new wisdom points is " << lions[playerIndexToMoveBack].getWisdom()<<endl;
        cout<<endl;
        cout<<endl;
    }
    else if (TileColor == "Purple")
    {
        cout << "You landed on a savannah tile, it's time to test your wits!" << endl;
        cout << "answer correctly and you will get 500 pride points!" << endl;
        cout << "answer wrong and you get nothing!" << endl;
        ifstream open("riddles.txt");        // opens riddles.txt
        purpleLinesToRead = rand() % 30 + 1; // need 1-30,
        for (int i = 0; i < purpleLinesToRead; i++)
        {
            getline(open, line);
        }
        split(line, '|', purpleArray, 2);
        cout << "Here is your riddle" << endl;
        cout << purpleArray[0] << endl;
        getline(cin, answer);
        if (answer==purpleArray[1]&&purpleLinesToRead==1){
            cout<<"Mufasa's spirit was impressed with your knowledge!"<<endl;
            cout<<"you gained 600 pride points and a very special dice!"<<endl;
            cout<<"Check the advisor option during your turn to learn more!"<<endl;
            lions[playerIndexToMoveBack].setAdvisorEqualToMufasasSpirit();
        }
        else if (answer == purpleArray[1])
        {
            cout << "Congrats you answered correctly!" << endl;
            cout << "You have gained 500 pride points" << endl;
            lions[playerIndexToMoveBack].increasePridePoints(500);
        }
        else
        {
            cout << "Sorry but you answer was wrong, too bad!" << endl;
        }
    }
    else if (TileColor == "Pink")
    {
        cout << "Welcome to the land of enrichment- when landing on this tile" << endl;
        cout << "your Stamina, Strength, and Wisdom points increase by 300, and you get a random advisor" << endl;
        lions[playerIndexToMoveBack].increaseStamina(300);
        lions[playerIndexToMoveBack].increaseStrength(300);
        lions[playerIndexToMoveBack].increaseWisdom(300);
        pinkAdvisorID = lions[playerIndexToMoveBack].getAdvisor();
        if (pinkAdvisorID != 1 && pinkAdvisorID != 2 && pinkAdvisorID != 3 && pinkAdvisorID != 4 && pinkAdvisorID != 5)
        { // player doesn't have advisor
            cout << "Player " << PlayerNum << " you don't have an advisor, here is your advisor" << endl;
            lions[playerIndexToMoveBack].setAdvisor();
            pinkAdvisorID = lions[playerIndexToMoveBack].getAdvisor();
            lions[playerIndexToMoveBack].printAdvisorStatsIfTheychoseTraining(pinkAdvisorID);
        }
        else
        {
            cout << "You already have an advisor do you want to switch out your advisor? Enter Y or N" << endl;
            cout<<"your current advisor and their stats are printed below"<<endl;
            lions[playerIndexToMoveBack].printAdvisorStatsIfTheychoseTraining(pinkAdvisorID);
            getline(cin,pinkChoice);
            while (pinkChoice != "Y" && pinkChoice != "N")
            { // ask if this while statement would work as IDK how to test this
                cout << "invalid input, please enter Y or N" << endl;
                getline(cin,pinkChoice);
            }
            if (pinkChoice == "Y")
            {                                                          // player decided to change their advisor
                cout << "You decided to choose a new advisor" << endl; // ask if allowed to get the same advisor
                cout << "Here are your new advisor's stats" << endl;
                lions[playerIndexToMoveBack].setAdvisor();
                pinkAdvisorID = lions[playerIndexToMoveBack].getAdvisor();
                lions[playerIndexToMoveBack].printAdvisorStatsIfTheychoseTraining(pinkAdvisorID);
            }
            else
            { // player decided not to change their advisor
                cout << "You decided to not change your advisor" << endl;
            }
        }
    }
    else if (TileColor == "Green")
    {
        greenAdvisorID=lions[playerIndexToMoveBack].getAdvisor();
        cout << "you landed on a Green tile" << endl;
        GreenRandom = rand() % 2; // gets a number between 0 and 1
        if (GreenRandom == 1)
        {
            cout << " but nothing happened" << endl;
        }
        else
        {
            cout <<  "and a random event will happen to you" << endl;
            if(lions[playerIndexToMoveBack].getPlayerBoardchoice()=="P"){ //organized random_events.txt so pride lands were first, 
            greenRandomLine =rand() % 25+1;}  // need 1-25
            else{
                greenRandomLine=rand()%26+26; //need 26-51 
            }
            ifstream open("random_events.txt");
            getline(open, greenline); //skip the first line as that is the format
            for (int i = 0; i < greenRandomLine; i++)
            {
                getline(open, greenline);
            }
            split(greenline,'|',greenArray,4);
            cout<<greenArray[0]<<endl;
            greenAdvisorForBadEffects=stoi(greenArray[2]); //converts the from random events.txt needed into it
            pridepointsgained=stoi(greenArray[3]);
            if(greenAdvisorID==6&&pridepointsgained<0){ //if player has mufasa's spirit and the event would cause you to lose pride points
                cout<<"Mufasa's spirit can help you avoid losing "<<abs(pridepointsgained)<<" pride points"<<endl;
                cout<<"do you want to use Mufasa's spirit enter Y(to use) or N(to not use)"<<endl;
                cout<<"Note: if you use Mufasa's spirit, you won't have him anymore"<<endl;
                getline(cin,didPlayerUseAdvisor);
                while(didPlayerUseAdvisor!="Y"&&didPlayerUseAdvisor!="N"){
                    cout<<"Please enter either Y or N"<<endl;
                    getline(cin,didPlayerUseAdvisor);
                }
                if(didPlayerUseAdvisor=="Y"){
                    cout<<"You decided to use Mufasa's spirit to avoid losing "<<abs(pridepointsgained)<<" pride points"<<endl;
                    cout<<"unfortunately, you don't have Mufasa's spirit anymore"<<endl;
                    lions[playerIndexToMoveBack].getRidOfPlayersAdvisor();
                    return; //so it doesn't continue to do the rest of the function
                }
                else{
                    cout<<"You decided to not use Mufasa's spirit"<<endl;
                    cout<<"Therefore you lost "<<abs(pridepointsgained)<<" pride points"<<endl;
                    cout<<"your new pride points total is"<<lions[playerIndexToMoveBack].getPridePoints();
                    return; //so it doesn't check the other if statements below
                }
            }
             if(greenAdvisorID==greenAdvisorForBadEffects &&pridepointsgained<0){ //if greenadvisorID=the pride points and the pride points is negative
                cout<<"You have an advisor who can help you with this event"<<endl; //which then asks the user if they want to use their advisor to avoid losing the associated pride points
                cout<<"Do you want to use your advisor to avoid having "<<abs(pridepointsgained)<<" pride points deducted?"<<endl; //learned there was a absolute value function by looking it up
                cout<<"Note:if you decide to use your advisor, you won't have your advisor anymore"<<endl;
                cout<<"Enter Y(to use) or N(to not use)"<<endl;
                getline(cin,didPlayerUseAdvisor);
                while(didPlayerUseAdvisor!="Y"&&didPlayerUseAdvisor!="N"){
                    cout<<"Please enter either Y or N"<<endl;
                    getline(cin,didPlayerUseAdvisor);
                }
                if(didPlayerUseAdvisor=="Y"){ //player decided to use advisor
                    cout<<"you decided to use your advisor to avoid losing "<<abs(pridepointsgained)<< " pride points"<<endl;
                    lions[playerIndexToMoveBack].getRidOfPlayersAdvisor();
                }
                else{ //player decided to not use advisor
                    cout<<"you decided to not use your advisor therefore you lost "<<abs(pridepointsgained)<<" pride points"<<endl;
                    lions[playerIndexToMoveBack].decreasePridePoints(abs(pridepointsgained)); //decrease the pride points by that much
                    cout<<"your new pride point is "<<lions[playerIndexToMoveBack].getPridePoints()<<endl;
                }
             }
             else if(greenAdvisorID!=greenAdvisorForBadEffects&&pridepointsgained<0){//player landed on bad event and doesn't have advisor
                    cout<<"You don't have the correct advisor to protect you therefore you lost "<<abs(pridepointsgained)<<" pride points"<<endl;
                    lions[playerIndexToMoveBack].decreasePridePoints(abs(pridepointsgained));
                    cout<<"your new pride point is "<<lions[playerIndexToMoveBack].getPridePoints()<<endl;
                }
                else if(greenAdvisorForBadEffects==0){ //event doesn't require an advisor, assume event that don't require advisor are good
                    cout<<"This event doesn't require an advisor therefore you gained "<<pridepointsgained<<" pride points"<<endl;
                    lions[playerIndexToMoveBack].increasePridePoints(pridepointsgained);
                    cout<<"your new pride point is "<<lions[playerIndexToMoveBack].getPridePoints()<<endl;
                }
                else if(greenAdvisorID!=greenAdvisorForBadEffects&&pridepointsgained>0){ //player landed on good space but doesn't have advisor
                    cout<<"you landed on a good space but you don't have the correct advisor"<<endl;
                    cout<<"therefore you missed out on gaining "<<pridepointsgained<< "pride points"<<endl;
                }
                else if(greenAdvisorID==greenAdvisorForBadEffects&&pridepointsgained>0){ //player landed on good space  and has advisor
                cout<<"lucky you, you landed on a good space but you have to use your advisor to gain "<<pridepointsgained<<" pride points"<<endl;
                cout<<"enter Y if you want to use your advisor and N if you don't want to use your advisor"<<endl;
                cout<<"note: if you use your advisor, you won't have your advisor anymore"<<endl;
                getline(cin,didPlayerUseAdvisor);
                while(didPlayerUseAdvisor!="Y"&&didPlayerUseAdvisor!="N"){ //asks player if they want to use their advisor
                    cout<<"Please enter Y or N "<<endl;
                    getline(cin,didPlayerUseAdvisor);
                }
                if(didPlayerUseAdvisor=="Y"){ //player decided to use advisor
                    cout<<"you decided to use your advisor to gain "<<pridepointsgained<<" pride points"<<endl;
                    lions[playerIndexToMoveBack].increasePridePoints(pridepointsgained);
                    lions[playerIndexToMoveBack].getRidOfPlayersAdvisor();
                }
                else{ //player decided not to use advisor
                    cout<<"you decided not to use your advisor therefore your pride points is still"<<lions[playerIndexToMoveBack].getPridePoints()<<endl;
                }
                } 
        }
    }
    else if (TileColor == "Red")
    {
        cout << "Uh oh!, you landed on the graveyard tile, that means you move back 10 spaces and lose 100 stamina, strength, and wisdom points" << endl;
        lions[playerIndexToMoveBack].decreaseStamina(100);
        lions[playerIndexToMoveBack].decreaseStrength(100);
        lions[playerIndexToMoveBack].decreaseWisdom(100);
        cout<<"Player"<<PlayerNum<<": your new stamina points is "<<lions[playerIndexToMoveBack].getStamina()<<endl;
        cout<<"Player"<<PlayerNum<<": your new strength points is "<<lions[playerIndexToMoveBack].getStrength()<<endl;
        cout<<"Player"<<PlayerNum<<": your new wisdom points is "<<lions[playerIndexToMoveBack].getWisdom()<<endl;
        for(int i=0;i<10;i++){
        movePlayerBackwards(playerIndexToMoveBack);
        }

    }
    else if (TileColor == "Brown")
    {
        cout << "you landed on the hyenas tile!, unfortunately they dragged you back to your last position and you lost 300 stamina points!" << endl;
        lions[playerIndexToMoveBack].decreaseStamina(300);
        for(int i=0;i<amountPlayerMovedDuringTurn;i++){
            movePlayerBackwards(playerIndexToMoveBack);
        }
    
    }
}
// did blue,purple,pink,green,red
void Board::initializeBoard()
{
    // Seed random number generator in your main function once
    for (int i = 0; i < 2; i++)
    {
        initializeTiles(i); // This ensures each lane has a unique tile distribution
    }
}

#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
void Board::initializeTiles(int player_index)
{
    Tile temp;
    int green_count = 0;
    int total_tiles = _BOARD_SIZE;

    // Keep track of green tile positions to ensure we place exactly 30 greens
    for (int i = 0; i < total_tiles; i++)
    {
        if (i == total_tiles - 1)
        {
            // Set the last tile as Orange for "Pride Rock"
            temp.color = 'O';
        }
        else if (i == 0)
        {
            // Set the last tile as Orange for "Pride Rock"
            temp.color = 'Y';
        }
        else if (green_count < 30 && (rand() % (total_tiles - i) < 30 - green_count))
        {
            temp.color = 'G';
            green_count++;
        }
        else
        {
            // Randomly assign one of the other colors: Blue, Pink, Brown, Red, Purple
            int color_choice = rand() % 5;
            switch (color_choice)
            {
            case 0:
                temp.color = 'B'; // Blue
                break;
            case 1:
                temp.color = 'P'; // Pink
                break;
            case 2:
                temp.color = 'N'; // Brown
                break;
            case 3:
                temp.color = 'R'; // Red
                break;
            case 4:
                temp.color = 'U'; // Purple
                break;
            }
        }

        // Assign the tile to the board for the specified lane
        _tiles[player_index][i] = temp;
    }
}


Board::Board(int player_count)
{
    
    if (player_count > _MAX_PLAYERS)
    {
        _player_count = _MAX_PLAYERS;
    }
    else
    {
        _player_count = player_count;
    }

    // Initialize player position
    for (int i = 0; i < _player_count; i++)
    {
        _player_position[i] = 0;
    }
    // Initialize tiles
    bool didPlayersChooseSameBoard=printIntro(); //checks to see if a player 
    initalizeBoardWIP(didPlayersChooseSameBoard); //putted everything inside one function so I could see if the players chose the same board and print everything accordingly
    printMenu(didPlayersChooseSameBoard);
    endGame();
}

void Board::initalizeBoardWIP(bool didPlayersChooseSameBoard){
    if(didPlayersChooseSameBoard==true){
        initializeTiles(0); //only prints 1 board
    }
    else{
        for (int i = 0; i < 2; i++)
    {
        initializeTiles(i); // This ensures each lane has a unique tile distribution
    }
    }
}

bool Board::isPlayerOnTile(int player_index, int pos)
{
    if (_player_position[player_index] == pos)
    {
        return true;
    }
    return false;
}

void Board::displayTile(int track_index, int pos)
{
    // string space = "
    string color = "";
    vector<int> players_on_track; //created a vector called players on track
    bool sameTrack = lions[0].getPlayerBoardchoice() == lions[1].getPlayerBoardchoice() && track_index == 0; //
    for (int i = 0; i < 2; i++) {
        bool onTile = isPlayerOnTile(i, pos); // checks to see if the player is on the tile
        bool onTrack = (sameTrack && track_index == 0) ; //bool to see if players decided to choose same track 
        if (onTile && onTrack)
        {
            players_on_track.push_back(i);
        }
    }

    // Template for displaying a tile: <line filler space> <color start> |<player symbol or blank space>| <reset color> <line filler space> <endl>

    // Determine color to display

    if (_tiles[track_index][pos].color == 'R')
    {
        color = RED;
    }
    else if (_tiles[track_index][pos].color == 'G')
    {
        color = GREEN;
    }
    else if (_tiles[track_index][pos].color == 'B')
    {
        color = BLUE;
    }
    else if (_tiles[track_index][pos].color == 'U')
    {
        color = PURPLE;
    }
    else if (_tiles[track_index][pos].color == 'N')
    {
        color = BROWN;
    }
    else if (_tiles[track_index][pos].color == 'P')
    {
        color = PINK;
    }
    else if (_tiles[track_index][pos].color == 'O')
    {
        color = ORANGE;
    }
    else if (_tiles[track_index][pos].color == 'Y')
    {
        color = GREY;
    }

    cout << color << "| ";
    for (int i = 0; i < (int) players_on_track.size(); i++) {
        if((int)players_on_track.size()==1){
            cout<<i+1; //only print 1 if both players are on the board
        }
        else
        {
            if(i==0){cout << i + 1 << "&";}
            else{
                cout<<i+1; //doesn't print out an &
            } 
        }
    }
    cout << "|"<<RESET;

}

void Board::displayTileWIP(int player_index, int pos)
{
    string playersontile="";
    // string space = "
    string color = "";
    int player = isPlayerOnTile(player_index, pos); 

    // Template for displaying a tile: <line filler space> <color start> |<player symbol or blank space>| <reset color> <line filler space> <endl>

    // Determine color to display
    if (_tiles[player_index][pos].color == 'R')
    {
        color = RED;
    }
    else if (_tiles[player_index][pos].color == 'G')
    {
        color = GREEN;
    }
    else if (_tiles[player_index][pos].color == 'B')
    {
        color = BLUE;
    }
    else if (_tiles[player_index][pos].color == 'U')
    {
        color = PURPLE;
    }
    else if (_tiles[player_index][pos].color == 'N')
    {
        color = BROWN;
    }
    else if (_tiles[player_index][pos].color == 'P')
    {
        color = PINK;
    }
    else if (_tiles[player_index][pos].color == 'O')
    {
        color = ORANGE;
    }
    else if (_tiles[player_index][pos].color == 'Y') 
    {
        color = GREY;
    }

    if (player == true)
    {
        cout << color << "|" << (player_index + 1) << "|" << RESET; // if player is on the space,
    } // then print the color and then add player index+1 as it would be 0 and 1 and  not 1 and 2
    else
    {
        cout << color << "| |" << RESET; // player isn't on tile so don't print the player on there
    }
    
    
}



void Board::displayTrack(int player_index)
{
    for (int i = 0; i < _BOARD_SIZE; i++) // goes through all 52 tiles, then uses display tile
    {
        displayTile(player_index, i);
    }
    cout << endl;
}

void Board::displayTrackIfPlayersChoseSameBoard(int player_index){
    for (int i = 0; i < _BOARD_SIZE; i++) // goes through all 52 tiles, then uses display tile
    {
        displayTileWIP(player_index, i);
    }
    cout << endl;
}

void Board::displayBoard()
{
    for (int i = 0; i <2; i++)
    {
        displayTrackIfPlayersChoseSameBoard(i);
        if (i == 0)
        {
            cout << endl; // Add an extra line between the two lanes
        }
        // this function is to call the display track twice
    }
}

void Board::displayBoardIfBothplayersChooseTheSamePosition(){
    displayTrack(0); //only displays the first board
}

int split(const string input_string, char separator, string arr[], const int ARR_SIZE)
{
    int StringLength = input_string.length(), stored = 0, start_index = 0;
    string temp = "";
    if (StringLength == 0)
    {
        return 0;
    }
    for (int i = 0; i < StringLength; i++)
    {
        if (input_string[i] == separator || i == StringLength - 1)
        {
            if (stored >= ARR_SIZE)
            {
                return -1;

            }
            if (i == StringLength - 1 && input_string[i] != separator)
            {
                i++;
            }
            arr[stored] = input_string.substr(start_index, i - start_index); // what gets stored is everthing after the main line
            stored++;                                                        // increment stored
            start_index = i + 1;                                             // move the start index after to after the delimiter
        }
    }
    return stored;
}

bool Board::printIntro()
{
    int playerIndex = 0;
    int AdvisorID = 0;
    int player1choice=0;
    string choiceS="";
    string boardchoice = "";
    string Player1ChoiceS="";
    string Player1BoardChoice="";
    string arr[6];
    string j = ""; // it is a string, not a char because if it was a char, then it would print string
    string line = "";
    string array[6];
    string nextPlayerIsHere;
    int choice = 0;
    int lionNum = 1;
    for (int in = 1; in < 3; in++)
    { // loop twice for all 2 of the players
        cout << "You are competing against another lion trying to be the next pride leader after Simba's retirement!" << endl;
        cout << "Along the way you will make strategic decisions, face unexpected challenges, and collect pride points" << endl;
        cout << "The player who earns the most pride points wins becoming the next pride leader!" << endl;
        cout << "Press Y to continue" << endl;
        getline(cin,j); // above is flavor text and it is to allow the player to continue

        while (j != "Y")
        {
            cout << "Please enter Y" << endl; //loops until player enters Y
            getline(cin,j);
        }
        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        cout << "Player " << in << ": Choose your lion:" << endl;
        ifstream open("characters.txt"); // open the characters.txt file which contains the characters
        getline(open, line);             // skip the first line as that is the format of the character
        while (getline(open, line))
        {                                    // as long as there are valid lines to read
            split(line, '|', arr, 6);                   // use split function to split it up
            if((in==2&&lions[0].getName()!=arr[0])||in==1){ 
// if statement above prints it out if it's the first players turn or when it's the second players turn and the name doesn't match the 1st player's name
            cout << "Lion number: " << lionNum << endl; // lion num is initalized at 1
            cout << "Name: " << arr[0] << endl;         // 0th index of the split is the name
            cout << "Age: " << arr[1] << endl;          // 1st index of the split is the age
            cout << "Strength: " << arr[2] << endl;     // 2nd index of the split is the strength
            cout << "Stamina: " << arr[3] << endl;      // 3rd index of the split is the strength
            cout << "Wisdom: " << arr[4] << endl;       // 4th index of the split is the wisdom
            cout << "Pride points: " << arr[5] << endl; // 5th index of the split is the pride points(always 2k)
            cout << endl;
            }
            lionNum++; // increment the lion num
        }
        open.close(); // closes the file
        lionNum = 1;  // reset it back to 1 for the second player
        if(in==1){
        cout << "Player " << in << " Please enter the corresponding lion number to choose that lion(1,2,3,4,5,6,7,8)" << endl;
        }
        else{ //this would be the second player
            if(player1choice==8){ //if player choice is 8, then print below, else print the other one that prints all the lions except for the one the player chose
                cout<<"Player "<< in <<" Please enter the corresponding lion number to choose that lion(1,2,3,4,5,6,7)"<<endl;
            }
            else{cout<<"Player "<< in << " Please enter the corresponding lion number to choose that lion(";
            for(int i=1;i<9;i++){ //goes through all avaiable lion numbers
                if(i!=choice){ //if i doesn't equal the first player's choice
                if(i==8){
                    cout<<i<<")"<<endl;//wouldn't print a comma at the end
                }
                    else{cout<<i<<",";}; //print the choices and then a comma afterwards
                }
            }}
        }
        getline(cin,choiceS);
        if(in==2){Player1ChoiceS=to_string(player1choice);}//convert player 1's choice to a string to compare against the choice in the next line as I'm using getline which only works with strings
        if((choiceS=="1"||choiceS=="2"||choiceS=="3"||choiceS=="4"||choiceS=="5"||choiceS=="6"||choiceS=="7"||choiceS=="8")&&choiceS!=Player1ChoiceS){ //if option was a valid number and the players choice doesn't equal the 1st player's choice
        choice=stoi(choiceS);} //need this or I would get an error from trying to convert strings to ints
        else{
            while((choiceS!="1"&&choiceS!="2"&&choiceS!="3"&&choiceS!="4"&&choiceS!="5"&&choiceS!="6"&&choiceS!="7"&&choiceS!="8") || choiceS==Player1ChoiceS){ 
            // player's choice can't be the 1st players choice or anything that isn't 1-8, if it is, stay in this loop until the 2nd player enters a valid input
            if(in==1){cout << "invalid input, please enter 1,2,3,4,5,6,7,8" << endl;
            getline(cin,choiceS);
            }
            else if(in==2){ //this was player 2 
            if(choiceS==Player1ChoiceS){
                cout<<"Player 1 already chose lion "<< player1choice<<", you can't both be the same lion therefore"<<endl;
            }
                if(player1choice==8){ //print this out if player's choice was 8 so it would work
                cout<<"invalid input, please enter 1,2,3,4,5,6,7"<<endl;
                getline(cin,choiceS);
            }
                else{cout<<"invalid input, please enter "; 
                for(int c=1;c<9;c++){
                    if(c!=player1choice){ //prints out the numbers that weren't choosen by player 1
                    if(c==8){
                        cout<<c<<endl; //don't need a comma after the 8th lion
                    }
                        else{cout<<c<<",";}//neds a comma if not the last lion
                    }
                }
                getline(cin,choiceS);
                }
            }
            }
            choice=stoi(choiceS);
        }
        open.open("characters.txt"); // opens the file again which means it starts at the 1st line
        getline(open, line);         // skip the first line as it is the format
        for (int k = 0; k < choice; k++)
        {                        // goes to the appriopriate line depending on the person's choice
            getline(open, line); // getline is to put the line inside of the line or skip the line
        }
        split(line, '|', array, 7);                                                          // use the split function to split everything based on the delimiter
        cout << "Congrats player " << in << "! you have choosen " << array[0] << "." << endl; // array 0 is the name of the lion
        cout << "Fun fact: " << array[0] << " means " << array[6] << endl;                   // created a 6th index which is the meaning of the lions name
        lions[playerIndex].setName(array[0]);
        int Age = stoi(array[1]);
        lions[playerIndex].setAge(Age);
        int Strength = stoi(array[2]);
        lions[playerIndex].setStrength(Strength);
        int Stamina = stoi(array[3]);
        lions[playerIndex].setStamina(Stamina);
        int wisdom = stoi(array[4]);
        lions[playerIndex].setWisdom(wisdom);
        int pridePoints = stoi(array[5]);
        lions[playerIndex].setPridePoints(pridePoints); // above sets the player's stats to the stats converting them to ints if necessary
        cout << endl;
        cout << "here are your stats" << endl;
        lions[playerIndex].printStats(in); // print the player's stats
        cout << "Player " << in << ". Do you want to go to the pride lands(P) or to cub training(C)?" << endl;
        cout << "going to the pride lands leads to gaining 5k pride points and gain 200 stamina, strength, and wisdom points but you don't have an advisor" << endl;
        cout << "doing cub training leads to losing 5k pride points but gain 500 stamina, 500 strength, and 1k wisdom and can pick a advisor at the start" << endl;
        cout << "Please enter C or P:" << endl;
        getline(cin,boardchoice);
        while (boardchoice != "P" && boardchoice != "C") // enters something that isn't P or C
        {
            cout << "Invalid choice" << endl;
            cout << "Please enter P if you want to go to the pride lands or C if you want to go to cub training" << endl;
            getline(cin,boardchoice);
        }
        if (boardchoice == "P")//decided to go to pride lands
        {
            cout << "You decided to go to the pride lands!" << endl;
            lions[playerIndex].toPrideLands(); // adjusts the stats appropriately
            lions[playerIndex].printStats(in);  // prints new stats
            lions[playerIndex].setPlayerBoardchoice(boardchoice); //sets the playerboardchoice to the board choice
        }
        else//decided to go to cub training
        {
            cout << "You decided to go to cub training!" << endl;
            lions[playerIndex].toCubTraining(); // adjusts the stats appropriately
            lions[playerIndex].printStats(in);   // prints new stats
            cout << endl;
            cout << "You also got an advisor!" << endl;
            lions[playerIndex].setAdvisor();                                    // set advisor picks a random number between 1 and 5,then sets _advisor= to that
            AdvisorID = lions[playerIndex].getAdvisor();                        // sets AdvisorID equal to the random number from setAdvisor
            lions[playerIndex].printAdvisorStatsIfTheychoseTraining(AdvisorID); // prints the advisor's stats depending on the AdvisorID
            cout << "Note: you can only have 1 advisor at a time" << endl;
            lions[playerIndex].setPlayerBoardchoice(boardchoice); //sets the player choice
        }

        if (playerIndex == 0) //if it was the 1st player's turn
        {
            cout << "enter yes for the second player to choose their character" << endl;
            getline(cin,nextPlayerIsHere);
            while (nextPlayerIsHere != "yes") // if person entered something that wasn't yes
            {
                cout << "please enter yes:" << endl; //repeatedly ask them to enter yes until they decide to do so
                getline(cin,nextPlayerIsHere);
            }
        }
        playerIndex++; //increment it for the second player
        cout << endl;
        cout << endl;
        player1choice=choice;//Player1choice

        if(in==1){Player1BoardChoice=boardchoice;};//if it was the first player choosing, the set player1boardchoice=whatever board choice the 1st player selected
    }
    //outside of the while loop so only runs after both players have choosen their lion as well as where they would like to go
    if(Player1BoardChoice==boardchoice){ 
            return true; //return true if both players decided to go to the same place
        }
        else{
            return false; //they didn't go to the same place so return false
        }
}

bool Board::movePlayer(int player_index)
{
    // Increment player position
    _player_position[player_index]++;
    if (_player_position[player_index] == _BOARD_SIZE - 1)
    {
        // Player reached last tile
        return true;
    }
    return false;
}

void Board::movePlayerBackwards(int player_index){
    _player_position[player_index]--;
    if(_player_position[player_index]<0){
        _player_position[player_index]=0;
    }
}

int Board::getPlayerPosition(int player_index) const // gets the position of the player on the board
{
    if (player_index >= 0 && player_index <= _player_count)
    {
        return _player_position[player_index];
    }
    return -1;
}
string Board::getPlayerColor(int player_index, int pos)
{ // get the color of the tile the specified player is on depending on the position
    if (_tiles[player_index][pos].color == 'R')
    {
        return "Red";
    }
    else if (_tiles[player_index][pos].color == 'G')
    {
        return "Green";
    }
    else if (_tiles[player_index][pos].color == 'B')
    {
        return "Blue";
    }
    else if (_tiles[player_index][pos].color == 'U')
    {
        return "Purple";
    }
    else if (_tiles[player_index][pos].color == 'N')
    {
        return "Brown";
    }
    else if (_tiles[player_index][pos].color == 'P')
    {
        return "Pink";
    }
    else if (_tiles[player_index][pos].color == 'O')
    {
        return "Orange";
    }
    else if (_tiles[player_index][pos].color == 'Y')
    {
        return "Grey";
    }
    return "Wrong";
}

void Board::printMenu(bool didPlayersChooseSameBoard)
{
    
    int playerIndex = 0; // index of the current player's turn
    string player1RPSchoice="";
    string player2RPSchoice="";
    int sameSpaceRandomEvent=0;
    int TilesPlayerMovedDuringTurn=0;
    bool winner;
    bool didHidingGameEnd=false;
    bool didCountingGameEnd=false;
    string player1HidingSpot="";
    string player2guess="";
    string player1countingchoiceS="";
    string player2countingchoiceS="";
    int player1countingchoice=0;
    int player2countingchoice=0;
    int countingGameTotal=0;
    bool didRPSGameEnd=false;
    int player1Index=0;
    int player2Index=1;
    int NonActivePlayersIndex = 0;
    string choice = ""; // what the person wants to do
    string mufasaDiceChoiceS="";
    int actualChoice=0;
    int AdvisorID = 0;
    int valueRolled = 0;
    string valueRolledS="";
    int Player1Position = 0;
    int Player2Position = 0;
    string YorN = "Y";
    bool WasDiceRolled = false;  // checks to see if an action was taken
    bool didLoopRunOnce = false; // checks to see if the while loop ran once
    while (true)
    { // looked how to make an infinite loop in c++ and this is what popped up
        WasDiceRolled = false;
        if (playerIndex == 0 && didLoopRunOnce == true) // setted didLoopRunOnce to true for it to be the first players turn, if it wasn't there, then it would be the 2nd players turn as I initalized playerIndex to 1
        {                                               // playerIndex 0=1st player
            playerIndex = 1;                            // playerIndex is 1 so it would be the second player's turn
            NonActivePlayersIndex = 0;
        }
        else
        {
            NonActivePlayersIndex = 1;
            playerIndex = 0; // player index must be 1 so it would then go to 0 which is the 1st player's turn
        }
        if(didPlayersChooseSameBoard==true){
            player1Index=0;
            player2Index=0;
        }
        if (getPlayerColor(player1Index, Player1Position) == "Orange" && getPlayerColor(player2Index, Player2Position) == "Orange")
        { // if both players reached the end
            cout << "you both reached the end" << endl;
            break;
        }
        else if (getPlayerColor(player1Index, Player1Position) == "Orange")
        {
            cout << "Player 1 already reached the end" << endl;
            playerIndex = 1;           // if 1st player reached the end, doesn't take any more actions with player 1
            NonActivePlayersIndex = 0; // and only take actions with player 2
        }
        else if (getPlayerColor(player2Index, Player2Position) == "Orange")
        {
            cout << "Player 2 already reached the end" << endl; // if 2nd player reached the end, doesn't take any more actions with player 2
            playerIndex = 0;                                    // and only take actions with player 1
            NonActivePlayersIndex = 1;
        }
        if(getPlayerColor(player1Index, Player1Position)== "Blue"){
            playerIndex=0;
            NonActivePlayersIndex=1;
            cout<<"Player "<<playerIndex+1<<", since you landed on the blue tile, you get to go again"<<endl;
        }
        else if(getPlayerColor(player2Index,Player2Position)=="Blue"){
            playerIndex=1;
            NonActivePlayersIndex=0;
            cout<<"Player "<<playerIndex+1<<", since you landed on the blue tile, you get to go again"<<endl;
        }
        while (WasDiceRolled == false) // if this runs again, the person didn't roll the dice so it prints the menu again
        {
            TilesPlayerMovedDuringTurn=0;
            cout << "It is player " << playerIndex + 1 << "'s turn" << endl;
            cout << endl;
            cout << endl;
            cout << "Menu" << endl;
            cout << "Option 1: Check Player progress" << endl;
            cout << "Option 2: Review Character " << endl;
            cout << "Option 3:check position" << endl;
            cout << "option 4:review advisor" << endl;
            cout << "option 5:roll the dice" << endl;
            // cin >> choice;
            getline(cin,choice);
            while(choice!="1"&&choice!="2"&&choice!="3"&&choice!="4"&&choice!="5"){
                cout<<"please enter 1,2,3,4 or 5"<<endl;
                getline(cin,choice);
            }
            if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5")//if choice was valid
            {
                actualChoice = stoi(choice); //if the choice wasn't valid and it went into this ie input was some chars, it wouldn't work as strings can't be converted to ints
            }
            switch (actualChoice)
            {
            case 1:
                lions[playerIndex].printStatsMenu(playerIndex);
                //  print out only the leadership trait stats and the pride points
                cout << "Do you want to see the other players stats? enter Y or N" << endl;
                getline(cin,YorN);
                while (YorN != "Y" && YorN != "N")
                {
                    cout << "invalid input" << endl;
                    cout << "Do you want to see the other player's stats? enter Y or N" << endl;
                    getline(cin,YorN);
                }
                if (YorN == "Y")
                {
                    lions[NonActivePlayersIndex].printStatsMenu(NonActivePlayersIndex);
                    cout << endl;
                }
                break;

            case 2:
                // option 2 wants to print out the lions name and also their age
                cout << "Character name: " << lions[playerIndex].getName() << endl;
                cout << lions[playerIndex].getName() << "'s age: " << lions[playerIndex].getAge() << endl;
                break;

            case 3:             // check the position of the player
            if(didPlayersChooseSameBoard==false){
                displayBoard();
            }
                else{
                    displayBoardIfBothplayersChooseTheSamePosition();
                }
                break;

            case 4:
                AdvisorID = lions[playerIndex].getAdvisor();                 // get the advisor id
                if(AdvisorID==6){
                if(lions[playerIndex].printAdvisorStats(AdvisorID) == true&&AdvisorID==6){
                    cout<<"what would you like to roll? enter 1,2,3,4,5 or 6"<<endl;
                    getline(cin,mufasaDiceChoiceS);
                    while(mufasaDiceChoiceS!="1"&&mufasaDiceChoiceS!="2"&&mufasaDiceChoiceS!="3"&&mufasaDiceChoiceS!="4"&&mufasaDiceChoiceS!="5"&&mufasaDiceChoiceS!="6"){
                        cout<<"Please enter 1,2,3,4,5, or 6"<<endl;
                        getline(cin,mufasaDiceChoiceS);
                    }
                    valueRolled=stoi(mufasaDiceChoiceS);
                    cout<<"Player "<<playerIndex+1<<", you decided to roll a "<<valueRolled<<endl;
                    WasDiceRolled=true;
                    lions[playerIndex].getRidOfPlayersAdvisor(); //sets player's advisor to an invalid option
                }}
                else if (lions[playerIndex].printAdvisorStats(AdvisorID) == true) // if player has an advisor and decides to roll the dice
                {
                    valueRolled = lions[playerIndex].rollAdvisorDice(AdvisorID);               // sets value rolled equal to the random number generated from the advisor's dice
                    cout << "using your advisor's dice, you rolled a " << valueRolled << endl; // prints the value rolled
                    WasDiceRolled = true;
                    lions[playerIndex].getRidOfPlayersAdvisor(); // sets the player's advisor to -1 which isn't a valid advisorID
                }
                else
                {
                    WasDiceRolled = false; //didn't roll a dice, just looked to see what advisor they had
                }
                break;
            case 5:
                // roll the dice
                valueRolled = lions[playerIndex].rollDice();                                      // value rolled=random number from 1-6
                cout << "Player " << playerIndex + 1 << ", you rolled a " << valueRolled << endl; // prints value rolled
                WasDiceRolled = true;
                break;
            default:
                cout << "invalid option selected" << endl; // didn't select a # from 1-8
                break;
            }
        }
        didLoopRunOnce = true;
        if (WasDiceRolled == true)
        { // if player rolled the dice
            for (int i = 0; i < valueRolled; i++)
            {
                if (movePlayer(playerIndex) == true) //if player reached the end
                { // learned from CSEL that this if statement moves the player
                    cout << "You reached the end, wait for the other player to reach the end" << endl;
                    if (playerIndex == 0)//need to check which player index it is to see what to set at the end
                    {
                        Player1Position = 51; // CSEL made me realize that when the player reached the end, the player position wouldn't go to 51 so I added the 2 lines below on my own
                    }
                    else if (playerIndex == 1)
                    {
                        Player2Position = 51; 
                    }
                    break; // stops moving the player if the player is at the orange tile
                }
                else
                {
                    if (playerIndex == 0)
                    {                      // this is the first player
                        Player1Position++; // keep track of the 1st players postion to put into functions
                        TilesPlayerMovedDuringTurn++;
                    }
                    else
                    {
                        Player2Position++; // it is the second player's turn so this keep tracks of the 2nd player's index to put into functions
                        TilesPlayerMovedDuringTurn++;
                        //TilesPlayerMovedDuringTurn is to check how much spaces the player moved so the player can be dragged back if they land on the Hyena tile
                    }
                }
            }
            if(didPlayersChooseSameBoard==false){ // display the board after moving
                displayBoard();
            }
                else{
                    displayBoardIfBothplayersChooseTheSamePosition();
                } 
            //need the if else statement below to account for both players as player 1 has player1position and player 2 has player2position
            if(playerIndex==0){//it was the first player
                TileEffects(playerIndex,Player1Position,TilesPlayerMovedDuringTurn,playerIndex);
                if(getPlayerColor(player1Index,Player1Position)=="Brown"){
                    Player1Position-=TilesPlayerMovedDuringTurn; //decrement the player position by the amount moved that turn
                }
                 if(getPlayerColor(player1Index,Player1Position)=="Red"){ 
                    Player1Position-=10; //decrement the player position by 10 as the red moves the player back 10 spaces
                    if(Player1Position<0){
                        Player1Position=0; //if player is off the board, set the player position equal to 0(start of the board)
                    }
                }
            }
            else{ //it was the second player
                TileEffects(player2Index,Player2Position,TilesPlayerMovedDuringTurn,playerIndex);
                if(getPlayerColor(player2Index,Player2Position)=="Brown"){ 
                    Player2Position-=TilesPlayerMovedDuringTurn; //decrement the player position by the amount they moved that turn as that is what the Hayenas do
                }
                if (getPlayerColor(player2Index, Player2Position) == "Red")
                {
                    Player2Position-=10; //decrement the player position by 10 as the red space moves the player back 10 spaces
                    if(Player2Position<0){
                        Player2Position=0; //would be off the board so set it equal to 0   
                    }
                }
            }
        }
                if (getPlayerColor(player1Index, Player1Position) == "Orange" && getPlayerColor(player2Index, Player2Position) == "Orange")
        { // if both players reached the end
            cout << "you both reached the end" << endl;
            break;
        }
        if(Player1Position==Player2Position&&Player2Position>0){ //if the position is the same and they are beyond the gray tile
        cout<<" you both are on the same tile"<<endl;
        cout<<" since both of you can't share a tile, you will have to battle by playing a minigame "<<endl;
        sameSpaceRandomEvent=rand()%3; //gets a number between 0,1,2
        if(sameSpaceRandomEvent==0){ //rock paper,scissors game
            cout<<"You will be playing Rock, Paper Scissors"<<endl;
            cout<<"remember, rock beats scissors, paper beats rock, and scissor beats paper"<<endl;
            cout<<"this will be a best of 1"<<endl;
            while(didRPSGameEnd==false){
            cout<<"Player 1: enter R for rock, P for paper, or S for scissors"<<endl;
            cout<<"please enter R,P, or S"<<endl;
            getline(cin,player1RPSchoice);
            while(player1RPSchoice!="R"&&player1RPSchoice!="S"&&player1RPSchoice!="P"){
                cout<<"Please enter R,P, or S"<<endl;
                getline(cin,player1RPSchoice);
            }
            for(int i=0;i<50;i++){
                cout<<"above is the first player's input, please don't scroll up or that ruins the game and that is uncharacteristic of a great lion leader"<<endl; //supposed to make a bunch of lines to hide the 1st players input
            }
            cout<<"Player 2: enter R for rock, P for paper, or S for scissors"<<endl;
            getline(cin,player2RPSchoice);
            while(player2RPSchoice!="R"&&player2RPSchoice!="S"&&player2RPSchoice!="P"){
                cout<<"Please enter R,P, or S"<<endl;
                getline(cin,player2RPSchoice);
            }
            if(player1RPSchoice==player2RPSchoice){
                cout<<"it was a tie, therefore it will continue again"<<endl;
            }
            else if(player1RPSchoice=="R"&&player2RPSchoice=="S"){
                cout<<"Rock beats scissors, player 1 wins"<<endl;
                didRPSGameEnd=true;
                winner=true;
            }
            else if(player2RPSchoice=="R"&&player1RPSchoice=="S"){
                cout<<"Rock beats scissors, player 2 wins"<<endl;
                didRPSGameEnd=true;
                winner=false;
            }
            else if(player1RPSchoice=="S"&&player2RPSchoice=="P"){
                cout<<"Scissors beats paper player 1 wins"<<endl;
                didRPSGameEnd=true;
                winner=true;
            }
            else if(player2RPSchoice=="S"&&player1RPSchoice=="P"){
                cout<<"Scissors beats paper player 2 wins"<<endl;
                didRPSGameEnd=true;
                winner=false;
            }
            else if(player1RPSchoice=="P"&&player1RPSchoice=="R"){
                cout << "Paper beats rock, Player 1 wins" << endl;
                didRPSGameEnd=true;
                winner=true;
            }
            else{
                cout<<"Paper beats rock, player 2 wins"<<endl;
                didRPSGameEnd=true;
                winner=false;
            }
            }
        }
        else if(sameSpaceRandomEvent==1){ //counting game
            cout<<"You will be playing a counting game"<<endl;
            cout<<"Here are the rules, you can choose a number from 1-3"<<endl;
            cout << "Then the score will be added, whoever counts to 20 loses" << endl;
            while(didCountingGameEnd==false){
            cout << "Player 1, please enter 1,2, or 3" << endl;
            getline(cin, player1countingchoiceS);
            while (player1countingchoiceS != "1" && player1countingchoiceS != "2" && player1countingchoiceS != "3")
            {
                cout << "Please enter 1,2, or 3" << endl;
                getline(cin, player1countingchoiceS);
            }
                player1countingchoice=stoi(player1countingchoiceS);
                countingGameTotal+=player1countingchoice;
                cout<<"counting score so far:"<<countingGameTotal<<endl;
                if(countingGameTotal>=20){
                    cout<<"player 1, you lost"<<endl;
                    winner=false;
                    didCountingGameEnd=true;
                    continue;
                }
                cout<<"Player 2, please enter 1,2, or 3"<<endl;
                getline(cin,player2countingchoiceS);
                while(player2countingchoiceS!="1"&&player2countingchoiceS!="2"&&player2countingchoiceS!="3"){
                    cout<<"Please enter 1,2, or 3"<<endl;
                    getline(cin,player2countingchoiceS);
                }
                player2countingchoice=stoi(player2countingchoiceS);
                countingGameTotal+=player2countingchoice;
                cout<<"Counting score so far:"<<countingGameTotal<<endl;
                if(countingGameTotal>=20){
                    cout<<"Player 2, you lost"<<endl;
                    winner=true;
                    didCountingGameEnd=true;
                }
            }
        }
        else{ //hiding game
            cout<<"You will be playing a simple hiding game"<<endl;
            cout<<"player 1 will choose a spot to hide from 3 different spots, then player 2 will have 2 chances to find player 1"<<endl;
            while(didHidingGameEnd==false){
            cout<<"Player 1, enter either G(to hide in grass), T(to hide in tree) or R(to hide in river)"<<endl;
            getline(cin,player1HidingSpot);
            while(player1HidingSpot!="G"&&player1HidingSpot!="T"&&player1HidingSpot!="R"){
                cout<<"please enter G,T, or R"<<endl;
                getline(cin,player1HidingSpot);
            }
            for(int i=0;i<50;i++){
                cout<<"above is the first player's input, please don't scroll up or that ruins the game and that is uncharacteristic of a great lion leader"<<endl; //supposed to make a bunch of lines to hide the 1st players input
            }
            cout<<"Player 2, please enter G(to look in the grass),T(to climb trees), or R(to look in the river)"<<endl;
            getline(cin,player2guess);
            if(player2guess==player1HidingSpot){
                cout<<"congrats, you found player 1"<<endl;
                didHidingGameEnd=true;
                winner=false;
            }
            else{
                cout<<"Player 2, your choice was wrong, you have 1 more chance to find player 1"<<endl;
                cout<<"Player 2, please enter G(to look in the grass),T(to climb trees), or R(to look in the river)"<<endl;
                getline(cin,player2guess);
                if(player2guess==player1HidingSpot){
                    cout<<"Congrats player 2, you found player 1"<<endl;
                    didHidingGameEnd=true;
                    winner=false;
                }
                else{
                        cout<<"Too bad, player 2, player 1 was hiding in the "<<player1HidingSpot<<endl;
                        didHidingGameEnd=true;
                        winner=true;
                    }
            }
            }
        }
        if(winner==true){
            cout<<"Player 1, since you won, you gain 200 wisdom points"<<endl;
            lions[0].increaseWisdom(200);
            cout<<"Player 2, since you lost, you have to move back 1 space"<<endl;
            Player2Position--;
            if(Player2Position>0){
            movePlayerBackwards(1);}//can't move into negative spaces
            else{
                Player2Position=0;
            }
        }
        else{
            cout<<"Player 2, since you won, you gain 200 wisdom points"<<endl;
            lions[1].increaseWisdom(200);
            cout<<"Player 1, since you lost, you have to move back 1 space"<<endl;
            Player1Position--;
            if(Player1Position>0){movePlayerBackwards(0);} //doesn't move player back if they were at the start and they lost
            else{
                Player1Position = 0;//set player 1 position=0 if they are out of the board
            }
        }
        didHidingGameEnd=false;
        countingGameTotal=0; //reset so it can actually be played again
        didRPSGameEnd=false;
        didCountingGameEnd=false;
        }
    }
}
void Board::endGame()
{
    int winnerIndex = 0;
    int loserIndex = 0;
    int totalPlayer1 = 0;
    int totalPlayer2 = 0;
    int timesLoopRan = 0;
    string enterYesTocontinue="";
    string enterNextTocontinue="";
    cout << "The journey has been long, you have faced a lot of challenges but you also made lots of friends" << endl;
    cout << "However, there can only be one lion who can become the next pride leader" << endl;
    cout << "for every 100 points in Stamina, Strength, or wisdom, you will get an additonal 1,000 pride points for your demonstrated leadership" << endl;
    cout<<"enter yes to continue "<<endl;
    getline(cin,enterYesTocontinue);
    while(enterYesTocontinue!="yes"){
        cout<<"Please enter yes to continue"<<endl;
        getline(cin,enterYesTocontinue);
    }
    for (int i = 0; i < 2; i++)
    {
        while (lions[i].getStamina() >= 100)
        {
            lions[i].setPridePoints(lions[i].getPridePoints() + 1000); // add 1000 to pride points
            lions[i].setStamina(lions[i].getStamina() - 100);          // reduce stamina by 100 each time
            timesLoopRan++;
        }
        cout << "Player " << i + 1 << ": you gained " << timesLoopRan * 100 << " points from excess stamina" << endl;
        timesLoopRan = 0;
        while (lions[i].getStrength() >= 100)
        {
            lions[i].setPridePoints(lions[i].getPridePoints() + 1000); // add 1k to pride points
            lions[i].setStrength(lions[i].getStrength() - 100);        // subtract 100 from strength
            timesLoopRan++;
        }
        cout << "Player " << i + 1 << ": you gained " << timesLoopRan * 100 << " points from excess strength" << endl;
        timesLoopRan = 0;
        while (lions[i].getWisdom() >= 100)
        {
            lions[i].setPridePoints(lions[i].getPridePoints() + 1000); // add 1k to pride points
            lions[i].setWisdom(lions[i].getWisdom() - 100);            // subtract 100 wisdom
            timesLoopRan++;
        }
        cout << "Player " << i + 1 << ": you gained " << timesLoopRan * 100 << " points from excess wisdom" << endl;
        timesLoopRan = 0;
        cout << endl;
    }
    // above nested loop is to convert leadership traits into pride points, add 1 to i as i is the index so need to add 1 to get the player number
    cout<<"The points have been calculated please enter next to see the results"<<endl;
    getline(cin,enterNextTocontinue);
    while(enterNextTocontinue!="next"){
        cout<<"Please enter next to see the results"<<endl;
        getline(cin,enterNextTocontinue);
    }
    if (lions[0].getPridePoints() > lions[1].getPridePoints())
    {                    // if player 1 has more pride points than the 2nd player
        winnerIndex = 0; // winner index is 0 because that array corresponds to the first player
        loserIndex = 1;
    }
    else if (lions[0].getPridePoints() < lions[1].getPridePoints())
    {                    // if player 2 has more pride points than the 1st player
        winnerIndex = 1; // winner index is 1 because that array corresponds to the second player
        loserIndex = 0;
    }
    else if (lions[0].getPridePoints() == lions[1].getPridePoints())
    { // if both players have the same pride points
        winnerIndex = -1;
    }
    if (winnerIndex != -1)
    { // if the score isn't tied
        cout << "With a total of " << lions[winnerIndex].getPridePoints() << ": the new pride leader is " << lions[winnerIndex].getName() << "!" << endl;
        cout << "Check results.txt for more information" << endl;
        ofstream write("results.txt");
        write << "Winner: Player " << winnerIndex + 1 << ", lion's name: " << lions[winnerIndex].getName() << ", age: " << lions[winnerIndex].getAge() << ", Total pride points:" << lions[winnerIndex].getPridePoints() << endl;
        write << "Loser: Player " << loserIndex + 1 << ", lion's name: " << lions[loserIndex].getName() << ", age: " << lions[loserIndex].getAge() << ", Total pride points:" << lions[loserIndex].getPridePoints() << endl;
    }
    else
    {
        cout << "It was a tie in pride points, the tiebreaker would be determined by who has the most total combined leadership points" << endl;
        cout << "Player 1's strength: " << lions[0].getStrength() << endl;
        cout << "Player 1's stamina: " << lions[0].getStamina() << endl; // whoever has the most combined leadership traits wins in the case of the same pride points
        cout << "player 1's wisdom: " << lions[0].getWisdom() << endl;
        totalPlayer1 = lions[0].getStamina() + lions[0].getStrength() + lions[0].getWisdom();
        cout << "Total combined leadership traits for player 1:" << totalPlayer1 << endl;
        totalPlayer2 = lions[1].getStamina() + lions[1].getStrength() + lions[1].getWisdom();
        cout << "Player 2's strength: " << lions[1].getStrength() << endl;
        cout << "Player 2's stamina: " << lions[1].getStamina() << endl;
        cout << "player 2's wisdom: " << lions[1].getWisdom() << endl;
        cout << "Total combined leadership traits for player 2: " << totalPlayer2 << endl;
        // adds all the leadership traits together

        if (totalPlayer1 > totalPlayer2)
        {
            winnerIndex = 0;
            loserIndex = 1;
        }
        else if (totalPlayer1 < totalPlayer2)
        {
            winnerIndex = 1;
            loserIndex = 0;
        }
        else
        {
            winnerIndex = -1;
        }
        if (winnerIndex != -1)
        { // players didn't tie
            cout << "With a total of " << lions[winnerIndex].getPridePoints() << " The new pride leader is " << lions[winnerIndex].getName() << "!" << endl;
            cout << "Check results.txt for more information" << endl;
            ofstream write("results.txt");
            write << "Winner: Player " << winnerIndex + 1 << " lion's name: " << lions[winnerIndex].getName() << ", age: " << lions[winnerIndex].getAge() << ", Total pride points:" << lions[winnerIndex].getPridePoints() << endl;
            write << "Loser: Player " << loserIndex + 1 << " lion's name: " << lions[loserIndex].getName() << ", age: " << lions[loserIndex].getAge() << ", Total pride points:" << lions[loserIndex].getPridePoints() << endl;
        }
        else
        { // players tied
            cout << "It was still a tie, a rare event, congrats to both players!" << endl;
            cout << "Check results.txt for more information" << endl;
            ofstream write("results.txt");
            write << "It was a tie" << endl;
            write << "You both scored a total of " << lions[0].getPridePoints() << " pride points and a total of " << totalPlayer1 << " combined leadership traits!" << endl;
        }
    }
}
