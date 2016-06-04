function getInfo()
  -- Title
  local title = {
  "Day 20.\n\nSome cannons to bring some fun!",
  "Jour 20.\n\nQuelques canons pour s'amuser un peu!" }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-bummer.mp3")
  -- Player 
  varPlayerX(16*3)
  varPlayerY(16*15)
  -- Gravity
  varGravityDir(2)
end


function setLevel()
  -- Temporary level matrix
  local lvl_w, lvl_h = 36, 20
  local lvl =
    {{0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0},
     {0,0,0,0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,0,0},
     {0,0,0,0,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0},
     {0,0,0,0,1,0,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,0,0},
     {0,5,0,5,1,0,1,5,0,1,1,1,0,0,0,0,1,5,0,5,0,5,0,5,0,5,0,5,1,0,1,5,0,5,0,5},
     {0,0,0,0,1,0,1,0,0,0,0,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0},
     {0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0},
     {0,5,0,5,1,0,1,5,0,5,0,5,0,5,1,0,1,5,0,5,0,5,0,5,0,5,0,5,1,0,1,5,0,5,0,5},
     {0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0},
     {0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0},
     {0,5,1,1,1,0,1,5,0,5,0,5,0,5,1,0,1,5,0,5,0,5,0,5,0,5,1,1,1,0,1,5,0,5,0,5},
     {0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0},
     {1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0},
     {1,0,0,0,0,0,1,5,0,5,0,5,1,1,1,0,1,5,0,5,0,5,0,5,1,0,0,0,0,0,1,5,0,5,0,5},
     {1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0},
     {0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0},
     {0,5,1,1,1,5,0,0,0,0,1,0,0,0,0,0,1,5,0,5,0,5,0,5,0,5,1,1,1,5,0,5,0,5,0,5},
     {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
     {0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}
     
      
     
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
  createObjectAligned(16*27,16*11,0,0,b,16)
  objectText("./levels/canon2.lua")
  
  -- Init checkpoints
  createObjectAligned(16*3,16*15,0,0,9,16)
  local t1 = {
  "It looks dangerous...",
  "Ça a l'air dangereux..." }
  objectText(t1[getLanguageID()+1])
  createObjectAligned(16*14,16*18,0,0,9,16)
  local t2 = {
  "Yeah! I love music!",
  "Yeah! J'adore la musique!" }
  objectText(t2[getLanguageID()+1])
  createObjectAligned(16*32,16*0,0,0,9,16)
  local t3 = {
  "Mi Mi Fa Sol, Sol Fa Mi Re, Do Do Re Mi, Mi Re... ",
  "Mi Mi Fa Sol, Sol Fa Mi Ré, Do Do Ré Mi, Mi Ré... " }
  objectText(t3[getLanguageID()+1])

  
  -- Init canons
  createObjectAligned(16*5,16*15,0,0,e,16)
	createObjectAligned(16*8,16*3,0,0,f,16)
  createObjectAligned(16*15,16*3,0,0,g,16)
  createObjectAligned(16*11,16*14,0,0,g,16)
  createObjectAligned(16*12,16*19,0,0,e,16)
  createObjectAligned(16*28,16*2,0,0,f,16)
	createObjectAligned(16*29,16*0,0,0,g,16)
  createObjectAligned(16*24,16*13,0,0,f,16)
  createObjectAligned(16*28,16*16,0,0,e,16)
end
