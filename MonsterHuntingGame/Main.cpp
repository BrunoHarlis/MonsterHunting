#include <iostream>
#include <string>
#include <array>
#include <string_view>
#include <cstdlib>
#include <ctime>

int getRandomNumber(int min, int max)
{
	static constexpr double fraction{ 1.0 / (RAND_MAX + 1.0) };

	return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}

class Creature
{
protected:
	std::string m_name;
	char m_symbol;
	int m_health;
	int m_damage;
	int m_gold;

public:
	Creature(std::string_view name, char symbol, int health, int damage, int gold) :
		m_name{ name },
		m_symbol{ symbol },
		m_health{ health },
		m_damage{ damage },
		m_gold{ gold }
	{
	}

	const std::string& getName() const { return m_name; }
	char getSymbol() const { return m_symbol; }
	int getHealth() const { return m_health; }
	int getDamage() const { return m_damage; }
	int getGold() const { return m_gold; }

	void reduceHealth(int damageSuffered) { m_health -= damageSuffered; }
	bool isDead() { return m_health <= 0; }
	void addGold(int addGolds) { m_gold += addGolds; }
};

class Player : public Creature
{
private:
	int m_level{ 1 };

public:
	Player(const std::string& name)
		:Creature{ name, '@', 10, 1, 0 }
	{
	}

	void levelUp()
	{
		++m_level;
		++m_damage;
	}

	int getLevel() const { return m_level; }
	bool hasWon() const { return m_level >= 20; }
};

class Monster : public Creature
{
public:
	enum class Type
	{
		DRAGON,
		ORC,
		SLIME,

		max_types
	};

private:
	static const Creature& getDefaultCreature(Type type)
	{
		static std::array<Creature, static_cast<std::size_t>(Type::max_types)> monsterData
		{
			{
				{"dragon", 'D', 20, 4, 100},
				{"orc", 'O', 4, 2, 25},
				{"slime", 'S', 1, 1, 10}
			}
		};

		return monsterData.at(static_cast<std::size_t>(type));
	}

public:
	Monster(Type type)
		: Creature{ getDefaultCreature(type) }
	{
	}

	static Monster getRandomMonster()
	{
		int num{ getRandomNumber(0, static_cast<int>(Type::max_types) - 1) };
		return static_cast<Type>(num);
	}

};

int main()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr))); 

	Monster m2{ Monster::Type::DRAGON };
	std::cout << "A " << m2.getName() << " (" << m2.getSymbol() << ") was created.\n";

	/*
	for (int i{ 0 }; i < 10; ++i)
	{
		Monster m{ Monster::getRandomMonster() };
		std::cout << "A " << m.getName() << " (" << m.getSymbol() << ") was created.\n";
	}

	std::cout << "Enter your name: ";
	std::string namePlayer;
	std::cin >> namePlayer;

	Player p{ namePlayer };

	std::cout << "\nWelcome, " << p.getName() << ".\n";
	std::cout << "You have " << p.getHealth() << " health and are carrying "
		<< p.getGold() << " gold.\n";

	Monster m{ Monster::Type::ORC };
	std::cout << "A " << m.getName() << " (" << m.getSymbol() << ") was created.\n";
	*/
	return 0;
}