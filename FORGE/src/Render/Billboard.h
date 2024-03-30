#pragma once
#ifndef BILLBOARD_H_
#define BILLBOARD_H_
#include <Component.h>
#include <Vector3.h>
#include <Vector2.h>
#include <string>

class RenderManager;
namespace Ogre {
    class BillboardSet;
}

class Billboard : public Component {
private:
    int size;
    forge::Vector2 billboardDimensions;
    forge::Vector3 totalDimensions;
    std::string material;
    Ogre::BillboardSet* bSet;
    RenderManager* renderManager;

public:
    static const std::string id;

    Billboard();

    ~Billboard();

    void onEnabled() override;

    void onDisabled() override;

    void initComponent(ComponentData* data) override;

    void addBillboards();

    #pragma region Getters
    int getSize();
    float getBillboardWidth();
    float getBillboardHeight();
    std::string getMaterial();
    #pragma endregion

    #pragma region Setters
    void setMaterial(std::string newMaterial);

    void setSize(int newSize);
    #pragma endregion


};

#endif//BILLBOARD_H_