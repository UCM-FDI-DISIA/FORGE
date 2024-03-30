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
                Animator = {
 		             mesh = "ninja.mesh",
                    activeAnimations = {
                       "Walk"
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
                        ParticleSystem = {
                            particle = "Examples/Smoke",
                            emitting = true
                        }
                    }
                }
            }
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
                    position = {0, 0, 140}
                },
                TestMovement = 0,
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
 		             mesh = "ogrehead.mesh",
                    activeAnimations = {
                       "Walk"
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