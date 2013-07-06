#include "HelloWorldScene.h"
//#include "SimpleAudioEngine.h"

using namespace cocos2d;
//using namespace CocosDenshion;

Scene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
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
    if ( !Layer::init() )
    {
        return false;
    }

    setTouchEnabled( true );

    _batchNode = SpriteBatchNode::create("ship.png", numShips);

    Sprite* background = Sprite::create("space.jpg");
    // scale the image (optional)
    background->setScale( 1.5f );
    // change the transform anchor point (optional)
    background->setAnchorPoint( ccp(0,0) );

    ParallaxNode* voidNode = ParallaxNode::create();
    voidNode->addChild(background, -1, ccp(1.0f,1.0f), PointZero);

    voidNode->addChild(_batchNode, 2, ccp(1.0f,1.0f), PointZero);
    addChild(voidNode, 0, 0);


    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    MenuItemImage *pCloseItem = MenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(Director::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    Menu* pMenu = Menu::create(pCloseItem, NULL);
    pMenu->setPosition( PointZero );
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    LabelTTF* pLabel = LabelTTF::create("Hello World", "Thonburi", 34);

    // ask director the window size
    Size size = Director::sharedDirector()->getWinSize();

    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );

    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    
    this->addShips();

    return true;
}

void HelloWorld::ccTouchesBegan(cocos2d::Set *pTouches, cocos2d::Event *pEvent)
{
    CCLog("HelloWorld::ccTouchesBegan");
    CCLog("_touchMoved = 0");
    _touchMoved = 0;
}


void HelloWorld::ccTouchesMoved(Set *pTouches, Event *pEvent)
{
    Touch *touch = (Touch*)pTouches->anyObject();
    Point diff = touch->getDelta();
    
    Node* node = getChildByTag(0);
    Point currentPos = node->getPosition();
    
    CCLog("distance %f",ccpDistance(PointZero, diff));
    if(ccpDistance(PointZero, diff) > 10){
        node->setPosition( ccpAdd(currentPos, diff) );
        CCLog("_touchMoved = 1");
        _touchMoved = 1;
    }
}

void HelloWorld::ccTouchesEnded(Set *pTouches, Event *pEvent)
{
    CCLog("HelloWorld::ccTouchesEnded");
    if(_touchMoved){ 
        _touchMoved = 0;
        return;
    }
    Touch* touch = (Touch*) pTouches->anyObject();
    
    Point location = touch->getLocation();

    Object* jt = NULL;

    Node * first = NULL;
    CCARRAY_FOREACH(_ships, jt){
        Sprite *target = dynamic_cast<Sprite*>(jt);
        Node* s = dynamic_cast<Node*>(jt);
        if(first == NULL){ 
            first = s;
            CCLog("location(%f,$f) first(%f,%f) ",location.x,location.y,first->getPosition().x,first->getPosition().y);
        }
        if(s==NULL){
            CCLog("child = NULL");
        }else{
            s->stopAllActions();
            s->runAction( MoveBy::create(1, ccp(location.x - first->getPosition().x, location.y - first->getPosition().y) ) );
            float o = location.x - s->getPosition().x;
            float a = location.y - s->getPosition().y;
            float at = (float) CC_RADIANS_TO_DEGREES( atanf( o/a) );
        
            if( a < 0 ) {
                if(  o < 0 )
                    at = 180 + fabs(at);
                else
                    at = 180 - fabs(at);    
            }
            s->runAction( RotateTo::create(1, at) );
        }
    }
    CCLog("_touchMoved = 0");
    _touchMoved = 0;
}


void HelloWorld::menuCloseCallback(Object* pSender)
{
    Director::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void HelloWorld::addShip(int index, int x,int y)
{
	Sprite *ship = Sprite::createWithTexture(_batchNode->getTexture());
    
	ship->setPosition( ccp(x,y) );
	_batchNode->addChild(ship,0,index);

	ship->setTag(1);
	_ships->addObject(ship);
}
void HelloWorld::addShips()
{
    int x,y,index=0;
    
    _ships = new Array;

    y=50;
    for(int j=0;j<5;j++){
        x=50;
        for(int i=0;i<40;i++){
            addShip(++index,x,y);
            x+=50;
        }
        y+=50;
    }
}
