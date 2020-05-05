#pragma once

#include "GameObject.h"
#include "cards/Card.h"

#include <vector>
#include <memory>

class Player : public GameObject
{
	private:
		std::vector<std::shared_ptr<Card>> handCards;

	public:
		//TODO
};