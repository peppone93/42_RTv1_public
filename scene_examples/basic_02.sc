camera
	{
		position: 0 0 -1000
		direction: 0 0 1
		fov: 50.0
	}

scene 
	{ 
		title: basic_02
		window: 1280 720
		ambient: 0.2
	}

light
	{
		intensity: 100000
		color: 0xffffff
		position: 400 400 -200 
	}

object
	{
		type: plane
		position: 0 0 300
		direction: 0 0 -1
		dimension: 100
		color: 0x0000ff
		shine: 1 0.01
	}


object
	{
		type: sphere
		position: 0 0 0
		direction: 0 1 0
		dimension: 200
		color: 0xff0000
		shine: 1 0.01
	}
