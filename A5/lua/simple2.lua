-- 

mat1 = gr.material({0.7, 1.0, 0.7}, {0.5, 0.7, 0.5}, 25, 0.3)
mat2 = gr.material({0.5, 0.5, 0.5}, {0.5, 0.7, 0.5}, 25, 0.3)
mat3 = gr.material({0.1, 0.1, 0.5}, {0.5, 0.7, 0.5}, 25, 0, 1.3)
mat4 = gr.material({0.3, 0.3, 0.3}, {0.5, 0.7, 0.5}, 25, 0.5, 1.5)
mat5 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25, 0.3)

scene_root = gr.node('root')

s1 = gr.nh_sphere('s1', {30, 0, 400}, 100)
scene_root:add_child(s1)
s1:set_material(mat3)

s2 = gr.nh_sphere('s2', {180, 50, -100}, 150)
scene_root:add_child(s2)
s2:set_material(mat1)


s3 = gr.nh_sphere('s3', {0, -1200, -500}, 1000)
scene_root:add_child(s3)
s3:set_material(mat5)

s4 = gr.nh_sphere('s4', {-180, 50, -300}, 150)
scene_root:add_child(s4)
s4:set_material(mat2)

--[[
b1 = gr.nh_box('b1', {-100, -100, 100}, 200)
scene_root:add_child(b1)
b1:rotate('Y',-30)
b1:set_material(mat4)

c1 = gr.nh_cylinder('cyl1', {-100, -100, -200}, {0, 1, 1}, 200, 200)
scene_root:add_child(c1)
--c1:rotate('X',70)
c1:set_material(mat1)


c2 = gr.nh_cone('cone1', {-50, -200,-100}, 200, 400, 200)
scene_root:add_child(c2)
--c2:rotate('X',-30)
c2:set_material(mat2)
]]--

blue_light = gr.light({-100.0, 150.0, 400.0}, {0.3, 0.3, 0.9}, {1, 0, 0})
orange_light = gr.light({400.0, 100.0, 300.0}, {0.7, 0.0, 0.7}, {1, 0, 0})
white_light = gr.conelight({300, -1000.0, 200.0}, {0.0, 0.0, 0.0}, {1, 0, 0}, {0,0,-1}, 2, 0.8)

gr.render(scene_root, 'simple.png', 256, 256,
	  {0, 0, 800}, {0, 0, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {blue_light, orange_light})
