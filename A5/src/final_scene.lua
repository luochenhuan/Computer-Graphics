-- A simple scene with wooden desk

--wooden = gr.imgtex('../wood_1.png', {0.1, 0.1, 0.1}, {0.1, 0.1, 0.1}, 10, 0.1, 0, 'pNormalMap', 10, 5)
green = gr.material({0.8, 0.8, 0.8}, {0.5, 0.7, 0.5}, 25, 0.5)
metal = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25, 0, 0, 'pNormalMap', 5, 10)
wooden = gr.imgtex('../data/wood_1.png', {0.1, 0.1, 0.1}, {0.1, 0.1, 0.1}, 10, 0, 0)
wooden_light = gr.imgtex('../data/wooden_light.png', {0.1, 0.1, 0.1}, {0.5, 0.7, 0.5}, 25, 0, 0)
kbdrawer_tex = gr.imgtex('../data/kbdrawer.png', {0.1, 0.1, 0.1}, {0.1, 0.1, 0.1}, 10, 0, 0)
kb = gr.imgtex('../data/kb.png', {0.1, 0.1, 0.1}, {0.1, 0.1, 0.1}, 10, 0, 0)
ckboard = gr.checker({0.3, 0.3, 0.3}, {0.5, 0.7, 0.5}, 10, 0, 0)
floorwood = gr.imgtex('../data/floor_texture.png', {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 20, 0.3, 0)
wall = gr.imgtex('../data/white_wall.png', {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, 20, 0, 0)

mat3 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25, 0.5)
mat4 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25, 0  )

cola_tex = gr.imgtex('../data/cola_zero1.png', {0.3, 0.3, 0.3}, {0.3, 0.3, 0.3}, 10, 0, 0)
alum = gr.material({0.3, 0.3, 0.3}, {0.7, 0.7, 0.7}, 25, 0, 0)

scene_root = gr.node('root')

--------------------------- desk -------------------------------------
desk = gr.node('desk')
scene_root:add_child(desk)
desk:rotate('Y',30)


surface = gr.cuboid('surface', {0, 0, 0}, 180, 10, 150)
desk:add_child(surface)
surface:translate(-90,0,-100)
surface:set_material(mat4)


left = gr.cuboid('left', {0, 0, 0}, 10, 80, 150)
desk:add_child(left)
left:translate(-100,-70,-100)
left:set_material(wooden)

right = gr.cuboid('right', {0, 0, 0}, 10, 80, 150) 
desk:add_child(right)
right:translate(90,-70,-100)
right:set_material(wooden)

back = gr.cuboid('back', {0, 0, 0}, 200, 50, 10)
desk:add_child(back)
back:translate(-100,-50,-140)
back:set_material(wooden)

--------------------------- drawer -------------------------------------
drawer = gr.node('drawer')
desk:add_child(drawer)
--drawer:scale(0.8, 1, 1)

drawerbox = gr.cuboid('drawerbox', {0, 0, 0}, 50, 25, 100)
drawer:add_child(drawerbox)
drawerbox:translate(40,-25,-100)
drawerbox:set_material(kbdrawer_tex)

bar = gr.plane('bar', {40, 0, 2},{1,0,0},{0,-1,0}, 50, 25)
drawer:add_child(bar)
--p2:rotate('Y',-90)
bar:set_material(metal)

cone_handle = gr.nh_cone('cone_handle', {0,0,0}, 20, 40, 20)
drawer:add_child(cone_handle)
cone_handle:translate(65,-12,8)
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
keyboarddrawer:translate(20,0,0)

kbleft = gr.cuboid('kbleft', {0, 0, 0}, 5, 20, 100)
keyboarddrawer:add_child(kbleft)
kbleft:translate(-85,-20,-100)
kbleft:set_material(kbdrawer_tex)

kbright = gr.cuboid('kbright', {0, 0, 0}, 5, 20, 100)
keyboarddrawer:add_child(kbright)
kbright:translate(-25,-20,-100)
kbright:set_material(kbdrawer_tex)


kbbottom = gr.node('kbbottom')
keyboarddrawer:add_child(kbbottom)
kbbottom:translate(-80,-20,-100)

kbbottom1 = gr.cuboid('kbbottom1', {0, 0, 0}, 60, 5, 100)
kbbottom:add_child(kbbottom1)
kbbottom1:set_material(kbdrawer_tex)

kbimg = gr.plane('kbimg', {0,0,0},{1,0,0},{0,0,1}, 60, 30)
kbbottom:add_child(kbimg)
kbimg:translate(0,6,70)
kbimg:set_material(kb)

--------------------------- desk lamp -------------------------------------
-- conelamp = gr.nh_cone('conelamp', {0,0,0}, 100, 200, 100)
-- scene_root:add_child(conelamp)
-- conelamp:translate(0, 60, 0)
-- --conelamp:rotate('Z',26)
-- conelamp:scale(0.2,0.2,0.2)
-- conelamp:set_material(mat3)



------------------------------ coke cola ------------------------------
cola = gr.node('cola')
desk:add_child(cola)
cola:translate(-50,12,-50)
cola:scale(0.5,0.5,0.5)

cola_cyl = gr.nh_cylinder('cola_cyl', {0, 0, 0}, {0, 1, 0}, 20, 60)
cola:add_child(cola_cyl)
cola_cyl:translate(0,0,0)
cola_cyl:rotate('Y',-1)
cola_cyl:set_material(cola_tex)

c2 = gr.nh_cone('cola_cone', {0,0,0}, 20, 40, 4)
cola:add_child(c2)
c2:translate(0,60,0)
c2:set_material(alum)

c1 = gr.nh_cone('cola_conebottom', {0,0,0}, 20, 40, 4)
cola:add_child(c1)
c1:rotate('Z',180)
c1:set_material(alum)




------------------------------ background plane ------------------------------
room_cube = gr.node('room_cube')
scene_root:add_child(room_cube)
room_cube:translate(-400, -180, -400)
desk:translate(-100,-110,50)

p1 = gr.plane('planeback', {0,0,0},{1,0,0},{0,1,0}, 2000, 1000)
room_cube:add_child(p1)
p1:set_material(wall)

p2 = gr.plane('planebottom', {0,0,0},{1,0,0},{0,0,1}, 2000, 1000)
room_cube:add_child(p2)
p2:set_material(floorwood)

p3 = gr.plane('planeleft', {0,0,0},{0,0,1},{0,1,0}, 1000, 1000)
room_cube:add_child(p3)
p3:set_material(wall)

-- p4 = gr.plane('planeup', {0,0,0},{1,0,0},{0,0,1}, 2000, 1000)
-- room_cube:add_child(p4)
-- p4:translate(0, 1000, 0)
-- p4:set_material(wall)

--------------------------- lights -------------------------------------
blue_light = gr.light({-100.0, 150.0, 400.0}, {0.3, 0.3, 0.9}, {1, 0, 0})
orange_light = gr.light({400.0, 100.0, 300.0}, {0.7, 0.0, 0.7}, {1, 0, 0})
white_light = gr.light({-300, 600.0, 200.0}, {0.9, 0.9, 0.9}, {1, 0, 0})
-- white_conelight = gr.light({0, 40.0, 0.0}, {1.0, 1.0, 1.0}, {1, 0, 0}, {0,-1,0}, 5, 0.95)

gr.render(scene_root, 'cola_desk.png', 256, 256,
	  {0, 0, 800}, {0, 0, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {white_light}) 
