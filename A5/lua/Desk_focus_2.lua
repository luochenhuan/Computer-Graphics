-- A simple scene with wooden desk

--wooden = gr.imgtex('../wood_1.png', {0.1, 0.1, 0.1}, {0.1, 0.1, 0.1}, 10, 0.1, 0, 'pNormalMap', 10, 5)
green = gr.material({0.8, 0.8, 0.8}, {0.5, 0.7, 0.5}, 25, 0.5)
yellow_perin = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25, 0, 0, 'pNormalMap', 5, 10)
ckboard = gr.checker({0.3, 0.3, 0.3}, {0.5, 0.7, 0.5}, 10, 0, 0)
refractmat = gr.material({0.1, 0.1, 0.1}, {0.5, 0.7, 0.5}, 25, 0, 1.5)
refractmat2 = gr.material({0.3, 0.3, 0.7}, {0.5, 0.7, 0.5}, 25, 0, 1.5)
turb1 = gr.turbulence({0.3, 0.3, 0.3}, {0.5, 0.7, 0.5}, 20, 0, 0, 100, 5, {0.2,0.3,0.5},{0.7,0.5,0.5})

mat3 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25, 0.5)
chairmat = gr.material({1, 0, 191.0/255}, {0.5, 0.7, 0.5}, 25, 0)

woodensurface = gr.imgtex('../data/desk_surface.png', {0.1, 0.1, 0.1}, {0.1, 0.1, 0.1}, 10, 0, 0)
wooden = gr.imgtex('../data/wood_1.png', {0.1, 0.1, 0.1}, {0.1, 0.1, 0.1}, 10, 0, 0)
wooden_light = gr.imgtex('../data/wooden_light.png', {0.1, 0.1, 0.1}, {0.5, 0.7, 0.5}, 25, 0, 0)
kbdrawer_tex = gr.imgtex('../data/kbdrawer.png', {0.1, 0.1, 0.1}, {0.1, 0.1, 0.1}, 10, 0, 0)
floorwood = gr.imgtex('../data/floor_texture.png', {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 20, 0.3, 0)
wall = gr.imgtex('../data/white_wall.png', {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, 20, 0, 0, 'imgNormalMap', '../data/concrete_nm.png')
whitewall = gr.imgtex('../data/whitewall.png', {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, 20, 0, 0)
shutters = gr.imgtex('../data/shutters2.png', {0, 0, 0}, {0.5, 0.5, 0.5}, 5, 0, 0)
brick_nm = gr.imgtex('../data/brick.png', {0,0,0}, {0.5, 0.5, 0.5}, 20, 0.0, 0,'imgNormalMap', '../data/brick_nm.png')

carpettex = gr.imgtex('../data/Carpet_01.png', {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, 20, 0, 0,'imgNormalMap', '../data/Carpet_01_NM.png')
screamtex = gr.imgtex('../data/scream.png', {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, 20, 0, 0)
chuntex = gr.imgtex('../data/chunge.png', {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, 20, 0, 0)

cola_tex = gr.imgtex('../data/cola_zero1.png', {0.3, 0.3, 0.3}, {0.3, 0.3, 0.3}, 10, 0, 0)
alum = gr.material({0.3, 0.3, 0.3}, {0.7, 0.7, 0.7}, 25, 0, 0)

scene_root = gr.node('root')


desk_all = gr.node('desk_all')
scene_root:add_child(desk_all)
desk_all:translate(-60,-150,20)

desk = gr.node('desk')
desk_all:add_child(desk)

deskstuff = gr.node('deskstuff')
desk_all:add_child(deskstuff)
deskstuff:translate(0,10,120)

cello_root = gr.node('cello_root')
scene_root:add_child(cello_root)


--desk:rotate('Y',30)
desk:scale(1.2,1,1.5)

--------------------------- desk -------------------------------------
surface = gr.cuboid('surface', {0, 0, 0}, 180, 10, 150)
desk:add_child(surface)
surface:translate(-90,0,0)
surface:set_material(woodensurface)

left = gr.cuboid('left', {0, 0, 0}, 10, 80, 150)
desk:add_child(left)
left:translate(-100,-70,0)
left:set_material(wooden)

right = gr.cuboid('right', {0, 0, 0}, 10, 80, 150) 
desk:add_child(right)
right:translate(90,-70,0)
right:set_material(wooden)

back = gr.cuboid('back', {0, 0, 0}, 180, 50, 10)
desk:add_child(back)
back:translate(-90,-50,0)
back:set_material(wooden)

--------------------------- drawer -------------------------------------
drawer = gr.node('drawer')
desk:add_child(drawer)
drawer:translate(40,-25,0)

drawerbox = gr.cuboid('drawerbox', {0, 0, 0}, 50, 25, 150)
drawer:add_child(drawerbox)
--drawerbox:translate(40,-25,0)
drawerbox:set_material(kbdrawer_tex)

bar = gr.plane('bar', {0, 0, 1},{1,0,0},{0,1,0}, 50, 25)
drawer:add_child(bar)
bar:translate(0,0,150)
--p2:rotate('Y',-90)
bar:set_material(turb1)

cone_handle = gr.nh_cone('cone_handle', {0,0,0}, 20, 40, 20)
drawer:add_child(cone_handle)
cone_handle:translate(25,15,158)
cone_handle:rotate('X',-90)
cone_handle:scale(0.4, 0.4, 0.4)
cone_handle:set_material(green)

--------------------------- keyboard drawer -------------------------------------
keyboarddrawer = gr.node('keyboarddrawer')
desk:add_child(keyboarddrawer)
keyboarddrawer:translate(-20,-20,0)

kbleft = gr.cuboid('kbleft', {0, 0, 0}, 5, 20, 150)
keyboarddrawer:add_child(kbleft)
kbleft:translate(-30,0,0)
kbleft:set_material(kbdrawer_tex)

kbright = gr.cuboid('kbright', {0, 0, 0}, 5, 20, 150)
keyboarddrawer:add_child(kbright)
kbright:translate(30,0,0)
kbright:set_material(kbdrawer_tex)


kbbottom = gr.node('kbbottom')
keyboarddrawer:add_child(kbbottom)
kbbottom:translate(-30,0,0)
                                                                                                                                                  
kbbottom1 = gr.cuboid('kbbottom1', {0, 0, 0}, 60, 5, 150)
kbbottom:add_child(kbbottom1)
kbbottom1:set_material(kbdrawer_tex)

-- kbimg = gr.plane('kbimg', {0,0,0},{1,0,0},{0,0,1}, 60, 30)
-- kbbottom:add_child(kbimg)
-- kbimg:translate(0,6,70)
-- kbimg:set_material(kb)

-------------------------  chair -------------------------------------
require('chair')
scene_root:add_child(chair)
chair:set_material(chairmat)
chair:translate(-90,-50,0)
chair:rotate('Y',-30)

-------------------------  cello -------------------------------------
require('cello')
--cello_root:add_child(cello)
cello_root:translate(140,-230,15)
cello_root:rotate('Z',10)

--------------------------- cola -------------------------------------
require('cola')
cola:translate(-60,17,0)
cola:scale(0.1,0.1,0.1)
deskstuff:add_child(cola)

--------------------------- laptop -------------------------------------
require('laptop')
laptop:translate(30,0,-15)
-- laptop:scale(0.1,0.1,0.1)
deskstuff:add_child(laptop)

--------------------------- supporter -------------------------------------
require('supporter')
scene_root:add_child(supporter)
supporter:translate(260,-320,150)
supporter:scale(0.6,0.6,0.6)

------------------------------ background plane ------------------------------
room_cube = gr.node('room_cube')
scene_root:add_child(room_cube)
room_cube:translate(-400, -300, -400)


p1 = gr.plane('planeback', {0,0,0},{1,0,0},{0,1,0}, 2000, 1000)
room_cube:add_child(p1)
p1:set_material(whitewall)

scream = gr.plane('scream', {0,0,1},{1,0,0},{0,1,0}, 600, 800)
room_cube:add_child(scream)
scream:translate(680,300,0)
scream:scale(0.4,0.4,0.4)
scream:set_material(screamtex)

chunge = gr.plane('chunge', {0,0,1},{1,0,0},{0,1,0}, 600, 800)
room_cube:add_child(chunge)
chunge:translate(20,300,0)
chunge:scale(0.4,0.4,0.4)
chunge:set_material(chuntex)

p2 = gr.plane('planebottom', {0,0,0},{1,0,0},{0,0,1}, 2000, 1000)
room_cube:add_child(p2)
p2:set_material(floorwood)

p3 = gr.plane('planeleft', {0,0,0},{0,0,1},{0,1,0}, 1000, 1000)
room_cube:add_child(p3)
p3:set_material(brick_nm)

shutter = gr.plane('shutter', {0,0,1}, {1,0,0},{0,1,0}, 500, 600)
room_cube:add_child(shutter)
shutter:translate(270,200,0)
shutter:scale(0.8,0.8, 0.8)
shutter:set_material(shutters)

p4 = gr.plane('planeup', {0,0,0},{1,0,0},{0,0,1}, 2000, 1000)
room_cube:add_child(p4)
p4:translate(0, 800, 0)
p4:set_material(wall)

--------------------------- upper lamp ------------------------------------
require('upperlamp')
room_cube:add_child(upperlamp)
upperlamp:translate(300,600,100)


---------------------------  carpet -------------------------------------
carpet = gr.plane('carpet', {0,1,0},{1,0,0},{0,0,1}, 400, 400)
room_cube:add_child(carpet)
carpet:translate(120,0,180)
-- carpet:scale(0.5,0.5,0.5)
carpet:set_material(carpettex)



--------------------------- lights -------------------------------------
blue_light = gr.light({-100.0, 150.0, 400.0}, {0.3, 0.3, 0.9}, {1, 0, 0})
orange_light = gr.light({300.0, 400.0, 300.0}, {0.6, 0.3, 0.6}, {1, 0, 0})
-- white_light = gr.light({-300, 600.0, 200.0}, {0.9, 0.9, 0.9}, {1, 0, 0})
-- white_conelight = gr.light({0, 40.0, 0.0}, {1.0, 1.0, 1.0}, {1, 0, 0}, {0,-1,0}, 5, 0.95)
white_light = gr.light({-300, 550.0, -380.0}, {0.9, 0.9, 0.9}, {1, 0, 0})
white_conelight = gr.light({-280, 10.0, 200.0}, {1.0, 1.0, 1.0}, {1, 0, 0}, {1,-2,-1}, 2, 0.96)


gr.render(scene_root, '../img/final_1024.png', 1024, 1024,
	  {0, 0, 800}, {0, 0, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {white_light,orange_light,white_conelight}) 
