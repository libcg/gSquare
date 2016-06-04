function getInfo()
  -- Title
  local title = {
  "Day 12.\n\nCoins are your friends",
  "Jour 12.\n\nLes pièces sont vos amies" }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-itscomplicated.mp3")
  -- Player 
  varPlayerX(16*9)
  varPlayerY(16*10)
  -- Gravity
  varGravityDir(1)
end


function setLevel()
  -- Temporary level matrix
  local lvl_w, lvl_h = 16, 19
  local lvl =
    {{0,0,0,0,0,0,4,4,4,0,0,0,0,0,0,0},
     {0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0},
     {0,0,4,2,2,2,0,0,0,2,4,4,4,4,4,0},
     {0,2,0,4,4,0,0,2,0,0,4,0,0,0,0,2},
     {2,0,0,c,0,0,0,4,0,9,0,0,0,0,0,2},
     {2,0,2,2,2,2,2,2,2,2,1,1,2,2,0,2},
     {2,0,2,0,0,0,5,5,5,5,5,0,2,0,0,2},
     {2,c,2,0,0,5,5,1,1,1,5,5,2,0,0,2},
     {0,0,0,0,0,5,1,0,0,0,1,5,2,0,4,2},
     {0,0,0,0,0,5,c,0,0,0,3,5,2,0,0,2},
     {0,0,0,0,0,5,1,0,0,0,1,5,2,0,0,2},
     {2,2,2,0,0,5,5,1,1,1,5,5,2,4,0,2},
     {2,0,2,0,0,0,5,5,5,5,5,0,2,0,0,2},
     {2,0,2,2,2,2,2,2,2,2,1,4,2,0,1,0},
     {2,0,0,0,0,0,4,0,0,2,0,0,0,0,2,0},
     {0,2,0,4,0,0,0,0,0,1,0,2,2,2,2,0},
     {0,0,2,4,2,2,2,0,0,1,0,2,0,0,0,0},
     {0,0,0,0,0,0,0,2,c,0,9,3,0,0,0,0},
     {0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0}}
     
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
  createObjectAligned(16*1,16*12,0,0,b,16)
  objectText("./levels/medium3.lua")
  
  -- Init checkpoints
  createObjectAligned(16*9,16*10,0,0,8,16)
  local t1 = {
  "Boing boing boing boing",
  "Boing boing boing boing" }
  objectText(t1[getLanguageID()+1])
end
