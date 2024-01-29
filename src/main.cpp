/**
 * Include the Geode headers.
 */
#include <Geode/Geode.hpp>
/**
 * Required to modify the MenuLayer class
 */
#include <Geode/modify/MenuLayer.hpp>
/**
 * Brings cocos2d and all Geode namespaces 
 * to the current scope.
 */
using namespace geode::prelude;

/**
 * `$modify` lets you extend and modify GD's 
 * classes; to hook a function in Geode, 
 * simply $modify the class and write a new 
 * function definition with the signature of 
 * the one you want to hook.
 */
class $modify(Menu, MenuLayer) {

	bool init(){
		if (!MenuLayer::init())
            return false;

		// Our code!

		// Get win size
		auto winSize = CCDirector::get()->getWinSize();

		float i = winSize.width/10;
		float j = winSize.height/10;

		// Get right side menu
		auto menuR = this->getChildByID("right-side-menu");
		
		auto sizeR = menuR->getContentSize();
		float rx = sizeR.height;
		float ry = sizeR.width;
		auto sizeR2 = {rx, ry};


		// Get daily Button
		auto dB = menuR->getChildByID("daily-chest-button");

		// Cat texture
		auto lelo = CCSprite::create("lelo.png"_spr);

		// Cat button
    	auto btn = CCMenuItemSpriteExtra::create(
        	lelo, this, menu_selector(Menu::onCat)
    	);
		btn->setID("meow");

		// Create a "center menu"
		auto menuC = CCMenu::create(nullptr);
		menuC->setID("center-menu");

		// Center menu position
		menuC->setPosition(0,0);

		// Get old chest position
		auto chestPos = dB->getPosition();


		// Get both settings
		auto isOn = Mod::get()->getSettingValue<bool>("isOn");
		auto isMeow = Mod::get()->getSettingValue<bool>("isMeow");
		auto fullHouse = Mod::get()->getSettingValue<bool>("fullHouse");
		float gap = Mod::get()->getSettingValue<double>("gap");

		auto childs = menuR->getChildren();

		auto lay = menuR->getLayout();
		auto horiz = RowLayout::create()->setGap(gap);
		
		// Setting shenanigans (ik i'm new to modding)
		if (isOn == true) {

		
			
			auto posY = this->getChildByID("main-menu")->getPositionY() - this->getChildByIDRecursive("play-button")->getPositionY();
			
			menuC->setPosition(0.5*winSize.width, posY);
			menuC->setContentSize({2*rx,ry});
			menuC->setAnchorPoint({0.5,0.9});
			menuC->setLayout(horiz);

			if (fullHouse == true) {
				
				if (Loader::get()->isModLoaded("abb2k.backup")){
					posY = posY + 23.75f;
				}
				//menuC->setPosition(menuR->getPosition());
				menuR->setPosition(0.5*winSize.width, posY);
				//menuC->setContentSize(menuR->getContentSize());
				menuR->setContentSize({2*rx,ry});
				//menuC->setAnchorPoint(menuR->getAnchorPoint());
				menuR->setAnchorPoint({0.5,0.9});
				//menuR->setLayout(RowLayout::create()
				//	->setGap(gap)
				//);
				menuR->setLayout(menuC->getLayout());
				menuC->setLayout(lay);

				//Vertical C
				/*menuC->alignItemsVertically();
				menuC->setLayout(ColumnLayout::create());
				menuC->updateLayout();*/
				
			} else {

				menuR->removeChildByID("daily-chest-button");
				menuC->addChild(dB);
			}
		} 

		if (isMeow == true) {
			if (fullHouse == true) {
				menuR->addChild(btn);
			} else {
				menuC->addChild(btn);
				menuC->setLayout(RowLayout::create());
				menuC->updateLayout();
			}
		} else {
			menuC->removeChildByID("meow");
			menuR->removeChildByID("meow");
		}

		// The menu birth (I spent 1 hour wondering why my custom ccmenu didnt appear, guess what)
		this->addChild(menuC);
		menuC->setLayout(horiz);

        return true;
	}

	// The cat job
	void onCat(CCObject*) {
		// El pepe ete sech
		FMODAudioEngine::sharedEngine()->playEffect("s3532.ogg"_spr, 1, 1, 1);
	}
};