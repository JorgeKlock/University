extends CharacterBody2D

# Constants 
const UP_DIRECTION = Vector2.UP

var SPEED = 350.0
const JUMP_VELOCITY = -700.0
const WALLJUMP_VELOCITY_X = 500
const maximum_jumps = 1
const max_wall_jumps = 1
const gravity_multiplier = 3.5
var dash_speed = 700
const walljump_multiplier = 3

var platform = load("res://Escenas/Plataforma.tscn")
var proyectil_path = preload("res://Escenas/Proyectil.tscn")

@export var controls: Resource = null
@export var can_dash = true # Comprobar si podemos dashear
@export var can_walljump = true # Comprobar si podemos hacer walljump
@export var can_use_ability = true #Comprobar si podemos usar la habilidad
@export var just_damaged = false
@export var damaged = false
@export var can_recover = false
var dashing : bool # Comprobar si estamos dasheando
var dash_direction

var walljumping : bool
var wavedashing : bool
var using_ability : bool #Comprobar si estamos usando la habilidad
var jumps_made = 0
var dash_cooldown = false

# Get the gravity from the project settings to be synced with RigidBody nodes.
#var gravity = ProjectSettings.get_setting("physics/2d/default_gravity")*1.2
var gravity = 1500
@onready var player_sprite = $AnimatedSprite2D

func _ready():
	if(self.get_index() == 0):
		$AnimatedSprite2D.hide()
		player_sprite = $AnimatedSprite2D2
	if(self.get_index() == 1):
		$AnimatedSprite2D2.hide()
		player_sprite = $AnimatedSprite2D
	


func nextToRightWall():
	return $RayCast2D.is_colliding()
func nextToLeftWall():
	return $RayCast2D2.is_colliding()


func motion_control(delta):
	var is_falling = velocity.y > 0.0 and not is_on_floor()
	var is_next_to_wall = nextToRightWall() or nextToLeftWall()
	var is_jumping = Input.is_action_just_pressed(controls.jump) and is_on_floor()
	var is_wall_jumping = Input.is_action_just_pressed(controls.jump) and not is_on_floor() and is_next_to_wall
	var is_double_jumping = Input.is_action_just_pressed(controls.jump) and not is_on_floor()
	is_double_jumping = false # Característica suprimida temporalmente
	var is_jump_cancelled = Input.is_action_just_released(controls.jump) and velocity.y < 0.0
	var is_idling = is_on_floor() and is_zero_approx(velocity.x)
	var is_running = is_on_floor() and not is_zero_approx(velocity.x)
	
	if(just_damaged):
		if(velocity.x < 0):
			print("lanzado hacia la derecha")
			velocity.x = +SPEED/1.5
		elif(velocity.x > 0):
			print("lanzado hacia la izquierda")
			velocity.x = -SPEED/1.5
		damaged = true
		just_damaged = false
		player_sprite.play("Damaged")
		$Damaged_Effect.start()
		
	if(damaged):
		
		velocity.y += gravity * delta
#		if(velocity.x < 0):
#			print("lanzado hacia la derecha")
#			velocity.x = +SPEED/1.5
#		if(velocity.x > 0):
#			print("lanzado hacia la izquierda")
#			velocity.x = -SPEED/1.5
	
	else:
			
		# Get the input direction and handle the movement/deceleration.
		var direction = Input.get_axis(controls.move_left, controls.move_right)
		if (not dashing):
			if is_jumping:
				jumps_made += 1
				velocity.y = JUMP_VELOCITY
			
			if is_wall_jumping:
				jumps_made += 1
				if (jumps_made <= maximum_jumps) and can_walljump:
					velocity.y = JUMP_VELOCITY
					player_sprite.play("Jump")
					if(not can_dash):
						velocity.y = JUMP_VELOCITY*1.3
						
						#Play cornerboost effect
					walljumping = true
					can_walljump = false
					$Walljump_Effect.start()
					if nextToLeftWall():
						velocity.x = -JUMP_VELOCITY/2.5
						if(not can_dash):
							velocity.x = -JUMP_VELOCITY/2
					elif nextToRightWall():
						velocity.x = +JUMP_VELOCITY/2.5
						if(not can_dash):
							velocity.x = +JUMP_VELOCITY/2
							
					if(not can_dash):
						can_dash = true
						dashing = false
	#		elif is_double_jumping:
	#			jumps_made += 1
	#			if jumps_made <= maximum_jumps:
	#				velocity.y = JUMP_VELOCITY
			elif is_jump_cancelled:
				velocity.y = 0.0
			elif is_idling or is_running:
				jumps_made = 0

		# Handle Animations
		if direction < 0:
			player_sprite.flip_h = true
		elif direction > 0:
			player_sprite.flip_h = false

		if wavedashing:
			player_sprite.play("Jump")
		elif dashing:
			player_sprite.play("Dash")
		elif is_double_jumping:
			player_sprite.play("Jump")
		elif is_jumping:
			player_sprite.play("Jump")
		elif walljumping:
			player_sprite.play("Jump")
		elif is_falling:
			player_sprite.play("Fall")
		elif is_running:
			player_sprite.play("Walk_Right")
		elif is_idling:
			player_sprite.play("Idle")


		if not is_on_floor():
			velocity.y += gravity * delta

		if (wavedashing):
			velocity.y = JUMP_VELOCITY*1.3
			velocity.x = direction * SPEED 
			
		if (dashing and not wavedashing):
			velocity.x = direction * dash_speed
			velocity.y = 0
			#velocity = dash_direction * SPEED * dash_multiplier
			if(Input.is_action_just_pressed(controls.jump) and is_on_floor() and $Dash_Effect.get_time_left() < 0.16):
				can_dash = true
				dashing = false
				wavedashing = true
				$Wavedash_Effect.start()
				
		## Gestión de la velocidad
		if (not walljumping and not dashing and not wavedashing):
			if direction:
				velocity.x = direction * SPEED
			else:
				velocity.x = move_toward(velocity.x, 0, SPEED)
	if(is_on_floor() and can_recover):
		damaged = false
		can_recover = false
	move_and_slide()

func dash_control():
	if (is_on_floor() and not dash_cooldown):
		can_dash = true
	
	if can_dash and Input.is_action_just_pressed(controls.dash):
		dashing = true
		can_dash = false
		dash_cooldown = true
		$Dash_Effect.start()
		$Dash_Cooldown.start()

func ability_control():
	if can_use_ability and Input.is_action_just_pressed(controls.action):
		var proyectil = proyectil_path.instantiate()
		#get_tree().current_scene.add_child(proyectil)
		get_parent().add_child(proyectil)
		proyectil.global_position = $Node2D/Spawn_Point.global_position
		
		var p_rotation
		print(controls.resource_path)
		if("player1" in controls.resource_path):
			p_rotation = self.global_position.direction_to(get_global_mouse_position()).angle()
		elif ("player2" in controls.resource_path):
			var xAxisRL = Input.get_joy_axis(0, JOY_AXIS_RIGHT_X)
			var yAxisUD = Input.get_joy_axis(0, JOY_AXIS_RIGHT_Y)
			if (abs(xAxisRL) < 0.15 && abs(yAxisUD) < 0.15):
				xAxisRL = 1
			p_rotation = Vector2(xAxisRL, yAxisUD).angle()
		proyectil.rotation = p_rotation
		
		using_ability = true
		can_use_ability = false
		$Ability_Effect.start()
		$Ability_Cooldown.start() 

func _physics_process(delta):
	dash_control()
	motion_control(delta)
	ability_control()
	

func _on_dash_effect_timeout():
	dashing = false

func _on_dash_cooldown_timeout():
	dash_cooldown = false

func _on_ability_cooldown_timeout():
	can_use_ability = true

func _on_ability_effect_timeout():
	using_ability = false
	$Ability_Cooldown.start()
	pass # Replace with function body.


func _on_walljump_effect_timeout():
	walljumping = false
	$Walljump_Cooldown.start()


func _on_walljump_cooldown_timeout():
	can_walljump = true


func _on_wavedash_effect_timeout():
	wavedashing = false



func _on_damaged_effect_timeout():
	can_recover = true
