#pragma once
#include "Entity.h"
class Item : public Entity
{
public:
	Item();
	~Item();

	enum Inventory_Characteristics {Equippable, Useable};

private:
	std::vector<bool> Inventory_Characteristics;
};

