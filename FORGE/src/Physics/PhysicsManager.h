#pragma once
#include <memory>
#include <unordered_map>
#include <btBulletDynamicsCommon.h>


class Transform;
class RigidBody;
class DebugMode;
namespace forge {
    class Vector3;
};

class PhysicsManager {
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
    /// Destructora del physics manager.
    /// </summary>
    ~PhysicsManager();

    /// <summary>
    /// Inicializa el mundo de fisicas y pone una gravedad default (9.8)
    /// </summary>
    void initPhysics();

    /// <summary>
    /// Dibuja los wireframes de los cuerpos fisicos en el mundo de fisicas
    /// </summary>
    void drawDebug();

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
    static PhysicsManager* GetInstance();
    
    /// <summary>
    /// Registra un btRigidbody y su transform asociado para busquedas y tratamiento de colisiones
    /// </summary>
    /// <param name="body">El btRigidbody a registrar</param>
    /// <param name="transform">El transform asociado al btRigidbody</param>
    void registerBody(btRigidBody* body, Transform* transform);
    /// <summary>
    /// Registra una instancia de rigidBody y la guarda en un mapa por nombre
    /// </summary>
    void createImportantBody(RigidBody* body, std::string name);
    /// <summary>
    /// Borra un rigidBody
    /// </summary>
    void deleteBody(btRigidBody* body);
    /// <summary>
    /// Activa o desactiva la visibilidad de cuerpos
    /// </summary>
    /// @param enabled Sirve para activar o desactivar el mundo fisico
    void setDebug(bool enabled);

    /// <summary>
    /// Devuelve si el modo depuracion esta activo
    /// </summary>
    /// <returns>Si el modo depuracion esta activo</returns>
    bool isDebugModeEnabled();
};

