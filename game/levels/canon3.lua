function getInfo()
  -- Title
  local title = {
  "Day 22.\n\nTake a breathe",
  "Jour 22.\n\nRespirez un coup" }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-hotelmusic.mp3")
  -- Timer
  varTimeElapsed(60)
  -- Player 
  varPlayerX(16*14)
  varPlayerY(16*5)
  -- Gravity
  varGravityDir(2)
end


function setLevel()
  -- Temporary level matrix
  local lvl_w, lvl_h = 30, 17
  local lvl =
      {{0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0},
       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
       {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
       {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
       {0,0,0,0,0,0,0,0,0,0,0,0,0,1,5,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
       {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
       {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,c,0,1},
       {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1},
       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
       {0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0}}

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
  createObjectAligned(16*28,16*12,0,0,b,16)
  objectText("./levels/canon4.lua")
  
  -- Init checkpoints
  createObjectAligned(16*14,16*5,0,0,9,16)
  local t1 = {
  "And I thought I saw the worst...",
  "Et dire que je pensais avoir vu le pire..." }
  objectText(t1[getLanguageID()+1])
    
  -- Init 4 directions canon
	createObjectAligned(16*7,16*3,0,0,e,16)
	createObjectAligned(16*7,16*3,0,0,f,16)
	createObjectAligned(16*7,16*3,0,0,g,16)
	createObjectAligned(16*7,16*3,0,0,h,16)
	
	createObjectAligned(16*9,16*11,0,0,e,16)
	createObjectAligned(16*9,16*11,0,0,f,16)
	createObjectAligned(16*9,16*11,0,0,g,16)
	createObjectAligned(16*9,16*11,0,0,h,16)
		
	createObjectAligned(16*23,16*13,0,0,e,16)
	createObjectAligned(16*23,16*13,0,0,f,16)
	createObjectAligned(16*23,16*13,0,0,g,16)
	createObjectAligned(16*23,16*13,0,0,h,16)
		
	createObjectAligned(16*19,16*4,0,0,e,16)
	createObjectAligned(16*19,16*4,0,0,f,16)
	createObjectAligned(16*19,16*4,0,0,g,16)
	createObjectAligned(16*19,16*4,0,0,h,16)
				
	createObjectAligned(16*25,16*9,0,0,e,16)
	createObjectAligned(16*25,16*9,0,0,f,16)
	createObjectAligned(16*25,16*9,0,0,g,16)
	createObjectAligned(16*25,16*9,0,0,h,16)

  -- Init lasers
	createObjectAligned(16*15,16*7,0,0,o,16)
  
end
