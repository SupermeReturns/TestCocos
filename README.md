TestCocos is an android game project using Cocos2dx-3.0 

TestCocos游戏美化：
The Balance Master
1.关于游戏性的改善：
	4.添加更加有趣的性质：
		1.加入多种形状(根据实现难度而定，如果实现难度较大，则加入多种图片相同性质也是可以的)，
		DONE
			1.可以考虑的形状有长方形（横与竖，横的可以当平台，竖的可以快速增加高度）。
				1.继承B2Sprite类型，Stick，可以使用多种图片，在掉下来之前会不停地旋转，点击之后定住，并且垂直下落

			2.也可以增加一个叫做炸弹的类型，不能够碰到积木，否则会爆炸并且失败
				1.检测到与GroundBox相碰撞则消失，检测到与Pivot_Body相碰撞则发生爆炸，并且在USEBox中标记游戏失败
				2.修改Use_Box的代码结构，将在DealWithCollision的碰撞处理中，将处理代码从Use_Box移动到其他的相关类型当中。
					激进做法：
						1.BeginContact：获取碰撞的双方，做成Pair放在容器当中
						2.DealCollision: 将Pair对从容器当中取出来，然后分别调用两者的DealCollsion方法，将另外一个碰撞者作为参数进行传递，在调用之前需要检验指针是否validate
					保守做法：
						1.由于这个游戏的实用性不高，为了节约时间，我会直接把与游戏关卡相关的信息直接放在Use_Box当中。

			3.（待定）也可以增加一个如同刺猬的类型，不能够丢弃，但是会把碰到的第一个积木给毁灭掉
				1.如果与GroundBox相碰撞则消失，如果检测到与Pivot_Body相碰撞则将Pivot_Body进行“肢解”
			4.（待定）加入风的特效（会在屏幕上提示风向以及到来的时间，如果）
			5.（待定）赠送道具的模式
			6.（待定）可以加入重力感应，在积木将要倒下的时候，通过重力感应使其平衡
			7.（待定）让天使的物块移动路线不稳定，在物体掉下的过程中对其进行引导  USE
			8.（待定）下面有火向上面漫 USE，时间限制


		2.尝试一下撞击之后的感觉：
			尝试着将BeginContact,置换成EndContact/Presolve/Postsolve
DONE
		3.根据当前难度提高产生较难物体的机率和提高悬浮物体横向移动的速度:
			游戏没有关卡的存在，使用文件存储的方式实用性不高，难度的提高到目前为止只有下降的种类和移动的速度，所以在GameLayer中增加一个方法描述游戏难度的控制

DONE
	5.HighScore显示显示出错 
		待会单独进行测试
Done
	6.SettingScene：
		1.音乐开关
		2.显示帮助和作者信息
		写两个Layer类型，一个显示选择，一个显示帮助信息

DONE
	7.MainScene中加入Quit选项，并且Quit之前会有提示窗口用于提示用户
		写一个专门的Layer类型进行载入
DONE
	8.从GameLayer中退出需要进行提示
		写一个专门的Layer进行载入

2.关于外观的美化：
	2.（待定）Replay的transition
DONE
	3.加入声音(音效来源:下载的游戏APK解压)：
		音效：
			1.普通按键点击的音效(touch)
			2.点击屏幕释放物体的音效
			3.物体坠落地面（Obj或者Pivot与GroundBox相接触）的音效，并且失败的提示音乐或则打破记录的音乐
			4.与派生类物体相关的声音
				1.Stick 旋转的声音，如同风扇，按住之后停止
				2.Bomb 与Pivot 碰撞的时候的爆炸声
			5.
		背景音乐：
			1.MainScene, HighScoresScene, SettingsScene同一个背景音乐
			2.GameScene使用一个背景音乐
			3.
		条件：能够全局进行调控		
DONE
	4.消除掉调试数据的显示
		you can add this code in main.lua: cc.Director:getInstance():setDisplayStats(false)
DONE
	5.按钮的美化,至少不要只是文字，搜寻一下Cocos的相关支持包，不行的话，在后面放张图片也是可以的。
	  MenuItemImage(Play, Highscores, Setting, Menu, Replay, Reset,Author, Help, )
DONE
	6.背景图片(特点：萌，卡通即可，主题相关)：，
		1.Main Scene:
		2.HighScore Scene:
		3.Setting Scene:
		4.Play Layer:背景可以是天空，从地面出发，然后会有云朵的下降表示积木的上升。
		5.EndLayer显示的美化：出现的方式，显示的背景突出和部分透明

	7.上方的角度计可以将周围的白色去除掉
		修图即可
DONE
	8.屏幕适配
	http://cocos2d.9tech.cn/news/2014/0307/39995.html