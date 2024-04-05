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
                RigidBody = {
                    scale = {30, 30, 30},
                    mass = 1,
                    friction = 5,
                    restitution = 1,
                    shapeType = "Sphere",
                    static = false
                }
            }
        },
        rampa = {
            handler = "rampa",
            components = {
                Transform = {
                    position = {0, -50, 0},
                    rotation = {0, 0, 1, 3.14/6 }
                },
                RigidBody = {
                    scale = {30, 10, 30},
                    mass = 1,
                    friction = 5,
                    restitution = 1,
                    shapeType = "Cube",
                    static = true
                }
            }
        },

        obstaculo = {
            group = "obstacle",
            components = {
                Transform = {
                    position = {0, 0, 0},
                    scale = {5, 5, 5}
                },
                Mesh = {
                    mesh = "Barrel.mesh"
                },
                -- RigidBody = {
                --     scale = {1, 1, 1},
                --     mass = 0.1,
                --     friction = 0.5,
                --     restitution = 0.6,
                --     shapeType = "Box"
                -- }
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