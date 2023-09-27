extends StaticBody2D

# Called when the node enters the scene tree for the first time.
func _ready():
	$AnimatedSprite2D.play("Crecimiento")
	pass # Replace with function body.

func start(_position, _direction):
	rotation = _direction
	global_position = _position

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass
	


