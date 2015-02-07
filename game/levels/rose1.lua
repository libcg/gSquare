function getInfo()
  setNextLevel("./levels/medium1.lua")
  -- Title
  local title = {
  "Day 10.\n\nHere, only gravity can help you",
  "Jour 10.\n\nIci, seule la gravité peut vous aider" }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-familiarfaces.mp3")
  -- Timer
  varTimeElapsed(120)
  -- Player 
  varPlayerX(16*10)
  varPlayerY(16*5)
  -- Gravity
  varGravityDir(2)
end


function setLevel()
  -- Temporary level matrix
  local lvl_w, lvl_h = 24, 11
  local lvl =
    {{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
	   {0,0,1,0,0,0,0,0,3,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0},
	   {0,0,1,0,0,0,0,0,0,0,0,0,3,0,0,1,0,0,0,1,0,0,0,0},
	   {0,0,1,0,0,1,1,1,0,1,1,1,1,0,0,3,0,0,0,1,0,0,0,0},
	   {1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0},
	   {1,6,0,0,1,0,0,0,3,1,0,1,0,0,1,0,0,0,0,0,0,1,0,0},
	   {1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0},
	   {0,0,1,0,0,1,1,1,0,1,1,1,1,0,0,3,0,0,0,1,0,0,0,0},
	   {0,0,1,0,0,0,0,0,0,0,0,0,3,0,0,1,0,0,0,1,0,0,0,0},
	   {0,0,1,0,0,0,0,0,3,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0},
	   {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0}}
      
     
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
  createObjectAligned(16*20,16*5,0,0,b,16)
  objectText("./levels/medium1.lua")

  -- Init checkpoints
  createObjectAligned(16*10,16*5,0,0,9,16)
  local t1 = {
  "So close, but also so far ...",
  "Si proches, et si lointains ..." }
  objectText(t1[getLanguageID()+1])
end
