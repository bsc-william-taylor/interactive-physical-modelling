
#pragma once

#include "Win32Header.h"
#include <map>

class SceneFactory
{
    std::map<std::string, void*> assets;
public:
	SceneFactory() = default;
	~SceneFactory() = default;

    void pushAsset(const std::string& uniqueID, void* data)
    {
        if (assets.count(uniqueID) == 0)
        {
            assets[uniqueID] = data;
        }
    }
		
	template<typename T>
	T* grabAsset(const std::string& uniqueID)
	{
        if (assets.count(uniqueID) != 0)
        {
            return static_cast<T*>(assets[uniqueID]);
        }

        MessageBox(0, "Could Not Find Asset", uniqueID.c_str(), MB_OK);
        PostQuitMessage(0);
		return nullptr;
	}
};