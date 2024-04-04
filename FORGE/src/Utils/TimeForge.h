#pragma once
#ifndef TIME_FORGE_H_
#define TIME_FORGE_H_
#include <ctime>
#include <memory>
class MainForge;
namespace forge {
	class __declspec(dllexport) Time {
	private:
		friend MainForge;
		
		static double _deltaTime;
		time_t previous;

		Time();
		static std::unique_ptr<Time> instance;
		static Time* getInstance();
		/// <summary>
		/// Inicializa el deltaTime
		/// </summary>
		void init() noexcept;
		/// <summary>
		/// Actualiza deltaTime en funcion al tiempo que pasara desde la ultima llamada al metodo
		/// </summary>
		void update() noexcept;
		//Al ser un singleton, no se puede copiar ni igualar
		Time(Time const&) = delete;
		void operator=(Time const&) = delete;
	public:
		/// <summary>
		/// Tiempo en segundos que ha pasado desde la anterior actualizacion
		/// </summary>
		static constexpr double const& deltaTime = _deltaTime;
		/// <summary>
		/// Tiempo en segundos cada el que se evaluan las operaciones fisicas
		/// </summary>
		static constexpr double fixedDeltaTime = 0.02;
	};
}
#endif // !TIME_FORGE_H_