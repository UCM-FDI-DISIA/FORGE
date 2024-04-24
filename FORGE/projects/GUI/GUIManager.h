#pragma once
#include <memory>
#include <unordered_map>
#include <string>

namespace Ogre {
	class OverlayManager;
	class Overlay;
	class OverlayContainer;
}

class GUIManager {
private:
	static std::unique_ptr<GUIManager> instance;
	static bool initialised;
	Ogre::OverlayManager* overlayManager;

	GUIManager();

public:
	/// <summary>
	/// Crea una instancia del UIManager
	/// </summary>
	/// <returns>Si la inicializacion fue correcta</returns>
	static bool Init();
	/// <returns>Devuelve una instancia al UIManager si existe, si no existe devuelve un puntero a nulo</returns>
	static GUIManager* GetInstance();

	~GUIManager();
};