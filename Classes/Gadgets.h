/*
 * Gadgets.h
 *
 *  Created on: 2014年7月20日
 *      Author: SunDongliang
 */

#ifndef GADGETS_H_
#define GADGETS_H_

#include "GameConfig.h"
#include "cocos2d.h"
#include "Box2D/Box2D.h"

USING_NS_CC;

class Marker : public Layer{
private:
	Sprite* m_line;
	Label* m_font;
	void updateFont();
public:
	static Marker* create(Size visibleSize);
	bool init(Size visibleSize);
	void update(float height);
    CC_SYNTHESIZE(float, m_height, Height);
};

/// Dashboard is a gadget that shows the balance information of 
class Dashboard : public Layer {
private:
	Sprite* m_pointer;
	Sprite* m_panel;
	float angle;
public:
	/// create a Dashboard instance and initiate it,it starts with pointer in 90 degree upstraight
	/// @return an Dashboard instance that has been autoreleased
	static Dashboard* create();

	/// initiate an Dashboard instance,it starts with pointer in 90 degree upstraight
	/// @return return ture if initiate succesful,false otherwise
	bool init();

	/// update the dashboard(It means update the angle of the pointer)
	/// @param the new angle of pointer to move to
	void update(float angle);
};




#endif /* GADGETS_H_ */
