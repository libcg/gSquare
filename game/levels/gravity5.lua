function getInfo()
  -- Title
  local title = {
  "Day 36.\n\nThink twice before you jump",
  "Jour 36.\n\nRéfléchissez deux fois avant de sauter" }
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
  local lvl_w, lvl_h = 20, 17
  local lvl =
    {{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {2,0,5,0,5,0,0,5,0,0,5,0,0,5,0,0,0,0,0,0},
	   {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0},
	   {2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0},
	   {0,0,0,0,0,0,0,q,0,9,0,0,0,0,0,0,0,4,0,5},
	   {0,0,0,0,0,0,0,3,1,1,1,0,0,0,0,0,0,2,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,i,0,0,0,2,0,5,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0},
	   {0,0,0,1,0,0,0,5,0,0,0,0,0,0,0,4,0,5,0,0},
	   {0,0,0,1,0,0,0,5,0,0,0,0,0,0,0,2,0,0,0,0},
	   {0,0,0,1,0,0,0,5,0,0,0,0,0,0,2,0,5,0,0,0},
	   {0,0,0,1,0,0,0,5,0,0,0,0,0,0,2,0,0,0,0,0},
	   {0,0,0,1,0,0,0,5,0,0,0,0,0,4,0,5,0,0,0,0},
	   {0,0,0,1,0,0,0,0,5,0,1,1,2,2,0,0,0,0,0,0},
	   {0,0,0,1,0,5,5,5,0,5,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,l,0}}
      
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
  createObjectAligned(16*1,16*1,0,0,b,16)
  objectText("./levels/hard1.lua")
  
  -- Init gravity points
	createObjectAligned(16*9,16*5,0,0,k,16)

		   
end
