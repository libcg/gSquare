function getInfo()
  -- Title
  local title = {
  "Day 13.\n\nKeep it simple, stupid",
  "Jour 13.\n\nRestez simple" }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-heyhey.mp3")
  -- Timer
  varTimeElapsed(120)
  -- Player 
  varPlayerX(16*6)
  varPlayerY(16*4)
  -- Gravity
  varGravityDir(2)
end


function setLevel()
  -- Temporary level matrix
  local lvl_w, lvl_h = 17, 16
  local lvl =
    {{0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0},
     {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
     {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
     {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
     {0,0,0,0,0,0,9,1,1,1,1,0,0,0,0,0,0},
     {0,0,0,0,0,0,1,0,4,0,1,1,0,0,0,0,0},
     {0,0,0,0,0,1,0,0,4,0,4,1,1,0,0,0,0},
     {0,0,0,0,1,0,0,0,0,0,0,0,2,0,0,0,0},
     {4,4,4,4,1,0,0,0,0,0,0,0,1,2,2,4,2},
     {0,0,0,0,1,0,0,4,0,0,4,0,1,0,0,0,0},
     {0,0,0,0,0,1,0,0,2,0,0,1,0,0,0,0,0},
     {0,0,0,0,0,0,2,0,0,2,1,0,0,0,0,0,0},
     {0,0,0,0,0,0,0,1,c,1,0,0,0,0,0,0,0},
     {0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0},
     {0,0,0,0,0,0,0,2,0,2,0,0,0,0,0,0,0},
     {0,0,0,0,0,0,0,2,0,2,0,0,0,0,0,0,0}}
       
     
  -- Reset level
  initObject()
  
  -- Init objects using the matrix
  for i=1,lvl_w do
    for j=1,lvl_h do
      if lvl[j][i]>0 then
        createObjectAligned(16*(i-1),16*(j-1),0,0,lvl[j][i],16)
      end
    end
  end
  
  -- Finish
  createObjectAligned(16*9,16*5,0,0,b,16)
  objectText("./levels/medium4.lua")
  
  -- Init checkpoints
  createObjectAligned(16*8,16*13,0,0,7,16)
  local t1 = {
  "Okay, let's go inside now !",
  "OK, je vais à l'intérieur maintenant !" }
  objectText(t1[getLanguageID()+1])
end
