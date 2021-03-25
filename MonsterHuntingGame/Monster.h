#ifndef MONSTER_H
#define MONSTER_H
#include "Creature.h"

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
	static const Creature& getDefaultCreature(Type type);
	
public:
	Monster(Type type);

	static Monster getRandomMonster();
};
#endif