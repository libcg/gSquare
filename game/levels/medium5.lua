function getInfo()
  -- Title
  local title = {
  "Day 15.",
  "Jour 15." }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-repetition.mp3")
  -- Timer
  varTimeElapsed(60)
  -- Player 
  varPlayerX(16*4)
  varPlayerY(16*4)
  -- Gravity
  varGravityDir(3)
end


function setLevel()
  -- Temporary level matrix
  local lvl_w, lvl_h = 20, 18
  local lvl =
     {{4,4,4,4,0,0,5,5,0,4,4,4,2,2,2,2,2,2,2,2},
      {4,0,0,0,0,5,0,0,5,0,0,0,0,0,0,0,0,0,0,2},
      {4,0,0,0,0,0,4,4,0,0,0,0,0,0,2,2,2,2,2,2},
      {4,0,0,2,2,2,0,0,2,2,2,2,2,2,0,0,5,0,5,2},
      {4,0,0,2,a,0,0,0,0,0,0,0,0,4,0,5,9,5,0,2},
      {4,0,0,2,2,2,2,2,2,2,2,0,0,2,0,0,2,2,5,1},
      {4,0,0,0,0,4,2,5,5,2,0,0,0,0,0,0,0,2,0,1},
      {4,4,3,0,0,0,2,5,5,2,0,5,5,5,5,5,0,2,5,1},
      {0,0,0,2,a,0,4,0,0,4,0,0,5,5,5,0,0,2,0,1},
      {0,0,0,0,2,0,5,0,0,1,0,0,0,5,0,0,0,1,5,1},
      {0,0,0,0,0,2,5,0,0,1,0,0,0,0,0,0,4,1,0,1},
      {0,0,0,0,0,0,3,0,0,1,4,3,3,3,3,3,1,1,5,1},
      {0,0,0,0,0,0,0,2,0,0,0,4,4,1,1,1,1,0,0,1},
      {0,0,0,0,0,0,0,0,2,0,0,0,0,1,5,0,0,0,3,0},
      {0,0,0,0,0,0,0,0,0,2,0,0,0,1,5,0,0,2,0,0},
      {0,0,0,0,0,0,0,0,0,0,4,0,0,3,0,0,2,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0}}
      
     
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
  createObjectAligned(16*18,16*1,0,0,b,16)
  objectText("./levels/medium6.lua")
  
  -- Init checkpoints
  createObjectAligned(16*12,16*16,0,0,9,16)
  local t1 = {
  "I'm feeling like ice climbers.",
  "Je me sens tel un alpiniste." }
  objectText(t1[getLanguageID()+1])
end
