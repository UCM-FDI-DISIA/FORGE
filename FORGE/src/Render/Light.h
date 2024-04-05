#pragma once
#ifndef LIGHT_H_
#define LIGHT_H_
#include <Component.h>
#include "ForgeExport.h"
class RenderManager;
namespace Ogre {
    class Light;
}

class Light : public Component {
private:
    int type;
    Ogre::Light* ogreLight;
    RenderManager* renderManager; 

public:
    static const FORGE_API_VAR std::string id;

    FORGE_API Light();
    
    FORGE_API ~Light();

    FORGE_API void initComponent(ComponentData* data) override;

	#pragma region setters
	#pragma endregion

	#pragma region getters
    FORGE_API const int& getType() const;
	#pragma endregion
};

#endif // !LIGHT_H_