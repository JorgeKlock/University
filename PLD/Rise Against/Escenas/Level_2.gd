extends Node2D


var Game_over_path = preload("res://Escenas/Game_Over_Scene.tscn")

func _on_area_2d_body_entered(body):
	print("Ha entrado en el vacío el elemento")
	print(body.get_name())
	if("Player" in body.get_name()):
		body.just_damaged = true
		body.velocity.y = -500
	if("Proyectil" in body.get_name()):
		body.destroy()


func _on_finish_lane_body_entered(body):
	if(body.get_class() == "CharacterBody2D"):
		var text = str(body.name) + " wins"
		var Game_Over = Game_over_path.instantiate()
		get_tree().get_root().add_child(Game_Over)
		Game_Over.set_text(text)
		self.queue_free()
