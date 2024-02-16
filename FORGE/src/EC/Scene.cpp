// #include "GameState.h"
// #include "../core/SDLApplication.h"

// // Constructor
// Scene::Scene() : entsByGroup_(), butNavigator(new ButtonNavigator()), gmCtrl_(gmCtrl()), lastButtonIndex(-1) {
//     for (auto & grpEnts : entsByGroup_) {
//         grpEnts.reserve(500); //Reserva espacio para cada lista
//     }
//     camera = addGameObject<Camera>();
//     pointer = addGameObject<Pointer>(_grp_POINTER);
// }

// // Destructor
// Scene::~Scene() {
//     for (auto& group : entsByGroup_) {
//         for (auto& e : group) {
//             delete e;
//             e = nullptr;
//         }
//     }
//     delete butNavigator;
// }

// // Actualiza los objetos de la escena
// void Scene::update() {
//     for (auto& group : entsByGroup_) {
//         for (auto e : group) {
//             e->update();
//         }
//     }

//     refresh();
// }

// // Dibuja la escena en pantalla
// void Scene::render() const {
//     for (auto& group : entsByGroup_) {
//         for (auto e : group) {
//             e->render();
//         }
//     }
// }

// // Maneja el evento actual
// void Scene::handleInput() {
//     for (auto& group : entsByGroup_) {
//         for (auto e : group) {
//             e->handleInput();
//         }
//     }
// }

// // Borra todos los GameObject no vivos
// void Scene::refresh() {

//     for (grpId_type gId = 0; gId < maxGroupId; gId++) {
//         auto& grpEnts = entsByGroup_[gId];
//         grpEnts.erase(
//             std::remove_if(grpEnts.begin(), grpEnts.end(),
//                 [](Entity* e) {
//                     if (e->isAlive()) {
//                         return false;
//                     }
//                     else {
//                         delete e;
//                         return true;
//                     }
//                 }),
//             grpEnts.end());
//     }
// }


// // Devuelve la camara de la escena
// Camera* Scene::getCamera() const { return camera; }

// // Devuelve el navegador entre botones
// ButtonNavigator* Scene::getButtonNavigator() const { return butNavigator; }

// // Crear un botón especificado en la escena
// Button* Scene::createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key, float horizontalMult, float verticalMult) {
//     AnimatorInfo aI = AnimatorInfo(key);
//     // Crear marco
//     Entity* frame = addGameObject();
//     frame->addComponent<Transform>(_fPos, Vector2D(), MM_BUTTONFRAME_WIDTH, MM_BUTTONFRAME_HEIGHT);
//     frame->addComponent<Animator>(SDLApplication::getTexture("ButtonFrame"), BUTTON_FRAME_SPRITE_WIDTH, BUTTON_FRAME_SPRITE_HEIGTH, aI.rows, aI.cols);

//     // Crear bot�n
//     return addGameObject<Button>(_cb, _bPos, aI, -1, frame, horizontalMult, verticalMult);
// }