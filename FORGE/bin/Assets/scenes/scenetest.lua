local prefabs = {
    player = {
        handler = "player",
        components = {
            Transform = {
                position = Vector3(0, -20, 0),
                scale = Vector3(0.05, 0.05, 0.05)
            },
            Animator = {
                mesh = "ninja.mesh",
                activeAnimations = {
                   "Walk"
                }
            }, 
            AudioSource = {
                sound = "Test",
                playOnAwake = true
            },
            RigidBody = {
                mass = 1,
                friction = 5,
                restitution = 1,
                shapeType = "Cube",
                static = false,
                layer = "ALL",
                scale = {20, 20, 20}
            },
            TestComponent = 0
        }
    },
    obstaculo = {
        group = "obstacle",
        components = {
            Transform = {
                position = {100, 0, -100},
            },
            ParticleSystem = {
                particle = "Examples/Smoke",
                emitting = true
            }
        }
    }
}

local scenes = {
    Test = {
        jugador = {
            blueprint = "player",
            children = {
                cam = {
                    components = {
                        Transform = {
                            position = {0, -50, 20}
                        },
                        Camera = {
                            nearClipDistance = 1,
                            autoAspectRatio = true,
                            backgroundColor = {0.6, 0.3, 0.3}
                        },
                        AudioListener = 0
                    }
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
        luz = {
            components = {
                Transform = {
                    position = {20, 80, 0}
                },
                Light = {
                    type = 0 
                }
            }
        },
        texto1 = {
            components = {
                RectTransform = {
                    position = {0, 0},
                    scale = {5, 5}
                },
                Text = {
                    text = "texto1",
                    fontName = "Willow.ttf",
                    fontHeight = 100
                }
            }
        },
        texto2 = {
            components = {
                RectTransform = {
                    position = {0, 400},
                    scale = {5, 5}
                },
                Text = {
                    text = "texto2",
                    fontName = "Willow.ttf",
                    fontHeight = 100
                }
            }
        },
        imagen1 = {
            components = {
                RectTransform = {
                    position = {20, 100},
                    scale = {200, 200}
                },
                Image = {
                    depth = 0,
                    texture = "panko.png"
                }
            }
        },
        imagen2 = {
            components = {
                RectTransform = {
                    position = {420, 100},
                    scale = {200, 300}
                },
                Image = {
                    depth = 1,
                    texture = "dinocat.png"
                }
            }
        },
        imagen3 = {
            components = {
                RectTransform = {
                    position = {220, 100},
                    scale = {200, 200}
                },
                Image = {
                    depth = 1,
                    texture = "dinoocat.png"
                }
            }
        },
        button = {
            components = {
                RectTransform = {
                    position = {50, 300},
                    scale = {100, 100}
                },
                Button = {
                    out = "out.png",
                    hover = "over.png",
                    clicked = "clicked.png",
                    onOverInvoker = "player",
                    onOver = function (inv)
                        print("Poto en Lua");
                        inv:invoke("Poto");
                    end,
                    onClick = function (inv)
                        print("Estoy clickando el boton");
                    end,
                    onRelease = function (inv)
                        print("He soltado el boton");
                    end
                }
            }
        },
        progress1 = {
            components = {
                RectTransform = {
                    position = {125, 350},
                    scale = {300, 100}
                },
                ProgressBar = {
                    front = "angry.png",
                    back = "angryBg.png",
                    growth = "LEFT_TO_RIGHT",
                    value = 0.85,
                    depth = 3
                }
            }
        },
        progress2 = {
            components = {
                RectTransform = {
                    position = {100, 0},
                    scale = {100, 300}
                },
                ProgressBar = {
                    front = "jynx.png",
                    back = "jynxBg.png",
                    value = 0.85,
                    growth = "DOWN_TO_UP",
                    depth = 2
                }
            }
        },
        progress3 = {
            components = {
                RectTransform = {
                    position = {220, 0},
                    scale = {200, 100}
                },
                ProgressBar = {
                    front = "howdy.png",
                    back = "howdyBg.png",
                    value = 0.85,
                    growth = "RIGHT_TO_LEFT",
                    depth = 2
                }
            }
        },
        progress4 = {
            components = {
                RectTransform = {
                    position = {425, 0},
                    scale = {200, 100}
                },
                ProgressBar = {
                    front = "fat.png",
                    back = "fatBg.png",
                    value = 0.65,
                    growth = "UP_TO_DOWN",
                    depth = 1
                }
            }
        }
    },
    Play = {
        jugador = {
            blueprint = "player",
            components = {
                Transform = {
                    position = {0, 0, 0},
                    scale = {0.25, 0.25, 0.25}
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
        },
        texto1 = {
            components = {
                RectTransform = {
                    position = {0, 0},
                    scale = {5, 5}
                },
                Text = {
                    text = "texto1",
                    fontName = "Willow.ttf",
                    fontHeight = 100
                }
            }
        }
    }
}

return prefabs, scenes