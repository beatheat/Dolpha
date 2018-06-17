

dofile('bullets.lua')

-- ShootBulletAcc(x,y,speed,dir,acc,acc_dir,tag,frame)
-- ShootBullet(x,y,speed,dir,tag,frame)
-- ShootCircle(x,y,speed,startdir,num,tags,frame)
-- ManipulateBullet(x,y,speed,dir,tag,frame)



for i=0,1000,1 do 
    SetBulletColor(blue)
    ShootBullet(width/2,height-30,4,i*7,1,i)
    ShootBullet(width/2,height-30,4,i*7+90,1,i)
    ShootBullet(width/2,height-30,4,i*7+180,1,i)
    ShootBullet(width/2,height-30,4,i*7+270,1,i)
    SetBulletColor(red)
    ShootBullet(width/2,height-30,4,-i*7,1,i)
    ShootBullet(width/2,height-30,4,-i*7+90,1,i)
    ShootBullet(width/2,height-30,4,-i*7+180,1,i)
    ShootBullet(width/2,height-30,4,-i*7+270,1,i)
end

SetBulletColor(green)
ShootCircle(width/2,height/2,6,0,15,{0},180)

-- ManipulateBullet(same,same,same,270,1,180)

Write('tutorial')

