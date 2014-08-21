/*
 * GameConfig.h
 *
 *  Created on: 2014年5月22日
 *      Author: SunDongliang
 */

#ifndef GAMECONFIG_H_
#define GAMECONFIG_H_

/// different tags for different sprites
const int OBJ_TAG = 1;
const int PIVOT_TAG = 2;
const int PTM_RATIO = 32;

/// properties for IronSprite
const float IRON_DENSITY = 10.0f;
const float IRON_FRICTION = 0.3f;
const float IRON_RESTITUTION = 0.0f;
const float IRON_SCALE = 0.5f;
const char IRON_PIC_PATH[] = "iron.png";

/// properties for CuttonSprite
const float CUTTON_DENSITY = 0.1f;
const float CUTTON_FRICTION = 0.3f;
const float CUTTON_RESTITUTION = 0.0f;
const float CUTTON_SCALE = 0.5f;
const char CUTTON_PIC_PATH[] = "cutton.png";

/// properties for BrickSprite
const float BRICK_DENSITY = 1.0f;
const float BRICK_FRICTION = 0.3f;
const float BRICK_RESTITUTION = 0.0f;
const float BRICK_SCALE = 0.5f;
const char BRICK_PIC_PATH[] = "brick.png";


#endif /* GAMECONFIG_H_ */
