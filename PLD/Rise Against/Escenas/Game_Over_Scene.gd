extends Control


# Called when the node enters the scene tree for the first time.
func _ready():
	pass

func set_text(new_text):
	$Panel/RichTextLabel.clear()
	$Panel/RichTextLabel.add_text(new_text)
