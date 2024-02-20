#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<iomanip>

using namespace std;

class Equipment{
	int hpmax;
	int atk;
	int def;
	public:
		Equipment(int,int,int);
		vector<int> getStat();			
};

class Unit{
		string name;
		string type;		
		int hp;
		int hpmax, hpmaxog;
		int atk, atkog;
		int def, defog;
		bool guard_on;
		bool dodge_on; 
		Equipment *equipment; 
	public:			
		Unit(string,string); 
		void showStatus();
		void newTurn();
		int attack(Unit &);
		int ultimateAttack(Unit &); 
		int beAttacked(int);
		int heal();	
		void guard();
		void dodge(); 
		bool isDead();
		void equip(Equipment *);  
};

Unit::Unit(string t,string n){ 
	type = t;
	name = n;
	if(type == "Hero"){
		hpmax = rand()%20+120;
		atk = rand()%5+14;
		def = rand()%3+9;
	}else if(t == "Monster"){
		hpmax = rand()%20+250;
		atk = rand()%5+25;
		def = rand()%3+5;
	}
	hp = hpmax;	
	guard_on = false;
	equipment = NULL;
	dodge_on = false;
	hpmaxog = hpmax;
	atkog = atk;
	defog = def;
}

void Unit::showStatus(){
	if(type == "Hero"){
		cout << "---------------------------------------\n"; 
		cout << name << "\n"; 
		cout << "HP: " << hp << "/" << hpmax << "\tATK: "<< atk << "\t\tDEF: "<< def;		
		cout << "\n---------------------------------------\n";
	}	
	else if(type == "Monster"){
		cout << "\t\t\t\t---------------------------------------\n"; 
		cout << "\t\t\t\t" << name << "\n"; 
		cout << "\t\t\t\tHP: " << hp << "\t\tATK: "<< atk << "\t\tDEF: "<< def;
		cout << "\n\t\t\t\t---------------------------------------\n";
	}
}

Equipment::Equipment(int hp,int atkp,int defp){
    hpmax = hp;
	atk = atkp;
	def = defp;
}

vector<int> Equipment::getStat(){
	vector<int> equipment;
	equipment.push_back(hpmax);
	equipment.push_back(atk);
	equipment.push_back(def);
	return equipment;
}

void Unit::equip(Equipment *equipment){
			hpmax = hpmaxog ;
			atk = atkog ;
			def = defog ;
			if(hp > hpmax)
					hp = hpmax;
			vector<int> equipmentState = equipment->getStat();
			hpmax += equipmentState[0];
			atk += equipmentState[1];
			def += equipmentState[2];
}


void Unit::newTurn(){
	guard_on = false; 
	dodge_on = false;
}

int Unit::beAttacked(int oppatk){
	int dmg;
	if(oppatk > def){
		dmg = oppatk-def;	
		if(guard_on) dmg = dmg/3;
		if(dodge_on){
		    int x = rand()%2;
		    if(x == 0){
		        dmg = 0;}
		    else {dmg = 2*dmg;}	
		    }	        
	}	
	hp -= dmg;
	if(hp <= 0){hp = 0;}
	
	return dmg;	
}

int Unit::attack(Unit &opp){
	return opp.beAttacked(atk);
}
int Unit::ultimateAttack(Unit &opp){
	return opp.beAttacked(2*atk);
}
int Unit::heal(){
	int h = rand()%21 + 10;
	if(hp + h > hpmax) h = hpmax - hp;
	hp = hp + h;
	return h;
}
void Unit::dodge(){
    dodge_on = true;
}

void Unit::guard(){
	guard_on = true;
}	

bool Unit::isDead(){
	if(hp <= 0) return true;
	else return false;
}

void drawScene(char p_action,int p,char m_action,int m){
	cout << "                                                       \n";
	if(p_action == 'A'){
	cout << "                                       "<< -p <<"\n";
	}else{
	cout << "                                                       \n";	
	}	
	cout << "                                *               *      \n";
	cout << "                                **  *********  **      \n";
	cout << "                                ****         ****      \n";
	if(m_action == 'A'){
	cout << "                 " << setw(5) << -m << "           *** **   ** ***       Attack!\n";
	}else if(m_action == 'G'){
	cout << "                                 *** **   ** ***       Guard!\n";
	}else if(m_action == 'D'){
	cout << "                                 *** **   ** ***       Dodge!\n";
	}else if(m_action == 'U'){
	cout << "                 " << setw(5) << -m << "           *** **   ** ***       Ultimate Attack!\n";
	}else{
	cout << "                                 *** **   ** ***       \n";	
	}
	cout << "                                  ** **   ** **        \n";
	cout << "                   ***             *         *         \n";
	if(p_action == 'A'){
	cout << "        Attack!    ***  *           *********          \n";		
	}else if(p_action == 'H'){
	cout << "      Heal! +" << setw(2) << p << "    ***  *           *********          \n";
	}else if(p_action == 'G'){
	cout << "         Guard!    ***  *           *********          \n";
	}else if(p_action == 'D'){
	cout << "         Dodge!    ***  *           *********          \n";
	}else{
	cout << "                   ***  *           *********          \n";	
	}
	cout << "                    *  *       ***  *  *  *            \n";
	cout << "                  *****           **   *   *           \n";
	cout << "                    *                  *    ***        \n";
	cout << "                   * *               **        *       \n";
	cout << "                  *   *                                \n";
	cout << "                                                       \n";
};


void playerWin(){	
	cout << "*******************************************************\n";
	for(int i = 0; i < 3; i++) cout << "*                                                     *\n";
	cout << "*                   YOU WIN!!!                        *\n";
	for(int i = 0; i < 3; i++) cout << "*                                                     *\n";
	cout << "*******************************************************\n";
};


void playerLose(){
	cout << "*******************************************************\n";
	cout << "*                                                     *\n";
	cout << "*                   YOU LOSE!!!                       *\n";
	cout << "*                                                     *\n";
	cout << "*******************************************************\n";
};

  
int main(){
	srand(time(0));
	
	string name;	
	cout << "Please input your name: ";
	getline(cin,name);	
	Unit hero("Hero",name);
	
	Equipment sword(0,8,4);
	Equipment axes(0,16,-3);
	Equipment shield(0,-1,7);
	Equipment armor(25,-2,2);
	
	char eq;	
	cout << " [1] Sword \n [2] Axes \n [3] Shield \n [4] Armor \n";
	cout << "Please selet your equipment: ";
	cin >> eq;
	
	if(eq == '1') hero.equip(&sword);
		else if(eq == '2') hero.equip(&axes);
		else if(eq == '3') hero.equip(&shield);
		else if(eq == '4') hero.equip(&armor);
	
	Unit mons("Monster","Kraken");
	
	int turn_count = 1;
	char player_action = '\0',monster_action = '\0';
	int p = 0, m = 0;
	while(true){
		mons.newTurn();	
		hero.newTurn();			
		mons.showStatus();
		drawScene(player_action,p,monster_action,m);
		hero.showStatus();		
		cout << "[A] Attack [H] Heal [G] Guard [D] Dodge [C] Change Equipment [E] Exit";
		cout << "\n[Turn " << turn_count << "] Enter your action: ";
		cin >> player_action;
		player_action = toupper(player_action);
		if(player_action == 'E') break; 
		
		int temp = rand()%5;
		if(temp <= 1) monster_action = 'A';
		else if(temp == 2) monster_action = 'G';
		else if(temp == 3) monster_action = 'D';
		else if(temp == 4) monster_action = 'U';
		
		if(player_action == 'G') hero.guard();
		if(monster_action == 'G') mons.guard();
		
		if(player_action == 'D') hero.dodge();
		if(monster_action == 'D') mons.dodge();
		
		if(player_action == 'H') p = hero.heal();
		
		if(player_action == 'C'){
			char eq;	
			cout << " [1] Sword \n [2] Axes \n [3] Shield \n [4] Armor \n";
			cout << "Please select your equipment: ";
			cin >> eq;
		
		if(eq == '1') hero.equip(&sword);
			else if(eq == '2') hero.equip(&axes);
			else if(eq == '3') hero.equip(&shield);
			else if(eq == '4') hero.equip(&armor);
			
		}
		
		if(player_action == 'A') p = hero.attack(mons); 
		if(monster_action == 'A') m = mons.attack(hero); 
		if(monster_action == 'U') m = mons.ultimateAttack(hero); 
		
		if(hero.isDead()){
			drawScene(player_action,p,monster_action,m);
			playerLose();
			break; 
		}
		
		if(mons.isDead()){
			drawScene(player_action,p,monster_action,m);
			playerWin();
			break; 
		}
		
		turn_count++;
	}
	return 0;
}
