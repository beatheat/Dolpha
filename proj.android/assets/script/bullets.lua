
bullets = {}
manis = {}

bullet_count = 1
mani_count = 1

width = 480
height = 90000
xheight = 960;
bottom = 160

same = 10000
to_player = 10001

bullet_type = 0
BTYPE = {}
BTYPE.bullet = 0
BTYPE.suriken = 1
BTYPE.triangle = 2

color = 0

red = 0
orange = 1
green = 2
blue = 3
violet = 4
black = 5

CLOCKWISE = 1
C_CLOCKWISE = -1

infinite = -1

bullet = {}
bullet.width = 22.5
bullet.height = 22.5

DIR_LEFT = 180
DIR_RIGHT = 0
DIR_UP = 90
DIR_DOWN = 270

T = {mani=0,cstart=1,cstop=2,cmove=3,cstarta=4}


function ShootBulletAcc(x,y,speed,dir,acc,acc_dir,tag,frame)
    bullets[bullet_count] = {x=x,y=y,speed=speed,dir=dir,color=color,bullet_type=bullet_type,life=1,acc=acc,acc_dir=acc_dir,tag=tag,frame=frame}
    bullet_count = bullet_count + 1
end

function ShootBulletAccLife(x,y,speed,dir,acc,acc_dir,life,tag,frame)
    bullets[bullet_count] = {x=x,y=y,speed=speed,dir=dir,color=color,bullet_type=bullet_type,life=life,acc=acc,acc_dir=acc_dir,tag=tag,frame=frame}
    bullet_count = bullet_count + 1
end

function ShootBullet(x,y,speed,dir,tag,frame)
    ShootBulletAcc(x,y,speed,dir,0,0,tag,frame)
end

function ShootBulletLife(x,y,speed,dir,life,tag,frame)
    ShootBulletAccLife(x,y,speed,dir,0,0,life,tag,frame)
end


function ShootCircle(x,y,speed,startdir,num,tags,frame)
    local angle = 360/num
    for i = 0,num-1 do
        ShootBullet(x,y,speed,startdir+i*angle,tag,frame)
    end
end


function ShootCircleLife(x,y,speed,startdir,num,life,tag,frame)
    local angle = 360/num
    for i = 0,num-1 do
        ShootBulletLife(x,y,speed,startdir+i*angle,life,tag,frame)
    end
end

function ManipulateBulletAcc(x,y,speed,dir,acc,acc_dir,tag,frame)
    manis[mani_count] = {type=T.mani ,x=x,y=y,speed=speed,dir=dir,color=color,bullet_type=bullet_type,acc=acc,acc_dir=acc_dir,tag=tag,frame=frame}
    mani_count = mani_count + 1
    end

function ManipulateBullet(x,y,speed,dir,tag,frame)
    ManipulateBulletAcc(x,y,speed,dir,same,same,tag,frame)
end

function SetBulletColor(c)
    color = c
end

function SetBulletType(T)
    bullet_type = T
end

function OnBulletCircle(centerX,centerY,speed,dir,tag,startframe,endframe)

    ManipulateBulletAcc(same,same,0,0,0,0,tag, startframe)
    ManipulateBulletAcc(same,same,0,0,0,0,tag, startframe)

    manis[mani_count] = {type=T.cstart,x=centerX,y=centerY,speed=speed,dir=dir,acc=same,acc_dir=same,color=color,bullet_type=bullet_type,tag=tag,frame=startframe}
    mani_count = mani_count + 1
    if endframe ~= infinite then
        manis[mani_count] = {type=2,x=same,y=same,speed=same,dir=same,acc=same,acc_dir=same,color=color,bullet_type=bullet_type,tag=tag,frame=endframe}
        mani_count = mani_count + 1
    end
end

function OnBulletCircleWithASpeed(centerX,centerY,speed,dir,tag,startframe,endframe)

    ManipulateBulletAcc(same,same,0,0,0,0,tag, startframe)
    ManipulateBulletAcc(same,same,0,0,0,0,tag, startframe)

    manis[mani_count] = {type=T.cstarta,x=centerX,y=centerY,speed=speed,dir=dir,acc=same,acc_dir=same,color=color,bullet_type=bullet_type,tag=tag,frame=startframe}
    mani_count = mani_count + 1
    if endframe ~= infinite then
        manis[mani_count] = {type=2,x=same,y=same,speed=same,dir=same,acc=same,acc_dir=same,color=color,bullet_type=bullet_type,tag=tag,frame=endframe}
        mani_count = mani_count + 1
    end
end

function StopBulletCircle(tag, frame)
    manis[mani_count] = {type=T.cstop,x=same,y=same,speed=same,dir=same,acc=same,acc_dir=same,color=color,bullet_type=bullet_type,tag=tag,frame=endframe}
    mani_count = mani_count + 1
end

function MoveBulletCircleAcc(speed,dir,acc,acc_dir,tag,frame)
    manis[mani_count] = {type=T.cmove,x=same,y=same,speed=speed,dir=dir,acc=acc,acc_dir=acc_dir,tag=tag,frame=frame,color=color,bullet_type=bullet_type}
    mani_count = mani_count + 1
end

function MoveBulletCircle(speed,dir,tag,frame)
    MoveBulletCircleAcc(speed,dir,same,same,tag,frame)
end


function Sort(tb)
    size = #tb
    for i=1,size do
        for j=1,size-i do
            if tb[j].frame > tb[j+1].frame then
                local hold = tb[j]
                tb[j] = tb[j+1]
                tb[j+1] = hold
            end
        end
    end

end


function Write(filename)
    file = io.open(filename..".shoot","w")
    io.output(file)

    -- table.sort(bullets, function(a,b) return a.frame < b.frame end)
    -- table.sort(manis, function(a,b) return a.frame < b.frame end)

    Sort(bullets)
    Sort(manis)


    for i=1,#bullets do
        -- io.write("shoot ")
        io.write(bullets[i].x.." ")
        io.write(bullets[i].y.." ")
        io.write(bullets[i].speed.." ")
        io.write(bullets[i].dir.." ")
        io.write(bullets[i].acc.." ")
        io.write(bullets[i].acc_dir.." ")
        io.write(bullets[i].color.." ")
        io.write(bullets[i].bullet_type.." ")
        io.write(bullets[i].life.." ")
        io.write(bullets[i].tag.." ")
        io.write(bullets[i].frame)
        io.write("\n")
    end

    -- io.write("0 0 0 0 0 0 0 0 0\n");

    io.close(file)

    file = io.open(filename..".mani","w")
    io.output(file)

    for i=1,#manis do
        -- io.write("manipulate ")
        io.write(manis[i].type.." ")
        io.write(manis[i].x.." ")
        io.write(manis[i].y.." ")
        io.write(manis[i].speed.." ")
        io.write(manis[i].dir.." ")
        io.write(manis[i].acc.." ")
        io.write(manis[i].acc_dir.." ")
        io.write(manis[i].color.." ")
        io.write(manis[i].tag.." ")
        io.write(manis[i].frame)
        io.write("\n")
    end

    -- io.write("0 0 0 0 0 0 0 0 0 0\n");

    io.close(file)
end
