local prefabs = {

}

local scenes = {
    Test = {
        jugador = {
            handler = "player",
            components = {
                Transform = {
                    position = {0, -20, 0},
                    scale = {0.25, 0.25, 0.25}
                },
                Animator = {
 		            mesh = "ninja.mesh",
                    activeAnimations = {
                       "Walk"
                    }
                },
                TestComponent = 0,
                AudioSource = {
                    sound = "Test",
                    playOnAwake = true
                },
                RigidBody = {
                    scale = {10, 15, 10},
                    mass = 1,
                    friction = 5,
                    restitution = 1,
                    shapeType = "Cube",
                    static = false
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
                        ParticleSystem = {
                            particle = "Examples/Smoke",
                            emitting = true
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
                    nearClipDistance = 1,
                    autoAspectRatio = true,
                    backgroundColor = {0.6, 0.3, 0.3}
                },
                AudioListener = 0
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
    },
    Play = {
        jugador = {
            handler = "player",
            components = {
                Transform = {
                    position = {0, 0, 0},
                    scale = {0.25, 0.25, 0.25}
                },
                Animator = {
 		            mesh = "ninja.mesh",
                    activeAnimations = {
                       "Walk"
                    }
                },
                TestComponent = 0,
                AudioSource = {
                    sound = "Test",
                    playOnAwake = true
                }
            },
        },
        cartel = {
            group = "obstacle",
            components = {
                Transform = {
                    position = {-100, 0, -100},
                    scale = {10,10,10}
                },
                Billboard = {
                    material = "practica1/points",
                    billboardDimensions = {10,10}
                }
            }
        },
        cartel2 = {
            group = "obstacle",
            components = {
                Transform = {
                    position = {100, 0, -100},
                    scale = {10,10,10}
                },
                Billboard = {
                    size = 5,
                    material = "practica1/points",
                    billboardDimensions = {5,5},
                    totalDimensions = {30,30,30}
                }
            }
        },
        cam = {
            components = {
                Transform = {
                    position = {0, 0, 70}
                },
                Camera = {
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
                },
            }
        }
    }
}

return prefabs, scenes