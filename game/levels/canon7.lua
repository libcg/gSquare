function getInfo()
  -- Title
  local title = {
  "Day 27.\n\nHey, don't you like cannons ?",
  "Jour 27.\n\nN'aimez-vous pas les canons ?" }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-repetition.mp3")
  -- Timer
  varTimeElapsed(120)
  -- Player 
  varPlayerX(16*16)
  varPlayerY(16*1)
  -- Gravity
  varGravityDir(2)
end


function setLevel()
  -- Temporary level matrix
  local lvl_w, lvl_h = 19, 14
  local lvl =
    {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
	   {1,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0},
	   {1,0,1,1,1,1,1,0,0,1,1,1,3,3,1,0,0,0,2},
	   {1,0,0,0,0,0,0,0,0,1,4,1,3,3,0,0,0,0,2},
	   {1,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,2},
	   {1,0,2,2,2,2,2,2,0,2,4,0,0,2,2,2,2,0,2},
	   {1,0,2,0,0,0,0,2,a,2,2,0,0,2,0,0,0,0,2},
	   {1,1,0,0,4,0,0,2,0,0,2,0,0,2,0,0,0,0,4},
	   {2,0,0,0,4,0,0,3,0,0,0,0,0,2,a,0,0,0,4},
	   {2,0,0,0,4,0,0,3,0,0,0,0,0,2,0,0,0,0,4},
	   {1,0,0,0,2,0,0,0,1,1,1,1,1,1,0,0,0,0,4},
	   {1,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,4,0},
	   {0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0}}
      
     
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
  createObjectAligned(16*2,16*12,0,0,b,16)
  objectText("./levels/canon8.lua")
  
  -- Init checkpoints
  createObjectAligned(16*16,16*1,0,0,9,16)
  local t1 = {
  "Why so much hatefulness ? I'm a gentle square, you know.",
  "Pourquoi tant de haine ? Je suis un gentil carré, vous savez." }
  objectText(t1[getLanguageID()+1])
  
  -- Init canons
  createObjectAligned(16*1,16*0,0,0,g,16)
	createObjectAligned(16*6,16*0,0,0,g,16)
	createObjectAligned(16*5,16*2,0,0,e,16)
	createObjectAligned(16*3,16*3,0,0,g,16)
	createObjectAligned(16*6,16*3,0,0,g,16)
	createObjectAligned(16*9,16*4,0,0,h,16)
	createObjectAligned(16*11,16*4,0,0,g,16)
	createObjectAligned(16*12,16*3,0,0,e,16)
	createObjectAligned(16*13,16*3,0,0,e,16)
	createObjectAligned(16*15,16*2,0,0,g,16)
	createObjectAligned(16*13,16*7,0,0,f,16)
	createObjectAligned(16*1,16*13,0,0,e,16)
	createObjectAligned(16*3,16*13,0,0,e,16)

end
