extends Control

# Called when the node enters the scene tree for the first time.
func _ready():
	$VBoxContainer/Sound_Button.grab_focus()

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass
		
func _on_h_slider_value_changed(value):
	AudioServer.set_bus_volume_db(AudioServer.get_bus_index("Master"), value)

func _on_sound_button_pressed():
	$VBoxContainer/Sound_Button/HSlider.grab_focus()


func _on_focus_entered():
	get_tree().change_scene_to_file("res://Escenas/Menu_Principal.tscn")


func _on_window_mode_button_item_selected(index):
	DisplayServer.window_set_mode($VBoxContainer/Window_Mode_Button.get_item_id(index), 0)
