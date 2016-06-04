function getInfo()
  -- Title
  local title = {
  "Day 19.",
  "Jour 19." }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-sometimesimakevideogamemusic.mp3")
  -- Player 
  varPlayerX(16*9)
  varPlayerY(16*7)
  -- Gravity
  varGravityDir(2)
end


function setLevel()
  -- Temporary level matrix
  local lvl_w, lvl_h = 19, 14
  local lvl =
    {{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	   {1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
	   {1,3,0,1,1,1,1,1,1,0,0,1,0,1,0,0,0,0,1},
	   {1,0,0,0,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1},
	   {1,0,0,3,0,0,0,3,1,0,0,1,0,1,0,1,0,0,1},
	   {1,0,0,0,0,3,0,0,0,0,1,1,0,0,0,1,0,0,1},
	   {1,3,0,0,0,0,0,0,0,1,0,0,0,3,0,0,0,0,1},
	   {1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,3,1},
	   {1,6,0,0,1,0,0,0,0,1,0,0,0,3,0,0,0,0,1},
	   {1,1,1,0,1,0,0,1,0,0,0,3,0,0,0,3,0,0,1},
	   {1,0,0,0,3,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
	   {1,0,0,0,0,0,0,1,0,0,0,3,0,0,0,3,0,0,1},
	   {1,0,0,0,3,0,0,1,0,0,0,0,0,3,0,0,0,0,1},
	   {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}}
      
     
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
  createObjectAligned(16*7,16*1,0,0,b,16)
  objectText("./levels/canon1.lua")
  
  -- Init checkpoints
  createObjectAligned(16*9,16*7,0,0,9,16)
  local t1 = {
  "I want to be free. Now.",
  "Je veux être libre. Maintenant." }
  objectText(t1[getLanguageID()+1])
end
