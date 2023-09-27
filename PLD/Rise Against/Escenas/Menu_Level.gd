extends Control


# Called when the node enters the scene tree for the first time.
func _ready():
	$CenterContainer/VBoxContainer/HBoxContainer/Button.grab_focus()


func _on_button_pressed():
	var level = get_node("/root/LevelSelected")
	level.Nivel_Actual = 1
	get_tree().change_scene_to_file("res://Escenas/Game.tscn")
	


func _on_button_2_pressed():
	var level = get_node("/root/LevelSelected")
	level.Nivel_Actual = 2
	get_tree().change_scene_to_file("res://Escenas/Game.tscn")
