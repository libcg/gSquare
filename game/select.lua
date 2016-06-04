function getInfo()
  -- Title
  local title = {
  "Warp Zone",
  "Warp Zone" }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-hotelmusic.mp3")
  -- Player 
  varPlayerX(16)
  varPlayerY(16)
  -- Gravity
  varGravityDir(2)
end


function setLevel()
  -- Temporary level matrix
  local lvl_w, lvl_h = 26, 4
  local lvl =
    {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,s},
     {1,1,1,c,1,c,1,c,1,c,1,c,1,c,1,c,1,c,1,c,1,c,1,c,1,1},
     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}
    
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
  createObjectAligned(16*3,16*3,0,0,b,16)
  objectText("./levels/easy1.lua")
  createObjectAligned(16*5,16*3,0,0,b,16)
  objectText("./levels/rose1.lua")
  createObjectAligned(16*7,16*3,0,0,b,16)
  objectText("./levels/medium1.lua")
  createObjectAligned(16*9,16*3,0,0,b,16)
  objectText("./levels/rose2.lua")
  createObjectAligned(16*11,16*3,0,0,b,16)
  objectText("./levels/canon1.lua")
  createObjectAligned(16*13,16*3,0,0,b,16)
  objectText("./levels/rose3.lua")
  createObjectAligned(16*15,16*3,0,0,b,16)
  objectText("./levels/labyrinth.lua")
  createObjectAligned(16*17,16*3,0,0,b,16)
  objectText("./levels/gravity1.lua")
  createObjectAligned(16*19,16*3,0,0,b,16)
  objectText("./levels/hard1.lua")
  createObjectAligned(16*21,16*3,0,0,b,16)
  objectText("./levels/hard2.lua")
  createObjectAligned(16*23,16*3,0,0,b,16)
  objectText("./levels/hard3.lua")
  
  -- Init checkpoints
  local t
  createObjectAligned(16*1,16*1,0,0,9,16)
  t = {
  "Here I can choose which level to play.",
  "Ici je peux choisir un niveau à jouer." }
  objectText(t[getLanguageID()+1])
  createObjectAligned(16*3,16*1,0,0,9,16)
  t = {
  "\"Easy\"",
  "\"Facile\"" }
  objectText(t[getLanguageID()+1])
  createObjectAligned(16*5,16*1,0,0,9,16)
  t = {
  "\"Rose 1\"",
  "\"Rose 1\"" }
  objectText(t[getLanguageID()+1])
  createObjectAligned(16*7,16*1,0,0,9,16)
  t = {
  "\"Medium\"",
  "\"Moyen\"" }
  objectText(t[getLanguageID()+1])
  createObjectAligned(16*9,16*1,0,0,9,16)
  t = {
  "\"Rose 2\"",
  "\"Rose 2\"" }
  objectText(t[getLanguageID()+1])
  createObjectAligned(16*11,16*1,0,0,9,16)
  t = {
  "\"Cannon\"",
  "\"Canon\"" }
  objectText(t[getLanguageID()+1])
  createObjectAligned(16*13,16*1,0,0,9,16)
  t = {
  "\"Rose 3\"",
  "\"Rose 3\"" }
  objectText(t[getLanguageID()+1])
  createObjectAligned(16*15,16*1,0,0,9,16)
  t = {
  "\"Labyrinth\"",
  "\"Labyrinthe\"" }
  objectText(t[getLanguageID()+1])
  createObjectAligned(16*17,16*1,0,0,9,16)
  t = {
  "\"Gravity\"",
  "\"Gravité\"" }
  objectText(t[getLanguageID()+1])
  createObjectAligned(16*19,16*1,0,0,9,16)
  t = {
  "\"Hard 1\"",
  "\"Difficile 1\"" }
  objectText(t[getLanguageID()+1])
  createObjectAligned(16*21,16*1,0,0,9,16)
  t = {
  "\"Hard 2\"",
  "\"Difficile 2\"" }
  objectText(t[getLanguageID()+1])
  createObjectAligned(16*23,16*1,0,0,9,16)
  t = {
  "\"Hard 3\"",
  "\"Difficile 3\"" }
  objectText(t[getLanguageID()+1])
end



