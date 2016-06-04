function getInfo()
  -- Title
  local title = {
  "Day 24.",
  "Jour 24." }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-peanuts.mp3")
  -- Player 
  varPlayerX(16*11)
  varPlayerY(16*5)
  -- Gravity
  varGravityDir(4)
end


function setLevel()
  -- Temporary level matrix
  local lvl_w, lvl_h = 25, 16
  local lvl =
    {{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	   {1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1},
	   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	   {1,0,4,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1},
	   {1,0,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1},
	   {1,0,0,0,0,0,0,0,0,0,0,7,1,1,1,0,0,0,0,0,0,0,0,1,4},
	   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,4},
	   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1},
	   {1,0,0,0,0,0,0,4,0,0,0,0,0,1,1,1,0,0,1,1,0,0,1,1,1},
	   {1,0,0,2,2,0,0,4,0,0,4,0,0,1,1,0,0,0,0,0,0,0,0,1,4},
	   {1,0,0,2,2,0,0,4,0,0,4,0,0,1,1,0,0,0,0,0,0,0,0,1,4},
	   {1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1},
	   {1,0,0,2,2,0,0,4,0,0,4,0,0,4,4,4,1,1,0,0,1,1,1,1,0},
	   {1,0,0,2,2,0,0,9,0,0,4,0,0,0,0,0,0,0,0,0,9,0,3,1,0},
	   {1,0,0,2,2,2,2,2,2,2,2,1,1,2,2,0,2,0,2,2,2,2,1,1,0},
	   {1,2,2,2,2,2,2,2,2,2,2,4,4,4,4,4,4,4,4,4,4,4,4,4,0}}
      
     
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
  createObjectAligned(16*2,16*14,0,0,b,16)
  objectText("./levels/canon6.lua")
  
  -- Init checkpoints
  createObjectAligned(16*7,16*3,0,0,9,16)
  local t1 = {
  "Marshmallow cannons would be funnier.",
  "Des canons en guimauve seraient plus drôles." }
  objectText(t1[getLanguageID()+1])
    
  -- Init Canons
	createObjectAligned(16*0,16*2,0,0,f,16)
	createObjectAligned(16*0,16*11,0,0,f,16)
	createObjectAligned(16*1,16*7,0,0,g,16)
	createObjectAligned(16*2,16*7,0,0,g,16)
	createObjectAligned(16*4,16*4,0,0,g,16)
	createObjectAligned(16*5,16*6,0,0,e,16)
	createObjectAligned(16*5,16*14,0,0,e,16)
	createObjectAligned(16*6,16*4,0,0,g,16)
	createObjectAligned(16*6,16*7,0,0,g,16)
	createObjectAligned(16*13,16*8,0,0,h,16)
	createObjectAligned(16*14,16*5,0,0,f,16)
	createObjectAligned(16*14,16*10,0,0,f,16)
	createObjectAligned(16*16,16*4,0,0,g,16)
	createObjectAligned(16*16,16*11,0,0,e,16)
	createObjectAligned(16*21,16*4,0,0,g,16)
	createObjectAligned(16*21,16*11,0,0,e,16)
	createObjectAligned(16*23,16*5,0,0,h,16)
	createObjectAligned(16*23,16*10,0,0,h,16) 
end
