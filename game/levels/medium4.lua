function getInfo()
  -- Title
  local title = {
  "Day 14.",
  "Jour 14." }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-peanuts.mp3")
  -- Timer
  varTimeElapsed(60)
  -- Player 
  varPlayerX(16*1)
  varPlayerY(16*2)
  -- Gravity
  varGravityDir(2)
end


function setLevel()
  -- Temporary level matrix
  local lvl_w, lvl_h = 25, 19
  local lvl =
    {{0,0,0,0,0,0,0,0,1,4,4,4,1,1,1,4,4,4,4,4,4,2,2,0,0},
     {1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,2,0,0},
     {1,9,0,0,0,0,0,0,0,5,5,5,0,0,1,0,0,0,0,0,0,0,2,0,0},
     {1,1,1,1,0,0,0,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,2,0,0},
     {1,0,0,0,1,4,1,0,0,0,0,2,0,0,1,0,0,0,0,4,0,8,2,0,0},
     {4,0,0,c,5,5,5,5,5,0,3,2,0,4,4,0,0,0,0,4,c,c,2,0,0},
     {4,0,0,c,5,5,5,5,5,0,3,2,0,4,0,0,0,0,0,4,5,5,2,0,0},
     {1,0,5,2,5,5,5,5,5,0,0,9,0,4,0,0,0,0,0,4,c,c,2,0,0},
     {2,5,0,2,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,1,2,c,2,0,0},
     {2,0,5,0,2,2,2,2,4,4,4,0,0,2,0,0,0,0,0,1,c,c,2,0,0},
     {0,2,0,5,0,0,0,2,4,0,0,0,0,2,0,3,3,3,0,1,5,5,2,0,0},
     {0,0,2,0,0,0,0,2,0,0,0,2,0,2,0,0,0,0,0,1,0,3,2,0,0},
     {0,0,2,4,4,0,0,2,0,0,0,2,0,0,1,1,0,1,1,1,0,0,0,4,0},
     {0,0,2,0,0,0,0,2,0,0,0,2,0,0,7,0,0,5,5,1,0,0,0,4,0},
     {0,0,2,0,0,0,0,2,0,0,0,3,0,1,1,1,0,1,1,1,4,0,0,4,0},
     {0,0,2,0,0,4,4,2,4,0,0,2,5,5,5,2,0,2,0,c,0,0,0,4,0},
     {0,0,2,0,0,0,0,2,0,0,0,2,5,5,5,2,0,2,0,0,2,2,2,2,2},
     {0,0,3,0,0,0,0,0,0,0,0,2,5,5,5,2,3,0,0,0,0,0,0,0,2},
     {0,0,2,2,2,2,2,2,2,3,2,2,3,2,2,2,2,4,4,4,4,4,4,2,2}}
      
     
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
  createObjectAligned(16*23,16*17,0,0,b,16)
  objectText("./levels/medium5.lua")
  
  -- Init checkpoints
  createObjectAligned(16*4,16*17,0,0,a,16)
  local t1 = {
  "I should name this trick.",
  "Je devrais donner un nom à cette figure." }
  objectText(t1[getLanguageID()+1])
end
