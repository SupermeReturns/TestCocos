#include "B2Sprite.h"

B2Sprite* B2Sprite::create (const std::string &filename)
	{
		B2Sprite *bs = new B2Sprite();
		if (bs && bs->initWithFile(filename))
		{
			bs->autorelease();
			return bs;
		}
		delete bs;
		return NULL;
	}
bool B2Sprite::initWithFile(const std::string &filename)
	{
		return Sprite::initWithFile(filename);
	}