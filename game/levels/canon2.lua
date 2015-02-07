function getInfo()
  -- Title
  local title = {
  "Day 21.",
  "Jour 21." }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-repetition.mp3")
  -- Timer
  varTimeElapsed(120)
  -- Player 
  varPlayerX(16*2)
  varPlayerY(16*2)
  -- Gravity
  varGravityDir(2)
end


function setLevel()
  -- Temporary level matrix
  local lvl_w, lvl_h = 31, 9
  local lvl =
    {{0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,4,1,1,1,3,3,4},
	   {0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
	   {0,1,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
	   {0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,4},
	   {4,0,0,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,4,1,1,1,1,1,1,4,0,0,4},
	   {4,0,0,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,0,0,0,0,2,2,2,2,2,2,0,0,4},
	   {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
	   {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
	   {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4}}
      
     
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
  createObjectAligned(16*2,16*4,0,0,b,16)
  objectText("./levels/canon3.lua")

  -- Init canons
  createObjectAligned(16*26,16*1,0,0,7,16)
	createObjectAligned(16*6,16*4,0,0,e,16)
	createObjectAligned(16*7,16*0,0,0,g,16)
	createObjectAligned(16*8,16*4,0,0,e,16)
	createObjectAligned(16*12,16*0,0,0,g,16)
	createObjectAligned(16*13,16*4,0,0,e,16)
	createObjectAligned(16*14,16*0,0,0,g,16)
	createObjectAligned(16*15,16*4,0,0,e,16)
	createObjectAligned(16*20,16*0,0,0,g,16)
	createObjectAligned(16*24,16*4,0,0,e,16)
	createObjectAligned(16*30,16*6,0,0,h,16)
	createObjectAligned(16*30,16*7,0,0,h,16)
	createObjectAligned(16*30,16*8,0,0,h,16)	   
end
