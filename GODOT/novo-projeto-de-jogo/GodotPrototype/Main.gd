extends Node2D

var score: int = 0

func _ready():
    if has_node("Coin"):
        var coin = $Coin
        coin.connect("collected", Callable(self, "_on_coin_collected"))

func _on_coin_collected():
    score += 1
    print("Moeda coletada! Score: ", score)
