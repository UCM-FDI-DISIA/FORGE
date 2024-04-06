local prefabs = {

	hola1= {
		components = {
			Transform= {
				position = {29.1627,5.643834,5.288186},
				rotation = {0.4082179,-0.2345697,0.1093816,0.8754261},
				scale = {1,1,1}
			},
			Miguel= {
				Eva = Lituania,
				Mik = Felis,
				Pav = Enfadao,
				Alex = true				
			}
		}
	}
}

local scenes = {
	Sample = {

		Main Camera= {
			handler = "MainCamera",
			components = {
				Transform= {
					position = {10.46,1,3.44},
					rotation = {0,0,0,1},
					scale = {1,1,1}
				},
				TestComponent= {
					Key = "string"					
				}
			}
		}

		Directional Light= {
			components = {
				Transform= {
					position = {15.49,3,-1.25},
					rotation = {0.4082179,-0.2345697,0.1093816,0.8754261},
					scale = {1,1,1}
				}
			}
			
			hola1= {
				blueprint = "hola"
			}
			
			hola2= {
				blueprint = "hola"
			}
		}

		hola3= {
			blueprint = "hola"
		}

		GameObject= {
			components = {
				Transform= {
					position = {-9.390345,-9.869844,2.388827},
					rotation = {0,0,0,1},
					scale = {1,1,1}
				}
			}
		}

		Cube= {
			group = "TransparentFX",
			components = {
				Transform= {
					position = {-2.2,-9.869844,2.388827},
					rotation = {0,0,0,1},
					scale = {1,1,1}
				}
			}
		}

		Cube_1= {
			handler = "MainCamera",
			components = {
				Transform= {
					position = {-9.390345,-9.869844,2.388827},
					rotation = {0,0,0,1},
					scale = {1,1,1}
				}
			}
		}
	}	
}
return prefabs, scenes