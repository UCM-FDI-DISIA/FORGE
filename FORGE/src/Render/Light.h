#pragma once
#ifndef LIGHT_H_
#define LIGHT_H_
#include <Component.h>
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
	static const std::string id;

    Light();
    
    ~Light();

    bool initComponent(ComponentData* data) override;

    void onEnabled() override;

    void onDisabled() override;

	#pragma region setters
	#pragma endregion

	#pragma region getters
    const int& getType() const;
	#pragma endregion
};

#endif // !LIGHT_H_