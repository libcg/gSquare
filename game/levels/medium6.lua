function getInfo()
  -- Title
  local title = {
  "Day 16.",
  "Jour 16." }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-familiarfaces.mp3")
  -- Timer
  varTimeElapsed(60)
  -- Player 
  varPlayerX(16*13)
  varPlayerY(16*1)
  -- Gravity
  varGravityDir(3)
end


function setLevel()
  -- Temporary level matrix
  local lvl_w, lvl_h = 27, 14
  local lvl =
    {{0,0,2,2,4,4,4,4,2,4,4,2,2,2,2,1,1,1,2,2,2,2,2,2,2,2,2},
     {0,2,0,0,0,0,0,0,0,0,0,0,1,a,0,0,0,1,0,0,0,0,0,0,0,0,1},
	   {2,0,0,0,0,0,0,4,4,4,4,2,2,2,2,5,0,1,5,5,5,0,0,2,0,0,1},
	   {2,0,0,0,0,2,2,a,0,0,0,0,0,0,2,0,5,1,a,5,5,0,0,2,4,0,1},
	   {3,0,0,0,4,2,0,0,4,4,4,4,0,0,2,5,0,1,5,5,5,0,0,3,0,0,1},
	   {3,0,0,0,4,2,0,2,0,0,0,0,0,0,2,0,5,1,2,2,4,0,0,2,0,0,1},
	   {2,0,0,2,2,4,0,1,5,5,5,5,0,5,2,5,0,0,0,0,0,0,0,2,0,0,1},
	   {2,0,0,2,0,0,0,2,0,5,1,1,1,1,3,0,0,0,0,0,0,0,0,2,0,0,4},
	   {4,0,0,2,0,0,0,2,5,0,1,c,c,0,3,1,1,4,4,2,2,2,3,0,0,4,4},
	   {4,0,0,2,0,0,4,2,0,0,0,0,2,0,0,0,0,4,0,0,0,0,0,0,0,4,0},
	   {4,0,2,1,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,4,0},
	   {2,0,0,2,4,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,4,0},
	   {2,a,0,0,0,0,0,2,0,0,0,0,4,4,0,0,0,0,0,0,0,4,0,0,0,2,0},
	   {0,2,4,4,4,2,2,0,0,0,0,0,0,4,4,2,2,2,2,2,2,4,4,2,2,2,0}}
      
     
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
  createObjectAligned(16*11,16*1,0,0,b,16)
  objectText("./levels/medium7.lua")
  
  -- Init checkpoints
  createObjectAligned(16*10,16*10,0,0,9,16)
  local t1 = {
  "I think I've got to go to the right. But what does mean right here ?",
  "Je pense que je dois aller à droite. Mais où est la droite ici ?" }
  objectText(t1[getLanguageID()+1])
end
