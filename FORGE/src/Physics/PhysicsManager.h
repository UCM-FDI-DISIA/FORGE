#pragma once
#include <memory>
#include <unordered_map>
#include <string>

class Transform;
class RigidBody;
class DebugMode;
class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;
class btRigidBody;
class Collider;
class btQuaternion;
class btVector3;
namespace forge {
    class Vector3;
    class Quaternion;
};

class PhysicsManager {
private:
	static std::unique_ptr<PhysicsManager> instance;
    static bool initialised;

    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* world;
    std::unordered_map<btRigidBody*, Transform*> transforms;
    std::unordered_map<std::string, btRigidBody*> importantObjects;
    std::unordered_map<std::string, int> collisionLayers;
    std::unordered_map<std::string, std::unordered_map<std::string,bool>> collisionMatrix;
    DebugMode* debugger;
    bool debugMode;
    int numberOfLayers;

    std::list<Collider*> collisionedObjects;

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
    /// Crea una instancia del manager iniacializada
    /// </summary>
    static void Init();
    /// <returns>Devuelve una instancia al PhysicsManager</returns>
    static PhysicsManager* GetInstance();
    /// <summary>
    /// Inicializa el mundo de fisicas y pone una gravedad default (9.8)
    /// </summary>
    bool setup();
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
    /// <summary>
    /// Registra un btRigidbody y su transform asociado para busquedas y tratamiento de colisiones
    /// </summary>
    /// <param name="body">El btRigidbody a registrar</param>
    /// <param name="transform">El transform asociado al btRigidbody</param>
    void registerBody(btRigidBody* body, Transform* transform, std::string layer = "ALL");
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
    /// <summary>
    /// Devuelve true si puede a�adir la capa de colision al registro y false si ya estaba
    /// </summary>
    /// <param name="layerName: ">El nombre de la capa a a�adir</param>
    /// <returns></returns>
    bool addLayer(std::string const& layerName);

    void setCollideWith(std::string const& layer, std::vector<std::string> const& layersToCollide);

    bool checkContact(btRigidBody* body1, btRigidBody* body2);
#pragma region Conversores
    /// <summary>
    /// Convierte un vector de forge a uno de bullet
    /// </summary>
    /// <param name="vect"> Vector de forge</param>
    /// <returns> Vector de bullet</returns>
    btVector3 fromForgeToBtVect(forge::Vector3 const& vect);

    /// <summary>
    /// Convierte un vector de bullet a uno de forge
    /// </summary>
    /// <param name="vect"> Vector de bullet</param>
    /// <returns> Vector de forge</returns>
    forge::Vector3 fromBtVectToForge(btVector3 const& vect);

    /// <summary>
    /// Convierte un quaternion de forge a bullet
    /// </summary>
    /// <param name="quat"> Quaternion de forge</param>
    /// <returns> Quaternion de bullet</returns>
    btQuaternion fromForgeToBtQuat(forge::Quaternion const& quat);

    /// <summary>
    /// Convierte un quaternion de bullet a forge
    /// </summary>
    /// <param name="quat"> Quaternion de bullet</param>
    /// <returns> Quaternion de forge</returns>
    forge::Quaternion fromBtQuatToForge(btQuaternion const& quat);
#pragma endregion

};
