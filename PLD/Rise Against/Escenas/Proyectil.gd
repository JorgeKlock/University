extends AnimatableBody2D

@export var SPEED: int = 600

var platform_path = load("res://Escenas/Plataforma.tscn")

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


func _physics_process(delta):
	$AnimatedSprite2D.play("Projectile_flying")
	
	var direction = Vector2.RIGHT.rotated(rotation)
	var collision_info = move_and_collide(direction*SPEED*delta)
	if (collision_info):
		print("Proyectil colisiona con ", collision_info.get_collider().name)
			#Si la categoría es pared se crea plataforma, si la categoria es plataforma se elimina
		
		if("Plataforma" in collision_info.get_collider().name):
			collision_info.get_collider().queue_free()
		elif("Tile" in collision_info.get_collider().name):
			var platform = platform_path.instantiate()
			get_parent().add_child(platform)
			platform.global_position = self.global_position
		else:
			self.destroy()
		self.destroy()

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass

func destroy():
	queue_free()
