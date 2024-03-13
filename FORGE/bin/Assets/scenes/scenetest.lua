local prefabs = {

}

local scenes = {
    Test = {
        jugador = {
            handler = "player",
            components = {
                Transform = {
                    position = {0, 0, 0}
                },
                Mesh = {
                    mesh = "ogrehead.mesh"
                },
                TestMovement = {
                    name = "maincam"
                }
            },
                obstaculo = {
                    group = "obstacle",
                    components = {
                        Transform = {
                            position = {100, 0, -100},
                            scale = {5, 5, 5}
                        },
                        Mesh = {
                            mesh = "Barrel.mesh"
                        }
                    }
                }
            }
        },
        cam = {
            components = {
                Transform = {
                    position = {0, 0, 140}
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
                    position = {20, 80, 0}
                },
                Light = {
                    type = 0 
                }
            }
        }
    }
}

return prefabs, scenes