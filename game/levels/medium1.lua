function getInfo()
  -- Title
  local title = {
  "Day 11.\n\nWhere difficulty increases (a little)",
  "Jour 11.\n\nOù la difficulté augmente (un peu)" }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-bummer.mp3")
  -- Player 
  varPlayerX(16*14)
  varPlayerY(16*6)
  -- Gravity
  varGravityDir(1)
end


function setLevel()
  -- Temporary level matrix
  local lvl_w, lvl_h = 30, 17
  local lvl =
    {{1,1,1,1,4,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
     {0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,1,3,5,5,5,5,5,5,5,0,0,0,0,0,2},
     {0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,1,1,2,2,4,4,0,0,0,0,4,5,2,0,2},
     {0,1,1,1,1,1,1,4,1,1,1,1,1,1,0,1,3,0,0,0,0,0,0,0,0,4,2,0,0,2},
     {0,0,0,4,0,0,0,0,0,5,0,5,0,1,0,1,0,0,0,0,0,0,0,0,0,2,0,0,2,5},
     {0,9,0,0,0,0,0,0,5,0,5,0,0,1,0,1,0,0,0,4,4,4,4,0,2,0,0,2,5,5},
     {2,2,2,2,2,2,4,2,2,2,2,2,0,1,0,1,a,0,0,0,0,0,0,2,0,0,2,5,5,5},
     {0,0,0,0,2,3,3,c,c,c,0,1,0,1,1,1,2,2,0,0,0,0,2,0,0,2,5,5,5,5},
     {0,0,0,2,0,c,c,c,c,c,0,3,0,0,0,0,0,0,0,0,0,2,0,0,0,2,5,5,5,5},
     {0,0,2,0,9,c,c,c,c,c,0,3,0,0,0,0,0,0,0,0,2,5,5,9,0,0,2,2,5,5},
     {0,2,0,0,2,c,2,2,2,2,0,0,2,4,4,4,4,2,2,2,0,5,5,1,2,5,5,5,2,2},
     {2,0,0,0,2,c,2,0,0,2,0,0,2,0,0,0,0,0,0,2,0,5,5,2,3,5,5,5,5,3},
     {2,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,1,0,0,2,0,5,5,1,3,5,5,5,5,3},
     {2,0,2,4,4,c,4,0,0,0,2,0,1,1,3,0,1,4,0,1,0,0,0,2,3,5,5,5,5,3},
     {2,0,0,0,0,c,0,0,0,2,0,0,0,0,0,0,1,0,0,1,1,0,0,1,3,5,5,5,5,3},
     {0,2,2,4,4,3,4,0,0,1,0,0,1,1,0,0,1,0,0,c,c,0,0,3,3,0,0,0,0,3},
     {0,0,0,0,0,0,0,2,2,1,1,1,5,5,1,1,1,1,1,1,1,3,3,1,0,3,3,3,3,2}}
     
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
  createObjectAligned(16*8,16*11,0,0,b,16)
  objectText("./levels/medium2.lua")
  
  -- Init checkpoints
  createObjectAligned(16*14,16*6,0,0,8,16)
  local t1 = {
  "Let's go! I've got to save Rose!",
  "C'est parti! Je dois sauver Rose!" }
  objectText(t1[getLanguageID()+1])
  createObjectAligned(16*15,16*15,0,0,a,16)
  local t1 = {
  "So many blocks to break, so little time.",
  "Tellement de blocs à casser, si peu de temps." }
  objectText(t1[getLanguageID()+1])
end


