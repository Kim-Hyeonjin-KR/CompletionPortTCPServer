#pragma once
#include "global.h"


// std::unique_ptr<NetworkManager> NetworkManager::sInstance; ??

class InitSystem : PacketBase
{
private:

public:
	bool Init(u_short inPort);

};