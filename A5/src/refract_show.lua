

mat1 = gr.material({0.3, 0.3, 0.3}, {0.5, 0.7, 0.5}, 25, 0)
mat2 = gr.material({0.6, 0.4, 0.1}, {0.5, 0.7, 0.5}, 25, 0.0, 0, 'imgNormalMap', '../data/brick_nm.png')
mat3 = gr.material({0.8, 0.5, 0.1}, {0.5, 0.7, 0.5}, 25, 0)
mat4 = gr.material({0.3, 0.3, 0.3}, {0.5, 0.7, 0.5}, 25, 0)

refractmat = gr.material({0.1, 0.1, 0.1}, {0.5, 0.7, 0.5}, 25, 0, 1.5)
chboard = gr.checker({0.3, 0.3, 0.3}, {0.5, 0.7, 0.5}, 25, 0, 0)
turb = gr.turbulence({0.3, 0.3, 0.3}, {0.5, 0.7, 0.5}, 20, 0, 0, 10, 5)
floorwood = gr.imgtex('../data/wooden_light.png', {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 20, 0.3, 0)
brick = gr.imgtex('../data/brick.png', {0.1, 0.1, 0.1}, {0.5, 0.7, 0.5}, 20, 0, 0, 'pNormalMap', 10, 2)
wall = gr.imgtex('../data/white_wall.png', {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, 20, 0, 0)

refractmat2 = gr.material({0.3, 0.3, 0.7}, {0.5, 0.7, 0.5}, 25, 0, 1.5)

scene_root = gr.node('root')


------------------------------ background plane ------------------------------
p1 = gr.plane('planeback', {0,0,0},{1,0,0},{0,1,0}, 1000, 800)
scene_root:add_child(p1)
p1:translate(-500, -300, -400)
p1:set_material(mat1)

p2 = gr.plane('planebottom', {0,0,0},{1,0,0},{0,0,1}, 1000, 1000)
scene_root:add_child(p2)
p2:translate(-500, -300, -400)
p2:set_material(mat4)

p3 = gr.plane('planeleft', {0,0,0},{0,0,1},{0,1,0}, 800, 800)
scene_root:add_child(p3)
p3:translate(-500, -300, -400)
p3:set_material(mat2)

-- p4 = gr.plane('planeright', {0,0,0},{0,0,1},{0,1,0}, 800, 800)
-- scene_root:add_child(p4)
-- p4:translate(500, -300, -400)
-- p4:set_material(mat2)

-- s1 = gr.nh_sphere('s1', {0, 0, 0}, 100)
-- scene_root:add_child(s1)
-- s1:translate(0, 0, -200)
-- s1:set_material(turb)

s2 = gr.nh_sphere('s2', {0, 0, 0}, 60)
scene_root:add_child(s2)
s2:translate(0, 0, 300)
s2:set_material(refractmat)


-- A small stellated dodecahedron.

require('smstdodeca')


scene_root:add_child(steldodec)
steldodec:translate(120, -100, -50)
steldodec:set_material(mat3)

s3 = gr.nh_sphere('s3', {0, 0, 0}, 100)
scene_root:add_child(s3)
s3:translate(80, -200, -200)
s3:set_material(turb)

b1 = gr.nh_box('b1', {0, 0, 0}, 100)
scene_root:add_child(b1)
b1:translate(-20, -200, 200)
b1:set_material(refractmat2)

-- c1 = gr.nh_cylinder('cyl1', {0, 0, 0}, {0, 1, 0}, 100, 100)
-- scene_root:add_child(c1)
-- c1:translate(0,-100,0)
-- c1:rotate('X',30)
-- c1:set_material(chboard)

--[[
c2 = gr.nh_cone('cone1', {-50, -200,-100}, 200, 400, 200)
scene_root:add_child(c2)
--c2:rotate('X',-30)
c2:set_material(mat4)


-- the floor
p1 = gr.plane('plane', {-350, -150, 50},{1,0,0},{0,1,0}, 300, 300)
scene_root:add_child(p1)
--p1:rotate('X',-90)
p1:set_material(wall)
]]--

green_light = gr.light({400.0, 100.0, 300.0}, {0.5, 0.7, 0.5}, {1, 0, 0})
-- green_light = gr.light({400.0, 100.0, 300.0}, {0.5, 0.7, 0.5}, {1, 0, 0}, {1,0,0}, {0,0,1}, 50, 50)
white_light = gr.light({-50.0, 100.0, 100.0}, {0.5, 0.5, 0.5}, {1, 0, 0})
--l1 = gr.light({200,200,400}, {0.8, 0.8, 0.8}, {1, 0, 0}, {1,0,0}, {0,0,1}, 50, 50)

gr.render(scene_root, '../img/refract_show_aa.png', 512, 512,
	  {0, 0, 800}, {0, 0, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {green_light, white_light})
