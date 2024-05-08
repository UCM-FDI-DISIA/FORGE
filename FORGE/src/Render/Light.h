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
    RenderManager& renderManager; 

public:
    static const FORGE_API_VAR std::string id;

    FORGE_API Light();
    
    FORGE_API ~Light();

    FORGE_API bool initComponent(ComponentData* data) override;

    FORGE_API void onEnabled() override;

    FORGE_API void onDisabled() override;

	#pragma region Getters
    FORGE_API const int& getType() const;
	#pragma endregion
};

#endif // !LIGHT_H_