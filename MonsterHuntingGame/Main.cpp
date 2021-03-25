#include <iostream>
#include <string>
#include <ctime>
#include "Creature.h"
#include "Monster.h"
#include "Player.h"

void attackPlayer(Player& p, Monster& m)
{
	if (m.isDead())
	{
		p.addGold(m.getGold());
		p.levelUp();
		std::cout << "You kill the " << m.getName() << ".\n";
		std::cout << "You are now level " << p.getLevel()
			<< " And you found " << m.getGold() << " gold.\n\n";
		return;
	}

	p.reduceHealth(m.getDamage());
	std::cout << "The " << m.getName() << " hit you for " << m.getDamage() << " damage.\n";
}

void attackMonster(Player& p, Monster& m)
{
	m.reduceHealth(p.getDamage());
	std::cout << "You hit the " << m.getName() << " for " << p.getDamage() << " damage.\n";	
}

void fightMonster(Player& p, Monster& m)
{
	while (!p.isDead())
	{
		std::cout << "\n(R)un or (F)ight: ";
		char answer;
		std::cin >> answer;

		if (answer == 'F' || answer == 'f') //Player chose to fight
		{
			attackMonster(p, m);
			attackPlayer(p, m);
			
			if (m.isDead())
				return;		 
		}
		else //Player chose to run.
		{
			//Player has 50% chance to run. 0 to fail and 1 to success
			static constexpr double fraction{ 1.0 / (RAND_MAX + 1.0) };
			int run{ 0 + static_cast<int>((1 - 0 + 1) * (std::rand() * fraction)) };
			
			if (run == 0)
			{
				std::cout << "You failed to flee.\n";
				attackPlayer(p, m);
			}
			else
			{
				std::cout << "\nYou successfully fled.\n";
				return;
			}
		}
	}

	std::cout << "\nYou died with " << p.getGold() << " gold :(\n";
	std::cout << "\nGAME OVER\n";
}

int main()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr))); 
	std::rand();

	std::cout << "Enter your name: ";
	std::string playerName;
	std::cin >> playerName;
	
	Player p{ playerName };
	
	std::cout << "\nWell come, " << p.getName() << "!\n";
	
	while (!p.isDead())
	{
		std::cout << "You have " << p.getHealth() << " health and carrying "
			<< p.getGold() << " gold\n";

		//Create a random monster
		Monster m{ Monster::getRandomMonster() };

		std::cout << "You find a " << m.getName() << " " << m.getSymbol() << "!\n";

		fightMonster(p, m);

		if (p.getLevel() >= 20)
		{
			std::cout << "you have " << p.getGold() << " gold!\n";
			std::cout << "You win!\n";
		}
	}

	return 0;
}