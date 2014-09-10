/*
 * GameConfig.h
 *
 *  Created on: 2014年5月22日
 *      Author: SunDongliang
 */

#ifndef GAMECONFIG_H_
#define GAMECONFIG_H_

#include "SimpleAudioEngine.h" 
#include "cocos2d.h"
 
using namespace CocosDenshion;
USING_NS_CC;

/// different tags for different sprites
const int kOBJ_TAG = 1;
const int kBOMB_TAG = 2;
const int kPIVOT_TAG = 3;
const int kCOMFIRM_PANEL_TAG = 4;
const int kMENU_TAG = 5;
const int kGAMELAYER_TAG = 6;
const int kENDLAYER_TAG = 7;

/// 世界的总体属性
const int kPTM_RATIO = 32;
const float kGRAVITY = -10.0f; // 重力的大小
const int kVELOCITY_ITERATIONS = 8; // velecity iterations
const int kPOSITION_ITERATIONS = 8; // position iterations
const float kONE_DIV_PAI = 0.01745329252f; // 数值约等于1/π
const float kMAX_MOTOR_TORQUE = 200.0f; // 平衡木的摩擦力大小
const float kGROUNDBOX_PADDLE = 20.0f; // groundbox下端距离屏幕的距离

/// strings of the confirm panel
const char kQUIT_GAME[] = "Quit Game?";
const char kQUIT_APP[] = "Quit App?";
const char kCONFIRM_BACKGROUD_PATH[] = "confirm_background.png";

/// backgroup image file path
const char kBG_GAMESCENE_TOP_PATH[] = "backgrounds/bg_gamescene_top.png";
const char kBG_GAMESCENE_MID_PATH[] = "backgrounds/bg_gamescene_mid.png";
const char kBG_GAMESCENE_BUT_PATH[] = "backgrounds/bg_gamescene_but.png";
const char kBG_MAINSCENE_PATH[] = "backgrounds/bg_mainscene.png";
const char kBG_SCORESCENE_PATH[] = "backgrounds/bg_scorescene.png";
const char kBG_SETTINGSCENE_PATH[] = "backgrounds/bg_settingscene.png";
const char kBG_ENDLAYER_PATH[] = "backgrounds/bg_endlayer.png";
const char kBG_INFOPANEL_PATH[] = "backgrounds/bg_endlayer.png";

/// 各种Button组件需要的图片路径
const char kBT_MUSIC_POS_PATH[] = "buttons/bt_music_pos.png";
const char kBT_MUSIC_NEG_PATH[] = "buttons/bt_music_neg.png";
const char kBT_PLAY_POS_PATH[] = "buttons/bt_play_pos.png";
const char kBT_PLAY_NEG_PATH[] = "buttons/bt_play_neg.png";
const char kBT_SCORE_POS_PATH[] = "buttons/bt_score_pos.png";
const char kBT_SCORE_NEG_PATH[] = "buttons/bt_score_neg.png";
const char kBT_SETTING_POS_PATH[] = "buttons/bt_setting_pos.png";
const char kBT_SETTING_NEG_PATH[] = "buttons/bt_setting_neg.png";
const char kBT_MENU_POS_PATH[] = "buttons/bt_menu_pos.png";
const char kBT_MENU_NEG_PATH[] = "buttons/bt_menu_neg.png";
const char kBT_REPLAY_POS_PATH[] = "buttons/bt_replay_pos.png";
const char kBT_REPLAY_NEG_PATH[] = "buttons/bt_replay_neg.png";
const char kBT_RESET_POS_PATH[] = "buttons/bt_replay_pos.png";
const char kBT_RESET_NEG_PATH[] = "buttons/bt_replay_neg.png";
const char kBT_AUTHOR_POS_PATH[] = "buttons/bt_author_pos.png";
const char kBT_AUTHOR_NEG_PATH[] = "buttons/bt_author_neg.png";
const char kBT_HELP_POS_PATH[] = "buttons/bt_help_pos.png";
const char kBT_HELP_NEG_PATH[] = "buttons/bt_help_neg.png";
const char kBT_COPYRIGHT_POS_PATH[] = "buttons/bt_copyright_pos.png";
const char kBT_COPYRIGHT_NEG_PATH[] = "buttons/bt_copyright_neg.png";
const char kBT_YES_POS_PATH[] = "buttons/bt_yes_pos.png";
const char kBT_YES_NEG_PATH[] = "buttons/bt_yes_neg.png";
const char kBT_NO_POS_PATH[] = "buttons/bt_NO_pos.png";
const char kBT_NO_NEG_PATH[] = "buttons/bt_NO_neg.png";

/// dashboard组件需要的panel, pointer图片路径
const char  kPANEL_PATH[] = "panel.png";
const char  kPOINTER_PATH[] = "pointer.png";

/// 产生cutton, brick, iron的机率，x表示x%的机率产生该物体(总数为100)
const int     kCUTTON_POSSIBILITY = 50;
const int     kBRICK_POSSIBILITY     = 20;
const int     kIRON_POSSIBILITY     = 10;
const int     kSTICK_POSSIBILITY     = 10;
const int     kBOMB_POSSIBILITY     = 10;

/// default properties for B2Sprite
const float kDEFAULT_DENSITY = 1.0f;
const float kDEFAULT_FRICTION = 0.3f;
const float kDEFAULT_RESTITUTION = 0.0f;
const float kDEFAULT_SCALE = 0.25f;
const char  kDEFAULT_PIC_PATH[] = "circle.png";

/// properties for CuttonSprite
const float kCUTTON_DENSITY = 1.0f;
const float kCUTTON_FRICTION = 0.3f;
const float kCUTTON_RESTITUTION = 0.0f;
const float kCUTTON_SCALE = 0.25f;
const char kCUTTON_PIC_PATH[] = "cutton.png";

/// properties for BrickSprite
const float kBRICK_DENSITY = 2.0f;
const float kBRICK_FRICTION = 0.3f;
const float kBRICK_RESTITUTION = 0.0f;
const float kBRICK_SCALE = 0.25f;
const char kBRICK_PIC_PATH[] = "brick.png";

/// properties for IronSprite
const float kIRON_DENSITY = 3.0f;
const float kIRON_FRICTION = 0.3f;
const float kIRON_RESTITUTION = 0.0f;
const float kIRON_SCALE = 0.25f;
const char kIRON_PIC_PATH[] = "iron.png";

/// properties for StickSpriteS
const float kSTICK_DENSITY = 1.0f;
const float kSTICK_FRICTION = 0.3f;
const float kSTICK_RESTITUTION = 0.0f;
const float kSTICK_SCALE = 0.25f;
const char kSTICK_PIC_PATH[] = "stick.png";

/// properties for BombSprite
const float kBOMB_DENSITY = 3.0f;
const float kBOMB_FRICTION = 0.3f;
const float kBOMB_RESTITUTION = 0.0f;
const float kBOMB_SCALE = 0.25f;
const char kBOMB_PIC_PATH[] = "bomb.png";

/// help informationg for setting scene
const char kAUTHOR_INFO[] = "Author:SunDongliang       \n"
                                                      "@SunYat-SunUniversity\n"
                                                      "Email:im123im123@163.com\n"
                                                      "This game is free and\n"
                                                      "opensourced.See github:\n"
                                                      "https://github.com/Superm \n"
                                                      "eReturns/TestCocos\n";

const char kHELP_INFO[] = "This is balance game!       \n"
                          "The higher pile you make,   \n"
                          "the more scores you get.    \n"
                          "Touch screen to drop your   \n"
                          "building material onto the  \n"
                          "pile!And diference objects  \n"
                          "have different weight       \n"
                          "Warning:You can't let a BOMB\n"
                          "collide with your pile!     \n";

const char kCOPYRIGHT_INFO[] = "Some pictures/music are\n"
                                "taken from games below:\n"
                                "<Escape Action> of CoolSoft\n"
                                "<Hill Climb> of FingerSoft\n"
                                "<Kitty Pong> of Tencent\n"
                                "If the original author is not\n"
                                "happy about it,please contact\n"
                                "me,I will take it down\n";

/// sound effects file path
const char kSX_TOUCH[]= "sound/touch.ogg";
const char kSX_RELEASE[] = "sound/release.ogg";
const char kSX_CLASH[] ="sound/clash.ogg";
const char kSX_ROTATE[] = "sound/rotate.ogg";
const char kSX_EXPLODE[] = "sound/explode.ogg";
const char kSX_FAIL[] = "sound/fail.mp3";
const char kSX_START[] = "sound/start.mp3";
const char kMC_GAMESCENE[] = "sound/gamescene.ogg";
const char kMC_OTHERSCENE[] = "sound/otherscene.ogg";
/// Game configuration
extern bool kSOUND_ON;

/// preload all music files
void initAudioEngine();

#endif /* GAMECONFIG_H_ */

