import unreal_engine as ue
from unreal_engine.classes import Actor, Character
from unreal_engine import FVector, FRotator

world = ue.get_editor_world()
actor000 = world.actor_spawn(Actor, FVector(0, 0, 0), FRotator(0, 0, 0))
character000 = world.actor_spawn(Character, FVector(100, 100, 100), FRotator(0, 0, 0))