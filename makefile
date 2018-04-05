#Basic compile stuff
COMPILER= g++
#'Pre' as in 'before the cpp file'
COMPILE_FLAGS_PRE= -g -c -Wall -std=c++11
#'Post' as in 'after the cpp file'
COMPILE_FLAGS_POST= -L/bin/lib/ -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lstdc++ -lm -lc -o

#Objects
OBJ= ./bin/obj/*.o

#Final out file name
EXE_NAME= acoc.out


#Source files

#src/
MAIN= ./src/main.cpp
GAME_HANDLER= ./src/GameHandler.cpp
GAME_STATE_HANDLER= ./src/GameStateHandler.cpp

#src/Basic_Components/
DRAW_COMPONENT= ./src/Basic_Components/DrawableComponent.cpp
MOVE_COMPONENT= ./src/Basic_Components/MoveableComponent.cpp
COLL_COMPONENT= ./src/Basic_Components/CollisionComponent.cpp

#src/Audio/
AUDIO_COMPONENT= ./src/Audio/AudioComponent.cpp
SOUND_COMPONENT= ./src/Audio/SoundComponent.cpp
MUSIC_COMPONENT= ./src/Audio/MusicComponent.cpp

#src/Utilities/General_Purpose/
RANDOM= ./src/Utilities/General_Purpose/Random.cpp
HELPFUL_METHODS= ./src/Utilities/General_Purpose/HelpfulMethods.cpp
TIMER= ./src/Utilities/General_Purpose/Timer.cpp
MATRIX= ./src/Utilities/General_Purpose/Matrix.cpp
TRACER= ./src/Utilities/General_Purpose/Tracer.cpp

#src/Utilities/Utility_Components/
VECTOR= ./src/Utilities/Utility_Components/Vector.cpp
AABB= ./src/Utilities/Utility_Components/AxisAllignedBoundingBox.cpp
INPUT_HANDLER= ./src/Utilities/Utility_Components/InputHandler.cpp
CAMERA= ./src/Utilities/Utility_Components/Camera.cpp

#src/Utilities/Color_Utilities/
AEOIAF_COLOR= ./src/Utilities/Color_Utilities/AEOIAFColor.cpp

#src/Utilities/AI_Utilities/
STEERING_HANDLER= ./src/Utilities/AI_Utilities/SteeringHandler.cpp

#src/Animation/
ANIMATION= ./src/Animation/Animation.cpp

#src/Actors/
ACTOR= ./src/Actors/Actor.cpp

#src/Actors/Character/
AEOIAF_CHARACTER= ./src/Actors/Character/Character.cpp
AEOIAF_PLAYER= ./src/Actors/Character/Player.cpp
AEOIAF_NONPLAYER= ./src/Actors/Character/NonPlayer.cpp
AEOIAF_TESTNONPLAYER= ./src/Actors/Character/TestNonPlayer.cpp
AEOIAF_FACTION= ./src/Actors/Character/Faction.cpp

#src/Actors/Item/
ITEM= ./src/Actors/Item/Item.cpp

#src/Actors/Item/Weapon/
WEAPON= ./src/Actors/Item/Weapon/Weapon.cpp

#src/Actors/Item/Weapon/Melee/
WEAPON_MELEE= ./src/Actors/Item/Weapon/Melee/WeaponMelee.cpp
WEAPON_MELEE_TEST= ./src/Actors/Item/Weapon/Melee/WeaponMeleeTest.cpp

#src/Actors/Item/Weapon/Projectile/
WEAPON_PROJECTILE= ./src/Actors/Item/Weapon/Projectile/WeaponProjectile.cpp
WEAPON_PROJECTILE_TEST= ./src/Actors/Item/Weapon/Projectile/TestWeaponProjectile.cpp
PROJECTILE= ./src/Actors/Item/Weapon/Projectile/Projectile.cpp
PROJECTILE_TEST= ./src/Actors/Item/Weapon/Projectile/TestProjectile.cpp

#src/Actors/Item/Weapon/Tracer/
WEAPON_TRACER= ./src/Actors/Item/Weapon/Tracer/WeaponTracer.cpp
WEAPON_TRACER_TEST= ./src/Actors/Item/Weapon/Tracer/TestWeaponTracer.cpp

#src/Actors/Item/Shield/
SHIELD= ./src/Actors/Item/Shield/Shield.cpp
SHIELD_TEST= ./src/Actors/Item/Shield/TestShield.cpp

#src/Actors/Prop/
PROP= ./src/Actors/Prop/Prop.cpp
PROP_SIMPLE= ./src/Actors/Prop/PropSimple.cpp

#src/Actors/Prop/Door/
PROP_DOOR= ./src/Actors/Prop/Door/PropDoor.cpp
PROP_DOOR_TESTS= ./src/Actors/Prop/Door/PropDoorTests.cpp

#src/Actors/Particle/
PARTICLE= ./src/Actors/Particle/Particle.cpp
PARTICLE_SIMPLE= ./src/Actors/Particle/ParticleSimple.cpp

#src/Actors/Scripted_Events/
SCRIPT_SEQ= ./src/Scripted_Events/ScriptSequence.cpp

#src/Level/
TILE= ./src/Level/Tile.cpp
LEVEL= ./src/Level/Level.cpp
LEVEL_DRAW_COMPONENT= ./src/Level/LevelDrawComponent.cpp
LEVEL_DRAW_COMPONENT_LIST= ./src/Level/LevelDrawComponentList.cpp

#src/Level/LevelDataTypes/
LEVEL_CHARACTER_LIST= ./src/Level/LevelDataTypes/LevelCharacterList.cpp
LEVEL_PROP_LIST= ./src/Level/LevelDataTypes/LevelPropList.cpp
LEVEL_PARTICLE_LIST= ./src/Level/LevelDataTypes/LevelParticleList.cpp
LEVEL_SCRIPT_SEQ_LIST= ./src/Level/LevelDataTypes/LevelScriptSequenceList.cpp
LEVEL_ACTOR_COLL_LIST= ./src/Level/LevelDataTypes/ActorCollisionList.cpp
LEVEL_TILE_COLL_LIST= ./src/Level/LevelDataTypes/TileCollisionList.cpp
REMOVE_SCRIPT_SEQ_STACK= ./src/Level/LevelDataTypes/RemoveScriptSequenceStack.cpp

#src/Level/Level_AI_Data/
LEVEL_PATHFINDING= ./src/Level/Level_AI_Data/LevelPathfinding.cpp
LEVEL_AI_DATA= ./src/Level/Level_AI_Data/LevelAIData.cpp

#src/UI/
MENU_COMPONENT= ./src/UI/MenuComponent.cpp
MENU_CONTAINER= ./src/UI/MenuContainer.cpp

#src/UI/Components/
BUTTON= ./src/UI/Components/Button.cpp

#src/UI/Menus/
MAIN_MENU= ./src/UI/Menus/MainMenu.cpp

#src/GameData/
DRAW_COMPONENT_LIST= ./src/GameData/DrawComponentList.cpp
AUDIO_COMPONENT_LIST= ./src/GameData/AudioComponentList.cpp
PROP_HANDLER= ./src/GameData/PropHandler.cpp
WEAPON_HANDLER= ./src/GameData/WeaponHandler.cpp
SHIELD_HANDLER= ./src/GameData/ShieldHandler.cpp
CHARACTER_HANDLER= ./src/GameData/CharacterHandler.cpp
PARTICLE_HANDLER= ./src/GameData/ParticleHandler.cpp
LEVEL_HANDLER= ./src/GameData/LevelHandler.cpp
GAME_DATA_HANDLER= ./src/GameData/GameDataHandler.cpp

#src/GameData/StreamData/
REMOVE_ACTOR_LIST= ./src/GameData/StreamData/RemoveActorList.cpp
INSERT_ACTOR_LIST= ./src/GameData/StreamData/InsertActorList.cpp
STREAM_DATA= ./src/GameData/StreamData/StreamData.cpp
LEVEL_STREAM_HANDLING= ./src/GameData/StreamData/LevelStreamHandling.cpp

#src/GameStates/
GAME_STATE= ./src/GameStates/GameState.cpp
STATE_INTRO= ./src/GameStates/StateIntro.cpp
STATE_MAIN_MENU= ./src/GameStates/StateMainMenu.cpp
STATE_TOP_DOWN= ./src/GameStates/StateTopDown.cpp

#Obj files

#src/
MAIN_O= ./bin/obj/main.o
GAME_HANDLER_O= ./bin/obj/GameHandler.o
GAME_STATE_HANDLER_O= ./bin/obj/GameStateHandler.o

#src/Basic_Components/
DRAW_COMPONENT_O= ./bin/obj/DrawableComponent.o
MOVE_COMPONENT_O= ./bin/obj/MoveableComponent.o
COLL_COMPONENT_O= ./bin/obj/CollisionComponent.o

#src/Audio/
AUDIO_COMPONENT_O= ./bin/obj/AudioComponent.o
SOUND_COMPONENT_O= ./bin/obj/SoundComponent.o
MUSIC_COMPONENT_O= ./bin/obj/MusicComponent.o

#src/Utilities/General_Purpose/
RANDOM_O= ./bin/obj/Random.o
HELPFUL_METHODS_O= ./bin/obj/HelpfulMethods.o
TIMER_O= ./bin/obj/Timer.o
MATRIX_O= ./bin/obj/Matrix.o
TRACER_O= ./bin/obj/Tracer.o

#src/Utilities/Utility_Components/
VECTOR_O= ./bin/obj/Vector.o
AABB_O= ./bin/obj/AxisAllignedBoundingBox.o
INPUT_HANDLER_O= ./bin/obj/InputHandler.o
CAMERA_O= ./bin/obj/Camera.o

#src/Utilities/Color_Utilities/
AEOIAF_COLOR_O= ./bin/obj/AEOIAFColor.o

#src/Utilities/AI_Utilities/
STEERING_HANDLER_O= ./bin/obj/SteeringHandler.o

#src/Animation/
ANIMATION_O= ./bin/obj/Animation.o

#src/Actors/
ACTOR_O= ./bin/obj/Actor.o

#src/Actors/Character/
AEOIAF_CHARACTER_O= ./bin/obj/Character.o
AEOIAF_PLAYER_O= ./bin/obj/Player.o
AEOIAF_NONPLAYER_O= ./bin/obj/NonPlayer.o
AEOIAF_TEST_NONPLAYER_O= ./bin/obj/TestPlayerNon.o
AEOIAF_FACTION_O= ./bin/obj/Faction.o

#src/Actors/Item/
ITEM_O= ./bin/obj/Item.o

#src/Actors/Item/Weapon/
WEAPON_O= ./bin/obj/Weapon.o

#src/Actors/Item/Weapon/Melee/
WEAPON_MELEE_O= ./bin/obj/WeaponMelee.o
WEAPON_MELEE_TEST_O= ./bin/obj/WeaponMeleeTest.o

#src/Actors/Item/Weapon/Projectile
WEAPON_PROJECTILE_O= ./bin/obj/WeaponProjectile.o
WEAPON_PROJECTILE_TEST_O= ./bin/obj/TestWeaponProjectile.o
PROJECTILE_O= ./bin/obj/Projectile.o
PROJECTILE_TEST_O= ./bin/obj/TestProjectile.o

#src/Actors/Item/Weapon/Tracer/
WEAPON_TRACER_O= ./bin/obj/WeaponTracer.o
WEAPON_TRACER_TEST_O= ./bin/obj/TestWeaponTracer.o

#src/Actors/Item/Shield/
SHIELD_O= ./bin/obj/Shield.o
SHIELD_TEST_O= ./bin/obj/TestShield.o

#src/Actors/Prop/
PROP_O= ./bin/obj/Prop.o
PROP_SIMPLE_O= ./bin/obj/PropSimple.o

#src/Actors/Prop/Door/
PROP_DOOR_O= ./bin/obj/PropDoor.o
PROP_DOOR_TESTS_O= ./bin/obj/PropDoorTests.o

#src/Actors/Particle/
PARTICLE_O= ./bin/obj/Particle.o
PARTICLE_SIMPLE_O= ./bin/obj/ParticleSimple.o

#src/Actors/Scripted_Events/
SCRIPT_SEQ_O= ./bin/obj/ScriptSequence.o

#src/Level/
TILE_O= ./bin/obj/Tile.o
LEVEL_O= ./bin/obj/Level.o
LEVEL_DRAW_COMPONENT_O= ./bin/obj/LevelDrawComponent.o
LEVEL_DRAW_COMPONENT_LIST_O= ./bin/obj/LevelDrawComponentList.o

#src/Level/LevelDataTypes/
LEVEL_CHARACTER_LIST_O= ./bin/obj/LevelCharacterList.o
LEVEL_PROP_LIST_O= ./bin/obj/LevelPropList.o
LEVEL_PARTICLE_LIST_O= ./bin/obj/LevelParticleList.o
LEVEL_SCRIPT_SEQ_LIST_O= ./bin/obj/LevelScriptSequenceList.o
LEVEL_ACTOR_COLL_LIST_O= ./bin/obj/ActorCollisionList.o
LEVEL_TILE_COLL_LIST_O= ./bin/obj/TileCollisionList.o
REMOVE_SCRIPT_SEQ_STACK_O= ./bin/obj/RemoveScriptSequenceStack.o

#src/Level/Level_AI_Data/
LEVEL_PATHFINDING_O= ./bin/obj/LevelPathfinding.o
LEVEL_AI_DATA_O= ./bin/obj/LevelAIData.o

#src/UI/
MENU_COMPONENT_O= ./bin/obj/MenuComponent.o
MENU_CONTAINER_O= ./bin/obj/MenuContainer.o

#src/UI/Components/
BUTTON_O= ./bin/obj/Button.o

#src/UI/Menus/
MAIN_MENU_O= ./bin/obj/MainMenu.o

#src/GameData/
DRAW_COMPONENT_LIST_O= ./bin/obj/DrawComponentList.o
AUDIO_COMPONENT_LIST_O= ./bin/obj/AudioComponentList.o
PROP_HANDLER_O= ./bin/obj/PropHandler.o
WEAPON_HANDLER_O= ./bin/obj/WeaponHandler.o
SHIELD_HANDLER_O= ./bin/obj/ShieldHandler.o
CHARACTER_HANDLER_O= ./bin/obj/CharacterHandler.o
PARTICLE_HANDLER_O= ./bin/obj/ParticleHandler.o
LEVEL_HANDLER_O= ./bin/obj/LevelHandler.o
GAME_DATA_HANDLER_O= ./bin/obj/GameDataHandler.o

#src/GameData/StreamData/
REMOVE_ACTOR_LIST_O= ./bin/obj/RemoveActorList.o
INSERT_ACTOR_LIST_O= ./bin/obj/InsertActorList.o
STREAM_DATA_O= ./bin/obj/StreamData.o
LEVEL_STREAM_HANDLING_O= ./bin/obj/LevelStreamHandling.o

#src/GameStates/
GAME_STATE_O= ./bin/obj/GameState.o
STATE_INTRO_O= ./bin/obj/StateIntro.o
STATE_MAIN_MENU_O= ./bin/obj/StateMainMenu.o
STATE_TOP_DOWN_O= ./bin/obj/StateTopDown.o

#Prereqs for all
ALL_PRE_REQ= main.o game_handler.o game_state_handler.o draw_component.o move_component.o coll_component.o audio_component.o sound_component.o music_component.o random.o helpful_methods.o timer.o matrix.o tracer.o vector.o aabb.o input_handler.o camera.o aeoiaf_color.o steering_handler.o animation.o actor.o aeoiaf_character.o aeoiaf_player.o aeoiaf_nonplayer.o aeoiaf_test_nonplayer.o aeoiaf_faction.o item.o weapon.o weapon_melee.o weapon_melee_test.o weapon_projectile.o weapon_projectile_test.o projectile.o projectile_test.o weapon_tracer.o weapon_tracer_test.o shield.o shield_test.o prop.o prop_simple.o prop_door.o prop_door_tests.o particle.o particle_simple.o script_seq.o tile.o level.o level_draw_component.o level_draw_component_list.o level_character_list.o level_prop_list.o level_particle_list.o level_script_seq_list.o level_actor_coll_list.o level_tile_coll_list.o remove_script_seq_stack.o level_pathfinding.o level_ai_data.o menu_component.o menu_container.o button.o main_menu.o draw_component_list.o audio_component_list.o prop_handler.o weapon_handler.o shield_handler.o character_handler.o particle_handler.o level_handler.o game_data_handler.o remove_actor_list.o insert_actor_list.o stream_data.o level_stream_handling.o game_state.o state_intro.o state_main_menu.o state_top_down.o 

all: clean cmp_all link_all

clean:
	rm -f ./bin/*.out ./bin/obj/*.o

cmp_all: $(ALL_PRE_REQ)

link_all:
	$(COMPILER) $(OBJ) -Wl,-rpath,'$$ORIGIN/lib/' -Wl,-z,origin $(COMPILE_FLAGS_POST) ./bin/$(EXE_NAME)

main.o: $(MAIN)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(MAIN) $(COMPILE_FLAGS_POST) $(MAIN_O)

game_handler.o: $(GAME_HANDLER)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(GAME_HANDLER) $(COMPILE_FLAGS_POST) $(GAME_HANDLER_O)

game_state_handler.o: $(GAME_STATE_HANDLER)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(GAME_STATE_HANDLER) $(COMPILE_FLAGS_POST) $(GAME_STATE_HANDLER_O)

draw_component.o: $(DRAW_COMPONENT)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(DRAW_COMPONENT) $(COMPILE_FLAGS_POST) $(DRAW_COMPONENT_O)

move_component.o: $(move_COMPONENT)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(MOVE_COMPONENT) $(COMPILE_FLAGS_POST) $(MOVE_COMPONENT_O)

coll_component.o: $(COLL_COMPONENT)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(COLL_COMPONENT) $(COMPILE_FLAGS_POST) $(COLL_COMPONENT_O)

audio_component.o: $(AUDIO_COMPONENT)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(AUDIO_COMPONENT) $(COMPILE_FLAGS_POST) $(AUDIO_COMPONENT_O)

sound_component.o: $(SOUND_COMPONENT)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(SOUND_COMPONENT) $(COMPILE_FLAGS_POST) $(SOUND_COMPONENT_O)

music_component.o: $(MUSIC_COMPONENT)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(MUSIC_COMPONENT) $(COMPILE_FLAGS_POST) $(MUSIC_COMPONENT_O)

random.o: $(RANDOM)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(RANDOM) $(COMPILE_FLAGS_POST) $(RANDOM_O)

helpful_methods.o: $(HELPFUL_METHODS)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(HELPFUL_METHODS) $(COMPILE_FLAGS_POST) $(HELPFUL_METHODS_O)

timer.o: $(TIMER)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(TIMER) $(COMPILE_FLAGS_POST) $(TIMER_O)

matrix.o: $(MATRIX)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(MATRIX) $(COMPILE_FLAGS_POST) $(MATRIX_O)

tracer.o: $(TRACER)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(TRACER) $(COMPILE_FLAGS_POST) $(TRACER_O)

vector.o: $(VECTOR)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(VECTOR) $(COMPILE_FLAGS_POST) $(VECTOR_O)

aabb.o: $(AABB)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(AABB) $(COMPILE_FLAGS_POST) $(AABB_O)

input_handler.o: $(INPUT_HANDLER)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(INPUT_HANDLER) $(COMPILE_FLAGS_POST) $(INPUT_HANDLER_O)

camera.o: $(CAMERA)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(CAMERA) $(COMPILE_FLAGS_POST) $(CAMERA_O)

aeoiaf_color.o: $(AEOIAF_COLOR)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(AEOIAF_COLOR) $(COMPILE_FLAGS_POST) $(AEOIAF_COLOR_O)

steering_handler.o: $(STEERING_HANDLER)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(STEERING_HANDLER) $(COMPILE_FLAGS_POST) $(STEERING_HANDLER_O)

animation.o: $(ANIMATION)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(ANIMATION) $(COMPILE_FLAGS_POST) $(ANIMATION_O)

actor.o: $(ACTOR)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(ACTOR) $(COMPILE_FLAGS_POST) $(ACTOR_O)

aeoiaf_character.o: $(AEOIAF_CHARACTER)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(AEOIAF_CHARACTER) $(COMPILE_FLAGS_POST) $(AEOIAF_CHARACTER_O)

aeoiaf_player.o: $(AEOIAF_PLAYER)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(AEOIAF_PLAYER) $(COMPILE_FLAGS_POST) $(AEOIAF_PLAYER_O)

aeoiaf_nonplayer.o: $(AEOIAF_NONPLAYER)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(AEOIAF_NONPLAYER) $(COMPILE_FLAGS_POST) $(AEOIAF_NONPLAYER_O)

aeoiaf_test_nonplayer.o: $(AEOIAF_TESTNONPLAYER)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(AEOIAF_TESTNONPLAYER) $(COMPILE_FLAGS_POST) $(AEOIAF_TEST_NONPLAYER_O)

aeoiaf_faction.o: $(AEOIAF_FACTION)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(AEOIAF_FACTION) $(COMPILE_FLAGS_POST) $(AEOIAF_FACTION_O)

item.o: $(ITEM)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(ITEM) $(COMPILE_FLAGS_POST) $(ITEM_O)

weapon.o: $(WEAPON)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(WEAPON) $(COMPILE_FLAGS_POST) $(WEAPON_O)

weapon_melee.o: $(WEAPON_MELEE)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(WEAPON_MELEE) $(COMPILE_FLAGS_POST) $(WEAPON_MELEE_O)

weapon_melee_test.o: $(WEAPON_MELEE_TEST)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(WEAPON_MELEE_TEST) $(COMPILE_FLAGS_POST) $(WEAPON_MELEE_TEST_O)

weapon_projectile.o: $(WEAPON_PROJECTILE)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(WEAPON_PROJECTILE) $(COMPILE_FLAGS_POST) $(WEAPON_PROJECTILE_O)

weapon_projectile_test.o: $(WEAPON_PROJECTILE_TEST)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(WEAPON_PROJECTILE_TEST) $(COMPILE_FLAGS_POST) $(WEAPON_PROJECTILE_TEST_O)

projectile.o: $(PROJECTILE)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(PROJECTILE) $(COMPILE_FLAGS_POST) $(PROJECTILE_O)

projectile_test.o: $(PROJECTILE_TEST)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(PROJECTILE_TEST) $(COMPILE_FLAGS_POST) $(PROJECTILE_TEST_O)

weapon_tracer.o: $(WEAPON_TRACER)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(WEAPON_TRACER) $(COMPILE_FLAGS_POST) $(WEAPON_TRACER_O)

weapon_tracer_test.o: $(WEAPON_TRACER_TEST)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(WEAPON_TRACER_TEST) $(COMPILE_FLAGS_POST) $(WEAPON_TRACER_TEST_O)

shield.o: $(SHIELD)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(SHIELD) $(COMPILE_FLAGS_POST) $(SHIELD_O)

shield_test.o: $(SHIELD_TEST)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(SHIELD_TEST) $(COMPILE_FLAGS_POST) $(SHIELD_TEST_O)

prop.o: $(PROP)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(PROP) $(COMPILE_FLAGS_POST) $(PROP_O)

prop_simple.o: $(PROP_SIMPLE)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(PROP_SIMPLE) $(COMPILE_FLAGS_POST) $(PROP_SIMPLE_O)

prop_door.o: $(PROP_DOOR)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(PROP_DOOR) $(COMPILE_FLAGS_POST) $(PROP_DOOR_O)

prop_door_tests.o: $(PROP_DOOR_TESTS)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(PROP_DOOR_TESTS) $(COMPILE_FLAGS_POST) $(PROP_DOOR_TESTS_O)

particle.o: $(PARTICLE)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(PARTICLE) $(COMPILE_FLAGS_POST) $(PARTICLE_O)

particle_simple.o: $(PARTICLE_SIMPLE)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(PARTICLE_SIMPLE) $(COMPILE_FLAGS_POST) $(PARTICLE_SIMPLE_O)

script_seq.o: $(SCRIPT_SEQ)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(SCRIPT_SEQ) $(COMPILE_FLAGS_POST) $(SCRIPT_SEQ_O)

tile.o: $(TILE)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(TILE) $(COMPILE_FLAGS_POST) $(TILE_O)

level.o: $(LEVEL)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(LEVEL) $(COMPILE_FLAGS_POST) $(LEVEL_O)

level_draw_component.o: $(LEVEL_DRAW_COMPONENT)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(LEVEL_DRAW_COMPONENT) $(COMPILE_FLAGS_POST) $(LEVEL_DRAW_COMPONENT_O)

level_draw_component_list.o: $(LEVEL_DRAW_COMPONENT_LIST)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(LEVEL_DRAW_COMPONENT_LIST) $(COMPILE_FLAGS_POST) $(LEVEL_DRAW_COMPONENT_LIST_O)

level_character_list.o: $(LEVEL_CHARACTER_LIST)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(LEVEL_CHARACTER_LIST) $(COMPILE_FLAGS_POST) $(LEVEL_CHARACTER_LIST_O)

level_prop_list.o: $(LEVEL_PROP_LIST)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(LEVEL_PROP_LIST) $(COMPILE_FLAGS_POST) $(LEVEL_PROP_LIST_O)

level_particle_list.o: $(LEVEL_PARTICLE_LIST)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(LEVEL_PARTICLE_LIST) $(COMPILE_FLAGS_POST) $(LEVEL_PARTICLE_LIST_O)

level_script_seq_list.o: $(LEVEL_SCRIPT_SEQ_LIST)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(LEVEL_SCRIPT_SEQ_LIST) $(COMPILE_FLAGS_POST) $(LEVEL_SCRIPT_SEQ_LIST_O)

level_actor_coll_list.o: $(LEVEL_ACTOR_COLL_LIST)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(LEVEL_ACTOR_COLL_LIST) $(COMPILE_FLAGS_POST) $(LEVEL_ACTOR_COLL_LIST_O)

level_tile_coll_list.o: $(LEVEL_TILE_COLL_LIST)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(LEVEL_TILE_COLL_LIST) $(COMPILE_FLAGS_POST) $(LEVEL_TILE_COLL_LIST_O)

remove_script_seq_stack.o: $(REMOVE_SCRIPT_SEQ_STACK)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(REMOVE_SCRIPT_SEQ_STACK) $(COMPILE_FLAGS_POST) $(REMOVE_SCRIPT_SEQ_STACK_O)

level_pathfinding.o: $(LEVEL_PATHFINDING)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(LEVEL_PATHFINDING) $(COMPILE_FLAGS_POST) $(LEVEL_PATHFINDING_O)

level_ai_data.o: $(LEVEL_AI_DATA)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(LEVEL_AI_DATA) $(COMPILE_FLAGS_POST) $(LEVEL_AI_DATA_O)

menu_component.o: $(MENU_COMPONENT)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(MENU_COMPONENT) $(COMPILE_FLAGS_POST) $(MENU_COMPONENT_O)

menu_container.o: $(MENU_CONTAINER)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(MENU_CONTAINER) $(COMPILE_FLAGS_POST) $(MENU_CONTAINER_O)

button.o: $(BUTTON)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(BUTTON) $(COMPILE_FLAGS_POST) $(BUTTON_O)

main_menu.o: $(MAIN_MENU)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(MAIN_MENU) $(COMPILE_FLAGS_POST) $(MAIN_MENU_O)

draw_component_list.o: $(DRAW_COMPONENT_LIST)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(DRAW_COMPONENT_LIST) $(COMPILE_FLAGS_POST) $(DRAW_COMPONENT_LIST_O)

audio_component_list.o: $(AUDIO_COMPONENT_LIST)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(AUDIO_COMPONENT_LIST) $(COMPILE_FLAGS_POST) $(AUDIO_COMPONENT_LIST_O)

prop_handler.o: $(PROP_HANDLER)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(PROP_HANDLER) $(COMPILE_FLAGS_POST) $(PROP_HANDLER_O)

weapon_handler.o: $(WEAPON_HANDLER)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(WEAPON_HANDLER) $(COMPILE_FLAGS_POST) $(WEAPON_HANDLER_O)

shield_handler.o: $(SHIELD_HANDLER)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(SHIELD_HANDLER) $(COMPILE_FLAGS_POST) $(SHIELD_HANDLER_O)

character_handler.o: $(CHARACTER_HANDLER)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(CHARACTER_HANDLER) $(COMPILE_FLAGS_POST) $(CHARACTER_HANDLER_O)

particle_handler.o: $(PARTICLE_HANDLER)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(PARTICLE_HANDLER) $(COMPILE_FLAGS_POST) $(PARTICLE_HANDLER_O)

level_handler.o: $(LEVEL_HANDLER)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(LEVEL_HANDLER) $(COMPILE_FLAGS_POST) $(LEVEL_HANDLER_O)

game_data_handler.o: $(GAME_DATA_HANDLER)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(GAME_DATA_HANDLER) $(COMPILE_FLAGS_POST) $(GAME_DATA_HANDLER_O)

remove_actor_list.o: $(REMOVE_ACTOR_LIST)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(REMOVE_ACTOR_LIST) $(COMPILE_FLAGS_POST) $(REMOVE_ACTOR_LIST_O)

insert_actor_list.o: $(INSERT_ACTOR_LIST)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(INSERT_ACTOR_LIST) $(COMPILE_FLAGS_POST) $(INSERT_ACTOR_LIST_O)

stream_data.o: $(STREAM_DATA)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(STREAM_DATA) $(COMPILE_FLAGS_POST) $(STREAM_DATA_O)

level_stream_handling.o: $(LEVEL_STREAM_HANDLING)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(LEVEL_STREAM_HANDLING) $(COMPILE_FLAGS_POST) $(LEVEL_STREAM_HANDLING_O)

game_state.o: $(GAME_STATE)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(GAME_STATE) $(COMPILE_FLAGS_POST) $(GAME_STATE_O)

state_intro.o: $(STATE_INTRO)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(STATE_INTRO) $(COMPILE_FLAGS_POST) $(STATE_INTRO_O)

state_main_menu.o: $(STATE_MAIN_MENU)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(STATE_MAIN_MENU) $(COMPILE_FLAGS_POST) $(STATE_MAIN_MENU_O)

state_top_down.o: $(STATE_TOP_DOWN)
	$(COMPILER) $(COMPILE_FLAGS_PRE) $(STATE_TOP_DOWN) $(COMPILE_FLAGS_POST) $(STATE_TOP_DOWN_O)
