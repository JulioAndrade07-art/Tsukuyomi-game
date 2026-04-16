extends CharacterBody3D

@export var walk_speed := 5.0
@export var run_speed := 15.0
@export var jump_force := 9.0
@export var gravity := 11.0
@export var dash_speed := 20.0
@export var dash_duration := 0.2
@export var stop_time := 0.5
@export var skid_time := 0.3

var is_dashing: bool = false
var dash_timer: float = 0.0
var facing_direction: float = 1.0

func _physics_process(delta):
	# Captura direção
	var direction := Input.get_axis("ui_left", "ui_right")
	if direction != 0:
		facing_direction = sign(direction)

	# Lógica do Dash Ativo
	if is_dashing:
		dash_timer -= delta
		velocity.x = facing_direction * dash_speed
		velocity.y = 0  # Congela a gravidade no frame do dash
		
		# Termina o Dash
		if dash_timer <= 0.0:
			is_dashing = false
			# Devolve o momento logo para a corrida, se ainda estiver segurando shift
			if Input.is_action_pressed("dash"):
				velocity.x = facing_direction * run_speed
	else:
		# Gravidade
		if not is_on_floor():
			velocity.y -= gravity * delta
		
		# Iniciar Dash (sem interromper fluidez)
		if Input.is_action_just_pressed("dash"):
			is_dashing = true
			dash_timer = dash_duration
		else:
			# Lógica de Corrida e Desaceleração Contínua
			var target_speed = 0.0
			
			if direction != 0:
				# Se segura o dash (Shift), velocidade alvo é 15. Senão é 5 (anda).
				var desired_mag = run_speed if Input.is_action_pressed("dash") else walk_speed
				target_speed = desired_mag * direction
				
				var is_turning_around = sign(velocity.x) != sign(direction) and abs(velocity.x) > 2.0
				
				if is_turning_around:
					# Derrapagem (Skid) - demora pra frear e ir pro outro lado
					velocity.x = move_toward(velocity.x, target_speed, ((run_speed * 2.0) / skid_time) * delta)
				elif abs(velocity.x) > desired_mag and sign(velocity.x) == sign(direction):
					# Reduzindo de correr para andar devagar
					velocity.x = move_toward(velocity.x, target_speed, (run_speed / stop_time) * delta)
				else:
					# Aceleração para movimento, mais ágil pra arrancar
					velocity.x = move_toward(velocity.x, target_speed, (run_speed / 0.1) * delta)
			else:
				# Desaceleração Contínua - para o personagem resvalando na pista em 0.5s exatamente!
				velocity.x = move_toward(velocity.x, 0, (run_speed / stop_time) * delta)

			# Pulo
			if is_on_floor() and Input.is_action_just_pressed("ui_accept"):
				velocity.y = jump_force

	# BLOQUEIA eixo Z (isso cria o efeito 2.5D)
	velocity.z = 0
	transform.origin.z = 0

	move_and_slide()
