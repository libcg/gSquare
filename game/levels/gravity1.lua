function getInfo()
  -- Title
  local title = {
  "Day 32.\n\nWhere your power disappears",
  "Jour 32.\n\nOù votre pouvoir disparaît" }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-peanuts.mp3")
  -- Timer
  varTimeElapsed(60)
  -- Player 
  varPlayerX(16*2)
  varPlayerY(16*6)
  -- Gravity
  varGravityDir(2)
end


function setLevel()
  -- Temporary level matrix
  local lvl_w, lvl_h = 32, 8
  local lvl =
    {{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	   {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,n},
	   {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	   {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	   {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,4,0,0,0,0,0,0,m,1},
	   {0,1,1,2,2,2,0,0,s,0,0,0,s,0,0,0,s,0,0,0,2,2,2,2,2,2,2,2,2,2,2,1}}
      
     
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
  createObjectAligned(16*0,16*3,0,0,b,16)
  objectText("./levels/gravity2.lua")
  
  -- Init gravity points
	createObjectAligned(16*2,16*6,0,0,k,16)

  -- Init checkpoints
	createObjectAligned(16*2,16*6,0,0,9,16)
  local t1 = {
  "It seems that I've lost my power because of this block.",
  "J'ai apparemment perdu mon pouvoir à cause de ce bloc." }
  objectText(t1[getLanguageID()+1])
	createObjectAligned(16*5,16*6,0,0,9,16)
  local t2 = {
  "What's this kind of block ?",
  "Quel est ce type de bloc ?" }
  objectText(t2[getLanguageID()+1])
	createObjectAligned(16*30,16*6,0,0,9,16)
  local t3 = {
  "My power is back !",
  "Mon pouvoir est de retour !" }
  objectText(t3[getLanguageID()+1])
end
