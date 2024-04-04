local scenes = {
	Sample = {

		Main Camera= {
			components = {
				Transform= {
					position = {0,1,-10},
					rotation = {0,0,0,1},
					scale = {1,1,1}
				}
			}
		}

		Directional Light= {
			components = {
				Transform= {
					position = {0,3,0},
					rotation = {0.4082179,-0.2345697,0.1093816,0.8754261},
					scale = {1,1,1}
				}
			}
			
			hola= {
				components = {
					Transform= {
						position = {15.11,0.8,-2.78},
						rotation = {0,0,0,1},
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
	}	
}
return prefabs, scenes