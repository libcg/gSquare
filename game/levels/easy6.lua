function getInfo()
  -- Title
  local title = {
  "Day 6.",
  "Jour 6." }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-repetition.mp3")
  -- Timer
  varTimeElapsed(60)
  -- Player 
  varPlayerX(16*1)
  varPlayerY(16*2)
  -- Gravity
  varGravityDir(3)
end


function setLevel()
  -- Temporary level matrix
  local lvl_w, lvl_h = 23, 17
  local lvl =
      {{1,1,1,1,4,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
       {1,0,0,0,0,4,0,0,0,5,0,5,0,1,0,5,0,0,0,0,0,0,1},
       {1,a,0,5,0,5,0,5,0,4,0,0,0,1,0,1,5,0,5,1,1,0,1},
       {1,1,1,1,1,1,1,1,4,4,1,1,5,4,5,1,0,5,0,1,0,0,3},
       {1,7,0,0,0,4,4,1,5,5,5,1,0,5,0,1,9,0,5,1,0,1,1},
       {1,0,0,4,0,0,4,1,5,5,5,1,1,1,1,1,1,1,1,3,0,0,1},
       {1,0,0,1,0,0,0,1,0,0,1,0,0,4,4,4,4,4,4,4,1,0,1},
       {1,0,4,1,0,0,0,1,0,0,0,0,0,0,0,0,0,4,0,0,0,0,1},
       {1,0,0,1,1,4,0,1,0,0,0,0,0,5,5,5,5,4,0,0,0,1,1},
       {1,0,0,1,0,0,0,1,0,0,1,1,1,1,0,0,1,4,0,0,0,0,4},
       {1,4,0,1,0,0,0,1,0,0,0,0,4,0,5,5,0,4,0,0,0,0,4},
       {1,0,0,1,0,4,1,1,5,0,0,0,4,0,5,5,0,4,0,0,0,1,1},
       {1,0,0,1,0,0,0,3,0,5,0,0,4,0,5,5,0,4,0,0,0,0,1},
       {1,0,4,1,0,0,0,3,0,5,0,0,4,0,5,5,0,1,1,1,0,0,1},
       {1,0,0,1,0,0,0,1,5,0,0,0,4,0,5,5,0,0,0,0,0,0,1},
       {1,0,0,1,0,0,0,0,0,0,0,0,4,0,0,0,0,1,4,0,0,8,1},
       {1,1,1,1,3,1,1,1,1,1,1,1,1,3,3,3,1,1,1,1,1,1,1}}

     
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
  createObjectAligned(16*1,16*15,0,0,b,16)
  objectText("./levels/easy7.lua")
  
  -- Init checkpoints
  createObjectAligned(16*7,16*15,0,0,7,16)
  local t1 = {
  "It was easier than I thought to get here.",
  "C'était plus facile que je ne le pensais pour arriver jusqu'ici." }
  objectText(t1[getLanguageID()+1])
  
end
