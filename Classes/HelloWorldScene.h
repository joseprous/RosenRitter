#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    const int numShips = 200;
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::Scene* scene();
    
    // a selector callback
    void menuCloseCallback(Object* pSender);

    void addShip(int index, int x,int y);
    void addShips();

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

    virtual void ccTouchesMoved(cocos2d::Set *pTouches, cocos2d::Event *pEvent);
    virtual void ccTouchesEnded(cocos2d::Set *pTouches, cocos2d::Event *pEvent);
    virtual void ccTouchesBegan(cocos2d::Set *pTouches, cocos2d::Event *pEvent);

 protected:
    
    cocos2d::Array *_ships;
    cocos2d::SpriteBatchNode * _batchNode;

    int _touchMoved;
};

#endif // __HELLOWORLD_SCENE_H__
