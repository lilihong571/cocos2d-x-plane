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
	//�������¿���Ϸ��ť�Ļص�����
	void menuReStartCallback(CCObject* pSender);
	//������ʼ��Ϸ��ť�Ļص�����
	void menuStartCallback(CCObject* pSender);
	//�����˳���Ϸ��ť�Ļص�����
	void menuQuitCallback(CCObject* pSender);
	//�����������ֿ��صĻص�����
	void menuMusicBgCallback(CCObject* pSender);
	//������Ч���صĻص�����
	void menuMusicSoundCallback(CCObject* pSender);

	////////////////////////////////////////////////////////
	//�����������ʼ������
	void initMain();
	//������Ϸ�����ʼ������
	void initGame();
	//����������ؼ�����ʾ�����غ���
	void visibleMain(bool visible);
	//������Ϸ����ؼ�����ʾ�����غ���
	void visibleGame(bool visble);

	////////////////////////////////////////////////
	//����ҳ��ؼ���ʾ������
	//�������㺯��
	void scoreCount();
	void visibleCount(bool visible);
	
	////////////////////////////////////////////////////////////
	//����������ʼ����
	bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
	//���������ƶ�����
	void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
	//����������������
	void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);

	/////////////////////////////////////////////////////////////
	//��������������
	void update(float dt);
	//�����Զ�������������������л��ӵ�
	void myMonsterUpdate(float dt);
	//�����л����Զ������������
	void MonsterProduct(float dt);
	//�����Զ�������������������ӵ�
	void myUpdate(float dt);

	/////////////////////////////////////////////////////////////
	//�����л������ĺ���
	void MonsterDeath(CCNode* pSender);

	//�������Ƿɻ����ٵ��õĻص�����
	void destroyFunction();


	// implement the "static node()" method manually
	CREATE_FUNC(HelloWorld);
private:
	///////////////////////////////////////
	//����һ�������汳��
	CCSprite *mainBg;
	//����һ����ϷLog
	CCSprite *mainLog;
	//����һ����ʼ��Ϸ��ť
	CCMenuItemImage *mainStart;
	//����һ���˳���Ϸ��ť
	CCMenuItemImage *mainQuit;
	//����һ���������ֿ���
	CCMenuItemToggle *musicBg;
	//����һ����Ч����
	CCMenuItemToggle *musicSound;

	////////////////////////////////////////////////
	//����һ����Ϸ���汳��
	CCSprite *gameBg1;
	CCSprite *gameBg2;
	//����һ������
	CCSprite *plane;
	//��ǩ������ʾ
	CCLabelTTF *Label;
	//��ǩ���ڼƷ�
	CCLabelTTF *scoreLabel;
	//ͳ�Ʒ���
	int score = 0;

	/////////////////////////////////////////////
	//����һ�����ж���
	CCAction *flyAction;
	//����һ�����ٶ���
	CCAction *destroyAction;

	//////////////////////////////////////////////
	//����һ���ӵ�����
	CCArray bulletArray;
	//�����л����ӵ�����
	CCArray bulletMonsterArray;
	//�����л�����
	CCArray monsterArray;
	//����������Ʒ����
	CCArray awardArray;
	//������Ʒ��ʣ��ʱ��
	float awardTime;

	///////////////////////////////////////////
	//��������ҳ����ʾ������
	//�ɼ���ǩ
	CCLabelTTF *scoreCJ;
	//������ǩ
	CCLabelTTF *scoreFS;
	//2����ť
	//���¿�ʼ
	CCMenuItemImage *reStart;
	//�ص�������
	CCMenuItemImage *returnMain;

	
};

#endif // __HELLOWORLD_SCENE_H__
