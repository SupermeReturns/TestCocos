#include "GameConfig.h"

bool kSOUND_ON = true;

void initAudioEngine() {
    // preload music and sound effects file
    SimpleAudioEngine::sharedEngine()->preloadEffect(kSX_TOUCH);
    SimpleAudioEngine::sharedEngine()->preloadEffect(kSX_RELEASE);
    SimpleAudioEngine::sharedEngine()->preloadEffect(kSX_CLASH);
    SimpleAudioEngine::sharedEngine()->preloadEffect(kSX_ROTATE);
    SimpleAudioEngine::sharedEngine()->preloadEffect(kSX_EXPLODE);
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(kMC_GAMESCENE);
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(kMC_OTHERSCENE);

    // init kSOUND_ON switch from file(true by default)
    kSOUND_ON = UserDefault::sharedUserDefault()->getFloatForKey("kSOUND_ON", true);
}