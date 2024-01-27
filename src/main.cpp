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

		// Get right side menu
		auto menuR = this->getChildByID("right-side-menu");

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

		// Center menu position
		menuC->setPosition(0,0);

		// Get old chest position
		auto chestPos = dB->getPosition();
		
		/* Create an empty node disguised as the daily button

		(I really wish I knew how to stop incompatibilities
		without creating a fake invisible daily button)
		*/
		auto node = CCNode::create();
		node->setID("daily-chest-button");

		// Get both settings
		auto isOn = Mod::get()->getSettingValue<bool>("isOn");
		auto isMeow = Mod::get()->getSettingValue<bool>("isMeow");

		// Setting shenanigans (ik i'm new to modding)
		if (isOn == true) {
			menuR->removeChildByID("daily-chest-button");
			menuC->removeChildByID("daily-chest-button");
			node->setPosition(chestPos);
			menuR->addChild(node);
			dB->setPosition(winSize.width/2, winSize.height/3*0.85);
			menuC->addChild(dB);
			btn->setPosition(winSize.width/2*1.2, winSize.height/3*0.85);
		} else {
			menuC->removeChildByID("daily-chest-button");
			menuR->removeChildByID("daily-chest-button");
			dB->setPosition(chestPos);
			menuR->addChild(dB);
			node->setPosition(winSize.width/2, winSize.height/3*0.85);
			menuC->addChild(node);
			btn->setPosition(winSize.width/2, winSize.height/3*0.85);
		}

		if (isMeow == true) {
			menuC->addChild(btn);
		} else {
			menuC->removeChildByID("meow");
		}

		// The menu birth (I spent 1 hour wondering why my custom ccmenu didnt appear, guess what)
		this->addChild(menuC);

        return true;
	}

	// The cat job
	void onCat(CCObject*) {
		// El pepe ete sech
		FMODAudioEngine::sharedEngine()->playEffect("s3532.ogg"_spr, 1, 1, 1);
	}
};
