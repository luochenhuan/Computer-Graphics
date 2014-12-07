-- need background set to simple background

mat1 = gr.material({0.3, 0.3, 0.3}, {0.5, 0.7, 0.5}, 25, 0)
mat2 = gr.material({0.8, 0.4, 0.1}, {0.5, 0.7, 0.5}, 25, 0.5, 0, 'imgNormalMap', '../brickwork.png')
mat3 = gr.material({.8, 0.5, 0.1}, {0.5, 0.7, 0.5}, 25, 0)
refractmat = gr.material({0.1, 0.1, 0.1}, {0.5, 0.7, 0.5}, 25, 0, 1.5)
chboard = gr.checker({0.3, 0.3, 0.3}, {0.5, 0.7, 0.5}, 25, 0, 0)
turb = gr.turbulence({0.3, 0.3, 0.3}, {0.5, 0.7, 0.5}, 20, 0, 0, 20, 10)
noise = gr.imgtex('../white_wall.png', {0.1, 0.1, 0.1}, {0.5, 0.7, 0.5}, 20, 0, 0, 'pNormalMap', 10, 2)
wall = gr.imgtex('../white_wall.png', {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, 20, 0, 0)
earth = gr.imgtex('../earth2.png', {0.0, 0.0, 0.0}, {0.5, 0.5, 0.5}, 20, 0, 0)


scene_root = gr.node('root')

s1 = gr.nh_sphere('s1', {0, 0, 0}, 50)
scene_root:add_child(s1)
s1:translate(-50, 240, 100)
s1:rotate('Y', 150)
--s1:rotate('Z', 180)
s1:set_material(earth)

s2 = gr.nh_sphere('s2', {0, 0, 0}, 50)
scene_root:add_child(s2)
s2:translate(-50, -10, 100)
s2:set_material(chboard)

s3 = gr.nh_sphere('s3', {0, 0, 0}, 50)
scene_root:add_child(s3)
s3:translate(-50, -260, 100)
s3:set_material(turb)

s4 = gr.nh_sphere('s4', {0, 0, 0}, 50)
scene_root:add_child(s4)
s4:translate(50, 240, 100)
s4:rotate('Y', 150)
--s1:rotate('Z', 180)
s4:set_material(noise)

-- s5 = gr.nh_sphere('s5', {0, 0, 0}, 100)
-- scene_root:add_child(s2)
-- s5:translate(50, -10, 0)
-- s5:set_material(chboard)

-- s6 = gr.nh_sphere('s6', {0, 0, 0}, 100)
-- scene_root:add_child(s6)
-- s6:translate(50, -260, 0)
-- s6:set_material(turb)

-- b1 = gr.nh_box('b1', {0, 0, 0}, 80)
-- scene_root:add_child(b1)
-- b1:translate(0,-200,-300)
-- b1:set_material(chboard)

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
white_light = gr.light({0.0, 100.0, 200.0}, {0.5, 0.5, 0.5}, {1, 0, 0})

gr.render(scene_root, 'texture_show.png', 256, 256,
	  {0, 0, 800}, {0, 0, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {white_light, green_light})
