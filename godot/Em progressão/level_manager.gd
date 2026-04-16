extends Node3D

@onready var world_env = $WorldEnvironment

# Paleta Noite (Roxo)
var night_fog = Color(0.25, 0.05, 0.4)
var night_ambient = Color(0.2, 0.05, 0.3)

# Paleta Natureza (Verde)
var nature_fog = Color(0.3, 0.5, 0.2)
var nature_ambient = Color(0.4, 0.6, 0.3)

var target_fog: Color
var target_ambient: Color
var player_body: CharacterBody3D = null

func _ready():
	target_fog = night_fog
	target_ambient = night_ambient
	
	# Procura o CharacterBody3D dentro da cena do player (que você chamou de Node3D)
	# ou qualquer CharacterBody3D na cena.
	_find_player()

func _find_player():
	# Tenta achar o nó que realmente se move
	player_body = get_tree().get_nodes_in_group("player").slice(0,1).pop_front() as CharacterBody3D
	if not player_body:
		# Busca forçada pelo tipo se não houver grupo
		for child in get_children():
			if child is CharacterBody3D:
				player_body = child
				break
			for subchild in child.get_children():
				if subchild is CharacterBody3D:
					player_body = subchild
					break
	
	if player_body:
		print("Player encontrado: ", player_body.name)
	else:
		print("ERRO: Player não encontrado para transição de cores!")

func _process(delta):
	if not player_body:
		# Tenta re-encontrar caso o player tenha nascido depois
		_find_player()
		return

	# Agora checamos a posição do CharacterBody3D (o que se move de verdade)
	if player_body.global_position.x > 78.0:
		target_fog = nature_fog
		target_ambient = nature_ambient
	else:
		target_fog = night_fog
		target_ambient = night_ambient
			
	# Transição suave
	var env = world_env.environment
	env.fog_light_color = env.fog_light_color.lerp(target_fog, delta * 2.5)
	env.ambient_light_color = env.ambient_light_color.lerp(target_ambient, delta * 2.5)
