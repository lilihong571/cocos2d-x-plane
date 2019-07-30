#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
class HelloWorld : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	////////////////////////////////////////////////////////
	void menuCloseCallback(CCObject* pSender);
	//声明重新开游戏按钮的回调函数
	void menuReStartCallback(CCObject* pSender);
	//声明开始游戏按钮的回调函数
	void menuStartCallback(CCObject* pSender);
	//声明退出游戏按钮的回调函数
	void menuQuitCallback(CCObject* pSender);
	//声明背景音乐开关的回调函数
	void menuMusicBgCallback(CCObject* pSender);
	//声明音效开关的回调函数
	void menuMusicSoundCallback(CCObject* pSender);

	////////////////////////////////////////////////////////
	//声明主界面初始化函数
	void initMain();
	//声明游戏界面初始化函数
	void initGame();
	//声明主界面控件的显示或隐藏函数
	void visibleMain(bool visible);
	//声明游戏界面控件的显示或隐藏函数
	void visibleGame(bool visble);

	////////////////////////////////////////////////
	//结算页面控件显示或隐藏
	//声明结算函数
	void scoreCount();
	void visibleCount(bool visible);
	
	////////////////////////////////////////////////////////////
	//声明触摸开始函数
	bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
	//声明触摸移动函数
	void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
	//声明触摸结束函数
	void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);

	/////////////////////////////////////////////////////////////
	//声明调度器函数
	void update(float dt);
	//声明自定义调度器，用来产生敌机子弹
	void myMonsterUpdate(float dt);
	//生产敌机的自定义调度器函数
	void MonsterProduct(float dt);
	//声明自定义调度器，用来产生子弹
	void myUpdate(float dt);

	/////////////////////////////////////////////////////////////
	//声明敌机死亡的函数
	void MonsterDeath(CCNode* pSender);

	//声明主角飞机销毁调用的回调函数
	void destroyFunction();


	// implement the "static node()" method manually
	CREATE_FUNC(HelloWorld);
private:
	///////////////////////////////////////
	//创建一个主界面背景
	CCSprite *mainBg;
	//创建一个游戏Log
	CCSprite *mainLog;
	//创建一个开始游戏按钮
	CCMenuItemImage *mainStart;
	//创建一个退出游戏按钮
	CCMenuItemImage *mainQuit;
	//创建一个背景音乐开关
	CCMenuItemToggle *musicBg;
	//创建一个音效开关
	CCMenuItemToggle *musicSound;

	////////////////////////////////////////////////
	//创建一个游戏界面背景
	CCSprite *gameBg1;
	CCSprite *gameBg2;
	//创建一个主角
	CCSprite *plane;
	//标签用于提示
	CCLabelTTF *Label;
	//标签用于计分
	CCLabelTTF *scoreLabel;
	//统计分数
	int score = 0;

	/////////////////////////////////////////////
	//创建一个飞行动作
	CCAction *flyAction;
	//创建一个销毁动作
	CCAction *destroyAction;

	//////////////////////////////////////////////
	//创建一个子弹数组
	CCArray bulletArray;
	//创建敌机的子弹数组
	CCArray bulletMonsterArray;
	//创建敌机数组
	CCArray monsterArray;
	//创建奖励物品数组
	CCArray awardArray;
	//奖励物品的剩余时间
	float awardTime;

	///////////////////////////////////////////
	//声明结算页面显示的内容
	//成绩标签
	CCLabelTTF *scoreCJ;
	//分数标签
	CCLabelTTF *scoreFS;
	//2个按钮
	//重新开始
	CCMenuItemImage *reStart;
	//回到主界面
	CCMenuItemImage *returnMain;

	
};

#endif // __HELLOWORLD_SCENE_H__
