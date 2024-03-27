#pragma once
#ifndef LIGHT_H_
#define LIGHT_H_
#include <Component.h>
#include <OgreLight.h>
class RenderManager;


class Light : public Component {
private:
    int type;
    Ogre::Light* ogreLight;
    RenderManager* renderManager; 

public:
	static const std::string id;

    Light();
    
    ~Light();

    void initComponent(ComponentData* data) override;

    void setEnabled(bool newActive) override;

	#pragma region setters
	#pragma endregion

	#pragma region getters
    const int& getType() const;
	#pragma endregion
};

#endif // !LIGHT_H_