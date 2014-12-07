-- A simple scene with wooden desk

--wooden = gr.imgtex('../wood_1.png', {0.1, 0.1, 0.1}, {0.1, 0.1, 0.1}, 10, 0.1, 0, 'pNormalMap', 10, 5)
green = gr.material({0.8, 0.8, 0.8}, {0.5, 0.7, 0.5}, 25, 0.5)
yellow_perin = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25, 0, 0, 'pNormalMap', 5, 10)
ckboard = gr.checker({0.3, 0.3, 0.3}, {0.5, 0.7, 0.5}, 10, 0, 0)
refractmat = gr.material({0.1, 0.1, 0.1}, {0.5, 0.7, 0.5}, 25, 0, 1.5)
mat3 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25, 0.5)
chairmat = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25, 0)

woodensurface = gr.imgtex('../data/desk_surface.png', {0.1, 0.1, 0.1}, {0.1, 0.1, 0.1}, 10, 0, 0)
wooden = gr.imgtex('../data/wood_1.png', {0.1, 0.1, 0.1}, {0.1, 0.1, 0.1}, 10, 0, 0)
wooden_light = gr.imgtex('../data/wooden_light.png', {0.1, 0.1, 0.1}, {0.5, 0.7, 0.5}, 25, 0, 0)
kbdrawer_tex = gr.imgtex('../data/kbdrawer.png', {0.1, 0.1, 0.1}, {0.1, 0.1, 0.1}, 10, 0, 0)
kb = gr.imgtex('../data/kb.png', {0.1, 0.1, 0.1}, {0.1, 0.1, 0.1}, 10, 0, 0)
floorwood = gr.imgtex('../data/floor_texture.png', {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 20, 0.3, 0)
wall = gr.imgtex('../data/white_wall.png', {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, 20, 0, 0)
whitewall = gr.imgtex('../data/whitewall.png', {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, 20, 0, 0)
shutters = gr.imgtex('../data/shutters2.png', {0, 0, 0}, {0.5, 0.5, 0.5}, 5, 0, 0)



cola_tex = gr.imgtex('../data/cola_zero1.png', {0.3, 0.3, 0.3}, {0.3, 0.3, 0.3}, 10, 0, 0)
alum = gr.material({0.3, 0.3, 0.3}, {0.7, 0.7, 0.7}, 25, 0, 0)



scene_root = gr.node('root')


desk_all = gr.node('desk_all')
scene_root:add_child(desk_all)
desk_all:translate(-50,-150,20)

desk = gr.node('desk')
desk_all:add_child(desk)

deskstuff = gr.node('deskstuff')
desk_all:add_child(deskstuff)
deskstuff:translate(0,10,120)

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
bar:set_material(yellow_perin)

cone_handle = gr.nh_cone('cone_handle', {0,0,0}, 20, 40, 20)
drawer:add_child(cone_handle)
cone_handle:translate(25,8,158)
cone_handle:rotate('X',-90)
cone_handle:scale(0.4, 0.4, 0.4)
cone_handle:set_material(green)

--[[
drawer2 = gr.cuboid('drawer2', {0, 0, 0}, 80, 25, 100)
desk:add_child(drawer2)
drawer2:translate(10,-50,-100)
drawer2:set_material(wooden)

cone_handle2 = gr.nh_cone('cone_handle2', {0,0,0}, 20, 40, 24)
desk:add_child(cone_handle2)
cone_handle2:translate(50,-37,12)
cone_handle2:rotate('X',-90)
cone_handle2:scale(0.5, 0.5, 0.5)
cone_handle2:set_material(mat3)
]]--

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

---------------------------  chair -------------------------------------
-- require('chair')
--scene_root:add_child(chair)
-- chair:set_material(chairmat)

--------------------------- cola -------------------------------------
require('cola')
cola:translate(-70,17,0)
cola:scale(0.1,0.1,0.1)
deskstuff:add_child(cola)

--------------------------- laptop -------------------------------------
require('laptop')
laptop:translate(30,0,-10)
-- laptop:scale(0.1,0.1,0.1)
deskstuff:add_child(laptop)

-- --------------------------- crystal sphere -------------------------------------
-- crystalball = gr.nh_sphere('crystalball', {0, 0, 0}, 15)
-- deskstuff:add_child(crystalball)
-- crystalball:translate(-20, 25, -10)
-- crystalball:set_material(refractmat)

-- supporter = gr.nh_cylinder('supporter', {0, 0, 0}, {0, 1, 0}, 100, 300)
-- deskstuff:add_child(supporter)
-- supporter:translate(-20, 0, -10)
-- supporter:set_material(alum)

-- supporter = gr.nh_cone('supporter', {0,0,0}, 20, 20, 15)
-- deskstuff:add_child(supporter)
-- supporter:translate(-20, 0, -10)
-- supporter:set_material(alum)

--------------------------- desk lamp -------------------------------------
-- conelamp = gr.nh_cone('conelamp', {0,0,0}, 100, 200, 100)
-- scene_root:add_child(conelamp)
-- conelamp:translate(0, 60, 0)
-- --conelamp:rotate('Z',26)
-- conelamp:scale(0.2,0.2,0.2)
-- conelamp:set_material(mat3)


------------------------------ background plane ------------------------------
room_cube = gr.node('room_cube')
scene_root:add_child(room_cube)
room_cube:translate(-400, -300, -400)


p1 = gr.plane('planeback', {0,0,0},{1,0,0},{0,1,0}, 2000, 1000)
room_cube:add_child(p1)
p1:set_material(whitewall)

p2 = gr.plane('planebottom', {0,0,0},{1,0,0},{0,0,1}, 2000, 1000)
room_cube:add_child(p2)
p2:set_material(floorwood)

p3 = gr.plane('planeleft', {0,0,0},{0,0,1},{0,1,0}, 1000, 1000)
room_cube:add_child(p3)
p3:set_material(wall)

shutter = gr.plane('shutter', {0,0,1}, {1,0,0},{0,1,0}, 500, 600)
room_cube:add_child(shutter)
shutter:translate(200, 250,0)
shutter:set_material(shutters)

-- p4 = gr.plane('planeup', {0,0,0},{1,0,0},{0,0,1}, 2000, 1000)
-- room_cube:add_child(p4)
-- p4:translate(0, 1000, 0)
-- p4:set_material(wall)

--------------------------- lights -------------------------------------
blue_light = gr.light({-100.0, 150.0, 400.0}, {0.3, 0.3, 0.9}, {1, 0, 0})
orange_light = gr.light({400.0, 100.0, 300.0}, {0.7, 0.0, 0.7}, {1, 0, 0})
-- white_light = gr.light({-300, 600.0, 200.0}, {0.9, 0.9, 0.9}, {1, 0, 0})
-- white_conelight = gr.light({0, 40.0, 0.0}, {1.0, 1.0, 1.0}, {1, 0, 0}, {0,-1,0}, 5, 0.95)
white_light = gr.light({-300, 600.0, -380.0}, {0.9, 0.9, 0.9}, {1, 0, 0})


gr.render(scene_root, 'deskfocus_laptop.png', 256, 256,
	  {0, 0, 800}, {0, 0, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {white_light}) 
