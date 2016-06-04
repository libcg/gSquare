function getInfo()
  -- Title
  local title = {
  "Day 26.\n\nWhere she can escape unlike you",
  "Jour 26.\n\nOù elle peut s'échapper contrairement à vous" }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-sometimesimakevideogamemusic.mp3")
  -- Player 
  varPlayerX(16*9)
  varPlayerY(16*5)
  -- Gravity
  varGravityDir(2)
end


function setLevel()
  -- Temporary level matrix
  local lvl_w, lvl_h = 19, 11
  local lvl =
    {{0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
	   {0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,0,0},
	   {0,0,0,1,0,0,0,0,1,0,0,0,3,0,0,1,0,0,0},
	   {0,0,1,0,0,1,0,0,0,0,0,3,0,0,0,0,1,0,0},
	   {0,1,6,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0},
	   {1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,3,0,0,1},
	   {0,0,0,0,0,3,0,0,0,1,0,0,0,0,0,0,0,1,0},
	   {0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,1,0,0},
	   {0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,1,0,0,0},
	   {0,0,0,0,0,0,0,0,0,3,0,0,0,0,1,0,0,0,0},
	   {0,0,0,0,0,3,0,0,0,0,0,0,0,1,0,0,0,0,0}}
      
     
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
  createObjectAligned(16*1,16*6,0,0,b,16)
  objectText("./levels/canon7.lua")
  
  -- Init checkpoints
  createObjectAligned(16*9,16*5,0,0,9,16)
  local t1 = {
  "Hidi Ho! I'm a pirate!",
  "Hidi Ho! Je suis un pirate!" }
  objectText(t1[getLanguageID()+1])
end
