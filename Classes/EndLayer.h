/*
 * EndLayer.h
 *
 *  Created on: 2014年7月15日
 *      Author: SunDongliang
 */

#ifndef ENDLAYER_H_
#define ENDLAYER_H_

#include "cocos2d.h"

class EndLayer: public cocos2d::Layer {

public:
	/// 调用该静态函数获取EndLayer对象
	/// @param 游戏结束时达到的高度
	static EndLayer* createWithHeight(float height);

private:
    CREATE_FUNC(EndLayer);
    virtual bool init();
    void initWithHeight(float height);

	/// 当用户点击Replay按钮时调用
    void onReplay(cocos2d::Ref *pSender);

	/// 当用户点击Menu按钮时调用
    void onMenu(cocos2d::Ref *pSender);
};



#endif /* ENDLAYER_H_ */
