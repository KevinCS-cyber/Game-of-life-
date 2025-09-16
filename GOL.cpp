#include"GOL.h"
Player::Player(){
    _name="";
    _age=1;
    _stamina=100;
    _strength=100;
    _wisdom=100;
    _pride_points=0;
}
Player::Player(string name, int strength, int stamina, int wisdom){
    _pride_points=0;
    _age=1;
    _name=name;
    if(strength>=100 && strength<=1000){
        _strength=strength;
    }
    else{
        _strength=100;
    }
    if(stamina>=100 && stamina<=1000){
        _stamina=stamina;
    }
    else{
        _stamina=100;
    }
    if(wisdom>=100 && wisdom<=1000){
        _wisdom=wisdom;
    }
    else{
        _wisdom=100;
    }
}
string Player::getName(){
    return _name;
}
int Player::getStrength(){
    return _strength;
}
int Player::getStamina(){
    return _stamina;
}
int Player::getWisdom(){
    return _wisdom;
}
int Player:: getAge(){
    return _age;
}
int Player::getAdvisor(){
    return _advisor;
}

int Player::getPridePoints(){
    return _pride_points;
}
void Player::setName(string name){
    _name=name;
}
void Player::setStrength(int strength){
    _strength=strength;
}
void Player::setStamina(int stamina){
    _stamina=stamina;
}
void Player::setWisdom(int wisdom){
    _wisdom=wisdom;
}
void Player::setPridePoints(int pride_points){
    _pride_points=pride_points;
}
void Player:: setAge(int age){
    _age=age;
}
void Player:: setAdvisor(){
    int advisorNum=rand()%5+1; //1-5
    _advisor=advisorNum;
}
void Player::trainCub(int strength, int stamina, int wisdom){
    _strength+=strength;
    _stamina+=stamina;
    _wisdom+=wisdom;
    _pride_points-=5000;
}
void Player::toCubTraining(){
    _pride_points-=5000;
    _stamina+=500;
    _strength+=500;
    _wisdom+=1000;
}

void Player::toPrideLands(){
    _pride_points+=5000;
    _strength+=200;
    _wisdom+=200;
    _stamina+=200;
}

void Player::printStats(int i){
cout<<"player "<<i<<"'s Stats:"<<endl;
cout<<_name<<", "<<_age<<" year(s) old"<<endl;
cout<<"Strength: "<<_strength<<endl;
cout<<"Stamina: "<<_stamina<<endl;
cout<<"Wisdom: "<<_wisdom<<endl;
cout<<"Pride points: "<<_pride_points<<endl;
}

void Player::printStatsMenu(int i){
cout<<"player "<<i+1<<"'s Stats:"<<endl;
cout<<"Strength: "<<_strength<<endl;
cout<<"Stamina: "<<_stamina<<endl;
cout<<"Wisdom: "<<_wisdom<<endl;
cout<<"Pride points: "<<_pride_points<<endl;
}

void Player::increaseWisdom(int incrementAmount){
    setWisdom(getWisdom()+incrementAmount);
}
void Player::increaseStamina(int incrementAmount){
    setStamina(getStamina()+incrementAmount);
}
void Player::increaseStrength(int incrementAmount){
    setStrength(getStrength()+incrementAmount);
}

void Player::decreaseWisdom(int decrementAmount){
    setWisdom(getWisdom()-decrementAmount);
}
void Player::decreaseStamina(int decrementAmount){
    setStamina(getStamina()-decrementAmount);
}
void Player::decreaseStrength(int decrementAmount){
    setStrength(getStrength()-decrementAmount);
}
void Player::increasePridePoints(int incrementAmount){
    setPridePoints(getPridePoints()+incrementAmount);
}
void Player::decreasePridePoints(int decrementAmount){
    setPridePoints(getPridePoints()-decrementAmount);
}

void Player::setPlayerBoardchoice(string type){
    _boardchoice=type;
}

string Player::getPlayerBoardchoice(){
    return _boardchoice;
}
// int Player::move(int rollValue){
//     //ask how to roll based on a board
// }


void Player::printAdvisorStatsIfTheychoseTraining(int advisor){
    if(advisor==1){
        cout<<"Name: Rafiki"<<endl;
        cout<<"unique ability: invisibility"<<endl;
        cout<<"dice: 4-6"<<endl;
    }
    else if(advisor==2){
        cout<<"Name: Nala"<<endl;
        cout<<"unique ability: night vision"<<endl;
        cout<<"dice: 1-3"<<endl;
    }
    else if(advisor==3){
        cout<<"Name: Sarabi"<<endl;
        cout<<"unique ability: energy manipulation"<<endl;
        cout<<"dice: 1-8"<<endl;
    }
    else if(advisor==4){
        cout<<"Name: Zazu"<<endl;
        cout<<"unique ability: weather control"<<endl;
        cout<<"dice: 0-1"<<endl;
    }
    else if(advisor==5){
        cout<<"Name: Sarafina"<<endl;
        cout<<"unique ability: super speed"<<endl;
        cout<<"dice: 1 or 6(can only roll 1 or 6)"<<endl;
    }
    else if(advisor==6){
        cout<<"Name: Mufasa's spirit"<<endl;
        cout<<"unique ability: godly powers(stops every negative effects)"<<endl;
        cout<<"dice: choice:1,2,3,4,5,6(can choose what to roll from 1-6)"<<endl;
    }
}

void Player::getRidOfPlayersAdvisor(){
    _advisor=-1;
}

bool Player::printAdvisorStats(int advisor){
    string choice="";
    bool haveAdvisor=true; //bool to check if the player has an advisor or not
    if(advisor==1){
        cout<<"Name: Rafiki"<<endl;
        cout<<"unique ability: invisibility"<<endl;
        cout<<"dice: 4-6"<<endl;
    }
    else if(advisor==2){
        cout<<"Name: Nala"<<endl;
        cout<<"unique ability: night vision"<<endl;
        cout<<"dice: 1-3"<<endl;
    }
    else if(advisor==3){
        cout<<"Name: Sarabi"<<endl;
        cout<<"unique ability: energy manipulation"<<endl;
        cout<<"dice: 1-8"<<endl;
    }
    else if(advisor==4){
        cout<<"Name: Zazu"<<endl;
        cout<<"unique ability: weather control"<<endl;
        cout<<"dice: 0-1"<<endl;
    }
    else if(advisor==5){
        cout<<"Name: Sarafina"<<endl;
        cout<<"unique ability: super speed"<<endl;
        cout<<"dice: 1 or 6"<<endl;
    }
    else if(advisor==6){
        cout<<"Name: Mufasa's spirit"<<endl;
        cout<<"unique ability: godly powers(stops every negative effect!)"<<endl;
        cout<<"dice: choice from 1,2,3,4,5,6(can choose what to roll from 1-6)"<<endl;
    }
    else{
        cout<<"You don't have an advisor"<<endl;
        return false;
    }
    if(haveAdvisor==true){
    cout<<"Do you want to use your advisor's dice?(Y/N)"<<endl;
    cout<<"Note, if you decide to roll your advisors dice, you will lose your advisor"<<endl;
    cout<<"and have to do the journey alone unless you get another advisor"<<endl;
    cout<<"enter Y or N"<<endl;
    getline(cin,choice);
    while(choice!="Y"&&choice!="N"){
        cout<<"Please enter Y or N"<<endl;
        
        cin>>choice;}
    }
    if(choice=="Y"){
        //roll advisor's dice
        return true;
    }
    else if(choice=="N"){
        return false;
    }
    return true;
    }

void Player::setAdvisorEqualToMufasasSpirit(){
    _advisor=6;
}

int Player::rollDice(){
    int value=rand() %6+1; //possible values are 0-5 therefore need to add 1 so it works
    return value;
}

int Player::rollAdvisorDice(int i){
    int rollValue=0;
    int temp=0; //need for the 1 or 6 dice
    switch(i){
        case 1:
        rollValue=rand()%3+4; 
        return rollValue;
        break;
        case 2:
        rollValue=rand()%3+1; 
        return rollValue;
        case 3:
        rollValue=rand()%8+1;
        return rollValue;
        case 4:
        rollValue=rand()%2;
        return rollValue;
        case 5:
        temp=rand()%2;
        if(temp==0){
            rollValue=1;
        }
        else{
            rollValue=6;
        }
        return rollValue;
    }
    return 1;
}


