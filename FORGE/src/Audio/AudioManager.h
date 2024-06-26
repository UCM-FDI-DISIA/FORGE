#pragma once
#ifndef AUDIO_H_
#define AUDIO_H_

#include <string>
#include <memory>
#include <unordered_map>
#include <unordered_set>

namespace irrklang {
	typedef float ik_f32;
	template <typename T>
	class vec3d;
	typedef vec3d<ik_f32> vec3df;
	class ISoundEngine;
}

namespace forge {
	class Vector3;
}

class Sound;
class SoundGenerator;
class AudioListener;

class AudioManager {
private:
	irrklang::ISoundEngine* engine;
	std::unordered_map<std::string, SoundGenerator*> soundLibrary;
	std::unordered_set<Sound*> currentSounds;
	AudioListener* currentListener;
	static std::unique_ptr<AudioManager> instance;
	static bool initialized;
	/// <summary>
	/// Inicializa el sistema de audio
	/// </summary>
	AudioManager();
public:
	/// <summary>
	/// Crea una instancia del AudioManager
	/// </summary>
	/// <returns>Si la inicializacion se completo o no</returns>
	static bool Init();
	/// <summary>
	/// Devuelve la instancia de AudioManager y si no existe devuelve un puntero a nulo
	/// </summary>
	/// <returns></returns>
	static AudioManager* GetInstance();
	AudioManager(AudioManager const&) = delete;
	void operator=(AudioManager const&) = delete;
	/// <summary>
	/// Cierra el sistema de audio
	/// </summary>
	~AudioManager();
	/// <summary>
	/// Actualiza los sonidos que existen
	/// </summary>
	void update();
	/// <summary>
	/// Agrega un sonido a la libreria de sonidos de audio
	/// </summary>
	/// <param name="name">Identificador del sonido</param>
	/// <param name="route">Archivo de sonido</param>
	/// <returns>Puntero al SoundGenerator creado. nullptr si no se pudo crear</returns>
	SoundGenerator* addSound(std::string const& name, std::string const& file);
	/// <summary>
	/// Accede al sonido con el identificador solicitado
	/// </summary>
	/// <param name="name">Identificador del sonido al que se quiere acceder</param>
	/// <returns>Puntero al sonido solicitado. nullptr si no existe</returns>
	Sound* getSound(std::string const& name);
	/// <summary>
	/// Elimina el sonido de los sonidos actuales y lo borra de memoria
	/// </summary>
	/// <param name="sound">Puntero del sonido a eliminar</param>
	/// <returns>Si se ha encontrado el sonido a eliminar y se ha eliminado</returns>
	bool removeSound(Sound* sound);
	/// <summary>
	/// Establece la position del escuchador de sonido
	/// </summary>
	/// <param name="position">Nueva posicion del escuchador</param>
	/// <param name="lookAt">Direccion a la que mira el escuchador</param>
	void setListenerPosition(forge::Vector3 const& position, forge::Vector3 const& lookAt);
	/// <summary>
	/// Registra el AudioListener pasado como el escuchador actual si no habia ya uno
	/// </summary>
	/// <param name="listener">Puntero al AudioListener que se quiere registrar</param>
	/// <returns>Booleano que indica si se ha podido registrar el listener</returns>
	bool registerListener(AudioListener* listener);
	/// <summary>
	/// Elimina el AudioListener pasado como escuchador actual si lo era
	/// </summary>
	/// <param name="listener">Puntero al AudioListener que se quiere desregistrar</param>
	/// <returns>Booleano que indica si el listener pasado era el registrado y se ha borrado</returns>
	bool deregisterListener(AudioListener* listener);

	#pragma region Conversores
	irrklang::vec3df forgeVector3ToIrrklangVec3(forge::Vector3 const& v) const;
	#pragma endregion
};

#endif