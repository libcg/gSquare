function getInfo()
  -- Title
  local title = {
  "Day 3.",
  "Jour 3." }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-itscomplicated.mp3")
  -- Timer
  varTimeElapsed(60)
  -- Player 
  varPlayerX(16)
  varPlayerY(240)
  -- Gravity
  varGravityDir(2)
end


function setLevel()
  -- Temporary level matrix
  local lvl_w, lvl_h = 30, 17
  local lvl =
    {{0,4,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,2,2,2,2,0},
     {4,0,0,0,0,5,0,5,0,5,0,5,0,0,0,1,0,0,0,1,0,0,0,0,0,2,0,0,0,2},
     {0,0,0,0,5,0,5,0,5,0,5,0,5,0,0,1,0,1,0,0,0,0,3,0,0,0,0,4,0,2},
     {0,0,0,0,1,2,2,2,2,2,2,2,2,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,2},
     {0,0,1,1,1,4,4,4,4,4,4,4,4,3,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,2},
     {0,0,4,4,4,0,0,0,0,0,0,0,4,2,2,2,2,2,2,2,0,0,0,0,0,0,1,0,0,2},
     {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,4},
     {5,0,5,0,5,0,3,0,0,0,0,0,1,0,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,4},
     {0,0,0,0,5,5,5,5,5,5,5,5,3,0,0,0,2,2,0,0,2,0,0,0,0,2,0,0,0,4},
     {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,2,0,0,0,0,2,0,0,0,4},
     {4,4,4,4,4,4,4,4,1,1,0,0,1,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,0,1},
     {1,1,1,1,1,1,1,1,1,0,0,1,1,2,0,0,0,0,0,0,3,0,0,2,0,0,2,0,0,1},
     {1,0,0,0,0,0,0,0,0,0,1,1,0,0,2,0,0,0,0,0,2,0,0,2,0,0,2,0,0,1},
     {1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,2,0,0,0,0,2,0,0,3,0,0,2,0,0,1},
     {1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,2,0,0,0,2,0,0,2,0,0,1,0,0,1},
     {1,9,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,2,0,0,9,0,0,1,0,0,1,0,0,1},
     {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,2,2,2,3,3,1,0,0,1,0,0,1}}
    
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
  createObjectAligned(16*16,16*2,0,0,b,16)
  objectText("./levels/easy4.lua")
  
  -- Init checkpoints
  createObjectAligned(16*3,16*3,0,0,9,16)
  local t1 = {
  "Oh! That looks pretty cool.",
  "Oh! Je vais m'amuser." }
  objectText(t1[getLanguageID()+1])
end


