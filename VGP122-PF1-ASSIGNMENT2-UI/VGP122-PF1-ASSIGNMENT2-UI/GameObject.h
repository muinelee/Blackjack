#pragma once

#include <string>

#include "Object.h"

class GameObject : public Object
{
public:
	virtual ~GameObject() = default;

	virtual void update() = 0;
	virtual void render() = 0;

private:
	std::string resourceID;
	std::string gameObjectID;
};