#pragma once
class Weapon
{
public:
	Weapon();
	~Weapon();

	virtual void Attack() = 0;
};

