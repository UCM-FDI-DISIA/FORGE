#pragma once
#include <btBulletDynamicsCommon.h>
#include <memory>
#include <unordered_map>


class Transform;
class RigidBody;
class DebugMode;
namespace forge {
    class Vector3;
};

class PhysicsManager
{
private:
	static std::unique_ptr<PhysicsManager> instance;
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* world;
    std::unordered_map<btRigidBody*, Transform*> transforms;
    std::unordered_map<std::string, btRigidBody*> importantObjects;
    DebugMode* debugger;
    bool debugMode;

    /// <summary>
    /// Constructora del physics manager.
    /// </summary>
    PhysicsManager();

public:
    
    /// <summary>
    /// Inicializa el mundo de fisicas y pone una gravedad default (9.8)
    /// </summary>
    void initPhysics();

    /// <summary>
    /// Ordena al mundo de fisicas que actualice su estado. Avabza la simulacion 20ms, para que coincida con el tiempo de refresco de fixedUpdate
    /// </summary>
    void updatePhysics();
    
    /// <summary>
    /// Comprueba las colisiones ocurridas en la ultima simulacion y las resuelve segun los callbacks definidos.
    /// </summary>
    void handleCollisions();

    /// <summary>
   /// Cambia la gravedad del mundo fisico
   /// </summary>
    void changeGravity(forge::Vector3 newGravity);

    /// <returns>Devuelve una instancia al PhysicsManager</returns>
    static PhysicsManager* getInstance();
    /// <summary>
   /// Crea una instancia de rigidBody
   /// </summary>
    btRigidBody* createBody(RigidBody* body);
    /// <summary>
  /// Crea una instancia de rigidBody y la guarda en un mapa por nombre
  /// </summary>
    btRigidBody* createImportantBody(RigidBody* body, std::string name);
    /// <summary>
   /// Borra un rigidBody
   /// </summary>
    void deleteBody(btRigidBody* body);
    /// <summary>
   /// Activa o desactiva la visibilidad de cuerpos
   /// </summary>
   /// @param enabled Sirve para activar o desactivar el mundo fisico
    inline void setDebug(bool enabled) {
        debugMode = enabled;
    }
};

