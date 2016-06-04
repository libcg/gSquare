function getInfo()
  -- Title
  local title = {
  "Day 9.\n\nThis creeper doesn't explode (yet)",
  "Jour 9.\n\nCe creeper n'explose pas (pour l'instant)" }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-hotelmusic.mp3")
  -- Player 
  varPlayerX(16*4)
  varPlayerY(16*0)
  -- Gravity
  varGravityDir(2)
end


function setLevel()
  -- Temporary level matrix
  local lvl_w, lvl_h = 10, 25
  local lvl =
    {{0,0,0,0,0,0,0,0,0,0},
     {0,2,2,2,2,2,2,2,2,0},
	   {0,2,2,2,2,2,2,2,2,0},
	   {0,2,4,4,2,2,4,4,2,0},
	   {0,2,4,4,2,2,4,4,2,0},
	   {0,2,2,2,4,4,2,2,2,0},
	   {0,2,2,4,4,4,4,2,2,0},
	   {0,2,2,4,4,4,4,2,2,0},
	   {0,2,2,4,2,2,4,2,2,0},
	   {0,0,2,2,2,2,2,2,0,0},
	   {0,0,2,2,2,2,2,2,0,0},
	   {0,0,2,2,2,2,2,2,0,0},
	   {0,0,2,2,2,2,2,2,0,0},
	   {0,0,2,2,2,2,2,2,0,0},
	   {0,0,2,2,2,2,2,2,0,0},
	   {0,0,2,2,2,2,2,2,0,0},
	   {0,0,2,2,2,2,2,2,0,0},
	   {0,0,2,2,2,2,2,2,0,0},
	   {0,0,2,2,2,2,2,2,0,0},
	   {0,0,2,2,2,2,2,2,0,0},
	   {0,2,2,2,2,2,2,2,2,0},
	   {0,2,2,2,2,2,2,2,2,0},
	   {0,2,4,2,4,2,4,2,4,0},
	   {0,4,2,4,2,4,2,4,2,0},
     {0,0,0,0,0,0,0,0,0,0}}
      
     
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
  createObjectAligned(16*4,16*24,0,0,b,16)
  objectText("./levels/rose1.lua")

  -- Init checkpoints
  createObjectAligned(16*4,16*0,0,0,9,16)
  local t1 = {
  "SsssssssShsSHhhhhhh",
  "SsssssssShsSHhhhhhh" }
  objectText(t1[getLanguageID()+1])
end
