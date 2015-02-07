function getInfo()
  -- Title
  local title = {
  "Day 38.",
  "Jour 38." }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-peanuts.mp3")
  -- Timer
  varTimeElapsed(60)
  -- Player 
  varPlayerX(16*1)
  varPlayerY(16*0)
  -- Gravity
  varGravityDir(2)
end


function setLevel()
  -- Temporary level matrix
  local lvl_w, lvl_h = 35, 15
  local lvl =
    {{0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,k,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,1,l,0,0,0,0,0,0,0,s,s,s,0,0,0,o,0,0,0,0,0,0,0},
	   {0,0,0,0,0,e,e,e,e,0,0,0,1,0,0,0,0,0,0,0,5,s,0,p,0,0,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,s,0,0,0,0,0,0,5,0,4,0,0,0,s,0,0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,s,0,0,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,1},
	   {0,0,0,0,0,0,0,0,0,0,0,0,s,0,0,0,0,0,0,0,5,s,0,0,0,0,0,0,0,j,0,0,0,0,1},
	   {0,0,0,0,0,0,0,0,0,0,0,0,s,0,n,0,0,0,0,0,0,s,0,0,0,0,s,0,0,0,0,0,0,0,1},
	   {0,0,0,0,0,0,0,0,0,0,0,0,s,0,0,0,0,0,0,0,0,s,0,0,0,0,0,0,4,0,0,0,0,0,1},
	   {0,0,0,0,0,0,0,0,0,0,0,0,s,0,0,0,0,0,0,0,0,s,0,0,0,0,0,0,0,4,0,0,0,0,1},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,s,0,0,0,0,0,0,0,s,0,0,0,0,0,0,0,0,4,0,0,0,1},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,s,0,0,0,0,0,0,s,0,0,0,0,0,0,0,0,0,4,0,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,s,0,k,0,0,j,s,0,0,0,0,0,0,0,0,0,0,4,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,s,s,s,s,s,0,0,0,0,0,0,0,0,0,0,0,0,4,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4}}
      
     
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
  createObjectAligned(16*33,16*10,0,0,b,16)
  objectText("./levels/hard2.lua")
  
  -- Init gravity points
	createObjectAligned(16*1,16*0,0,0,k,16)

  -- Init canons
	createObjectAligned(16*38,16*8,0,0,g,16)
	createObjectAligned(16*40,16*11,0,0,g,16)
	createObjectAligned(16*38,16*17,0,0,g,16)
	createObjectAligned(16*39,16*17,0,0,g,16)
			   
end
