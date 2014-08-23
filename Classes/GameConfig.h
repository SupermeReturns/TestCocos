/*
 * GameConfig.h
 *
 *  Created on: 2014年5月22日
 *      Author: SunDongliang
 */

#ifndef GAMECONFIG_H_
#define GAMECONFIG_H_

/// different tags for different sprites
const int kOBJ_TAG = 1;
const int kPIVOT_TAG = 2;
const int kPTM_RATIO = 32;

/// 世界的总体属性
const float kGRAVITY = -10.0f; // 重力的大小
const int kVELOCITY_ITERATIONS = 8; // velecity iterations
const int kPOSITION_ITERATIONS = 8; // position iterations
const float kONE_DIV_PAI = 0.01745329252f; // 数值约等于1/π
const float kMAX_MOTOR_TORQUE = 200.0f; // 平衡木的摩擦力大小
const float kGROUNDBOX_PADDLE = 20.0f; // groundbox下端距离屏幕的距离

/// dashboard组件需要的panel, pointer图片路径
const char  kPANEL_PATH[] = "panel.jpg";
const char  kPOINTER_PATH[] = "pointer.png";

/// 产生cutton, brick, iron的机率，x表示x%的机率产生该物体(总数为100)
const int 	kCUTTON_POSSIBILITY = 70;
const int 	kBRICK_POSSIBILITY 	= 20;
const int 	kIRON_POSSIBILITY 	= 10;

/// default properties for B2Sprite
const float kDEFAULT_DENSITY = 1.0f;
const float kDEFAULT_FRICTION = 0.3f;
const float kDEFAULT_RESTITUTION = 0.0f;
const float kDEFAULT_SCALE = 0.25f;
const char 	kDEFAULT_PIC_PATH[] = "circle.png";

/// properties for CuttonSprite
const float kCUTTON_DENSITY = 1.0f;
const float kCUTTON_FRICTION = 0.3f;
const float kCUTTON_RESTITUTION = 0.0f;
const float kCUTTON_SCALE = 0.25f;
const char 	kCUTTON_PIC_PATH[] = "cutton.png";

/// properties for BrickSprite
const float kBRICK_DENSITY = 2.0f;
const float kBRICK_FRICTION = 0.3f;
const float kBRICK_RESTITUTION = 0.0f;
const float kBRICK_SCALE = 0.25f;
const char 	kBRICK_PIC_PATH[] = "brick.png";

/// properties for IronSprite
const float kIRON_DENSITY = 3.0f;
const float kIRON_FRICTION = 0.3f;
const float kIRON_RESTITUTION = 0.0f;
const float kIRON_SCALE = 0.25f;
const char 	kIRON_PIC_PATH[] = "iron.png";

#endif /* GAMECONFIG_H_ */
