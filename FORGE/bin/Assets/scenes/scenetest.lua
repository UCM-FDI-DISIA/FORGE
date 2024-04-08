local prefabs = {

}

local scenes = {
    Test = {
        jugador = {
            handler = "player",
            components = {
                Transform = {
                    position = {-30, 0, 0}
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
                    position = {-30, -50, 0},
                    rotation = {0, 0, -1, 3.14/6 }
                },
                 Collider = {
                    scale = {30, 10, 30},
                    shapeType = "Cube"
                }
            }
        },
        jugador2 = {
            handler = "player2",
            components = {
                Transform = {
                    position = {30, 0, 0}
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
        rampa2 = {
            handler = "rampa2",
            components = {
                Transform = {
                    position = {30, -50, 0},
                    rotation = {0, 0, 1, 3.14/6 }
                },
                 Collider = {
                    scale = {30, 10, 30},
                    shapeType = "Cube"
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