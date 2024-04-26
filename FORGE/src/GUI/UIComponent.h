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

    // Tamano del objeto
    forge::Vector2 size;

    // Contenedor del elemento de ogre
    Ogre::OverlayContainer* overlayPanel;
    Ogre::Overlay* overlay;

    // Porfundidad
    int zOrder;

    /// <summary>
    /// Crea un panel el cual será el contenedor de la Overlay
    /// </summary>	
    void createPanel();

    /// <summary>
    /// Crea el Overlay correspondiente a este componente
    /// </summary>
    /// <param name="depth"> Capa en la que se crea la Overlay</param>	
    void createOverlay(int depth);

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


    virtual FORGE_API void onEnabled();


    virtual FORGE_API void onDisabled();

    #pragma region Getters
    /// <summary>
    /// Devuelve el tamaño actual
    /// </summary>	
    /// <returns>El tamaño actual</returns>
    FORGE_API forge::Vector2 getSize() const;
    #pragma endregion

    #pragma region Setter
    /// <summary>
    /// Asigna un tamaño
    /// </summary>	
    /// <param name="data"> Tamaño a asignar</param>
    FORGE_API void setSize(forge::Vector2 const& s);

    /// <summary>
    /// Devuelve el texto
    /// </summary>	
    /// <param name="zO"> Profundidad</param>
    FORGE_API void setDepth(int zO);
    #pragma endregion

};