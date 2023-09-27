extends Control

func _ready():
	$Background/CenterContainer/VBoxContainer/Resume.grab_focus()
	
var is_paused = false : set = set_is_paused, get = get_is_paused

func _unhandled_input(event):
	if event.is_action_pressed("Pause"):
		self.is_paused = !is_paused

func get_is_paused():
	return is_paused
func set_is_paused(value):
	is_paused = value
	get_tree().paused = is_paused
	visible = is_paused
	if(visible):
		$Background/CenterContainer/VBoxContainer/Resume.grab_focus()


func _on_quit_pressed():
	get_tree().quit()


func _on_reset_pressed():
	self.is_paused = false
	get_tree().reload_current_scene()
	get_tree().change_scene_to_file("res://Escenas/Menu_Principal.tscn")


func _on_resume_pressed():
	self.is_paused = false
