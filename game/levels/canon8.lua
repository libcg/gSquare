function getInfo()
  -- Title
  local title = {
  "Day 28.",
  "Jour 28." }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-bummer.mp3")
  -- Timer
  varTimeElapsed(60)
  -- Player 
  varPlayerX(16*26)
  varPlayerY(16*0)
  -- Gravity
  varGravityDir(2)
end


function setLevel()
  -- Temporary level matrix
  local lvl_w, lvl_h = 29, 7
  local lvl =
    {{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,4},
	   {0,0,0,0,0,0,c,0,0,0,0,0,c,0,0,0,0,0,c,0,0,0,c,0,0,0,1,0,4},
	   {0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
	   {0,0,0,1,1,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}
      
     
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
  createObjectAligned(16*3,16*4,0,0,b,16)
  objectText("./levels/canon9.lua")
  
  -- Init canons
	createObjectAligned(16*0,16*0,0,0,f,16)

  -- Init lasers
	createObjectAligned(16*28,16*1,0,0,o,16)
		   
end
