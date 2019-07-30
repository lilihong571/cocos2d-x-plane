#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init())
	{
		return false;
	}

	initMain();
	initGame();
	return true;
}
//声明开始游戏按钮的回调函数
void HelloWorld::menuStartCallback(CCObject* pSender){
	score = 0;
	//隐藏主界面控件
	visibleMain(false);
	//显示游戏界面控件
	visibleGame(true);
	
	////播放销毁动画
	//plane->runAction(destroyAction);
}
//声明退出游戏按钮的回调函数
void HelloWorld::menuQuitCallback(CCObject* pSender){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
#else
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}
//声明背景音乐开关的回调函数
void HelloWorld::menuMusicBgCallback(CCObject* pSender){

}
//声明音效开关的回调函数
void HelloWorld::menuMusicSoundCallback(CCObject* pSender){

}
//声明主界面初始化函数
void HelloWorld::initMain(){
	//获取屏幕宽高
	CCSize visiblesize = CCDirector::sharedDirector()->getVisibleSize();
	//给主界面背景赋值
	mainBg = CCSprite::create("background.png");
	//设置位置
	mainBg->setPosition(ccp(visiblesize.width / 2, visiblesize.height / 2));
	//添加到图层
	this->addChild(mainBg);
	//给游戏log赋值
	mainLog = CCSprite::create("name.png");
	//设置位置
	mainLog->setPosition(ccp(visiblesize.width / 2, visiblesize.height - 200));
	//添加到图层
	this->addChild(mainLog);
	//给开始游戏按钮赋值
	mainStart = CCMenuItemImage::create("start1.png", "start2.png", this, menu_selector(HelloWorld::menuStartCallback));
	//设置位置
	mainStart->setPosition(ccp(visiblesize.width / 2, visiblesize.height / 2 + 50));
	//给退出游戏按钮赋值
	mainQuit = CCMenuItemImage::create("quit1.png", "quit2.png", this, menu_selector(HelloWorld::menuQuitCallback));
	//设置位置
	mainQuit->setPosition(ccp(visiblesize.width / 2, visiblesize.height / 2 - 50));
	//给背景音乐开关赋值
	musicBg = CCMenuItemToggle::createWithTarget(this,
		menu_selector(HelloWorld::menuMusicBgCallback),
		CCMenuItemImage::create("BgMusicToggle1.png", "BgMusicToggle1.png"),
		CCMenuItemImage::create("BgMusicToggle2.png", "BgMusicToggle2.png"),
		NULL);
	//设置位置
	musicBg->setPosition(ccp(visiblesize.width / 4, visiblesize.height / 4));
	//给音效开关赋值
	musicSound = CCMenuItemToggle::createWithTarget(this,
		menu_selector(HelloWorld::menuMusicSoundCallback),
		CCMenuItemImage::create("SoundToggle1.png", "SoundToggle1.png"),
		CCMenuItemImage::create("SoundToggle2.png", "SoundToggle2.png"),
		NULL);
	//设置位置
	musicSound->setPosition(ccp(visiblesize.width / 4 * 3, visiblesize.height / 4));

	//创建一个菜单
	CCMenu *menu = CCMenu::create(mainStart, mainQuit, musicBg, musicSound, NULL);
	//设置位置
	menu->setPosition(CCPointZero);
	//添加到图层
	this->addChild(menu);
}
//声明游戏界面初始化函数
void HelloWorld::initGame(){
	score = 0;
	//获取屏幕宽高
	CCSize visiblesize = CCDirector::sharedDirector()->getVisibleSize();
	//bg1
	gameBg1 = CCSprite::create("background.png");
	//设置位置
	gameBg1->setPosition(ccp(visiblesize.width / 2, visiblesize.height / 2));
	//添加到图层
	this->addChild(gameBg1);
	//bg2
	gameBg2 = CCSprite::create("background.png");
	//设置位置
	gameBg2->setPosition(ccp(gameBg1->getPositionX(), gameBg1->getPositionY() + gameBg2->getContentSize().height));
	//添加到图层
	this->addChild(gameBg2);

	//游戏界面提示系统赋值///////////////////////////////////////////
	Label = CCLabelTTF::create("Score: ", "Arial", 30);
	Label->setPosition(ccp(0 + Label->getContentSize().width / 2, visiblesize.height - Label->getContentSize().height / 2));
	this->addChild(Label);

	//游戏界面给计分系统赋值
	scoreLabel = CCLabelTTF::create("00000000", "Arial", 30);
	scoreLabel->setPosition(ccp(0 + scoreLabel->getContentSize().width / 2 + 0 + Label->getContentSize().width, visiblesize.height - scoreLabel->getContentSize().height / 2));
	this->addChild(scoreLabel);
	//写入计分板中
	char str[100] = { '0' };
	sprintf(str, "%08d", score);
	scoreLabel->setString(str);
	////////////////////////////////////////////////////////////////

	//给主角赋值
	plane = CCSprite::create("hero1.png");
	//设置位置
	plane->setPosition(ccp(visiblesize.width / 2, plane->getContentSize().height));
	//添加到图层
	this->addChild(plane);
	//收集飞行图片
	CCAnimation *animation1 = CCAnimation::create();
	animation1->addSpriteFrameWithFileName("hero1.png");
	animation1->addSpriteFrameWithFileName("hero2.png");
	//设置图片切换帧率
	animation1->setDelayPerUnit(0.2f);
	//播放完是否回到初始状态
	animation1->setRestoreOriginalFrame(true);
	//将图片制作成动画
	CCAnimate *animate1 = CCAnimate::create(animation1);
	//给飞行动作赋值
	flyAction = CCRepeatForever::create(animate1);
	//设置不释放
	flyAction->retain();
	//收集销毁图片
	CCAnimation *animation2 = CCAnimation::create();
	animation2->addSpriteFrameWithFileName("playerdeth1.png");
	animation2->addSpriteFrameWithFileName("playerdeth2.png");
	animation2->addSpriteFrameWithFileName("playerdeth3.png");
	animation2->addSpriteFrameWithFileName("playerdeth4.png");
	//设置图片切换帧率
	animation2->setDelayPerUnit(0.2f);
	//播放完是否回到初始状态
	animation2->setRestoreOriginalFrame(true);
	//将图片制作成动画
	CCAnimate *animate2 = CCAnimate::create(animation2);
	//给飞行动作赋值													*********************************************结算界面
	//destroyAction = CCSequence::create(animate2, CCCallFunc::create(this, SEL_CallFunc(&HelloWorld::destroyFunction)), NULL);
	destroyAction = CCSequence::create(animate2, CCCallFunc::create(this, SEL_CallFunc(&HelloWorld::scoreCount)), NULL);
	//scoreCount();
	//设置不释放
	destroyAction->retain();


	//隐藏游戏界面
	visibleGame(false);
}
//声明主界面控件的显示或隐藏函数
void HelloWorld::visibleMain(bool visible){
	//bg
	mainBg->setVisible(visible);
	//log
	mainLog->setVisible(visible);
	//strat
	mainStart->setVisible(visible);
	//quit
	mainQuit->setVisible(visible);
	//musicBg
	musicBg->setVisible(visible);
	//musicSound
	musicSound->setVisible(visible);
}
//声明游戏界面控件的显示或隐藏函数
void HelloWorld::visibleGame(bool visble){
	//bg1
	gameBg1->setVisible(visble);
	//bg2
	gameBg2->setVisible(visble);
	//plane
	plane->setVisible(visble);
	//////////////////////////////////////////////////
	//提示系统
	Label->setVisible(visble);
	//计分系统
	scoreLabel->setVisible(visble);
	//////////////////////////////////////////////
	//awardTime奖励时效
	awardTime = -0.0f;
	//如果可见
	if (visble == true){
		//开启默认调度器
		scheduleUpdate();
		//播放飞行动画
		plane->runAction(flyAction);
		//添加触摸事件监听
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
		//开启自定义调度器
		schedule(SEL_SCHEDULE(&HelloWorld::myUpdate), 0.15f, -1, 2.0f);
		//开启敌机生产的调度器
		schedule(SEL_SCHEDULE(&HelloWorld::MonsterProduct), 1.0f, -1, 2.0f);
	}
	else
	{
		//关闭默认调度器
		unscheduleUpdate();
		//停止所有动作
		plane->stopAllActions();
		//移除触摸监听
		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
		//关闭自定义调度器
		unschedule(SEL_SCHEDULE(&HelloWorld::myUpdate));
		//关闭敌机生产自定义调度器
		unschedule(SEL_SCHEDULE(&HelloWorld::MonsterProduct));

		//清除上一局子弹
		for (int i = 0; i < bulletArray.count(); i++){
			//移除下标为i的子弹
			CCSprite *bullet = (CCSprite*)bulletArray.objectAtIndex(i);
			bullet->removeFromParentAndCleanup(true);
		}
		//全部子弹移除后，清空数组
		bulletArray.removeAllObjects();

		//飞机复位
		//获取屏幕宽高
		CCSize visiblesize = CCDirector::sharedDirector()->getVisibleSize();
		plane->setPosition(ccp(visiblesize.width / 2, plane->getContentSize().height));

		//清除上一局产生的敌机
		for (int i = 0; i < monsterArray.count(); i++){
			//取出元素
			CCSprite *monster = (CCSprite*)monsterArray.objectAtIndex(i);
			monster->removeFromParentAndCleanup(true);
		}
		//清空数组
		monsterArray.removeAllObjects();

		//清除奖励物品//////////////////////////////////////////////////////////////////
		for (int i = 0; i < awardArray.count(); i++){
			//取出元素
			CCSprite *award = (CCSprite*)awardArray.objectAtIndex(i);
			//销毁
			award->removeFromParentAndCleanup(true);
		}
		//清空数组
		awardArray.removeAllObjects();

		score = 0;
	}
}
//声明调度器函数
void HelloWorld::update(float dt){
	//碰撞检测
	//1.主角与敌机
	for (int i = 0; i < monsterArray.count(); i++){
		//取出元素
		CCSprite *monster = (CCSprite*)monsterArray.objectAtIndex(i);

		//判断主角与敌机是否碰撞(两个框和两个框相碰)
		if (plane->boundingBox().intersectsRect(monster->boundingBox())){
			//主角死亡
			//关闭默认调度器
			unscheduleUpdate();
			//停止所有动作
			plane->stopAllActions();
			//移除触摸监听
			CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
			//关闭自定义调度器
			unschedule(SEL_SCHEDULE(&HelloWorld::myUpdate));
			//关闭敌机生产自定义调度器
			unschedule(SEL_SCHEDULE(&HelloWorld::MonsterProduct));
			plane->runAction(destroyAction);
			//清除奖励物品//////////////////////////////////////////////////////////////////
			for (int i = 0; i < awardArray.count(); i++){
				//取出元素
				CCSprite *award = (CCSprite*)awardArray.objectAtIndex(i);
				//销毁
				award->removeFromParentAndCleanup(true);
			}
			//清空数组
			awardArray.removeAllObjects();
		}

		//2.判断敌机与子弹是否碰撞
		for (int j = 0; j < bulletArray.count(); j++){
			//取出子弹
			CCSprite *bullet = (CCSprite*)bulletArray.objectAtIndex(j);
			//判断monster和子弹是否碰撞
			if (monster->boundingBox().intersectsRect(bullet->boundingBox())){
				//子弹销毁
				//从子弹数组中移除
				bulletArray.removeObjectAtIndex(j);
				j--;
				bullet->removeFromParentAndCleanup(true);
				//敌机播放死亡动画（有三种飞机）
				switch (monster->getTag())
				{
					//播放小敌机爆炸动画
				case 0:
				{
						  //创建图片收集者
						  CCAnimation *animation = CCAnimation::create();
						  animation->addSpriteFrameWithFileName("enemy0down1.png");
						  animation->addSpriteFrameWithFileName("enemy0down2.png");
						  animation->addSpriteFrameWithFileName("enemy0down3.png");
						  animation->addSpriteFrameWithFileName("enemy0down4.png");
						  //设置播放速度
						  animation->setDelayPerUnit(0.25f);
						  //将收集的图片制作成动画
						  CCAnimate *animate = CCAnimate::create(animation);
						  //播放动画
						  //monster->runAction(animate);
						  //播放顺序动画
						  monster->runAction(CCSequence::create(animate,
							  CCCallFuncN::create(this, SEL_CallFuncN(&HelloWorld::MonsterDeath)), NULL));

				}
					//第一种飞机//计分系统计分
					score += 10;
					break;
					//击中中型敌机
				case 1:
				{
						  //创建图片收集者
						  CCAnimation *animation = CCAnimation::create();
						  animation->addSpriteFrameWithFileName("enemy1down1.png");
						  animation->addSpriteFrameWithFileName("enemy1down2.png");
						  animation->addSpriteFrameWithFileName("enemy1down3.png");
						  animation->addSpriteFrameWithFileName("enemy1down4.png");
						  //设置播放速度
						  animation->setDelayPerUnit(0.25f);
						  //将收集的图片制作成动画
						  CCAnimate *animate = CCAnimate::create(animation);
						  //播放动画
						  //monster->runAction(animate);
						  //播放顺序动画
						  monster->runAction(CCSequence::create(animate,
							  CCCallFuncN::create(this, SEL_CallFuncN(&HelloWorld::MonsterDeath)), NULL));

				}
					//第2种飞机//计分系统计分
					score += 20;
					break;
					//击中大型敌机
				case 2:
				{
						  //创建图片收集者
						  CCAnimation *animation = CCAnimation::create();

						  animation->addSpriteFrameWithFileName("enemy2_down1.png");
						  animation->addSpriteFrameWithFileName("enemy2_down2.png");
						  animation->addSpriteFrameWithFileName("enemy2_down3.png");
						  animation->addSpriteFrameWithFileName("enemy2_down4.png");
						  animation->addSpriteFrameWithFileName("enemy2_down5.png");
						  //设置播放速度
						  animation->setDelayPerUnit(0.25f);
						  //将收集的图片制作成动画
						  CCAnimate *animate = CCAnimate::create(animation);
						  //播放动画
						  //monster->runAction(animate);
						  //播放顺序动画
						  monster->runAction(CCSequence::create(animate,
							  CCCallFuncN::create(this, SEL_CallFuncN(&HelloWorld::MonsterDeath)), NULL));

				}
					//第一种飞机//计分系统计分
					score += 50;
					break;
				default:
					break;
				}

				//写入计分板中
				char str[100] = { '0' };
				sprintf(str, "%08d", score);
				scoreLabel->setString(str);

				//将怪物从数组中移除
				monsterArray.removeObjectAtIndex(i);
				i--;
				//怪物没有销毁，从数组中移除了
				break;
			}

		}
	}
	//////////////////////////////////////////////////////////////////////
	////碰撞检测，敌机子弹与主角
	for (int i = 0; i < bulletMonsterArray.count(); i++){

		//取出子弹
		CCSprite *bullet = (CCSprite*)bulletMonsterArray.objectAtIndex(i);
		if (plane->boundingBox().intersectsRect(bullet->boundingBox())){
			//主角死亡
			//关闭默认调度器
			unscheduleUpdate();
			//停止所有动作
			plane->stopAllActions();
			//移除触摸监听
			CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
			//关闭自定义调度器
			unschedule(SEL_SCHEDULE(&HelloWorld::myUpdate));
			//关闭敌机生产自定义调度器
			unschedule(SEL_SCHEDULE(&HelloWorld::MonsterProduct));
			plane->runAction(destroyAction);
			//子弹销毁
			//从子弹数组中移除
			bulletMonsterArray.removeObjectAtIndex(i);
			i--;
			bullet->removeFromParentAndCleanup(true);
			//清除奖励物品//////////////////////////////////////////////////////////////////
			for (int i = 0; i < awardArray.count(); i++){
				//取出元素
				CCSprite *award = (CCSprite*)awardArray.objectAtIndex(i);
				//销毁
				award->removeFromParentAndCleanup(true);
			}
			//清空数组
			awardArray.removeAllObjects();

		}
	}
	/////////////////////////////////////////////////////////////////////////

	//3.背景滚动
	gameBg1->setPositionY(gameBg1->getPositionY() - 500 * dt);
	gameBg2->setPositionY(gameBg2->getPositionY() - 500 * dt);
	if (gameBg1->getPositionY() <= -gameBg1->getContentSize().height / 2){
		gameBg1->setPositionY(gameBg2->getPositionY() + gameBg1->getContentSize().height);
	}
	if (gameBg2->getPositionY() <= -gameBg2->getContentSize().height / 2){
		gameBg2->setPositionY(gameBg1->getPositionY() + gameBg2->getContentSize().height);
	}
	//4.子弹飞行
	for (int i = 0; i < bulletArray.count(); i++){
		//取出子弹
		CCSprite *bullet = (CCSprite*)bulletArray.objectAtIndex(i);
		//设置位置
		bullet->setPositionY(bullet->getPositionY() + 500 * dt);
	}
	//清除飞出屏幕的子弹
	for (int i = 0; i < bulletArray.count(); i++){
		//取出子弹
		CCSprite *bullet = (CCSprite*)bulletArray.objectAtIndex(i);
		if (bullet->getPositionY() >= 900){
			//从数组中移除
			bulletArray.removeObjectAtIndex(i);
			//下标-1
			i--;
			//从层中移除
			bullet->removeFromParentAndCleanup(true);
			//指针赋空
			bullet = nullptr;
		}
	}
	///////////////////////////////////////////////////////////
	//4.子弹飞行
	for (int i = 0; i < bulletMonsterArray.count(); i++){
		//取出子弹
		CCSprite *bullet = (CCSprite*)bulletMonsterArray.objectAtIndex(i);
		//设置位置
		bullet->setPositionY(bullet->getPositionY() - 500 * dt);
	}
	//清除飞出屏幕的子弹
	for (int i = 0; i < bulletMonsterArray.count(); i++){
		//取出子弹
		CCSprite *bullet = (CCSprite*)bulletMonsterArray.objectAtIndex(i);
		if (bullet->getPositionY() <= -100){
			//从数组中移除
			bulletMonsterArray.removeObjectAtIndex(i);
			//下标-1
			i--;
			//从层中移除
			bullet->removeFromParentAndCleanup(true);
			//指针赋空
			bullet = nullptr;
		}
	}
	////////////////////////////////////////////////////////////
	//5.敌机的飞行与销毁
	for (int i = 0; i < monsterArray.count(); i++){
		//取出元素
		CCSprite *monster = (CCSprite*)monsterArray.objectAtIndex(i);
		//设置Y坐标
		monster->setPositionY(monster->getPositionY() - 300 * dt);
	}
	//销毁
	for (int i = 0; i < monsterArray.count(); i++){
		//取出元素
		CCSprite *monster = (CCSprite*)monsterArray.objectAtIndex(i);
		if (monster->getPositionY()<-monster->getContentSize().height / 2){
			monsterArray.removeObjectAtIndex(i);
			i--;
			monster->removeFromParentAndCleanup(true);
			monster = nullptr;
		}
	}
	//奖励物品下落和销毁////////////////////////////////////////////
	for (int i = 0; i < awardArray.count(); i++){
		//取出第i个奖励物品
		CCSprite * award = (CCSprite*)awardArray.objectAtIndex(i);
		//奖励物品与主角的碰撞
		if (award->boundingBox().intersectsRect(plane->boundingBox())){
			//奖励物品消失
			//从数组中移除(删除索引为i的)
			awardArray.removeObjectAtIndex(i);
			i--;
			//销毁
			award->removeFromParentAndCleanup(true);
			//主角开启连发模式、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、
			awardTime = 10.0f;
			continue;//重新开始这个循环
		}
		//如果奖励物品已经下落在屏幕外，直接销毁
		if (award->getPositionY() < -50){
			//从数组中移除(删除索引为i的)
			awardArray.removeObjectAtIndex(i);
			i--;
			//销毁
			award->removeFromParentAndCleanup(true);
		}
		else
		{
			//往下走
			award->setPositionY(award->getPositionY() - 300 * dt);

		}
	}
}
////声明飞机销毁调用的回调函数
void HelloWorld::destroyFunction(){
	////显示主界面
	//visibleMain(true);
	////隐藏游戏界面
	//visibleGame(false);
	//scoreCount();
	//所有敌机炸毁
	//取出敌机
	for (int i = 0; i < monsterArray.count(); i++){
		//取出元素
		CCSprite *monster = (CCSprite*)monsterArray.objectAtIndex(i);
		//播放所有敌机死亡动画
		if (monster->getTag() == 0){
			//创建图片收集者
			CCAnimation *animation = CCAnimation::create();
			animation->addSpriteFrameWithFileName("enemy0down1.png");
			animation->addSpriteFrameWithFileName("enemy0down2.png");
			animation->addSpriteFrameWithFileName("enemy0down3.png");
			animation->addSpriteFrameWithFileName("enemy0down4.png");
			//设置播放速度
			animation->setDelayPerUnit(0.25f);
			//将收集的图片制作成动画
			CCAnimate *animate = CCAnimate::create(animation);
			//播放动画
			//monster->runAction(animate);
			//播放顺序动画
			monster->runAction(animate);
			monster->removeFromParentAndCleanup(true);
		}
		else if (monster->getTag() == 1)
		{
			//创建图片收集者
			CCAnimation *animation = CCAnimation::create();
			animation->addSpriteFrameWithFileName("enemy1down1.png");
			animation->addSpriteFrameWithFileName("enemy1down2.png");
			animation->addSpriteFrameWithFileName("enemy1down3.png");
			animation->addSpriteFrameWithFileName("enemy1down4.png");
			//设置播放速度
			animation->setDelayPerUnit(0.25f);
			//将收集的图片制作成动画
			CCAnimate *animate = CCAnimate::create(animation);
			//播放动画
			//monster->runAction(animate);
			//播放顺序动画
			monster->runAction(animate);
			monster->removeFromParentAndCleanup(true);
		}
		else
		{
			//创建图片收集者
			CCAnimation *animation = CCAnimation::create();
			animation->addSpriteFrameWithFileName("enemy2_down1.png");
			animation->addSpriteFrameWithFileName("enemy2_down2.png");
			animation->addSpriteFrameWithFileName("enemy2_down3.png");
			animation->addSpriteFrameWithFileName("enemy2_down4.png");
			animation->addSpriteFrameWithFileName("enemy2_down5.png");
			//设置播放速度
			animation->setDelayPerUnit(0.25f);
			//将收集的图片制作成动画
			CCAnimate *animate = CCAnimate::create(animation);
			//播放动画
			//monster->runAction(animate);
			//播放顺序动画
			monster->runAction(animate);
			monster->removeFromParentAndCleanup(true);
		}
		//将怪物从数组中移除
		monsterArray.removeObjectAtIndex(i);
		i--;
	}
}
//声明触摸开始函数
bool HelloWorld::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent){
	if (plane->boundingBox().containsPoint(pTouch->getLocation())){
		return true;
	}
	return false;
}
//声明触摸移动函数
void HelloWorld::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent){
	//获取屏幕宽高
	CCSize visiblesize = CCDirector::sharedDirector()->getVisibleSize();
	//设置飞机位置
	plane->setPosition(pTouch->getLocation());
	if (plane->getPositionX() >= visiblesize.width - plane->getContentSize().width / 2){
		plane->setPositionX(visiblesize.width - plane->getContentSize().width / 2);
	}
	if (plane->getPositionX() <= 0 + plane->getContentSize().width / 2){
		plane->setPositionX(0 + plane->getContentSize().width / 2);
	}
	if (plane->getPositionY() >= visiblesize.height - plane->getContentSize().height / 2){
		plane->setPositionY(visiblesize.height - plane->getContentSize().height / 2);
	}
	if (plane->getPositionY() <= 0 + plane->getContentSize().height / 2){
		plane->setPositionY(0 + plane->getContentSize().height / 2);
	}
}
//声明触摸结束函数
void HelloWorld::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent){

}
//声明自定义调度器，用来产生子弹
void HelloWorld::myUpdate(float dt){


	//创建一个子弹精灵（中）
	CCSprite *bullet = CCSprite::create("bullet1.png");
	//设置位置
	bullet->setPosition(ccp(plane->getPositionX(), plane->getPositionY() + plane->getContentSize().height / 2));
	//添加到图层
	this->addChild(bullet);
	//保存子弹
	bulletArray.addObject(bullet);


	if (awardTime > 0.0f){
		awardTime -= dt;
		//创建一个子弹精灵(左)
		CCSprite *bulletleft = CCSprite::create("bullet2.png");
		//设置位置、、位置要变化
		bulletleft->setPosition(ccp(plane->getPositionX() - plane->getContentSize().width / 3, plane->getPositionY() + plane->getContentSize().height / 2));
		//添加到图层
		this->addChild(bulletleft);
		//保存子弹
		bulletArray.addObject(bulletleft);

		//创建一个子弹精灵（右）
		CCSprite *bulletright = CCSprite::create("bullet2.png");
		//设置位置、、位置偏主角的右边
		bulletright->setPosition(ccp(plane->getPositionX() + plane->getContentSize().width / 3, plane->getPositionY() + plane->getContentSize().height / 2));
		//添加到图层
		this->addChild(bulletright);
		//保存子弹
		bulletArray.addObject(bulletright);
	}

}
////声明自定义调度器，用来产生子弹
//void HelloWorld::myMonsterUpdate(float dt){
//	
//}
//s生产敌机的自定义调度器函数
void HelloWorld::MonsterProduct(float dt){

	CCSize visiblesize = CCDirector::sharedDirector()->getVisibleSize();

	int i = rand() % 3;//产生0,1,2
	char str[15];
	sprintf(str, "enemy%d.png", i);

	//生产一架敌机
	CCSprite *monster = CCSprite::create(str);
	//位置
	monster->setPositionY(852 + monster->getContentSize().height / 2);

	//monster->getContentSize().width/2   到   屏幕宽度-敌机宽度的一半
	//200  -- 500
	//rand()%(500-200+1)+200
	monster->setPositionX(rand() % (int)(visiblesize.width - monster->getContentSize().width) + monster->getContentSize().width / 2);
	//设置标记值
	monster->setTag(i);
	this->addChild(monster);
	//敌机存入数组中
	monsterArray.addObject(monster);


	/////////////////////////////////////////////////////////////////////////////////////
	//创建一个子弹精灵（中）
	CCSprite *Mbullet = CCSprite::create("bullet.png");
	//设置位置
	Mbullet->setPosition(ccp(monster->getPositionX(), monster->getPositionY() + monster->getContentSize().height / 2));
	//添加到图层
	this->addChild(Mbullet);
	//保存子弹
	bulletMonsterArray.addObject(Mbullet);
	/////////////////////////////////////////////////////////////////////////////////////
}

//实现敌机死亡的函数   CCObject* pSender谁调用了这个函数，就会将谁作为参数传过来
void HelloWorld::MonsterDeath(CCNode* pSender){
	//随机生成一个奖励物品
	CCSprite *award = CCSprite::create("award_type_1.png");///////////////////////
	//设置随机生成数字
	rand();
	//销毁播放完死亡动画的敌机
	CCSprite *monster = (CCSprite*)pSender;
	//设置奖励物品位置
	award->setPosition(monster->getPosition());
	//添加奖励物品到图层
	this->addChild(award);
	//将生成的奖励物品存到数组中
	awardArray.addObject(award);


	monster->removeFromParentAndCleanup(true);

}
//实现结算函数
void HelloWorld::scoreCount(){
	//所有敌机炸毁
	//取出敌机
	for (int i = 0; i < monsterArray.count(); i++){
		//取出元素
		CCSprite *monster = (CCSprite*)monsterArray.objectAtIndex(i);
		//播放所有敌机死亡动画
		if (monster->getTag() == 0){
			//创建图片收集者
			CCAnimation *animation = CCAnimation::create();
			animation->addSpriteFrameWithFileName("enemy0down1.png");
			animation->addSpriteFrameWithFileName("enemy0down2.png");
			animation->addSpriteFrameWithFileName("enemy0down3.png");
			animation->addSpriteFrameWithFileName("enemy0down4.png");
			//设置播放速度
			animation->setDelayPerUnit(0.25f);
			//将收集的图片制作成动画
			CCAnimate *animate = CCAnimate::create(animation);
			//播放动画
			//monster->runAction(animate);
			//播放顺序动画
			monster->runAction(animate);
			monster->removeFromParentAndCleanup(true);
		}
		else if (monster->getTag() == 1)
		{
			//创建图片收集者
			CCAnimation *animation = CCAnimation::create();
			animation->addSpriteFrameWithFileName("enemy1down1.png");
			animation->addSpriteFrameWithFileName("enemy1down2.png");
			animation->addSpriteFrameWithFileName("enemy1down3.png");
			animation->addSpriteFrameWithFileName("enemy1down4.png");
			//设置播放速度
			animation->setDelayPerUnit(0.25f);
			//将收集的图片制作成动画
			CCAnimate *animate = CCAnimate::create(animation);
			//播放动画
			//monster->runAction(animate);
			//播放顺序动画
			monster->runAction(animate);
			monster->removeFromParentAndCleanup(true);
		}
		else
		{
			//创建图片收集者
			CCAnimation *animation = CCAnimation::create();
			animation->addSpriteFrameWithFileName("enemy2_down1.png");
			animation->addSpriteFrameWithFileName("enemy2_down2.png");
			animation->addSpriteFrameWithFileName("enemy2_down3.png");
			animation->addSpriteFrameWithFileName("enemy2_down4.png");
			animation->addSpriteFrameWithFileName("enemy2_down5.png");
			//设置播放速度
			animation->setDelayPerUnit(0.25f);
			//将收集的图片制作成动画
			CCAnimate *animate = CCAnimate::create(animation);
			//播放动画
			//monster->runAction(animate);
			//播放顺序动画
			monster->runAction(animate);
			monster->removeFromParentAndCleanup(true);
		}
		//将怪物从数组中移除
		monsterArray.removeObjectAtIndex(i);
		i--;
	}
	//移除子弹
	//清除上一局子弹
	for (int i = 0; i < bulletArray.count(); i++){
		//移除下标为i的子弹
		CCSprite *bullet = (CCSprite*)bulletArray.objectAtIndex(i);
		bullet->removeFromParentAndCleanup(true);
	}
	//全部子弹移除后，清空数组
	bulletArray.removeAllObjects();

	//移除子弹
	//清除上一局子弹
	for (int i = 0; i < bulletMonsterArray.count(); i++){
		//移除下标为i的子弹
		CCSprite *bullet = (CCSprite*)bulletMonsterArray.objectAtIndex(i);
		bullet->removeFromParentAndCleanup(true);
	}
	//全部子弹移除后，清空数组
	bulletMonsterArray.removeAllObjects();
	//清除上一局产生的敌机
	for (int i = 0; i < monsterArray.count(); i++){
		//取出元素
		CCSprite *monster = (CCSprite*)monsterArray.objectAtIndex(i);
		monster->removeFromParentAndCleanup(true);
	}
	//清空数组
	monsterArray.removeAllObjects();
	//清除奖励物品//////////////////////////////////////////////////////////////////
	for (int i = 0; i < awardArray.count(); i++){
		//取出元素
		CCSprite *award = (CCSprite*)awardArray.objectAtIndex(i);
		//销毁
		award->removeFromParentAndCleanup(true);
	}
	//清空数组
	awardArray.removeAllObjects();

	//隐藏主界面的一些控件
	//飞机
	//销毁
	//plane->removeFromParentAndCleanup(true);
	//隐藏
	plane->setVisible(false);

	//显示新控件
	//获取屏幕宽高
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	////给主界面背景赋值
	//CountBg = CCSprite::create("background.png");
	////设置位置
	//CountBg->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	////添加到图层
	//this->addChild(CountBg);
	scoreCJ = CCLabelTTF::create("Score: ", "Arial", 30);
	//位置
	scoreCJ->setPosition(ccp(visibleSize.width / 2 - scoreCJ->getContentSize().width / 2, visibleSize.height / 2 + 150));
	//添加到层
	this->addChild(scoreCJ);
	//分数标签
	scoreFS = CCLabelTTF::create("0", "Arial", 30);
	//位置
	scoreFS->setPosition(ccp(scoreCJ->getPositionX() + scoreCJ->getContentSize().width / 2 + scoreFS->getContentSize().width / 2 + 30, visibleSize.height / 2 + 150));
	//添加到层
	this->addChild(scoreFS);
	//写入计分板中
	char str[100] = { '0' };
	sprintf(str, "%d", score);
	scoreFS->setString(str);

	//2个按钮
	//重新开始
	//给开始游戏按钮赋值
	reStart = CCMenuItemImage::create("restart_nor.png", "restart_sel.png", this, menu_selector(HelloWorld::menuReStartCallback));
	//设置位置
	reStart->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 + 50));
	//给退出游戏按钮赋值
	returnMain = CCMenuItemImage::create("quit_nor.png", "quit_sel.png", this, menu_selector(HelloWorld::menuQuitCallback));
	//设置位置
	returnMain->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 - 50));

	//创建菜单
	//创建一个菜单
	CCMenu *menu = CCMenu::create(reStart, returnMain, NULL);
	//设置位置
	menu->setPosition(CCPointZero);
	//添加到图层
	this->addChild(menu);
}
//新界面隐藏函数
void HelloWorld::visibleCount(bool visible){
	scoreCJ->setVisible(visible);
	scoreFS->setVisible(visible);
	reStart->setVisible(visible);
	returnMain->setVisible(visible);
}

//
////实现结算页面的初始化
//void HelloWorld::initCount(){
//
//	//获取屏幕宽高
//	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
//	//给主界面背景赋值
//	CountBg = CCSprite::create("background.png");
//	//设置位置
//	CountBg->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
//	//添加到图层
//	this->addChild(CountBg);
//	scoreCJ = CCLabelTTF::create("分数: ", "Arial", 30);
//	//位置
//	scoreCJ->setPosition(ccp(visibleSize.width / 2 - scoreCJ->getContentSize().width/2, visibleSize.height / 2 + 150));
//	//添加到层
//	this->addChild(scoreCJ);
//	//分数标签
//	scoreFS =  CCLabelTTF::create("0", "Arial", 30);
//	//位置
//	scoreFS->setPosition(ccp(scoreCJ->getPositionX() + scoreCJ->getContentSize().width/2 + scoreFS->getContentSize().width/2, visibleSize.height / 2 + 150));
//	//添加到层
//	this->addChild(scoreFS);
//	//2个按钮
//	//重新开始
//	//给开始游戏按钮赋值
//	reStart = CCMenuItemImage::create("restart_nor.png", "restart_sel.png", this, menu_selector(HelloWorld::menuStartCallback));
//	//设置位置
//	reStart->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 + 50));
//	//给退出游戏按钮赋值
//	returnMain = CCMenuItemImage::create("quit_nor.png", "quit_sel.png", this, menu_selector(HelloWorld::menuQuitCallback));
//	//设置位置
//	returnMain->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 - 50));
//
//	//创建菜单
//	//创建一个菜单
//	CCMenu *menu = CCMenu::create(reStart, returnMain, NULL);
//	//设置位置
//	menu->setPosition(CCPointZero);
//	//添加到图层
//	this->addChild(menu);
//	//隐藏结算页面
//	visibleCount(false);
//}
//////结算页面控件显示或隐藏
//void HelloWorld::visibleCount(bool visible){
//	//bg
//	CountBg->setVisible(vis);
//	//标签
//	scoreCJ->setVisible(visible);
//	scoreFS->setVisible(visible);
//	//按钮
//	reStart->setVisible(visible);
//	returnMain->setVisible(visible);
//}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
#else
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}
void HelloWorld::menuReStartCallback(CCObject* pSender){
	score = 0;
	//隐藏主界面控件
	visibleMain(false);
	//显示游戏界面控件
	visibleGame(true);
	//隐藏结算页面
	visibleCount(false);
	//写入计分板中
	char str[100] = { '0' };
	sprintf(str, "%08d", score);
	scoreLabel->setString(str);
	//飞机复位
	//飞机复位
	//获取屏幕宽高
	CCSize visiblesize = CCDirector::sharedDirector()->getVisibleSize();
	plane->setPosition(ccp(visiblesize.width / 2, plane->getContentSize().height));

}
