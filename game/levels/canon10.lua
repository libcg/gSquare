function getInfo()
  -- Title
  local title = {
  "Day 30.",
  "Jour 30." }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-familiarfaces.mp3")
  -- Player 
  varPlayerX(16*1)
  varPlayerY(16*5)
  -- Gravity
  varGravityDir(2)
end


function setLevel()
  -- Temporary level matrix
  local lvl_w, lvl_h = 24, 10
  local lvl =
    {{0,0,4,1,1,4,1,1,1,1,1,4,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,4,0,0,0,0,0,1,0,0,0,4,4,4,1,1,1,4,4,4,4,4,0},
	   {0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
	   {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
	   {1,1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,4},
	   {1,0,0,0,0,1,0,0,4,0,0,1,1,1,1,4,4,4,1,1,1,0,1,0},
	   {1,1,1,1,1,1,4,4,4,4,4,1,0,0,0,0,0,0,0,1,0,0,1,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0}}
      
     
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
  createObjectAligned(16*21,16*8,0,0,b,16)
  objectText("./levels/labyrinth.lua")

  -- Init Checkpoints
  createObjectAligned(16*1,16*5,0,0,9,16)
  local t1 = {
  "I'm Blue Force, let's go!",
  "C'est parti, je suis Force Bleue!" }
  objectText(t1[getLanguageID()+1])
  
  -- Init Canons
	createObjectAligned(16*2,16*3,0,0,f,16)
	createObjectAligned(16*3,16*0,0,0,g,16)
	createObjectAligned(16*4,16*0,0,0,g,16)
	createObjectAligned(16*6,16*0,0,0,g,16)
	createObjectAligned(16*7,16*0,0,0,g,16)
	createObjectAligned(16*9,16*0,0,0,g,16)
	createObjectAligned(16*10,16*0,0,0,g,16)
	createObjectAligned(16*20,16*5,0,0,g,16)
	createObjectAligned(16*22,16*4,0,0,h,16)
  
end
