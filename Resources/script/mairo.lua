
dofile('bullets.lua')


-- ShootBulletAcc(x,y,speed,dir,acc,acc_dir,tag,frame)
-- ShootBullet(x,y,speed,dir,tag,frame)
-- ShootCircle(x,y,speed,startdir,num,tags,frame)
-- ManipulateBullet(x,y,speed,dir,tag,frame)
-- ManipulateBulletAcc(x,y,speed,dir,acc,acc_dir,tag,frame)
-- OnBulletCircle(centerX,centerY,speed,dir,tag,startframe,endframe)
-- MoveBulletCircle(speed,dir,tag,frame)

function ShootLine(spot, num, _frame)
    for i=0,num-1 do
        ShootBullet(spot + i*20,height,3,270,0,_frame)
    end
end

function ShootLineR(spot, num, _frame)
    for i=0,num-1 do
        ShootBullet(spot - i*20, height,3,270,0,_frame)
    end
end

function ShootLineU(spot,num,speed,tag, _frame)
    for i=0,num-1 do
        ShootBullet(spot + i*20,bottom,speed,90,tag,_frame)
    end
end

function ShootLineUL(spot,num,speed,tag, _frame)
    for i=0,num-1 do
        ShootBulletLife(spot + i*20,bottom,speed,90,2,tag,_frame)
    end
end

function ShootLineT(spot,num,speed,tag,_frame)
    for i=0,num-1 do
        ShootBulletLife(spot+i*20,xheight+16.4,speed,270,2,tag,_frame)
    end
end

function ShootLineRT(spot,num,speed,tag,_frame)
    for i=0,num-1 do
        ShootBulletLife(spot - i*20,xheight+16.4,speed,270,2,tag,_frame)
    end
end



function ShootLineSpeed(spot, num, speed, _frame)
    for i=0,num-1 do
        ShootBullet(spot + i*20,height,speed,270,0,_frame)
    end
end

function ShootLineSpeedR(spot, num, speed, _frame)
    for i=0,num-1 do
        ShootBullet(spot - i*20, height,speed,270,0,_frame)
    end
end




HRIGHT = 0
HLEFT = 1
function ShootHammer(dir,_frame)

    local y = height - math.random(0,800)

    tag_hammer = GetTag()

    local x = dir * width;
    local dir = dir * 180

    for h=1,5 do
        ShootBullet(x,y,3,dir,tag_hammer,_frame + h*5)
        ShootBullet(x,y+20,3,dir,tag_hammer,_frame + h*5)
        ShootBullet(x,y+40,3,dir,tag_hammer,_frame + h*5)
    end

    _frame = _frame + 30
    ManipulateBullet(same,same,5,180 - dir,tag_hammer,_frame)

    _frame = _frame + 70

    for h=1,25 do
        ShootBullet(x,y,15,dir,tag_hammer,_frame + h)
        ShootBullet(x,y+20,15,dir,tag_hammer,_frame + h)
        ShootBullet(x,y+40,15,dir,tag_hammer,_frame + h)
    end


end


tag_generator = 1
function GetTag()
    tag_generator = tag_generator + 1
    return tag_generator
end

bulletstart = bullet.width/2
bulletend = width - bullet.width/2


frame = 0;

tags = {}

tags.door1 = GetTag()
tags.door2 = GetTag()

math.randomseed(168);


SetBulletColor(green)

frame = 15

for i=0,11 do
    ShootBullet(bullet.width/2 + i * 20,height,3,270,tags.door1,frame)
    ShootBullet(width - bullet.width/2 - i * 20,height,3,270,tags.door2,frame)
end

frame = 70

OnBulletCircle(bullet.width/2, height - 55 * 3, 1.5, C_CLOCKWISE, tags.door1, frame, infinite)
OnBulletCircle(width - bullet.width/2, height - 55 * 3, 1.5, CLOCKWISE, tags.door2, frame, infinite)


MoveBulletCircle(3, 270, tags.door1, frame)
MoveBulletCircle(3, 270, tags.door2, frame)

frame = 260

--처음 가운데
for h=1,30 do
    for i=0,10 do
        ShootBullet(bullet.width/2 + i * 20,height,3,270,0,frame + h*10)
        ShootBullet(width - bullet.width/2 - i * 20,height,3,270,0,frame + h*10)
    end
end


-- 가장자리
frame = 560
for x=frame,9300,10 do
    ShootBullet(bullet.width/2,height,3,270,0,x)
    ShootBullet(width - bullet.width/2,height,3,270,0,x)
end

-- 좌로 이동
for h=1,10 do
    ShootLine(bulletstart + 20,9-h,frame + h*10)
    ShootLineR(bulletend + 20,9+h,frame+h*10)
end

frame = 660

-- 우로 이동
for h=1,18 do
    adh = 0
    if h>10 then adh = h-10 end 
    ShootLine(bulletstart,h,frame+h*10)
    ShootLineR(bulletend,18-h,frame+h*10)
end

frame = 840

-- 잠시 대기
for h=1,20 do
    ShootLine(bulletstart,18,frame+h*10)
end

frame = 1040

for h=1,3 do
    ShootLine(bulletstart,23,frame+h*10)
end

frame = 1070

for h=1,20 do
    ShootLine(bulletstart,10,frame+h*10)
    ShootLineR(bulletend,10,frame+h*10)
end

frame = 1270

for h=1,5 do
    ShootLine(bulletstart,23,frame+h*10)
end

frame = 1320

for h=1,20 do
    ShootLine(bulletstart,10,frame+h*10)
    ShootLineR(bulletend,10,frame+h*10)
end

frame = 1520

-- 마름모 통과
for h=1,10 do
    ShootLine(bulletstart,10-h,frame+h*10)
    ShootLineR(bulletend,10-h,frame+h*10)
end

frame = 1660

for i=1,3 do
    ShootBullet(0,height - math.random(0,800),6,to_player,0,frame+i*4)
end

frame = 1720

for i=1,3 do
    ShootBullet(width,height - math.random(0,800),6,to_player,0,frame+i*4)
end

frame = 1780

for i=1,3 do
    ShootBullet(width,height - math.random(0,800),6,to_player,0,frame+i*4)
end


frame = 1840

for i=1,3 do
    ShootBullet(0,height - math.random(0,800),6,to_player,0,frame+i*4)
end

frame = 1720

for h=1,10 do
    ShootLine(bulletstart,h,frame+h*10)
    ShootLineR(bulletend,h,frame+h*10)
end

frame = 1820

for h=1,10 do
    ShootLine(bulletstart,10-h,frame+h*10)
    ShootLineR(bulletend,10-h,frame+h*10)
end

frame = 2100

for times = 1,7 do
    for h=1,5 do
        ShootLineSpeed(bulletstart + times*50,4,20,frame+h+times*25)
    end
end

-- 햄머패턴

frame = 2400
for h=1,5 do
    ShootHammer(math.random(0,1), frame + h*100)
end

frame = 2870
for h=1,27 do
    ShootHammer(math.random(0,1), frame + h*30)
end

-- 빠르게 떨어지는 패턴

frame = 3950

for h=1,5 do
    ShootLineSpeed(bulletstart+20,22,10,frame+h*3)
end

frame = 4030

for h=1,5 do
    ShootLineSpeed(bulletstart+20,22,10,frame+h*3)
end

frame = 4110

for h=1,5 do
    ShootLineSpeed(bulletstart+20,22,10,frame+h*3)
end

--가운데 구멍

frame = 4190

for h=1,5 do
    ShootLineSpeed(bulletstart+20,22,10,frame+h*3)
end


frame = 4205

for h=1,25 do
    ShootLineSpeed(bulletstart+20,8,10,frame+h*3)
    ShootLineSpeedR(bulletend-20,8,10,frame+h*3)
end

frame = 4280 --여기까지


for h=1,25 do
    ShootLineSpeed(bulletstart+20*8,8,10,frame+h*3)
end

--양쪽
frame = 4355

for h=1,25 do
    ShootLineSpeed(bulletstart+20,8,10,frame+h*3)
    ShootLineSpeedR(bulletend-20,8,10,frame+h*3)
end

--양쪽 선

frame = 4430

for h=1,25 do
    ShootBullet(bulletstart+20*8,height,10,270,0,frame+h*3)
    ShootBullet(bulletend-20*8,height,10,270,0,frame+h*3)
end


--벽

frame = 4505

for h=1,5 do
    ShootLineSpeed(bulletstart+20,22,10,frame+h*3)
end

frame = 4520

--삼선

for h=1,25 do
    ShootBullet(bulletstart+20*5,height,10,270,0,frame+h*3)
    ShootBullet(bulletstart+20*12,height,10,270,0,frame+h*3)
    ShootBullet(bulletstart+20*19,height,10,270,0,frame+h*3)
end

frame = 4595

--벽

for h=1,5 do
    ShootLineSpeed(bulletstart+20,22,10,frame+h*3)
end


frame = 4750

for h=1,50 do
    ShootLineSpeed(bulletstart+20*4,19,10,frame+h*3)
end

frame = 4970

for h=1,50 do
    ShootLineSpeedR(bulletend-20*4,19,10,frame+h*3)
end

frame = 5250

for h=0,8 do
    local x = bullet.width + 25 + h*48
    local y = height + 100

    tags.circle = GetTag()

    ShootCircleLife(x,y,5,0,20,2,tags.circle,frame)
    OnBulletCircle(x,y,5,CLOCKWISE,tags.circle,frame+10,infinite)
    MoveBulletCircle(15,270,tags.circle,frame+10)
end

frame = 5350

for h=0,8 do
    local x = bullet.width + 25 + h*48
    local y = height + 100

    tags.circle = GetTag()

    ShootCircleLife(x,y,5,0,20,2,tags.circle,frame)
    OnBulletCircle(x,y,5,C_CLOCKWISE,tags.circle,frame+10,infinite)
    MoveBulletCircle(15,270,tags.circle,frame+10)
end


frame = 5500

for h=1,25 do
    local x = math.random(bullet.width+25,width-25-bullet.width)
    local y = height + 100

    tags.circle = GetTag()

    ShootCircleLife(x,y,5,0,20,2,tags.circle,frame+h*20)
    OnBulletCircle(x,y,5,-2*math.random(0,1) + 1,tags.circle,frame+h*20+10,infinite)
    MoveBulletCircle(15,270,tags.circle,frame+h*20+10)
end

frame = 5430

--바닥
tags.under = GetTag()
for h=1,8 do
    ShootLineU(bulletstart+20,22,1,tags.under,frame+h*25)
end

frame = 5680
ManipulateBullet(same,same,0,0,tags.under,frame)


frame = 6050

--기둥
tags.pillarL = GetTag()
for h=1,35 do
    ShootLineT(120,4,16.4,tags.pillarL,frame+h*1)
end

frame = 6086
ManipulateBullet(same,same,0,0,tags.pillarL,frame)


frame = 6040

tags.pillarR = GetTag()
for h=1,35 do
    ShootLineRT(width-120,4,16.4,tags.pillarR,frame+h*1)
end

frame = 6076
ManipulateBullet(same,same,0,0,tags.pillarR,frame)

-- 여기서부터
frame = 6200

-- 난이도 수정
for h=1,15 do
    for i=1,3 do
        x = math.random(0,1)*width
        ShootBullet(x,height - math.random(0,800),6,to_player,0,frame+i*5+ h*60)
    end
end

frame = 7250

for h=1,10 do
    ShootHammer(math.random(0,1), frame + h*40)
end

frame = 7650

for h=1,25 do
    ShootHammer(math.random(0,1), frame + h*20)
end

frame = 8350

ManipulateBullet(same,same,10,90,tags.pillarL,frame)
ManipulateBullet(same,same,10,90,tags.pillarR,frame)
ManipulateBullet(same,same,5,270,tags.under,frame)


-- 마름모진입
frame = 8550

for h=1,9 do
    ShootLine(bulletstart,h,frame+h*10)
    ShootLineR(bulletend,h,frame+h*10)
end

frame = 8640

for h=1,20 do
    ShootLine(bulletstart,9,frame+h*10)
    ShootLineR(bulletend,9,frame+h*10)
end

frame = 8840

-- 좌로 이동
for h=1,10 do
    -- if h==1 then h = 0 end
    ShootLine(bulletstart,9-h,frame + h*10)
    if h==10 then
        ShootLineR(bulletend,18, frame+h*10)
    else
        ShootLineR(bulletend,9+h,frame+h*10)
    end
end

frame = 8940

-- 우로 이동
for h=1,17 do
    -- adh = 0
    -- if h>10 then adh = h-10 end 
    ShootLine(bulletstart,h-1,frame+h*10)
    ShootLineR(bulletend,19-h,frame+h*10)
end

frame =9110

-- 다시 좌로 이동
for h=1,10 do
    ShootLine(bulletstart,18-h,frame+h*10)
    ShootLineR(bulletend,h,frame+h*10)
end

frame = 9210

for h=1,9 do
    ShootLine(bulletstart,h,frame+h*10)
    ShootLineR(bulletend,h,frame+h*10)
end

frame = 9300

for h=1,2 do
    ShootLine(bulletstart,9+h,frame+h*10)
    ShootLineR(bulletend,9+h,frame+h*10)
end


frame = 9320

for h=1,20 do
    ShootLine(bulletstart,11,frame+h*10)
    ShootLineR(bulletend,11,frame+h*10)
end

frame = 9600

for i=0,11 do
    ShootBullet(bullet.width/2 + i * 20,height,3,270,tags.door1,frame)
    ShootBullet(width - bullet.width/2 - i * 20,height,3,270,tags.door2,frame)
end

frame = 9640

OnBulletCircle(bullet.width/2, height - 55 * 3, 1.5, C_CLOCKWISE, tags.door1, frame, infinite)
OnBulletCircle(width - bullet.width/2, height - 55 * 3, 1.5, CLOCKWISE, tags.door2, frame, infinite)


MoveBulletCircle(3, 270, tags.door1, frame)
MoveBulletCircle(3, 270, tags.door2, frame)




Write('mairo')