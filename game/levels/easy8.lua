function getInfo()
  -- Title
  local title = {
  "Day 8.",
  "Jour 8." }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-sometimesimakevideogamemusic.mp3")
  -- Timer
  varTimeElapsed(120)
  -- Player 
  varPlayerX(16*2)
  varPlayerY(16*3)
  -- Gravity
  varGravityDir(2)
end


function setLevel()
  -- Temporary level matrix
  local lvl_w, lvl_h = 34, 12
  local lvl =
    {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0},
	   {0,0,0,0,0,5,5,0,5,5,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,1,0,9,0,0,4,0,0,0,0,0,0,0,1,0,0,0},
	   {4,1,1,1,1,0,0,1,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,4,4,1,1,1,1,0,0,0},
	   {4,1,1,4,0,0,0,0,0,0,0,4,4,4,4,1,5,5,5,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
	   {4,1,1,1,4,4,4,4,4,4,4,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,5},
	   {4,0,0,0,0,1,0,1,0,0,1,0,0,0,0,1,5,7,5,0,1,1,4,4,1,1,1,1,1,1,4,4,0,5},
	   {4,0,5,0,0,0,0,0,0,0,0,0,2,2,0,0,0,1,0,0,0,1,0,0,1,1,1,1,1,1,1,0,0,5},
	   {4,0,0,5,5,0,5,0,5,5,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,1,1,1,1,1,1,a,0,0},
	   {0,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,5,5,0,0,1,1,1,1,1,0,0,0},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,1,1,1,4,0,0,0}}
      
     
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
  createObjectAligned(16*2,16*7,0,0,b,16)
  objectText("./levels/easy9.lua")

  -- Init checkpoints
  createObjectAligned(16*2,16*3,0,0,9,16)
  local t1 = {
  "Coins, coins, I need more coins !",
  "Des pièces, des pièces, je veux plus de pièces !" }
  objectText(t1[getLanguageID()+1])

  -- Init lasers
  createObjectAligned(16*0,16*5,0,0,q,16)  
end
