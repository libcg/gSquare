function getInfo()
  -- Title
  local title = {
  "Day 37.\n\nWhere difficulty increases at least",
  "Jour 37.\n\nOù la difficulté s'accentue enfin" }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-heyhey.mp3")
  -- Timer
  varTimeElapsed(60)
  -- Player 
  varPlayerX(16)
  varPlayerY(16)
  -- Gravity
  varGravityDir(2)
end


function setLevel()
  -- Temporary level matrix
  local lvl_w, lvl_h = 30, 17
  local lvl =
    {{1,1,1,1,1,1,1,1,1,3,1,1,1,4,4,2,1,1,2,2,4,4,4,2,2,2,1,1,1,1},
     {1,9,0,0,0,0,4,0,5,0,0,7,5,0,0,5,5,5,5,5,0,4,0,0,0,0,5,0,7,1},
     {1,0,0,5,0,0,1,0,0,5,5,0,0,5,5,0,0,4,0,0,0,4,0,0,0,0,5,0,0,1},
     {1,0,0,5,1,0,1,0,0,0,0,0,0,0,0,0,0,4,0,5,5,5,5,5,0,0,4,0,0,1},
     {1,0,0,5,1,0,1,5,4,4,4,4,4,4,4,4,4,4,4,2,2,2,2,2,4,4,2,0,0,1},
     {1,0,0,0,1,0,1,5,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,2,0,0,1},
     {1,3,1,1,1,0,1,5,0,0,0,0,0,0,1,5,5,5,5,0,0,0,0,0,0,0,2,0,4,4},
     {1,0,5,5,5,0,1,0,5,0,0,0,0,0,1,5,5,5,5,0,0,0,0,0,0,0,2,0,0,1},
     {1,0,0,1,1,3,1,0,0,5,5,5,0,0,1,5,5,5,5,0,0,9,0,0,0,0,2,0,0,1},
     {1,0,4,1,1,1,1,2,2,4,2,2,2,2,1,5,5,5,5,0,2,2,2,0,0,0,4,4,0,1},
     {1,0,0,1,0,0,0,0,0,0,0,0,9,0,3,0,0,0,0,0,4,5,5,0,0,0,1,0,0,1},
     {1,0,0,1,0,0,1,2,2,2,2,2,2,0,1,0,0,0,0,0,4,5,5,0,0,0,2,5,0,1},
     {4,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,2,2,2,4,0,5,2,5,0,4},
     {4,4,0,1,0,0,4,5,5,5,5,5,4,0,1,0,0,0,0,0,0,0,0,4,0,5,2,5,0,4},
     {1,0,0,0,0,0,1,5,5,5,5,5,5,0,1,3,3,3,3,3,3,0,0,4,0,5,5,5,0,4},
     {1,0,0,0,0,0,1,5,5,5,5,5,5,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,4},
     {1,4,4,4,1,3,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,1,1,1,4,4,4,4,4,4}}
     
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
  createObjectAligned(16*12,16*8,0,0,b,16)
  objectText("./levels/gravity6.lua")
  
  -- Init checkpoints
  createObjectAligned(16*1,16*9,0,0,a,16)
  local t1 = {
  "I feel so weak...",
  "Je me sens si faible..." }
  objectText(t1[getLanguageID()+1])
end
