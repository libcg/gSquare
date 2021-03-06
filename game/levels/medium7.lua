function getInfo()
  -- Title
  local title = {
  "Day 17.",
  "Jour 17." }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-sometimesimakevideogamemusic.mp3")
  -- Player 
  varPlayerX(16*1)
  varPlayerY(16*7)
  -- Gravity
  varGravityDir(2)
end


function setLevel()
  -- Temporary level matrix
  local lvl_w, lvl_h = 31, 15
  local lvl =
    {{0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,2,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,3,3,4,4,0,0},
	   {0,0,0,0,2,0,5,0,0,0,0,0,0,5,5,0,0,0,0,0,4,1,1,0,0,0,0,0,4,0,0},
	   {0,0,0,0,2,5,0,2,2,2,0,2,0,0,0,0,5,0,0,0,4,1,7,0,0,0,5,0,4,0,0},
	   {0,0,0,0,2,5,0,4,4,4,4,4,4,1,1,0,5,0,0,4,0,0,0,0,0,0,0,0,4,0,0},
	   {1,1,1,1,1,0,0,0,0,0,0,0,0,4,1,0,0,0,0,4,1,0,0,0,0,0,5,0,4,0,0},
	   {1,0,0,0,0,1,0,0,0,0,0,0,0,2,4,0,0,0,0,4,1,0,0,0,4,0,0,4,4,4,4},
	   {1,9,0,0,5,0,1,0,9,0,0,0,0,2,4,1,0,0,0,4,0,0,0,0,4,0,5,2,2,1,4},
	   {1,1,1,1,0,5,0,1,2,2,2,0,0,2,4,0,0,5,0,4,0,0,0,0,4,0,0,0,5,0,4},
	   {0,0,0,0,4,0,5,0,1,1,1,0,0,4,0,0,0,5,0,4,1,0,0,0,4,0,0,0,0,0,4},
	   {0,0,0,0,0,4,0,5,0,4,1,0,0,4,0,0,0,5,0,4,1,0,0,4,0,0,0,0,5,0,4},
	   {0,0,0,0,0,0,1,0,5,0,4,0,0,2,4,2,0,0,0,4,1,0,1,1,0,0,0,5,0,0,4},
	   {0,0,0,0,0,0,0,1,0,5,0,0,0,2,4,2,0,0,0,0,0,0,1,0,0,5,0,0,0,0,4},
	   {0,0,0,0,0,0,0,0,1,0,5,0,0,2,4,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,4},
	   {0,0,0,0,0,0,0,0,0,1,1,1,3,2,4,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,0}}
      
     
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
  createObjectAligned(16*23,16*12,0,0,b,16)
  objectText("./levels/medium8.lua")

  -- Init checkpoints
  createObjectAligned(16*16,16*12,0,0,a,16)
  local t1 = {
  "Side by side!",
  "Côte à côte!" }
  objectText(t1[getLanguageID()+1])
end
