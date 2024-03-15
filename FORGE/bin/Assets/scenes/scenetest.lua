local prefabs = {

}

local scenes = {
    Test = {
        jugador = {
            handler = "player",
            components = {
                Transform = {
                    position = {0, 0, 0},
                    scale = {0.25, 0.25, 0.25}
                },
                Mesh = {
                    mesh = "ninja.mesh"
                },
                TestMovement = {
                    name = "maincam"
                },
                Animator = {
                    activeAnimations = {
                        "Idle"
                    }
                }
            },
            children = {
                obstaculo = {
                    group = "obstacle",
                    components = {
                        Transform = {
                            position = {100, 0, -100},
                            scale = {10, 10, 10}
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