a,b,c,d,e,f,g,h,i,j,k,l,m,n,o = 10,11,12,13,14,15,16,17,18,19,20,21,22,23,24
p,q,r,s = 25,26,27,28
bullet_speed = 4.5

-- Touch callbacks

function coin_touch_callback()
  -- TODO find coins a purpose
  playSound("coin")
end

function checkpoint_north_touch_callback()
  setPlayerState(varObjX()+2,varObjY()+2,0)
end

function checkpoint_east_touch_callback()
  setPlayerState(varObjX()+2,varObjY()+2,1)
end

function checkpoint_south_touch_callback()
  setPlayerState(varObjX()+2,varObjY()+2,2)
end

function checkpoint_west_touch_callback()
  setPlayerState(varObjX()+2,varObjY()+2,3)
end

function finish_touch_callback()
  setMusic("!")
  setNextLevel(varObjText())
  pushGameState(WIN)
end

function gravity_north_touch_callback()
  varGravityDir(0)
  varGravityLock(1)
end

function gravity_east_touch_callback()
  varGravityDir(1)
  varGravityLock(1)
end

function gravity_south_touch_callback()
  varGravityDir(2)
  varGravityLock(1)
end

function gravity_west_touch_callback()
  varGravityDir(3)
  varGravityLock(1)
end

function gravity_all_touch_callback()
  varGravityLock(0)
end

function autodestroy_touch_callback()
  varObjReg(0,1)
end

-- Tick callbacks

function cannon_north_tick_callback()
  if (varObjReg(0,varObjReg(0)+1) > 120) then
    createObject(varObjX()+6,varObjY()-4,0,-bullet_speed,d)
    varObjReg(0,0)
  end
end

function cannon_east_tick_callback()
  if (varObjReg(0,varObjReg(0)+1) > 120) then
    createObject(varObjX()+20,varObjY()+6,bullet_speed,0,d)
    varObjReg(0,0)
  end
end

function cannon_south_tick_callback()
  if (varObjReg(0,varObjReg(0)+1) > 120) then
    createObject(varObjX()+6,varObjY()+20,0,bullet_speed,d)
    varObjReg(0,0)
  end
end

function cannon_west_tick_callback()
  if (varObjReg(0,varObjReg(0)+1) > 120) then
    createObject(varObjX()-4,varObjY()+6,-bullet_speed,0,d)
    varObjReg(0,0)
  end
end

function death_ray_launcher_north_tick_callback()
  createRay(varObjX()+6,varObjY()+2,4,0,r)
end

function death_ray_launcher_east_tick_callback()
  createRay(varObjX()+14,varObjY()+6,4,1,r)
end

function death_ray_launcher_south_tick_callback()
  createRay(varObjX()+6,varObjY()+14,4,2,r)
end

function death_ray_launcher_west_tick_callback()
  createRay(varObjX()+2,varObjY()+6,4,3,r)
end

function death_ray_launcher_west_tick_callback()
  createRay(varObjX()+2,varObjY()+6,4,3,r)
end

function autodestroy_tick_callback()
  if varObjReg(0) == 1 then
    varObjReg(1,varObjReg(1)+1)
    if varObjReg(1) > 10 then varObjState(1) end
    if varObjReg(1) > 20 then varObjState(2) end
    if varObjReg(1) > 30 then varObjState(3) end
    if varObjReg(1) > 40 then varObjState(4) end
    if varObjReg(1) > 50 then varObjDeath(1) end
  end
end

loadSound("./audio/coin.wav","coin")

initObjectType()

-- Bluz 0
createObjectType(0,0,
                 12,12,
                 GRAVITY + FRICTION + COLLIDE + CAN_BREAK +
                 AIR_RESISTANCE + PLAYER,
                 "!",
                 "!")
-- Floor 1
createObjectType(1*17,0,
                 16,16,
                 FIXED + FRICTION + COLLIDE + INVINCIBLE,
                 "!",
                 "!")
-- Ice 2
createObjectType(2*17,0,
                 16,16,
                 FIXED + COLLIDE + INVINCIBLE,
                 "!",
                 "!")
-- Jump 3
createObjectType(3*17,0,
                 16,16,
                 FIXED + FRICTION + COLLIDE + BIG_JUMP + INVINCIBLE,
                 "!",
                 "!")
-- Kill 4
createObjectType(4*17,0,
                 16,16,
                 FIXED + FRICTION + COLLIDE + TOUCH_TO_DIE + INVINCIBLE,
                 "!",
                 "!")
-- Coin 5
createObjectType(5*17,0,
                 6,6,
                 FIXED + DEATH_BY_TOUCH,
                 "coin_touch_callback",
                 "!")
-- Princess 6
createObjectType(6*17,0,
                 12,12,
                 GRAVITY + COLLIDE + FRICTION + AIR_RESISTANCE + PLAYER,
                 "!",
                 "!") 
-- Checkpoint North 7
createObjectType(7*17,17*0,
                 16,16,
                 FIXED + INVINCIBLE + TEXT,
                 "checkpoint_north_touch_callback",
                 "!")
-- Checkpoint East 8
createObjectType(7*17,17*1,
                 16,16,
                 FIXED + INVINCIBLE + TEXT,
                 "checkpoint_east_touch_callback",
                 "!")
-- Checkpoint South 9       
createObjectType(7*17,17*2,
                 16,16,
                 FIXED + INVINCIBLE + TEXT,
                 "checkpoint_south_touch_callback",
                 "!")
-- Checkpoint West a
createObjectType(7*17,17*3,
                 16,16,
                 FIXED + INVINCIBLE + TEXT,
                 "checkpoint_west_touch_callback",
                 "!")
-- Finish b
createObjectType(8*17,0,
                 16,16,
                 FIXED + INVINCIBLE,
                 "finish_touch_callback",
                 "!")    
-- Breakable c
createObjectType(9*17,0,
                 16,16,
                 FIXED + FRICTION + COLLIDE + BREAKABLE,
                 "!",
                 "!")
-- Bullet d
createObjectType(10*17,0,
                 4,4,
                 COLLIDE + TOUCH_TO_DIE + DEATH_BY_TOUCH,
                 "!",
                 "!")
-- Cannon North e
createObjectType(11*17,17*0,
                 16,16,
                 FIXED + INVINCIBLE,
                 "!",
                 "cannon_north_tick_callback")
-- Cannon East f
createObjectType(11*17,17*1,
                 16,16,
                 FIXED + INVINCIBLE,
                 "!",
                 "cannon_east_tick_callback")
-- Cannon South g
createObjectType(11*17,17*2,
                 16,16,
                 FIXED + INVINCIBLE,
                 "!",
                 "cannon_south_tick_callback")
-- Cannon West h
createObjectType(11*17,17*3,
                 16,16,
                 FIXED + INVINCIBLE,
                 "!",
                 "cannon_west_tick_callback")
-- Gravity North i
createObjectType(12*17,17*0,
                 16,16,
                 FIXED + INVINCIBLE,
                 "gravity_north_touch_callback",
                 "!")
-- Gravity East j
createObjectType(12*17,17*1,
                 16,16,
                 FIXED + INVINCIBLE,
                 "gravity_east_touch_callback",
                 "!")
-- Gravity South k
createObjectType(12*17,17*2,
                 16,16,
                 FIXED + INVINCIBLE,
                 "gravity_south_touch_callback",
                 "!")
-- Gravity West l
createObjectType(12*17,17*3,
                 16,16,
                 FIXED + INVINCIBLE,
                 "gravity_west_touch_callback",
                 "!")
-- Gravity All m
createObjectType(12*17,17*4,
                 16,16,
                 FIXED + INVINCIBLE,
                 "gravity_all_touch_callback",
                 "!")
-- Death Ray Launcher North n
createObjectType(13*17,17*0,
                 16,16,
                 FIXED + INVINCIBLE,
                 "!",
                 "death_ray_launcher_north_tick_callback")
-- Death Ray Launcher East o
createObjectType(13*17,17*1,
                 16,16,
                 FIXED + INVINCIBLE,
                 "!",
                 "death_ray_launcher_east_tick_callback")
-- Death Ray Launcher South p
createObjectType(13*17,17*2,
                 16,16,
                 FIXED + INVINCIBLE,
                 "!",
                 "death_ray_launcher_south_tick_callback")
-- Death Ray Launcher West q
createObjectType(13*17,17*3,
                 16,16,
                 FIXED + INVINCIBLE,
                 "!",
                 "death_ray_launcher_west_tick_callback")
-- Death Ray r, can't be used as a regular object
createObjectType(14*17,17*0,
                 4,4,
                 TOUCH_TO_DIE,
                 "!",
                 "!")
-- Autodestroy s
createObjectType(15*17,17*0,
                 16,16,
                 FIXED + FRICTION + COLLIDE,
                 "autodestroy_touch_callback",
                 "autodestroy_tick_callback")
