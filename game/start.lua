-- Define constants
INGAME = 0
LOSE = 1
WIN = 2

FIXED = 1
GRAVITY = 2
BIG_JUMP = 4
FRICTION = 8
DEATH_BY_TOUCH = 16
TOUCH_TO_DIE = 32
COLLIDE = 64
BREAKABLE = 128
CAN_BREAK = 256
INVINCIBLE = 512
AIR_RESISTANCE = 1024
PLAYER = 2048
TEXT = 4096

dofile("obj_types.lua")

setNextLevel("./levels/easy1.lua")
