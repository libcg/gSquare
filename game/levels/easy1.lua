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
  "Hello ! I can move using the directional arrows.",
  "Bonjour ! Je peux bouger en utilisant les flèches directionnelles." }
  objectText(t1[getLanguageID()+1])
  createObjectAligned(16*2,16*9,0,0,9,16)
  local t2 = {
  "I can also jump by pressing Cross button.",
  "Je peux aussi sauter en appuyant sur Croix." }
  objectText(t2[getLanguageID()+1])
  createObjectAligned(16*10,16*9,0,0,9,16)
  local t3 = {
  "I can jump higher by holding Cross button.",
  "Je peux sauter plus haut en maintenant Croix appuyé." }
  objectText(t3[getLanguageID()+1])
  createObjectAligned(16*13,16*11,0,0,9,16)
  local t4 = {
  "Coins give me more time to finish the level.",
  "Les pièces me donnent plus de temps pour finir le niveau." }
  objectText(t4[getLanguageID()+1])
  createObjectAligned(16*2,16*15,0,0,9,16)
  local t5 = {
  "Black squares are naughty ! They can kill me ! I have to avoid them.",
  "Les carrés noirs sont dangereux ! Je dois les éviter." }
  objectText(t5[getLanguageID()+1])
  createObjectAligned(16*25,16*15,0,0,9,16)
  local t6 = {
  "Purple squares can help me to jump much higher !",
  "Les carrés violets me font sauter beaucoup plus haut !" }
  objectText(t6[getLanguageID()+1])
  createObjectAligned(16*25,16*3,0,0,9,16)
  local t7 = {
  "In case of trouble, simply take a break by pressing Start.",
  "En cas de problème, faites une pause en appuyant sur Start." }
  objectText(t7[getLanguageID()+1])
  createObjectAligned(16*15,16*8,0,0,9,16)
  local t8 = {
  "I have the ability to control the gravity ! Press L or R button to try.",
  "Je peux contrôler la gravité ! Appuyez sur L ou R pour essayer." }
  objectText(t8[getLanguageID()+1])
  createObjectAligned(16*22,16*4,0,0,9,16)
  local t9 = {
  "This bigger coin there makes me go to the next level.",
  "La plus grosse pièce ici me permet d'aller au niveau suivant." }
  objectText(t9[getLanguageID()+1])
  createObjectAligned(16*13,16*1,0,0,9,16)
  local t10 = {
  "Pressing L and R at the same time is useful to invert the gravity !",
  "Appuyer simultanément sur L et R me permet d'inverser la gravité !" }
  objectText(t10[getLanguageID()+1])
end


