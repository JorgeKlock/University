extends Control

var level1_path = load("res://Escenas/Level_1.tscn")
# Called when the node enters the scene tree for the first time.
func _ready():
	print("level selection is ready")
	var level = level1_path.instantiate()
	get_parent().add_child(level)

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
