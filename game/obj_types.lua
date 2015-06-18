a,b,c,d,e,f,g,h,i,j,k,l,m,n,o = 10,11,12,13,14,15,16,17,18,19,20,21,22,23,24
p,q,r,s = 25,26,27,28

-- Touch callbacks

function collect_touch_callback()
  varTimeElapsed(varTimeElapsed() + 5)
  setTimerAspect(1.5,255,255,0)
  playSound("coin")
end

function checkpoint_north_touch_callback()
  setTimerAspect(-1,0,255,0)
  setPlayerState(varObjX()+2,varObjY()+2,0)
end

function checkpoint_east_touch_callback()
  setTimerAspect(-1,0,255,0)
  setPlayerState(varObjX()+2,varObjY()+2,1)
end

function checkpoint_south_touch_callback()
  setTimerAspect(-1,0,255,0)
  setPlayerState(varObjX()+2,varObjY()+2,2)
end

function checkpoint_west_touch_callback()
  setTimerAspect(-1,0,255,0)
  setPlayerState(varObjX()+2,varObjY()+2,3)
end

function finish_touch_callback()
  setMusic("!")
  setNextLevel(varObjText())
  pushGameState(WIN)
end

-- Tick callbacks

function collect_tick_callback()
  varObjReg(0,varObjReg(0)+1.5)
  if     varObjReg(0) < 10 then varObjState(0)
  elseif varObjReg(0) < 20 then varObjState(1)
  elseif varObjReg(0) < 30 then varObjState(2)
  elseif varObjReg(0) < 40 then varObjState(3)
  elseif varObjReg(0) < 50 then varObjState(4)
  elseif varObjReg(0) < 60 then varObjState(5)
  elseif varObjReg(0) < 70 then varObjState(6)
  else varObjReg(0,0) end
end

--loadSound("./audio/coin.wav","coin")

initObjectType()

-- Player
createObjectType(7*32,0*32,
                 25,25,
                 GRAVITY + COLLIDE + FRICTION + CAN_BREAK + AIR_RESISTANCE + PLAYER,
                 "!",
                 "!")
-- Floor 1
createObjectType(0*32,0*32,
                 32,32,
                 FIXED + FRICTION + COLLIDE + INVINCIBLE,
                 "!",
                 "!")
-- Floor 2
createObjectType(0*32,1*32,
                 32,32,
                 FIXED + FRICTION + COLLIDE + INVINCIBLE,
                 "!",
                 "!")
-- Floor 3
createObjectType(0*32,2*32,
                 32,32,
                 FIXED + FRICTION + COLLIDE + INVINCIBLE,
                 "!",
                 "!")
-- Floor 4
createObjectType(0*32,3*32,
                 32,32,
                 FIXED + FRICTION + COLLIDE + INVINCIBLE,
                 "!",
                 "!")
-- Floor 5
createObjectType(0*32,4*32,
                 32,32,
                 FIXED + FRICTION + COLLIDE + INVINCIBLE,
                 "!",
                 "!")
-- Floor 6
createObjectType(0*32,5*32,
                 32,32,
                 FIXED + FRICTION + COLLIDE + INVINCIBLE,
                 "!",
                 "!")
-- Slime 7
createObjectType(2*32,3*32,
                 32,32,
                 FIXED + FRICTION + COLLIDE + BIG_JUMP + INVINCIBLE,
                 "!",
                 "!")
-- Avoid 8
createObjectType(1*32,3*32,
                 32,32,
                 FIXED + FRICTION + COLLIDE + TOUCH_TO_DIE + INVINCIBLE,
                 "!",
                 "!")
-- Collect 9
createObjectType(6*32,0*32,
                 17,17,
                 FIXED + DEATH_BY_TOUCH,
                 "collect_touch_callback",
                 "collect_tick_callback")
-- Checkpoint North a
createObjectType(400,400,
                 32,32,
                 FIXED + INVINCIBLE + TEXT,
                 "checkpoint_north_touch_callback",
                 "!")
-- Checkpoint East b
createObjectType(400,400,
                 32,32,
                 FIXED + INVINCIBLE + TEXT,
                 "checkpoint_east_touch_callback",
                 "!")
-- Checkpoint South c       
createObjectType(400,400,
                 32,32,
                 FIXED + INVINCIBLE + TEXT,
                 "checkpoint_south_touch_callback",
                 "!")
-- Checkpoint West d
createObjectType(400,400,
                 32,32,
                 FIXED + INVINCIBLE + TEXT,
                 "checkpoint_west_touch_callback",
                 "!")
-- Finish b
createObjectType(8*17,0,
                 16,16,
                 FIXED + INVINCIBLE,
                 "finish_touch_callback",
                 "!")    

