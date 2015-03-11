function getInfo()
  -- Title
  local title = {
  "Day 39.\n\nWhere you learn to fly",
  "Jour 39.\n\nOù vous apprenez à voler" }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-itscomplicated.mp3")
  -- Timer
  varTimeElapsed(120)
  -- Player 
  varPlayerX(16*1)
  varPlayerY(16*1)
  -- Gravity
  varGravityDir(3)
end


function setLevel()
  -- Temporary level matrix
  local lvl_w, lvl_h = 26, 21
  local lvl =
     {{1,1,1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1,1,1,0,0,0,0},
      {1,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
      {1,1,1,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
      {0,0,4,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0},
      {0,0,4,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,4,0,0,0,0},
      {0,0,4,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,4,0,0,0,0},
      {0,0,4,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,4,0,0,0,0},
      {0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,0,4,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,0,0,0,4,4,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,4,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,4,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,4,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,4,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,4,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,4,4,4,0,0,0,0,4,0,0},
      {0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,4,1,1,1,4,0,0,0,0,4,0},
      {0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,4,0,0,0,4,0,0,0,0,0,4},
      {0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
      {0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
      {0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
      {0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0}}
      
     
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
  createObjectAligned(16*17,16*16,0,0,b,16)
  objectText("./levels/gravity7.lua")
  
  -- Init checkpoints
  createObjectAligned(16*1,16*1,0,0,9,16)
  local t1 = {
  "OK. Looks great but can't I just go back home? Pleeeeeease!",
  "OK. Cela semble génial mais je pourrais rentrer chez moi?.." }
  objectText(t1[getLanguageID()+1])
  createObjectAligned(16*20,16*1,0,0,7,16)
  local t2 = {
  "And this was the easy part ...",
  "Et c'était la partie facile ..." }
  objectText(t2[getLanguageID()+1])
end
