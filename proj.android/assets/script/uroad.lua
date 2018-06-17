
dofile('bullets.lua')

-- ShootBulletAcc(x,y,speed,dir,acc,acc_dir,tag,frame)
-- ShootBullet(x,y,speed,dir,tag,frame)
-- ShootCircle(x,y,speed,startdir,num,tags,frame)
-- ManipulateBullet(x,y,speed,dir,tag,frame)
-- ManipulateBulletAcc(x,y,speed,dir,acc,acc_dir,tag,frame)
-- OnBulletCircle(centerX,centerY,speed,dir,tag,startframe,endframe)
-- MoveBulletCircle(speed,dir,tag,frame)

function GetBulletInterval(speed)
    return math.floor(30 / speed)
end


function ShootLineS(spot, speed, num, _frame)
    for i=0,num-1 do
        ShootBullet(spot + i*20,height,speed,270,0,_frame)
    end
end

function ShootLineSR(spot,speed, num, _frame)
    for i=0,num-1 do
        ShootBullet(spot - i*20, height,speed,270,0,_frame)
    end
end



frame = 0


SetBulletColor(black)


for h=1,math.floor(10000/GetBulletInterval(8)) do
    ShootBullet(bullet.width/2 + 20,height,8,DIR_DOWN,0,frame + h*GetBulletInterval(8))
    ShootBullet(width - bullet.width/2 - 20, height, 8 , DIR_DOWN,0,frame + h*GetBulletInterval(8))
end

frame = 150



for h=1,17 do
    x = math.random(-150,width+150);
    y = height
    ShootBulletLife(x,y,10,to_player,2,0, frame + h*40)
end

frame = 1000

ShootLineS(bullet.width/2+40,8,20,frame)

frame = 1150

ShootLineS(bullet.width/2+40,8,20,frame)

frame = 1300

ShootLineS(bullet.width/2+40,8,20,frame)

frame = 1450

ShootLineS(bullet.width/2+40,13,20,frame)

frame = 1540

ShootLineS(bullet.width/2+40,13,20,frame)

frame = 1630

ShootLineS(bullet.width/2+40,13,20,frame)

---------------------

frame = 1650

ShootLineS(bullet.width/2+40,8,20,frame)

frame = 1720

ShootLineS(bullet.width/2+40,13,20,frame)

frame = 1750

ShootLineS(bullet.width/2+40,8,20,frame)

-- frame = 1770

-- ShootLineS(bullet.width/2+40,13,20,frame)

frame = 1850

ShootLineS(bullet.width/2+40,13,20,frame)

ShootLineS(bullet.width/2+40,8,20,frame)

------------------------------

frame = 1950

for h=1,10 do
    x = math.random(-150,width+150);
    y = height
    -- for i=1,3 do
        ShootBulletLife(x,y,10,to_player,2,0, frame + h*60)
    -- end
end

ShootLineS(bullet.width/2+40,8,20,frame)

frame = 2050

ShootLineS(bullet.width/2+40,8,20,frame)

frame = 2150

ShootLineS(bullet.width/2+40,8,20,frame)

frame = 2250

ShootLineS(bullet.width/2+40,8,20,frame)

frame = 2350

ShootLineS(bullet.width/2+40,8,20,frame)

frame = 2450

ShootLineS(bullet.width/2+40,8,20,frame)

frame = 2598

for h=1,60 do
    ShootLineS(bullet.width/2+40,8,15,frame+h*GetBulletInterval(8))
end

frame = 2850

for h=1,60 do
    ShootLineSR(width - bullet.width/2- 40,8,15,frame+h*GetBulletInterval(8))
end

frame = 3150

for i=0,8 do
    ShootBullet(bullet.width/2 + 40+ i * 20,height,3,270,0,frame)
    ShootBullet(width - bullet.width/2-40 - i * 20,height,3,270,0,frame)
end


Write("uroad")