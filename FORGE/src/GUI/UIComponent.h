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
    GUIManager* gui;

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
    /// Crea un panel el cual ser� el contenedor del elemento de la UI
    /// </summary>	
    void createPanel();

    /// <summary>
    /// Crea el Overlay correspondiente a este componente
    /// </summary>
    /// <param name="depth"> Capa en la que se crea la Overlay</param>	
    void createOverlay(int depth);

    /// <summary>
    /// Destruye el panel contenedor del elemento de la UI
    /// </summary>	
    void destroyPanel();

    /// <summary>
    /// Destruye el Overlay correspondiente a este componente
    /// </summary>
    void destroyOverlay();

public:
    static const FORGE_API_VAR std::string id;

    /// <summary>
    /// Contructora de un componente de interfaz
    /// </summary>	
    UIComponent();

    /// <summary>
    /// Destructora
    /// </summary>	
    ~UIComponent();

    /// <summary>
    /// Inicializa el UIComponent con los parametros adecuados
    /// </summary>
    /// <param name="data"> Parametros necesarios para la iniciacion del componente</param>
    bool initComponent(ComponentData* data) override;

    #pragma region Getters
    /// <summary>
    /// Devuelve el tama�o actual
    /// </summary>	
    /// <returns>El tama�o actual</returns>
    //FORGE_API forge::Vector2 getSize() const;

    /// <summary>
    /// Devuelve la posicion actual
    /// </summary>	
    /// <returns>La posicion actual</returns>
    FORGE_API forge::Vector2 getPosition() const;
    #pragma endregion

    #pragma region Setter
    /// <summary>
    /// Cambiar la posicion del componente
    /// </summary>
    /// <param name="newPosition">La nueva posicion del componente</param>
    virtual FORGE_API void setPosition(forge::Vector2 const& p);

    /// <summary>
    /// Asigna un tama�o
    /// </summary>	
    /// <param name="data"> Tama�o a asignar</param>
    //virtual FORGE_API void setSize(forge::Vector2 const& s);

    /// <summary>
    /// Devuelve el texto
    /// </summary>	
    /// <param name="zO"> Profundidad</param>
    FORGE_API void setDepth(int zO);
    #pragma endregion

};