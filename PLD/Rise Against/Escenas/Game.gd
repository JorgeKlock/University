extends Node

#var player_path = $HBoxContainer/SubViewportContainer/SubViewport/Level1/Player1

@onready var players =	{
		"1": 
			{
				viewport = $"HBoxContainer/SubViewportContainer/SubViewport",
				camera = $"HBoxContainer/SubViewportContainer/SubViewport/Camera2D",
				player = $HBoxContainer/SubViewportContainer/SubViewport/Level1/Player1,
			},
		"2":
			{
				viewport = $"HBoxContainer/SubViewportContainer2/SubViewport",
				camera = $"HBoxContainer/SubViewportContainer2/SubViewport/Camera2D",
				player = $HBoxContainer/SubViewportContainer/SubViewport/Level1/Player2,
			}
	}

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	var level = get_node("/root/LevelSelected")
	
	if (level.Nivel_Actual == 1):
		$HBoxContainer/SubViewportContainer/SubViewport/Level2.queue_free()
	elif (level.Nivel_Actual == 2):
		$HBoxContainer/SubViewportContainer/SubViewport/Level1.queue_free()
		players["1"].player = $HBoxContainer/SubViewportContainer/SubViewport/Level2/Player1
		players["2"].player = $HBoxContainer/SubViewportContainer/SubViewport/Level2/Player2
	
	players["2"].viewport.world_2d = players["1"].viewport.world_2d
	for node in players.values():
		var remote_transform := RemoteTransform2D.new()
		remote_transform.remote_path = node.camera.get_path()
		node.player.add_child(remote_transform)

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass
