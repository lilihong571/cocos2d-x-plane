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
//������ʼ��Ϸ��ť�Ļص�����
void HelloWorld::menuStartCallback(CCObject* pSender){
	score = 0;
	//����������ؼ�
	visibleMain(false);
	//��ʾ��Ϸ����ؼ�
	visibleGame(true);
	
	////�������ٶ���
	//plane->runAction(destroyAction);
}
//�����˳���Ϸ��ť�Ļص�����
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
//�����������ֿ��صĻص�����
void HelloWorld::menuMusicBgCallback(CCObject* pSender){

}
//������Ч���صĻص�����
void HelloWorld::menuMusicSoundCallback(CCObject* pSender){

}
//�����������ʼ������
void HelloWorld::initMain(){
	//��ȡ��Ļ���
	CCSize visiblesize = CCDirector::sharedDirector()->getVisibleSize();
	//�������汳����ֵ
	mainBg = CCSprite::create("background.png");
	//����λ��
	mainBg->setPosition(ccp(visiblesize.width / 2, visiblesize.height / 2));
	//��ӵ�ͼ��
	this->addChild(mainBg);
	//����Ϸlog��ֵ
	mainLog = CCSprite::create("name.png");
	//����λ��
	mainLog->setPosition(ccp(visiblesize.width / 2, visiblesize.height - 200));
	//��ӵ�ͼ��
	this->addChild(mainLog);
	//����ʼ��Ϸ��ť��ֵ
	mainStart = CCMenuItemImage::create("start1.png", "start2.png", this, menu_selector(HelloWorld::menuStartCallback));
	//����λ��
	mainStart->setPosition(ccp(visiblesize.width / 2, visiblesize.height / 2 + 50));
	//���˳���Ϸ��ť��ֵ
	mainQuit = CCMenuItemImage::create("quit1.png", "quit2.png", this, menu_selector(HelloWorld::menuQuitCallback));
	//����λ��
	mainQuit->setPosition(ccp(visiblesize.width / 2, visiblesize.height / 2 - 50));
	//���������ֿ��ظ�ֵ
	musicBg = CCMenuItemToggle::createWithTarget(this,
		menu_selector(HelloWorld::menuMusicBgCallback),
		CCMenuItemImage::create("BgMusicToggle1.png", "BgMusicToggle1.png"),
		CCMenuItemImage::create("BgMusicToggle2.png", "BgMusicToggle2.png"),
		NULL);
	//����λ��
	musicBg->setPosition(ccp(visiblesize.width / 4, visiblesize.height / 4));
	//����Ч���ظ�ֵ
	musicSound = CCMenuItemToggle::createWithTarget(this,
		menu_selector(HelloWorld::menuMusicSoundCallback),
		CCMenuItemImage::create("SoundToggle1.png", "SoundToggle1.png"),
		CCMenuItemImage::create("SoundToggle2.png", "SoundToggle2.png"),
		NULL);
	//����λ��
	musicSound->setPosition(ccp(visiblesize.width / 4 * 3, visiblesize.height / 4));

	//����һ���˵�
	CCMenu *menu = CCMenu::create(mainStart, mainQuit, musicBg, musicSound, NULL);
	//����λ��
	menu->setPosition(CCPointZero);
	//��ӵ�ͼ��
	this->addChild(menu);
}
//������Ϸ�����ʼ������
void HelloWorld::initGame(){
	score = 0;
	//��ȡ��Ļ���
	CCSize visiblesize = CCDirector::sharedDirector()->getVisibleSize();
	//bg1
	gameBg1 = CCSprite::create("background.png");
	//����λ��
	gameBg1->setPosition(ccp(visiblesize.width / 2, visiblesize.height / 2));
	//��ӵ�ͼ��
	this->addChild(gameBg1);
	//bg2
	gameBg2 = CCSprite::create("background.png");
	//����λ��
	gameBg2->setPosition(ccp(gameBg1->getPositionX(), gameBg1->getPositionY() + gameBg2->getContentSize().height));
	//��ӵ�ͼ��
	this->addChild(gameBg2);

	//��Ϸ������ʾϵͳ��ֵ///////////////////////////////////////////
	Label = CCLabelTTF::create("Score: ", "Arial", 30);
	Label->setPosition(ccp(0 + Label->getContentSize().width / 2, visiblesize.height - Label->getContentSize().height / 2));
	this->addChild(Label);

	//��Ϸ������Ʒ�ϵͳ��ֵ
	scoreLabel = CCLabelTTF::create("00000000", "Arial", 30);
	scoreLabel->setPosition(ccp(0 + scoreLabel->getContentSize().width / 2 + 0 + Label->getContentSize().width, visiblesize.height - scoreLabel->getContentSize().height / 2));
	this->addChild(scoreLabel);
	//д��Ʒְ���
	char str[100] = { '0' };
	sprintf(str, "%08d", score);
	scoreLabel->setString(str);
	////////////////////////////////////////////////////////////////

	//�����Ǹ�ֵ
	plane = CCSprite::create("hero1.png");
	//����λ��
	plane->setPosition(ccp(visiblesize.width / 2, plane->getContentSize().height));
	//��ӵ�ͼ��
	this->addChild(plane);
	//�ռ�����ͼƬ
	CCAnimation *animation1 = CCAnimation::create();
	animation1->addSpriteFrameWithFileName("hero1.png");
	animation1->addSpriteFrameWithFileName("hero2.png");
	//����ͼƬ�л�֡��
	animation1->setDelayPerUnit(0.2f);
	//�������Ƿ�ص���ʼ״̬
	animation1->setRestoreOriginalFrame(true);
	//��ͼƬ�����ɶ���
	CCAnimate *animate1 = CCAnimate::create(animation1);
	//�����ж�����ֵ
	flyAction = CCRepeatForever::create(animate1);
	//���ò��ͷ�
	flyAction->retain();
	//�ռ�����ͼƬ
	CCAnimation *animation2 = CCAnimation::create();
	animation2->addSpriteFrameWithFileName("playerdeth1.png");
	animation2->addSpriteFrameWithFileName("playerdeth2.png");
	animation2->addSpriteFrameWithFileName("playerdeth3.png");
	animation2->addSpriteFrameWithFileName("playerdeth4.png");
	//����ͼƬ�л�֡��
	animation2->setDelayPerUnit(0.2f);
	//�������Ƿ�ص���ʼ״̬
	animation2->setRestoreOriginalFrame(true);
	//��ͼƬ�����ɶ���
	CCAnimate *animate2 = CCAnimate::create(animation2);
	//�����ж�����ֵ													*********************************************�������
	//destroyAction = CCSequence::create(animate2, CCCallFunc::create(this, SEL_CallFunc(&HelloWorld::destroyFunction)), NULL);
	destroyAction = CCSequence::create(animate2, CCCallFunc::create(this, SEL_CallFunc(&HelloWorld::scoreCount)), NULL);
	//scoreCount();
	//���ò��ͷ�
	destroyAction->retain();


	//������Ϸ����
	visibleGame(false);
}
//����������ؼ�����ʾ�����غ���
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
//������Ϸ����ؼ�����ʾ�����غ���
void HelloWorld::visibleGame(bool visble){
	//bg1
	gameBg1->setVisible(visble);
	//bg2
	gameBg2->setVisible(visble);
	//plane
	plane->setVisible(visble);
	//////////////////////////////////////////////////
	//��ʾϵͳ
	Label->setVisible(visble);
	//�Ʒ�ϵͳ
	scoreLabel->setVisible(visble);
	//////////////////////////////////////////////
	//awardTime����ʱЧ
	awardTime = -0.0f;
	//����ɼ�
	if (visble == true){
		//����Ĭ�ϵ�����
		scheduleUpdate();
		//���ŷ��ж���
		plane->runAction(flyAction);
		//��Ӵ����¼�����
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
		//�����Զ��������
		schedule(SEL_SCHEDULE(&HelloWorld::myUpdate), 0.15f, -1, 2.0f);
		//�����л������ĵ�����
		schedule(SEL_SCHEDULE(&HelloWorld::MonsterProduct), 1.0f, -1, 2.0f);
	}
	else
	{
		//�ر�Ĭ�ϵ�����
		unscheduleUpdate();
		//ֹͣ���ж���
		plane->stopAllActions();
		//�Ƴ���������
		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
		//�ر��Զ��������
		unschedule(SEL_SCHEDULE(&HelloWorld::myUpdate));
		//�رյл������Զ��������
		unschedule(SEL_SCHEDULE(&HelloWorld::MonsterProduct));

		//�����һ���ӵ�
		for (int i = 0; i < bulletArray.count(); i++){
			//�Ƴ��±�Ϊi���ӵ�
			CCSprite *bullet = (CCSprite*)bulletArray.objectAtIndex(i);
			bullet->removeFromParentAndCleanup(true);
		}
		//ȫ���ӵ��Ƴ����������
		bulletArray.removeAllObjects();

		//�ɻ���λ
		//��ȡ��Ļ���
		CCSize visiblesize = CCDirector::sharedDirector()->getVisibleSize();
		plane->setPosition(ccp(visiblesize.width / 2, plane->getContentSize().height));

		//�����һ�ֲ����ĵл�
		for (int i = 0; i < monsterArray.count(); i++){
			//ȡ��Ԫ��
			CCSprite *monster = (CCSprite*)monsterArray.objectAtIndex(i);
			monster->removeFromParentAndCleanup(true);
		}
		//�������
		monsterArray.removeAllObjects();

		//���������Ʒ//////////////////////////////////////////////////////////////////
		for (int i = 0; i < awardArray.count(); i++){
			//ȡ��Ԫ��
			CCSprite *award = (CCSprite*)awardArray.objectAtIndex(i);
			//����
			award->removeFromParentAndCleanup(true);
		}
		//�������
		awardArray.removeAllObjects();

		score = 0;
	}
}
//��������������
void HelloWorld::update(float dt){
	//��ײ���
	//1.������л�
	for (int i = 0; i < monsterArray.count(); i++){
		//ȡ��Ԫ��
		CCSprite *monster = (CCSprite*)monsterArray.objectAtIndex(i);

		//�ж�������л��Ƿ���ײ(�����������������)
		if (plane->boundingBox().intersectsRect(monster->boundingBox())){
			//��������
			//�ر�Ĭ�ϵ�����
			unscheduleUpdate();
			//ֹͣ���ж���
			plane->stopAllActions();
			//�Ƴ���������
			CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
			//�ر��Զ��������
			unschedule(SEL_SCHEDULE(&HelloWorld::myUpdate));
			//�رյл������Զ��������
			unschedule(SEL_SCHEDULE(&HelloWorld::MonsterProduct));
			plane->runAction(destroyAction);
			//���������Ʒ//////////////////////////////////////////////////////////////////
			for (int i = 0; i < awardArray.count(); i++){
				//ȡ��Ԫ��
				CCSprite *award = (CCSprite*)awardArray.objectAtIndex(i);
				//����
				award->removeFromParentAndCleanup(true);
			}
			//�������
			awardArray.removeAllObjects();
		}

		//2.�жϵл����ӵ��Ƿ���ײ
		for (int j = 0; j < bulletArray.count(); j++){
			//ȡ���ӵ�
			CCSprite *bullet = (CCSprite*)bulletArray.objectAtIndex(j);
			//�ж�monster���ӵ��Ƿ���ײ
			if (monster->boundingBox().intersectsRect(bullet->boundingBox())){
				//�ӵ�����
				//���ӵ��������Ƴ�
				bulletArray.removeObjectAtIndex(j);
				j--;
				bullet->removeFromParentAndCleanup(true);
				//�л��������������������ַɻ���
				switch (monster->getTag())
				{
					//����С�л���ը����
				case 0:
				{
						  //����ͼƬ�ռ���
						  CCAnimation *animation = CCAnimation::create();
						  animation->addSpriteFrameWithFileName("enemy0down1.png");
						  animation->addSpriteFrameWithFileName("enemy0down2.png");
						  animation->addSpriteFrameWithFileName("enemy0down3.png");
						  animation->addSpriteFrameWithFileName("enemy0down4.png");
						  //���ò����ٶ�
						  animation->setDelayPerUnit(0.25f);
						  //���ռ���ͼƬ�����ɶ���
						  CCAnimate *animate = CCAnimate::create(animation);
						  //���Ŷ���
						  //monster->runAction(animate);
						  //����˳�򶯻�
						  monster->runAction(CCSequence::create(animate,
							  CCCallFuncN::create(this, SEL_CallFuncN(&HelloWorld::MonsterDeath)), NULL));

				}
					//��һ�ַɻ�//�Ʒ�ϵͳ�Ʒ�
					score += 10;
					break;
					//�������͵л�
				case 1:
				{
						  //����ͼƬ�ռ���
						  CCAnimation *animation = CCAnimation::create();
						  animation->addSpriteFrameWithFileName("enemy1down1.png");
						  animation->addSpriteFrameWithFileName("enemy1down2.png");
						  animation->addSpriteFrameWithFileName("enemy1down3.png");
						  animation->addSpriteFrameWithFileName("enemy1down4.png");
						  //���ò����ٶ�
						  animation->setDelayPerUnit(0.25f);
						  //���ռ���ͼƬ�����ɶ���
						  CCAnimate *animate = CCAnimate::create(animation);
						  //���Ŷ���
						  //monster->runAction(animate);
						  //����˳�򶯻�
						  monster->runAction(CCSequence::create(animate,
							  CCCallFuncN::create(this, SEL_CallFuncN(&HelloWorld::MonsterDeath)), NULL));

				}
					//��2�ַɻ�//�Ʒ�ϵͳ�Ʒ�
					score += 20;
					break;
					//���д��͵л�
				case 2:
				{
						  //����ͼƬ�ռ���
						  CCAnimation *animation = CCAnimation::create();

						  animation->addSpriteFrameWithFileName("enemy2_down1.png");
						  animation->addSpriteFrameWithFileName("enemy2_down2.png");
						  animation->addSpriteFrameWithFileName("enemy2_down3.png");
						  animation->addSpriteFrameWithFileName("enemy2_down4.png");
						  animation->addSpriteFrameWithFileName("enemy2_down5.png");
						  //���ò����ٶ�
						  animation->setDelayPerUnit(0.25f);
						  //���ռ���ͼƬ�����ɶ���
						  CCAnimate *animate = CCAnimate::create(animation);
						  //���Ŷ���
						  //monster->runAction(animate);
						  //����˳�򶯻�
						  monster->runAction(CCSequence::create(animate,
							  CCCallFuncN::create(this, SEL_CallFuncN(&HelloWorld::MonsterDeath)), NULL));

				}
					//��һ�ַɻ�//�Ʒ�ϵͳ�Ʒ�
					score += 50;
					break;
				default:
					break;
				}

				//д��Ʒְ���
				char str[100] = { '0' };
				sprintf(str, "%08d", score);
				scoreLabel->setString(str);

				//��������������Ƴ�
				monsterArray.removeObjectAtIndex(i);
				i--;
				//����û�����٣����������Ƴ���
				break;
			}

		}
	}
	//////////////////////////////////////////////////////////////////////
	////��ײ��⣬�л��ӵ�������
	for (int i = 0; i < bulletMonsterArray.count(); i++){

		//ȡ���ӵ�
		CCSprite *bullet = (CCSprite*)bulletMonsterArray.objectAtIndex(i);
		if (plane->boundingBox().intersectsRect(bullet->boundingBox())){
			//��������
			//�ر�Ĭ�ϵ�����
			unscheduleUpdate();
			//ֹͣ���ж���
			plane->stopAllActions();
			//�Ƴ���������
			CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
			//�ر��Զ��������
			unschedule(SEL_SCHEDULE(&HelloWorld::myUpdate));
			//�رյл������Զ��������
			unschedule(SEL_SCHEDULE(&HelloWorld::MonsterProduct));
			plane->runAction(destroyAction);
			//�ӵ�����
			//���ӵ��������Ƴ�
			bulletMonsterArray.removeObjectAtIndex(i);
			i--;
			bullet->removeFromParentAndCleanup(true);
			//���������Ʒ//////////////////////////////////////////////////////////////////
			for (int i = 0; i < awardArray.count(); i++){
				//ȡ��Ԫ��
				CCSprite *award = (CCSprite*)awardArray.objectAtIndex(i);
				//����
				award->removeFromParentAndCleanup(true);
			}
			//�������
			awardArray.removeAllObjects();

		}
	}
	/////////////////////////////////////////////////////////////////////////

	//3.��������
	gameBg1->setPositionY(gameBg1->getPositionY() - 500 * dt);
	gameBg2->setPositionY(gameBg2->getPositionY() - 500 * dt);
	if (gameBg1->getPositionY() <= -gameBg1->getContentSize().height / 2){
		gameBg1->setPositionY(gameBg2->getPositionY() + gameBg1->getContentSize().height);
	}
	if (gameBg2->getPositionY() <= -gameBg2->getContentSize().height / 2){
		gameBg2->setPositionY(gameBg1->getPositionY() + gameBg2->getContentSize().height);
	}
	//4.�ӵ�����
	for (int i = 0; i < bulletArray.count(); i++){
		//ȡ���ӵ�
		CCSprite *bullet = (CCSprite*)bulletArray.objectAtIndex(i);
		//����λ��
		bullet->setPositionY(bullet->getPositionY() + 500 * dt);
	}
	//����ɳ���Ļ���ӵ�
	for (int i = 0; i < bulletArray.count(); i++){
		//ȡ���ӵ�
		CCSprite *bullet = (CCSprite*)bulletArray.objectAtIndex(i);
		if (bullet->getPositionY() >= 900){
			//���������Ƴ�
			bulletArray.removeObjectAtIndex(i);
			//�±�-1
			i--;
			//�Ӳ����Ƴ�
			bullet->removeFromParentAndCleanup(true);
			//ָ�븳��
			bullet = nullptr;
		}
	}
	///////////////////////////////////////////////////////////
	//4.�ӵ�����
	for (int i = 0; i < bulletMonsterArray.count(); i++){
		//ȡ���ӵ�
		CCSprite *bullet = (CCSprite*)bulletMonsterArray.objectAtIndex(i);
		//����λ��
		bullet->setPositionY(bullet->getPositionY() - 500 * dt);
	}
	//����ɳ���Ļ���ӵ�
	for (int i = 0; i < bulletMonsterArray.count(); i++){
		//ȡ���ӵ�
		CCSprite *bullet = (CCSprite*)bulletMonsterArray.objectAtIndex(i);
		if (bullet->getPositionY() <= -100){
			//���������Ƴ�
			bulletMonsterArray.removeObjectAtIndex(i);
			//�±�-1
			i--;
			//�Ӳ����Ƴ�
			bullet->removeFromParentAndCleanup(true);
			//ָ�븳��
			bullet = nullptr;
		}
	}
	////////////////////////////////////////////////////////////
	//5.�л��ķ���������
	for (int i = 0; i < monsterArray.count(); i++){
		//ȡ��Ԫ��
		CCSprite *monster = (CCSprite*)monsterArray.objectAtIndex(i);
		//����Y����
		monster->setPositionY(monster->getPositionY() - 300 * dt);
	}
	//����
	for (int i = 0; i < monsterArray.count(); i++){
		//ȡ��Ԫ��
		CCSprite *monster = (CCSprite*)monsterArray.objectAtIndex(i);
		if (monster->getPositionY()<-monster->getContentSize().height / 2){
			monsterArray.removeObjectAtIndex(i);
			i--;
			monster->removeFromParentAndCleanup(true);
			monster = nullptr;
		}
	}
	//������Ʒ���������////////////////////////////////////////////
	for (int i = 0; i < awardArray.count(); i++){
		//ȡ����i��������Ʒ
		CCSprite * award = (CCSprite*)awardArray.objectAtIndex(i);
		//������Ʒ�����ǵ���ײ
		if (award->boundingBox().intersectsRect(plane->boundingBox())){
			//������Ʒ��ʧ
			//���������Ƴ�(ɾ������Ϊi��)
			awardArray.removeObjectAtIndex(i);
			i--;
			//����
			award->removeFromParentAndCleanup(true);
			//���ǿ�������ģʽ��������������������������������������������������������������������
			awardTime = 10.0f;
			continue;//���¿�ʼ���ѭ��
		}
		//���������Ʒ�Ѿ���������Ļ�⣬ֱ������
		if (award->getPositionY() < -50){
			//���������Ƴ�(ɾ������Ϊi��)
			awardArray.removeObjectAtIndex(i);
			i--;
			//����
			award->removeFromParentAndCleanup(true);
		}
		else
		{
			//������
			award->setPositionY(award->getPositionY() - 300 * dt);

		}
	}
}
////�����ɻ����ٵ��õĻص�����
void HelloWorld::destroyFunction(){
	////��ʾ������
	//visibleMain(true);
	////������Ϸ����
	//visibleGame(false);
	//scoreCount();
	//���ел�ը��
	//ȡ���л�
	for (int i = 0; i < monsterArray.count(); i++){
		//ȡ��Ԫ��
		CCSprite *monster = (CCSprite*)monsterArray.objectAtIndex(i);
		//�������ел���������
		if (monster->getTag() == 0){
			//����ͼƬ�ռ���
			CCAnimation *animation = CCAnimation::create();
			animation->addSpriteFrameWithFileName("enemy0down1.png");
			animation->addSpriteFrameWithFileName("enemy0down2.png");
			animation->addSpriteFrameWithFileName("enemy0down3.png");
			animation->addSpriteFrameWithFileName("enemy0down4.png");
			//���ò����ٶ�
			animation->setDelayPerUnit(0.25f);
			//���ռ���ͼƬ�����ɶ���
			CCAnimate *animate = CCAnimate::create(animation);
			//���Ŷ���
			//monster->runAction(animate);
			//����˳�򶯻�
			monster->runAction(animate);
			monster->removeFromParentAndCleanup(true);
		}
		else if (monster->getTag() == 1)
		{
			//����ͼƬ�ռ���
			CCAnimation *animation = CCAnimation::create();
			animation->addSpriteFrameWithFileName("enemy1down1.png");
			animation->addSpriteFrameWithFileName("enemy1down2.png");
			animation->addSpriteFrameWithFileName("enemy1down3.png");
			animation->addSpriteFrameWithFileName("enemy1down4.png");
			//���ò����ٶ�
			animation->setDelayPerUnit(0.25f);
			//���ռ���ͼƬ�����ɶ���
			CCAnimate *animate = CCAnimate::create(animation);
			//���Ŷ���
			//monster->runAction(animate);
			//����˳�򶯻�
			monster->runAction(animate);
			monster->removeFromParentAndCleanup(true);
		}
		else
		{
			//����ͼƬ�ռ���
			CCAnimation *animation = CCAnimation::create();
			animation->addSpriteFrameWithFileName("enemy2_down1.png");
			animation->addSpriteFrameWithFileName("enemy2_down2.png");
			animation->addSpriteFrameWithFileName("enemy2_down3.png");
			animation->addSpriteFrameWithFileName("enemy2_down4.png");
			animation->addSpriteFrameWithFileName("enemy2_down5.png");
			//���ò����ٶ�
			animation->setDelayPerUnit(0.25f);
			//���ռ���ͼƬ�����ɶ���
			CCAnimate *animate = CCAnimate::create(animation);
			//���Ŷ���
			//monster->runAction(animate);
			//����˳�򶯻�
			monster->runAction(animate);
			monster->removeFromParentAndCleanup(true);
		}
		//��������������Ƴ�
		monsterArray.removeObjectAtIndex(i);
		i--;
	}
}
//����������ʼ����
bool HelloWorld::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent){
	if (plane->boundingBox().containsPoint(pTouch->getLocation())){
		return true;
	}
	return false;
}
//���������ƶ�����
void HelloWorld::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent){
	//��ȡ��Ļ���
	CCSize visiblesize = CCDirector::sharedDirector()->getVisibleSize();
	//���÷ɻ�λ��
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
//����������������
void HelloWorld::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent){

}
//�����Զ�������������������ӵ�
void HelloWorld::myUpdate(float dt){


	//����һ���ӵ����飨�У�
	CCSprite *bullet = CCSprite::create("bullet1.png");
	//����λ��
	bullet->setPosition(ccp(plane->getPositionX(), plane->getPositionY() + plane->getContentSize().height / 2));
	//��ӵ�ͼ��
	this->addChild(bullet);
	//�����ӵ�
	bulletArray.addObject(bullet);


	if (awardTime > 0.0f){
		awardTime -= dt;
		//����һ���ӵ�����(��)
		CCSprite *bulletleft = CCSprite::create("bullet2.png");
		//����λ�á���λ��Ҫ�仯
		bulletleft->setPosition(ccp(plane->getPositionX() - plane->getContentSize().width / 3, plane->getPositionY() + plane->getContentSize().height / 2));
		//��ӵ�ͼ��
		this->addChild(bulletleft);
		//�����ӵ�
		bulletArray.addObject(bulletleft);

		//����һ���ӵ����飨�ң�
		CCSprite *bulletright = CCSprite::create("bullet2.png");
		//����λ�á���λ��ƫ���ǵ��ұ�
		bulletright->setPosition(ccp(plane->getPositionX() + plane->getContentSize().width / 3, plane->getPositionY() + plane->getContentSize().height / 2));
		//��ӵ�ͼ��
		this->addChild(bulletright);
		//�����ӵ�
		bulletArray.addObject(bulletright);
	}

}
////�����Զ�������������������ӵ�
//void HelloWorld::myMonsterUpdate(float dt){
//	
//}
//s�����л����Զ������������
void HelloWorld::MonsterProduct(float dt){

	CCSize visiblesize = CCDirector::sharedDirector()->getVisibleSize();

	int i = rand() % 3;//����0,1,2
	char str[15];
	sprintf(str, "enemy%d.png", i);

	//����һ�ܵл�
	CCSprite *monster = CCSprite::create(str);
	//λ��
	monster->setPositionY(852 + monster->getContentSize().height / 2);

	//monster->getContentSize().width/2   ��   ��Ļ���-�л���ȵ�һ��
	//200  -- 500
	//rand()%(500-200+1)+200
	monster->setPositionX(rand() % (int)(visiblesize.width - monster->getContentSize().width) + monster->getContentSize().width / 2);
	//���ñ��ֵ
	monster->setTag(i);
	this->addChild(monster);
	//�л�����������
	monsterArray.addObject(monster);


	/////////////////////////////////////////////////////////////////////////////////////
	//����һ���ӵ����飨�У�
	CCSprite *Mbullet = CCSprite::create("bullet.png");
	//����λ��
	Mbullet->setPosition(ccp(monster->getPositionX(), monster->getPositionY() + monster->getContentSize().height / 2));
	//��ӵ�ͼ��
	this->addChild(Mbullet);
	//�����ӵ�
	bulletMonsterArray.addObject(Mbullet);
	/////////////////////////////////////////////////////////////////////////////////////
}

//ʵ�ֵл������ĺ���   CCObject* pSender˭����������������ͻὫ˭��Ϊ����������
void HelloWorld::MonsterDeath(CCNode* pSender){
	//�������һ��������Ʒ
	CCSprite *award = CCSprite::create("award_type_1.png");///////////////////////
	//���������������
	rand();
	//���ٲ��������������ĵл�
	CCSprite *monster = (CCSprite*)pSender;
	//���ý�����Ʒλ��
	award->setPosition(monster->getPosition());
	//��ӽ�����Ʒ��ͼ��
	this->addChild(award);
	//�����ɵĽ�����Ʒ�浽������
	awardArray.addObject(award);


	monster->removeFromParentAndCleanup(true);

}
//ʵ�ֽ��㺯��
void HelloWorld::scoreCount(){
	//���ел�ը��
	//ȡ���л�
	for (int i = 0; i < monsterArray.count(); i++){
		//ȡ��Ԫ��
		CCSprite *monster = (CCSprite*)monsterArray.objectAtIndex(i);
		//�������ел���������
		if (monster->getTag() == 0){
			//����ͼƬ�ռ���
			CCAnimation *animation = CCAnimation::create();
			animation->addSpriteFrameWithFileName("enemy0down1.png");
			animation->addSpriteFrameWithFileName("enemy0down2.png");
			animation->addSpriteFrameWithFileName("enemy0down3.png");
			animation->addSpriteFrameWithFileName("enemy0down4.png");
			//���ò����ٶ�
			animation->setDelayPerUnit(0.25f);
			//���ռ���ͼƬ�����ɶ���
			CCAnimate *animate = CCAnimate::create(animation);
			//���Ŷ���
			//monster->runAction(animate);
			//����˳�򶯻�
			monster->runAction(animate);
			monster->removeFromParentAndCleanup(true);
		}
		else if (monster->getTag() == 1)
		{
			//����ͼƬ�ռ���
			CCAnimation *animation = CCAnimation::create();
			animation->addSpriteFrameWithFileName("enemy1down1.png");
			animation->addSpriteFrameWithFileName("enemy1down2.png");
			animation->addSpriteFrameWithFileName("enemy1down3.png");
			animation->addSpriteFrameWithFileName("enemy1down4.png");
			//���ò����ٶ�
			animation->setDelayPerUnit(0.25f);
			//���ռ���ͼƬ�����ɶ���
			CCAnimate *animate = CCAnimate::create(animation);
			//���Ŷ���
			//monster->runAction(animate);
			//����˳�򶯻�
			monster->runAction(animate);
			monster->removeFromParentAndCleanup(true);
		}
		else
		{
			//����ͼƬ�ռ���
			CCAnimation *animation = CCAnimation::create();
			animation->addSpriteFrameWithFileName("enemy2_down1.png");
			animation->addSpriteFrameWithFileName("enemy2_down2.png");
			animation->addSpriteFrameWithFileName("enemy2_down3.png");
			animation->addSpriteFrameWithFileName("enemy2_down4.png");
			animation->addSpriteFrameWithFileName("enemy2_down5.png");
			//���ò����ٶ�
			animation->setDelayPerUnit(0.25f);
			//���ռ���ͼƬ�����ɶ���
			CCAnimate *animate = CCAnimate::create(animation);
			//���Ŷ���
			//monster->runAction(animate);
			//����˳�򶯻�
			monster->runAction(animate);
			monster->removeFromParentAndCleanup(true);
		}
		//��������������Ƴ�
		monsterArray.removeObjectAtIndex(i);
		i--;
	}
	//�Ƴ��ӵ�
	//�����һ���ӵ�
	for (int i = 0; i < bulletArray.count(); i++){
		//�Ƴ��±�Ϊi���ӵ�
		CCSprite *bullet = (CCSprite*)bulletArray.objectAtIndex(i);
		bullet->removeFromParentAndCleanup(true);
	}
	//ȫ���ӵ��Ƴ����������
	bulletArray.removeAllObjects();

	//�Ƴ��ӵ�
	//�����һ���ӵ�
	for (int i = 0; i < bulletMonsterArray.count(); i++){
		//�Ƴ��±�Ϊi���ӵ�
		CCSprite *bullet = (CCSprite*)bulletMonsterArray.objectAtIndex(i);
		bullet->removeFromParentAndCleanup(true);
	}
	//ȫ���ӵ��Ƴ����������
	bulletMonsterArray.removeAllObjects();
	//�����һ�ֲ����ĵл�
	for (int i = 0; i < monsterArray.count(); i++){
		//ȡ��Ԫ��
		CCSprite *monster = (CCSprite*)monsterArray.objectAtIndex(i);
		monster->removeFromParentAndCleanup(true);
	}
	//�������
	monsterArray.removeAllObjects();
	//���������Ʒ//////////////////////////////////////////////////////////////////
	for (int i = 0; i < awardArray.count(); i++){
		//ȡ��Ԫ��
		CCSprite *award = (CCSprite*)awardArray.objectAtIndex(i);
		//����
		award->removeFromParentAndCleanup(true);
	}
	//�������
	awardArray.removeAllObjects();

	//�����������һЩ�ؼ�
	//�ɻ�
	//����
	//plane->removeFromParentAndCleanup(true);
	//����
	plane->setVisible(false);

	//��ʾ�¿ؼ�
	//��ȡ��Ļ���
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	////�������汳����ֵ
	//CountBg = CCSprite::create("background.png");
	////����λ��
	//CountBg->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	////��ӵ�ͼ��
	//this->addChild(CountBg);
	scoreCJ = CCLabelTTF::create("Score: ", "Arial", 30);
	//λ��
	scoreCJ->setPosition(ccp(visibleSize.width / 2 - scoreCJ->getContentSize().width / 2, visibleSize.height / 2 + 150));
	//��ӵ���
	this->addChild(scoreCJ);
	//������ǩ
	scoreFS = CCLabelTTF::create("0", "Arial", 30);
	//λ��
	scoreFS->setPosition(ccp(scoreCJ->getPositionX() + scoreCJ->getContentSize().width / 2 + scoreFS->getContentSize().width / 2 + 30, visibleSize.height / 2 + 150));
	//��ӵ���
	this->addChild(scoreFS);
	//д��Ʒְ���
	char str[100] = { '0' };
	sprintf(str, "%d", score);
	scoreFS->setString(str);

	//2����ť
	//���¿�ʼ
	//����ʼ��Ϸ��ť��ֵ
	reStart = CCMenuItemImage::create("restart_nor.png", "restart_sel.png", this, menu_selector(HelloWorld::menuReStartCallback));
	//����λ��
	reStart->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 + 50));
	//���˳���Ϸ��ť��ֵ
	returnMain = CCMenuItemImage::create("quit_nor.png", "quit_sel.png", this, menu_selector(HelloWorld::menuQuitCallback));
	//����λ��
	returnMain->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 - 50));

	//�����˵�
	//����һ���˵�
	CCMenu *menu = CCMenu::create(reStart, returnMain, NULL);
	//����λ��
	menu->setPosition(CCPointZero);
	//��ӵ�ͼ��
	this->addChild(menu);
}
//�½������غ���
void HelloWorld::visibleCount(bool visible){
	scoreCJ->setVisible(visible);
	scoreFS->setVisible(visible);
	reStart->setVisible(visible);
	returnMain->setVisible(visible);
}

//
////ʵ�ֽ���ҳ��ĳ�ʼ��
//void HelloWorld::initCount(){
//
//	//��ȡ��Ļ���
//	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
//	//�������汳����ֵ
//	CountBg = CCSprite::create("background.png");
//	//����λ��
//	CountBg->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
//	//��ӵ�ͼ��
//	this->addChild(CountBg);
//	scoreCJ = CCLabelTTF::create("����: ", "Arial", 30);
//	//λ��
//	scoreCJ->setPosition(ccp(visibleSize.width / 2 - scoreCJ->getContentSize().width/2, visibleSize.height / 2 + 150));
//	//��ӵ���
//	this->addChild(scoreCJ);
//	//������ǩ
//	scoreFS =  CCLabelTTF::create("0", "Arial", 30);
//	//λ��
//	scoreFS->setPosition(ccp(scoreCJ->getPositionX() + scoreCJ->getContentSize().width/2 + scoreFS->getContentSize().width/2, visibleSize.height / 2 + 150));
//	//��ӵ���
//	this->addChild(scoreFS);
//	//2����ť
//	//���¿�ʼ
//	//����ʼ��Ϸ��ť��ֵ
//	reStart = CCMenuItemImage::create("restart_nor.png", "restart_sel.png", this, menu_selector(HelloWorld::menuStartCallback));
//	//����λ��
//	reStart->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 + 50));
//	//���˳���Ϸ��ť��ֵ
//	returnMain = CCMenuItemImage::create("quit_nor.png", "quit_sel.png", this, menu_selector(HelloWorld::menuQuitCallback));
//	//����λ��
//	returnMain->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 - 50));
//
//	//�����˵�
//	//����һ���˵�
//	CCMenu *menu = CCMenu::create(reStart, returnMain, NULL);
//	//����λ��
//	menu->setPosition(CCPointZero);
//	//��ӵ�ͼ��
//	this->addChild(menu);
//	//���ؽ���ҳ��
//	visibleCount(false);
//}
//////����ҳ��ؼ���ʾ������
//void HelloWorld::visibleCount(bool visible){
//	//bg
//	CountBg->setVisible(vis);
//	//��ǩ
//	scoreCJ->setVisible(visible);
//	scoreFS->setVisible(visible);
//	//��ť
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
	//����������ؼ�
	visibleMain(false);
	//��ʾ��Ϸ����ؼ�
	visibleGame(true);
	//���ؽ���ҳ��
	visibleCount(false);
	//д��Ʒְ���
	char str[100] = { '0' };
	sprintf(str, "%08d", score);
	scoreLabel->setString(str);
	//�ɻ���λ
	//�ɻ���λ
	//��ȡ��Ļ���
	CCSize visiblesize = CCDirector::sharedDirector()->getVisibleSize();
	plane->setPosition(ccp(visiblesize.width / 2, plane->getContentSize().height));

}
