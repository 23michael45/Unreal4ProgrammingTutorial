import unreal_engine as ue
from unreal_engine.classes import Actor, Character
from unreal_engine import FVector, FRotator

#use ue.exec('WorldActor.py')

world = ue.get_editor_world()
actor000 = world.actor_spawn(Actor, FVector(0, 0, 0), FRotator(0, 0, 0))
character000 = world.actor_spawn(Character, FVector(100, 100, 100), FRotator(0, 0, 0))

# select an actor
unreal_engine.editor_select_actor(actor000)

'''
# get access to the editor world
editor = unreal_engine.get_editor_world()

# get the list of selected actors
selected_actors = unreal_engine.editor_get_selected_actors()

# deselect actors
unreal_engine.editor_deselect_actors()


# import an asset
new_asset = unreal_engine.import_asset(filename, package[, factory_class])


# get a factory class
factory = ue.find_class('TextureFactory')

# import the asset using the specified class
new_asset = ue.import_asset('C:/Users/Tester/Desktop/logo.png', '/Game/FooBar/Foo', factory)

# print the asset class (it will be a Texture2D)
ue.log(new_asset.get_class().get_name())


factory = ue.find_class('TextureFactory')
# instantiate the factory
factory_obj = ue.new_object(factory)

# print the properties list
ue.log(str(factory_obj.properties()))

# set a property
factory_obj.set_property('bRGBToEmissive', True)

# import the asset (this time using a factory object instead of a factory class)
new_object = ue.import_asset('C:/Users/Tester/Desktop/logo.png', '/Game/FooBar/20tab', factory_obj)
'''