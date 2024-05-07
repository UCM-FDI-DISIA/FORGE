#pragma once
#include "Component.h"
#include "Vector2.h"
#include "Vector4.h"

namespace Ogre {
    class OverlayContainer;
    class Overlay;
}
class GUIManager;
class RectTransform;

class UIComponent : public Component {
protected:
    // Referencia al GuiManager
    GUIManager& gui;

    // Nombre del elemento (para los nodos de Ogre)
    std::string elementID;

    // Referencia al transform
    RectTransform* transform;

    // Contenedores del elemento de ogre
    Ogre::OverlayContainer* overlayPanel;
    Ogre::Overlay* overlay;

    // Profundidad
    int zOrder;

    /// <summary>
    /// Crea un panel el cual será el contenedor del elemento de la UI
    /// </summary>	
    Ogre::OverlayContainer* createPanel();

    /// <summary>
    /// Crea el Overlay correspondiente a este componente
    /// </summary>
    /// <param name="depth"> Capa en la que se crea la Overlay</param>	
    Ogre::Overlay* createOverlay(Ogre::OverlayContainer* panel, int depth);

    /// <summary>
    /// Destruye el panel contenedor del elemento de la UI
    /// </summary>	
    void destroyPanel(Ogre::OverlayContainer* _panel);

    /// <summary>
    /// Destruye el Overlay correspondiente a este componente
    /// </summary>
    void destroyOverlay(Ogre::Overlay* _over);

public:
    static const FORGE_API_VAR std::string id;

    /// <summary>
    /// Contructora de un componente de interfaz
    /// </summary>	
    FORGE_API UIComponent();

    /// <summary>
    /// Destructora
    /// </summary>	
    FORGE_API ~UIComponent();

    /// <summary>
    /// Inicializa el UIComponent con los parametros adecuados
    /// </summary>
    /// <param name="data"> Parametros necesarios para la iniciacion del componente</param>
    FORGE_API bool initComponent(ComponentData* data) override;

    /// <summary>
    /// Agrega el elemento al canvas
    /// </summary>
    FORGE_API void onEnabled() override;

    /// <summary>
    /// Quita el elemento del canvas
    /// </summary>
    FORGE_API void onDisabled() override;

    /// <summary>
    /// Ajusta el UIComponent al nuevo ajuste de la ventana
    /// </summary>
    FORGE_API virtual void resize(forge::Vector2 const& prev, forge::Vector2 const& updated);

    #pragma region Getters
    /// <returns>
    /// La posicion actual
    /// </returns>
    FORGE_API forge::Vector2 const& getPosition() const;
    #pragma endregion

    #pragma region Setter
    /// <summary>
    /// Cambiar la posicion del componente
    /// </summary>
    /// <param name="newPosition">La nueva posicion del componente</param>
    FORGE_API virtual void setPosition(forge::Vector2 const& newPosition);

    /// <summary>
    /// Devuelve el texto
    /// </summary>	
    /// <param name="_zOrder">Profundidad</param>
    FORGE_API void setDepth(int _zOrder);
    #pragma endregion

};