#pragma once
class Serializable
{
public:

	std::string name;
	virtual json serialize() = 0;
	virtual void load(json &save) = 0;
};

