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

/// 询问用户确认的面板，包括一条字符和两个按钮和一个背景
class  ConfirmPanel: public Layer{
public:
	/// initiate an ConfirmPanel instance
	/// @return return ture if initiate succesful,false otherwise
	bool initWithString(const char[] str);

protected:
	void addMenu();

	///  当同意的按钮被按下时被调用
	void onYes(Ref *pSender);

	///  当不同意的按钮被按下时被调用
	void onNo(Ref *pSender);
};

class QuitGame: public ConfirmPanel
{
public:
	/// create a QuitGame instance and initiate it
	/// @return an QuitGame instance that has been autoreleased
	static QuiGame* create();
};

class QuitApp : public ConfirmPanel
{
public:
	/// create a QuitApp instance and initiate it
	/// @return an QuitApp instance that has been autoreleased
	static QuitApp* create();

protected:
	void addMenu();
	void onYes(Ref *pSender);
};
#endif /* GADGETS_H_ */
