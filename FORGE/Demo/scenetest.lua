local prefabs = {

}

local scenes = {
    Test = {
        jugador = {
            handler = "player",
            components = {
                Transform = {
                    position = {-10, 0 -10}
                },
                Mesh = {
                    mesh = "ogrehead.mesh"
                }
            }
        },
        obstaculo = {
            group = "obstacle",
            components = {
                Transform = {
                    position = {10, 0 -10}
                },
                Mesh = {
                    mesh = "Barrel.mesh"
                }
            }
        },
        cam = {
            components = {
                Transform = {
                    position = {0, 0, 0}
                },
                Camera = {
                    name = "maincam",
                    nearClipDistance = 1,
                    autoAspectRatio = true,
                    backgroundColor = {0.6, 0.3, 0.3}
                }
            }
        },
        luz = {
            components = {
                Transform = {
                    rotation = {0, -1, 0, 0}
                },
                Light = {
                    type = 1
                }
            }
        }
    }
}

return prefabs, scenes