/*!
\file BehaviorHealth.h
\author Khaled S. Ishaque
\date 1-27-2022
\brief
	H file for BehaviorHealth class and functions in class.
		("health" means the 1 bar and # of shields online for player)
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include "Behavior.h"

class Texture;

class BehaviorHealth : public Behavior {
public:
	BehaviorHealth(float timeframe = 2.0f);
	BehaviorHealth(const BehaviorHealth& base);

	unsigned int getShield();

	void setTimer(float timeframe);

	void setShieldNum(int sNum);

	//void setTexture(Texture& text);

	void update(float dt);

	Component* clone() const;

private:
	int shieldNumber; // total shield count
	float regenTime; //shield pops back into place when timer hits
	bool isDisplayed = true;
};