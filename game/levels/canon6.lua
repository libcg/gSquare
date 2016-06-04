function getInfo()
  -- Title
  local title = {
  "Day 25.",
  "Jour 25." }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-itscomplicated.mp3")
  -- Player 
  varPlayerX(16*3)
  varPlayerY(16*4)
  -- Gravity
  varGravityDir(2)
end


function setLevel()
  -- Temporary level matrix
  local lvl_w, lvl_h = 34, 12
  local lvl =
    {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,4,0,4,4,0,4,4,0,4,0,0},
	   {0,0,0,0,0,0,4,4,4,4,4,4,4,1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,1,1,1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {4,1,0,9,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {4,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {1,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,1,1},
	   {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1},
	   {0,1,1,0,0,c,0,0,4,0,0,0,c,0,0,0,0,0,c,0,0,4,0,0,0,c,0,0,0,0,0,0,1,1},
	   {0,1,0,0,0,0,0,0,4,0,0,0,0,0,0,4,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}
      
     
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
  createObjectAligned(16*2,16*9,0,0,b,16)
  objectText("./levels/rose3.lua")

  -- Init checkpoints
  createObjectAligned(16*18,16*5,0,0,9,16)
  local t1 = {
  "No way I'll do this more than three times...",
  "Pas possible de le faire plus de trois fois..." }
  objectText(t1[getLanguageID()+1])
  
  -- Init canons
	createObjectAligned(16*0,16*6,0,0,f,16)
	createObjectAligned(16*21,16*7,0,0,e,16)
	createObjectAligned(16*23,16*7,0,0,e,16)
	createObjectAligned(16*25,16*7,0,0,e,16)
	createObjectAligned(16*26,16*7,0,0,e,16)
	createObjectAligned(16*28,16*7,0,0,e,16)
	createObjectAligned(16*29,16*7,0,0,e,16)
	createObjectAligned(16*31,16*7,0,0,e,16)

  -- Init lasers
  createObjectAligned(16*0,16*5,0,0,q,16)
  
end
