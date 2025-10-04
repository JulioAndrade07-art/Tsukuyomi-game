extends CharacterBody2D

@export var speed: float = 200.0
@export var jump_force: float = -400.0

var gravity = ProjectSettings.get_setting("physics/2d/default_gravity")

func _physics_process(delta):
	if not is_on_floor():
		velocity.y += gravity * delta

	var input_dir = Input.get_axis("ui_left", "ui_right")
	velocity.x = input_dir * speed

	if Input.is_action_just_pressed("ui_accept") and is_on_floor():
		velocity.y = jump_force

	move_and_slide()
