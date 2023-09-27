extends Control

# Called when the node enters the scene tree for the first time.
func _ready():
	$VBoxContainer/Start_Button.grab_focus()


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass

var game_path = preload("res://Escenas/Game.tscn")

func _on_start_button_pressed():
	get_tree().change_scene_to_file("res://Escenas/Menu_Level.tscn")

func _on_settings_button_pressed():
	get_tree().change_scene_to_file("res://Escenas/Menu_Settings.tscn")

func _on_quit_button_pressed():
	get_tree().quit()
