// #pragma once
// #include <vector>
// #include "../gameObjects/GameObject.h"
// #include "../gameObjects/General Objects/Camera.h"
// #include "../gameObjects/General Objects/Pointer.h"
// #include "../core/ButtonNavigator.h"
// #include "../gameObjects/UI/Button.h"

// class SDLApplication;
// using namespace std;

// class Scene {
// protected:
//     Camera* camera;
//     Pointer* pointer;
//     ButtonNavigator* butNavigator;
//     GameControl& gmCtrl_;

//     array<std::vector<Entity*>, maxGroupId> entsByGroup_;
//     int lastButtonIndex;
// public:
//     // Constructor
//     Scene();
//     // Destructor
//     virtual ~Scene();
//     // Actualiza los objetos de la escea
//     virtual void update();
//     // Dibuja la escena en pantalla
//     virtual void render() const;
//     // Maneja el evento actual
//     virtual void handleInput();
//     // Borra todos los GameObject no vivos
//     void refresh();

//     //Inserta un nuevo GameObject a la escena indicando su grupo
//     template<typename T = Entity, typename ...Ts>
//     T* addGameObject(grpId group, Ts&& ...args) {
//         T* e = new T();
//         e->setAlive(true);
//         e->setContext(this, group);
//         e->initGameObject(std::forward<Ts>(args)...);
//         entsByGroup_[group].push_back(e);
//         return e;
//     }
//     //Inserta un nuevo GameObject a la escena en el grupo General
//     template<typename T = Entity, typename ...Ts>
//     T* addGameObject(Ts&& ...args) {
//         return addGameObject<T>(_grp_GENERAL, std::forward<Ts>(args)...);
//     }
//     // Devuelve una lista con el grupo seleccionado
//     inline const vector<Entity*>& getEntitiesByGroup(grpId_type gId) {
//         return entsByGroup_[gId];
//     }

//     // Devuelve la camara
//     Camera* getCamera() const;

//     // Devuelve el puntero
//     inline Pointer* getPointer() const { return pointer; }

//     // Devuelve el navegador entre botones
//     ButtonNavigator* getButtonNavigator() const;

//     // Crear un bot�n especificado en la escena
//     Button* createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key, float horizontalMult = 1.0f, float verticalMult = 1.0f);

//     inline void setLastIndex(int index) { lastButtonIndex = index; }
// };
