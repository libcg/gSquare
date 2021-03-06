function getInfo()
  -- Title
  local title = {
  "Day 1.\n\nTutorial",
  "Jour 1.\n\nTutoriel" }
  levelText(title[getLanguageID()+1])
end


function setGame()
  -- Music
  setMusic("./audio/c418-familiarfaces.mp3")
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
    {{1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
     {1,0,0,0,0,0,0,0,0,0,0,0,1,0,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
     {1,1,1,1,1,1,1,1,1,1,1,0,1,5,5,5,0,0,0,0,0,0,5,1,1,1,1,1,1,1},
     {1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,5,5,1,0,0,0,0,1,1},
     {1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,5,5,0,1,0,1,1,0,1,1},
     {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,0,0,1,1},
     {1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1},
     {1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1},
     {1,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1},
     {1,0,0,0,0,1,0,0,1,0,0,1,0,0,1,1,1,0,0,1,1,1,0,0,1,1,0,0,1,1},
     {1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1},
     {1,0,5,5,5,5,5,5,5,5,5,5,5,0,1,4,4,4,4,4,4,4,4,4,4,1,0,0,5,3},
     {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,1},
     {1,0,1,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,5,1},
     {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,1,0,0,5,1},
     {1,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,4,0,0,0,0,5,5,5,0,0,0,5,1},
     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1}}
     
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
  createObjectAligned(16*28,16*1,0,0,b,16)
  objectText("./levels/easy2.lua")
  
  -- Checkpoints
  createObjectAligned(16*1,16*1,0,0,9,16)
  local t1 = {
  "Hello! I can move using the directional arrows.",
  "Bonjour! Je peux bouger en utilisant les flèches directionnelles." }
  objectText(t1[getLanguageID()+1])
  createObjectAligned(16*2,16*9,0,0,9,16)
  local t2 = {
  "I can also jump by pressing the S key.",
  "Je peux aussi sauter en appuyant sur la touche S." }
  objectText(t2[getLanguageID()+1])
  createObjectAligned(16*10,16*9,0,0,9,16)
  local t3 = {
  "I can jump higher by holding the S key.",
  "Je peux sauter plus haut en maintenant la touche S appuyée." }
  objectText(t3[getLanguageID()+1])
  createObjectAligned(16*13,16*11,0,0,9,16)
  local t4 = {
  "Coins give me more time to finish the level.",
  "Les pièces me donnent plus de temps pour finir le niveau." }
  objectText(t4[getLanguageID()+1])
  createObjectAligned(16*2,16*15,0,0,9,16)
  local t5 = {
  "Dark squares are dangerous! I have to avoid them.",
  "Les carrés sombres sont dangereux! Je dois les éviter." }
  objectText(t5[getLanguageID()+1])
  createObjectAligned(16*25,16*15,0,0,9,16)
  local t6 = {
  "Purple squares can help me jump much higher!",
  "Les carrés violets me font sauter beaucoup plus haut!" }
  objectText(t6[getLanguageID()+1])
  createObjectAligned(16*25,16*3,0,0,9,16)
  local t7 = {
  "If you are stuck, take a break by pressing the Esc key.",
  "En cas de problème, faites une pause en appuyant sur la touche Échap." }
  objectText(t7[getLanguageID()+1])
  createObjectAligned(16*15,16*8,0,0,9,16)
  local t8 = {
  "I have the ability to control the gravity! Press A or D keys to try.",
  "Je peux contrôler la gravité! Appuyez sur les touches Q ou D pour essayer." }
  objectText(t8[getLanguageID()+1])
  createObjectAligned(16*22,16*4,0,0,9,16)
  local t9 = {
  "This bigger coin there makes me go to the next level.",
  "La plus grosse pièce me permet d'aller au niveau suivant." }
  objectText(t9[getLanguageID()+1])
  createObjectAligned(16*13,16*1,0,0,9,16)
  local t10 = {
  "Pressing A and D at the same time is useful to invert the gravity!",
  "Appuyer simultanément sur Q et D me permet d'inverser la gravité!" }
  objectText(t10[getLanguageID()+1])
end


