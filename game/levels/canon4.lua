function getInfo()
  -- Title
  local title = {
  "Day 23.",
  "Jour 23." }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-heyhey.mp3")
  -- Timer
  varTimeElapsed(120)
  -- Player 
  varPlayerX(16*1)
  varPlayerY(16*15)
  -- Gravity
  varGravityDir(2)
end


function setLevel()
  -- Temporary level matrix
  local lvl_w, lvl_h = 18, 17
  local lvl =
    {{0,0,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0},
	   {0,4,g,4,g,4,g,4,g,4,g,4,g,4,0,0,0,0},
	   {1,g,0,1,0,g,0,g,0,g,0,1,0,g,1,1,1,1},
	   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
	   {1,0,0,0,0,0,0,0,1,0,0,1,4,4,1,0,0,0},
	   {1,0,0,0,0,1,0,0,0,0,0,g,4,4,1,0,0,0},
	   {1,0,0,1,0,0,0,0,0,0,0,0,g,4,1,0,0,0},
	   {1,0,4,g,0,0,0,0,1,0,0,0,0,g,1,0,0,0},
	   {1,0,4,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
	   {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
	   {1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0},
	   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
	   {1,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0},
	   {1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
	   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
	   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0}}
      
     
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
  createObjectAligned(16*16,16*3,0,0,b,16)
  objectText("./levels/canon5.lua")

  -- Init checkpoints
  createObjectAligned(16*1,16*15,0,0,9,16)
  local t1 = {
  "Am I getting closer or not ? I'm lost again ...",
  "Suis-je en train d'approcher ou non ? Je suis encore perdu ..." }
  objectText(t1[getLanguageID()+1])
end
