-- need background set to simple background

mat1 = gr.material({0.3, 0.3, 0.3}, {0.5, 0.7, 0.5}, 25, 0)
mat2 = gr.material({0.8, 0.4, 0.1}, {0.5, 0.7, 0.5}, 25, 0.5, 0, 'imgNormalMap', '../brickwork.png')
mat3 = gr.material({.8, 0.5, 0.1}, {0.5, 0.7, 0.5}, 25, 0)
refractmat = gr.material({0.1, 0.1, 0.1}, {0.5, 0.7, 0.5}, 25, 0, 1.5)
chboard = gr.checker({0.3, 0.3, 0.3}, {0.5, 0.7, 0.5}, 25, 0, 0)
turb = gr.turbulence({0.3, 0.3, 0.3}, {0.5, 0.7, 0.5}, 20, 0, 0, 20, 5)
noise = gr.imgtex('../white_wall.png', {0.1, 0.1, 0.1}, {0.5, 0.7, 0.5}, 20, 0, 0, 'pNormalMap', 10, 2)
wall = gr.imgtex('../white_wall.png', {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, 20, 0, 0)
rope = gr.imgtex('../rope_tex.png', {0.0, 0.0, 0.0}, {0.3, 0.3, 0.3}, 10, 0, 0)


cola_tex = gr.imgtex('../cola_zero1.png', {0.3, 0.3, 0.3}, {0.3, 0.3, 0.3}, 10, 0, 0)
-- metal = gr.material({173.0/255, 160.0/255, 189.0/255}, {0.7, 0.7, 0.7}, 25, 0, 0)
alum = gr.material({0.3, 0.3, 0.3}, {0.7, 0.7, 0.7}, 25, 0, 0)

scene_root = gr.node('root')


-- c1 = gr.nh_cylinder('cyl1', {0, 0, 0}, {0, 1, 0}, 100, 100)
-- scene_root:add_child(c1)
-- c1:translate(-200,100,0)
-- c1:rotate('X',30)
-- c1:set_material(chboard)

-- c2 = gr.nh_cylinder('cyl2', {0, 0, 0}, {0, 1, 0}, 100, 100)
-- scene_root:add_child(c2)
-- c2:translate(-200,-100,0)
-- c2:rotate('X',-30)
-- c2:set_material(chboard)

cola = gr.node('cola')
scene_root:add_child(cola)

cola_cyl = gr.nh_cylinder('cola_cyl', {0, 0, 0}, {0, 1, 0}, 100, 300)
cola:add_child(cola_cyl)
cola_cyl:translate(0,-200,0)
cola_cyl:rotate('Y',-1)
cola_cyl:set_material(cola_tex)

c2 = gr.nh_cone('cone1', {0, 0,0}, 100, 200, 20)
cola:add_child(c2)
c2:translate(0,100,0)
c2:set_material(alum)

c1 = gr.nh_cone('cola_cone', {0,0,0}, 100, 200, 20)
cola:add_child(c1)
c1:translate(0,-200,0)
c1:rotate('Z',180)
c1:set_material(alum)

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

gr.render(scene_root, 'cola_test.png', 256, 256,
	  {0, 0, 800}, {0, 0, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {white_light, green_light})
