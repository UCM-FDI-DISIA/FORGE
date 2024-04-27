# FORGE un motor creado por *nullptr*

![FORGE-Logo](https://github.com/UCM-FDI-DISIA/FORGE/blob/main/FORGE-Logo.png)

## Autores
- Miguel Curros García ([MiguelCGa](https://github.com/MiguelCGa))
- Alejandro González Sanchez ([algonz39](https://github.com/algonz39))
- Rafael Vilches Hernández ([Zorromatamoscas](https://github.com/Zorromatamoscas))
- Rafael Argandoña Blácido ([Rafaa0514](https://github.com/Rafaa0514))
- Javier Murillo González ([LittleWallSt](https://github.com/LittleWallSt))
- Eduardo de Orellana Sánchez ([Edu-git1](https://github.com/Edu-git1))
- Daniel Alonso Herranz ([espiridife](https://github.com/espiridifen))
- Diego López Balboa ([DDiegoP](https://github.com/DDiegoP))
- Alberto Peñalba Martos ([albpenal](https://github.com/albpenal))
- Pablo González Arroyo ([PabloGonzalezArroyoo](https://github.com/PabloGonzalezArroyoo))
- Sofía Sánchez Fernández ([sosanc03](https://github.com/sosanc03))

## Descripción
**FORGE** es un motor de videojuegos desarrollado por 11 alumnos de la UCM el cual cuenta con todo lo necesario para crear juegos en 3D.

## Estructura
**FORGE** está contenido dentro de una solución de Visual Studio de C++, dentro de la cual hay diferentes proyectos dedicados a las distintas funcionalidades que tiene el motor:
- **Input:** Se encarga de gestionar toda la entrada del juego.
- **Render:** Dibuja en la ventana los elementos del juego.
- **EC (Entidad-Componente):** Implementa el sistema de escenas, entidades y componentes que se utilizan para gestionar los elementos del juego durante su ejecución.
- **Audio:** Gestiona y reproduce el sonido.
- **Physics:** Maneja todas las interacciones físicas.
- **GUI:** Implementa los elementos que conforman la interfaz de usuario.
- **Load:** Carga en el motor todos los recursos y configuración introducida por el usuario para adaptarla al funcionamiento del resto del motor.
- **Main:** Bucle principal del juego desde el que se comienza la ejecución y se llama a las diferentes implementaciones del motor durante todo el juego, así como variables generales que permitan
acceso al tiempo del programa como deltaTime.

Además de esto, **FORGE** cuenta también con varios componentes genéricos que sirven para implementar funcionalidades dentro de las entidades de un juego que generalmente se vayan a necesitar o que
faciliten el uso de los diferentes elementos del motor.

| Renderizado    | Posición y tamaño | Audio         | Física    | Interfaz |
|:--------------:|:-----------------:|:-------------:|:---------:|:--------:|
| Mesh           | Transform         | AudioListener | Collider  | Text     |
| Camera         | RectTransform     | AudioSource   | Rigidbody | Button   |
| Light          |                   |               |           | Image    |
| Animator       |                   |               |           |          |
| Billboard      |                   |               |           |          |
| ParticleSystem |                   |               |           |          |

Para todo lo mencionado anteriormente, **FORGE** usa las siguientes bibliotecas las cuales están unificadas en su implementación (wrappers) en un manager propio para cada módulo:

| Módulo                              | Manager                    | Biblioteca                                                                         |
|:-----------------------------------:|:--------------------------:|:----------------------------------------------------------------------------------:|
| **Input**                           | InputManager               | [SDL](https://www.libsdl.org)                                                      |
| **Interfaz y Render**               | GUIManager y RenderManager | [Ogre](https://www.ogre3d.org)                                                     |
| **Audio**                           | AudioManager               | [IrrKlang](https://www.ambiera.com/irrklang/)                                      |
| **EC y Load (Escenas y scripting)** | SceneManager y LoadManager | [Lua](https://www.lua.org) y [LuaBridge](https://github.com/vinniefalco/LuaBridge) |
| **Físicas**                         | PhysicsManager             | [Bullet](https://pybullet.org/wordpress/)                                          |

## Juegos
Existen dos juegos creados por nosotros en los cuales se pueden ver todas las características desarrolladas. Estos son:

- **Petanca, tremendas bolas:** un tremendo simulador de deportes basado en el popular juego de la petanca al puro estilo del Wii Sports. Los jugadores o equipos lanzan bolas con el objetivo de acercarlas
lo máximo posible a una bola más pequeña, el “boliche”. Cada jugador realiza lanzamientos desde un círculo de lanzamiento, buscando estratégicamente posicionar sus tremendas bolas cerca del “boliche”. El
ganador se determina según los puntos acumulados al final de la partida.

- **Uxia, a nécora de Montealto:** un juego basado en plataformas cuyo objetivo es alcanzar una guarida en la que se encuentra otra nécora, la nécora coquette. Durante los niveles, el jugador deberá evitar
los tentáculos de pulpo que le atacarán, así como otras nécoras que compiten con Uxía por ver a la nécora coquette y recolectar algas para llevarle un ramo a esta.

Los enlaces a dichos juegos están en la zona de enlaces.

## Enlaces
A continuación se listan los enlaces donde ver toda la información relativa al proyecto

- Motor: [FORGE](https://github.com/UCM-FDI-DISIA/FORGE) - [EDD](https://docs.google.com/document/d/1gnY79ZN1rDgsFYOg8CUmBzGkRfKNqf5E0Gg3asBUjL4/edit?usp=sharing)
- Juego: [Uxia, a nécora de montealto](https://github.com/UCM-FDI-DISIA/Uxia_a_necora_de_Montealto) - [GDD](https://docs.google.com/document/d/1qhXG5eayVSIhVhaa-odtMs7WHkoYvobOv148bnzgtfA/edit?usp=sharing)
- Juego: [Petanca, tremendas bolas](https://github.com/UCM-FDI-DISIA/PetancaTremendasBolas) - [GDD](https://docs.google.com/document/d/1KWhTAMYCEv_KCxSgf4dUYAY_Zr1mSU1htN8rSdoUbd0/edit?usp=sharing)
- Gestión: [nullptr](https://github.com/orgs/UCM-FDI-DISIA/projects/39)
- Documentos, presentaciones y archivos: [P3-G3 (Nullptr)](https://drive.google.com/drive/folders/1CcqhdkfPwWD9lIRAc1RixdXn9I-TEb-7?usp=sharing).
