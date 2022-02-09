#include <iostream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Player {
	public:
		int plife = 10;
		float pAttack;
		
		float getAttackValue(void){
			srand(time(0));
			pAttack = rand() % 6 + 1;
			return pAttack;
		}
};

class Master : public Player {
	public:
		int doubleAttack(void){
			char input;
			float sAttack, mAttack;
			cout << "Do you want to use Master's double attack (Y/N): ";
			cin >> input;
			
			if(input == 'y'){
				sAttack = pAttack * 2;
				plife = 0;
			}
			else if(input == 'n'){;
			}
			return sAttack;
		}
};

class Healer : public Player {
	public:
		int wLife;
		int HealerAbility = 1;
		int HealerAttack = 1;
		
		float restoreWarrior(int healeratk, int& wLife){
			char input;
			cout << "Do you want to use Healers healing power (Y/N): ";
			cin >> input;
			
			if(input == 'y' && HealerAbility == 1){
				HealerAbility = 0;
				wLife = 10;
				HealerAttack = healeratk / 2;
				cout << "\nHealing Power Activated! Warrior Life Restored! " << endl;
				cout << "\n***Healer Attack = " << healeratk << " /2 = " << HealerAttack << endl;
			}
			else if(input == 'n'){
				HealerAttack = healeratk;
				cout << "\n***Healer Attack = " << HealerAttack << endl;				
			}
			else if(HealerAbility == 0){
				HealerAbility = 0;
				cout << "\nHealing Power already used! " << endl;
				HealerAttack = healeratk;
				cout << "\n***Healer Attack = " << HealerAttack << endl;
			}
			return HealerAttack;
		}
};

class Warrior : public Player {
};

class Monster{
	public:
		int mlife = 30;
		float mAttack;
		
		float getMAttackValue(void){
			mAttack = rand() % 6 + 1;
		}
};

int Damage(int incoming, int health){
	health = health - incoming;
	if(health < 0){
		health = 0;
	}
	return health;
}

int main(){
	
	Master mp;
	Healer hp;
	Warrior wp;
	Monster x;
	
	int round = 1;
	char choice;
	
	while (mp.plife != 0 && hp.plife != 0 && wp.plife != 0 or x.mlife != 0){
			
		cout << "\n\n======== ROUND " << round << " ========" << endl;
		round = round + 1;
		
		cout << " Choose a player (m, h, w): ";
		cin >> choice;
		
		if(choice == 'm'){
			if(mp.plife != 0){
			mp.pAttack = mp.getAttackValue();
			x.mAttack = x.getMAttackValue();
			
			int doubleattack, playerlivehp, monsterlivehp;
			
			doubleattack = mp.doubleAttack();
			
			playerlivehp = Damage(x.mAttack, mp.plife);
			monsterlivehp = Damage(doubleattack, x.mlife);
			x.mlife = monsterlivehp;
			mp.plife = playerlivehp;
			
			cout << "\n***Masters Attack: " << doubleattack << endl;
			cout << "***Monsters Attack: " << x.mAttack << endl;
			
			if(mp.plife == 0){
			cout << "\nMaster has died :( " << endl;
			}
			
			cout << "\nLife Status: " << " M = " << mp.plife << " H = " << hp.plife << " W = " << wp.plife << ";  Monster = " << x.mlife << endl;		
		}else{
			cout << "\nMaster is dead, unlucky" << endl;
		}
		}
		
		if(choice == 'h'){
			if(hp.plife != 0){
			hp.pAttack = hp.getAttackValue();
			x.mAttack = x.getMAttackValue();
			
			int playerlivehp, HealerAttack, monsterlivehp;
			
			HealerAttack = hp.restoreWarrior(hp.pAttack, wp.plife);
			
			playerlivehp = Damage(x.mAttack, hp.plife);
			monsterlivehp = Damage(HealerAttack, x.mlife);
			hp.plife = playerlivehp;
			x.mlife = monsterlivehp;
			
			cout << "***Monsters Attack: " << x.mAttack << endl;
			
			if(hp.plife == 0){
			cout << "\nHealer has died :( " << endl;
			}
			
			cout << "\nLife Status: " << " M = " << mp.plife << " H = " << hp.plife << " W = " << wp.plife << ";  Monster = " << x.mlife << endl;	
		}else{
			cout << "\nHealer is dead! HAHAHAHA" << endl;
		}
		}
		
		if(choice == 'w'){
			if(wp.plife != 0){
			wp.pAttack = wp.getAttackValue();
			x.mAttack = x.getMAttackValue();
			
			int playerlivehp, monsterlivehp;
			
			playerlivehp = Damage(x.mAttack, wp.plife);
			monsterlivehp = Damage(wp.pAttack, x.mlife);
			wp.plife = playerlivehp;
			x.mlife = monsterlivehp;
			
			cout << "\n***Warriors Attack: " << wp.pAttack << endl;
			cout << "***Monsters Attack: " << x.mAttack << endl;
			
			if(wp.plife == 0){
				cout << "\nWarrior has died :( " << endl;
			}
			
			cout << "\nLife Status: " << " M = " << mp.plife << " H = " << hp.plife << " W = " << wp.plife << ";  Monster = " << x.mlife << endl;				
			
		}else{
			cout << "\nWarrior is dead!! LOL XD " << endl;
		}
		}
		if(x.mlife == 0){
			cout << system("Color A") <<"\nTHE MONSTER HAS BEEN KILLED!! YOU WIN!! LETS GOO!! :D";
		}
		if(mp.plife == 0 && hp.plife == 0 && wp.plife ==0){
			cout << system("Color C") << "\nYOU HAVE BEEN SLAIN... YOU LOSE!!! D: ";
		}
	} 
	}
