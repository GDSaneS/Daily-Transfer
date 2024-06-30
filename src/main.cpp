/**
 * Include the Geode headers.
 */
#include <Geode/Geode.hpp>

/**
 * Brings cocos2d and all Geode namespaces to the current scope.
 */
using namespace geode::prelude;

/**
 * `$modify` lets you extend and modify GD's classes.
 * To hook a function in Geode, simply $modify the class
 * and write a new function definition with the signature of
 * the function you want to hook.
 *
 * Here we use the overloaded `$modify` macro to set our own class name,
 * so that we can use it for button callbacks.
 *
 * Notice the header being included, you *must* include the header for
 * the class you are modifying, or you will get a compile error.
 *
 * Another way you could do this is like this:
 *
 * struct MyMenuLayer : Modify<MyMenuLayer, MenuLayer> {};
 */
#include <Geode/modify/MenuLayer.hpp>
class $modify(MyMenuLayer, MenuLayer) {
	/**
	 * Typically classes in GD are initialized using the `init` function, (though not always!),
	 * so here we use it to add our own button to the bottom menu.
	 *
	 * Note that for all hooks, your signature has to *match exactly*,
	 * `void init()` would not place a hook!
	*/
	bool init() {
		/**
		 * We call the original init function so that the
		 * original class is properly initialized.
		 */
		if (!MenuLayer::init()) {
			return false;
		}

		if (Mod::get()->getSettingValue<bool>("isOn")==false){
			return true;
		}

		auto onlyDaily = Mod::get()->getSettingValue<bool>("onlyDaily");

		auto menu = this->getChildByID("bottom-menu");
		auto menuR = this->getChildByID("right-side-menu");
		auto winSize = CCDirector::get()->getWinSize();

		float x = winSize.width/2;
		float y = menu->getPositionY()+menu->getContentHeight()*0.9;

		auto dailyB = menuR->getChildByID("daily-chest-button");

		if (onlyDaily == true){
			auto menuC = CCMenu::create(nullptr);
			this->addChild(menuC);
			menuC->setID("center-menu");
			menuC->setLayout(menu->getLayout());

			menuC->setPosition(0,0);
			menuC->setContentWidth(menu->getContentWidth());

			
			menuR->removeChildByID("daily-chest-button");
			menuC->addChild(dailyB);

			menuC->setPosition(x,y);

			menuC->updateLayout();

		} else {
			menuR->setLayout(menu->getLayout());

			menuR->setPosition(x,y);
			menuR->setContentWidth(menu->getContentWidth());

			menuR->updateLayout();
		}

		menu->updateLayout();

		return true;
	}
};
