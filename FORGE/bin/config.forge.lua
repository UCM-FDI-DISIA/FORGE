Config = {
	game = "Demo",
	debugGame = "Demo_d",
	assetsFile = "Assets/assets.forge.lua",
	scenesFile = "Assets/scenes/scenetest.lua",
	initialScene = "Test"
}

Window = {
	width  = 1280,
	height = 768
}

Physics = {
	layers = {	--		Default	Layer1	Layer2	Layer3
		--Layer3	= {	false,	false,	false,	true},
		--Layer2	= {	true,	false,	true},
		--Layer1	= {	true,	false},
		Default		= {	true }
	},
	debug		= true
}