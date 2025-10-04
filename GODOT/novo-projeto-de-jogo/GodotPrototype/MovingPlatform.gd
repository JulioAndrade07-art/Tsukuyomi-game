extends Node2D

@export var speed: float = 100.0
@export var distance: float = 200.0

var direction: int = 1
var start_pos: Vector2

func _ready():
    start_pos = position

func _process(delta):
    position.x += speed * direction * delta
    if abs(position.x - start_pos.x) > distance:
        direction *= -1
