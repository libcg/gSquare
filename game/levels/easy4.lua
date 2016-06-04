function getInfo()
  -- Title
  local title = {
  "Day 4.",
  "Jour 4." }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-peanuts.mp3")
  -- Player 
  varPlayerX(32)
  varPlayerY(16)
  -- Gravity
  varGravityDir(2)
end


function setLevel()
  -- Temporary level matrix
  local lvl_w, lvl_h = 30, 18
  local lvl =
    {{1,3,1,3,1,3,1,0,2,2,2,2,0,0,0,0,2,2,2,2,2,2,2,2,4,2,2,2,2,2},
     {1,0,0,0,0,0,1,0,0,0,0,0,2,0,0,0,2,4,0,0,0,0,0,5,5,c,7,0,0,2},
     {1,c,1,c,1,c,1,4,4,4,0,0,2,2,2,0,1,1,0,0,1,4,1,1,1,1,1,1,0,2},
     {1,5,1,5,1,5,1,0,0,0,4,0,2,3,2,0,0,1,2,0,5,5,5,5,5,c,0,1,0,2},
     {1,0,1,0,1,0,1,0,0,0,0,0,2,0,2,3,0,0,2,2,2,2,2,5,2,2,2,2,0,2},
     {1,0,1,0,1,0,1,0,2,0,0,0,2,5,2,2,2,0,2,0,0,0,0,2,3,0,0,c,0,2},
     {1,0,1,0,1,0,1,0,0,2,2,2,5,7,5,0,2,0,2,0,0,0,7,c,0,2,c,2,1,1},
     {1,5,1,5,1,5,1,2,0,0,2,5,5,5,5,5,2,0,2,0,0,4,1,1,0,1,0,0,0,1},
     {1,0,1,0,1,0,1,0,2,0,2,0,0,5,0,0,1,0,1,0,5,5,0,1,0,4,0,0,0,1},
     {1,0,1,0,1,0,1,0,0,0,2,0,0,5,0,0,2,0,2,5,0,5,0,2,0,4,3,3,0,2},
     {1,0,1,0,1,0,1,0,0,0,2,0,0,5,0,0,2,0,2,1,1,5,1,2,0,2,2,0,0,2},
     {1,5,1,5,1,5,1,0,4,4,4,0,2,0,2,2,2,0,2,4,4,5,4,4,0,0,4,0,0,2},
     {1,0,1,0,1,0,1,0,0,0,0,0,2,0,2,5,2,c,2,0,0,0,0,1,0,0,4,0,0,2},
     {1,0,1,0,1,0,1,2,2,2,2,2,2,c,2,5,0,0,0,0,0,5,0,1,0,0,4,0,0,2},
     {2,0,1,0,1,0,0,0,2,0,0,0,2,c,2,5,0,0,0,0,1,0,0,1,0,0,0,0,0,2},
     {2,0,0,0,0,0,0,0,0,0,3,0,0,0,2,5,2,4,1,1,1,c,1,1,0,0,0,0,0,2},
     {2,2,2,2,2,2,2,2,2,2,2,2,2,3,2,2,0,0,0,1,1,0,1,1,1,4,2,2,2,2},
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,1,0,0,0,0,0,0,0}}
    
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
  createObjectAligned(16*26,16*3,0,0,b,16)
  objectText("./levels/easy5.lua")
  
  -- Init random beginnings
  math.randomseed(os.time())
  local rnd = math.random(1,3)
  if (rnd == 1 or rnd == 2) then
    createObjectAligned(16*1,16*13,0,0,4,16)
  end
  if (rnd == 2 or rnd == 3) then
    createObjectAligned(16*3,16*13,0,0,4,16)
  end
  if (rnd == 3 or rnd == 1) then
    createObjectAligned(16*5,16*13,0,0,4,16)
  end
  
  -- Init checkpoints
  createObjectAligned(16*2,16*1,0,0,9,16)
  local t1 = {
  "Oh. It seems breakable. Which way to go?",
  "Oh. Cela a l'air cassable. Quelle voie choisir?" }
  objectText(t1[getLanguageID()+1])
  createObjectAligned(16*14,16*1,0,0,9,16)
  local t2 = {
  "I can't go too far, otherwise I will fall in the void... Scary.",
  "Je ne peux pas aller trop loin, sinon je vais tomber dans le vide..." }
  objectText(t2[getLanguageID()+1])
end



