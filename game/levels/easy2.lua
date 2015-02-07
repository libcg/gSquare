function getInfo()
  -- Title
  local title = {
  "Day 2.\n\nRelax, this is easy",
  "Jour 2.\n\nDétendez-vous, c'est facile" }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-bummer.mp3")
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
    {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
     {1,9,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,4,0,0,0,0,0,0,0,5,1},
     {1,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,5,1,5,1},
     {1,0,0,0,0,0,0,5,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
     {1,0,0,0,0,0,5,1,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
     {1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,4,0,0,0,0,0,0,0,0,0,1,1,1,0,1},
     {1,0,0,0,0,1,1,1,4,4,1,4,1,1,1,4,1,1,1,4,1,1,4,4,1,1,0,0,0,1},
     {1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,1,0,a,0,0,1},
     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,1,0,1,1,1,1},
     {0,0,4,4,0,0,4,4,0,0,1,1,1,1,0,0,5,5,0,0,0,0,0,0,4,0,0,0,0,4},
     {0,1,0,0,2,2,0,0,2,2,2,0,0,5,0,0,5,5,0,0,0,0,0,0,4,0,0,0,0,4},
     {0,5,0,0,5,5,0,0,5,0,0,0,0,5,0,0,5,5,0,0,0,1,4,4,4,0,0,0,0,1},
     {0,5,0,0,5,5,0,0,0,0,0,0,0,5,0,0,5,5,0,0,0,1,0,0,4,0,0,0,0,1},
     {0,0,5,5,0,0,5,5,0,0,0,0,0,5,0,0,5,5,0,0,1,1,0,5,5,5,0,0,0,1},
     {0,0,0,0,0,0,4,1,1,0,0,0,0,5,0,0,5,5,0,0,5,0,0,0,0,0,0,0,1,1},
     {0,0,0,5,5,5,5,0,1,0,0,0,0,0,5,5,0,0,5,5,0,0,0,0,4,0,0,0,0,4},
     {1,1,1,4,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4}}
     
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
  createObjectAligned(16*7,16*15,0,0,b,16)
  objectText("./levels/easy3.lua")
  
  -- Init checkpoints
  createObjectAligned(16*21,16*14,0,0,7,16)
  local t1 = {
  "Funny ! I see a new kind of block away... it looks like ice...",
  "Tiens ! Je vois un nouveau type de bloc là-bas... comme de la glace..." }
  objectText(t1[getLanguageID()+1])
end
