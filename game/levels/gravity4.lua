function getInfo()
  -- Title
  local title = {
  "Day 35.",
  "Jour 35." }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-hotelmusic.mp3")
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
  local lvl_w, lvl_h = 20, 14
  local lvl =
   {{0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	  {1,1,1,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	  {0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,5,0,k,0,2},
	  {0,0,0,0,0,j,0,0,0,0,0,0,0,5,5,0,0,0,0,5},
	  {0,0,0,0,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,5},
	  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
	  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,q,0,0,5,0},
	  {0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,5,5,0},
	  {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,5,5,0},
	  {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
	  {0,0,0,0,0,0,0,0,0,1,0,5,0,0,0,0,0,0,0,0},
	  {0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,l,0,0},
	  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0}}
      
     
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
  createObjectAligned(16*10,16*9,0,0,b,16)
  objectText("./levels/gravity5.lua")
  
  -- Init gravity points
	createObjectAligned(16*1,16*0,0,0,k,16)

		   
end
