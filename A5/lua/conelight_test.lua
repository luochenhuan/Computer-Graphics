-- -- A simple scene with five spheres

mat1 = gr.material({0.4, 0.5, 0.4}, {0.5, 0.7, 0.5}, 25, 0)
mat2 = gr.material({0.5, 0.5, 0.5}, {0.5, 0.7, 0.5}, 25, 0)
mat3 = gr.material({0.3, 0.3, 0.3}, {0.5, 0.7, 0.5}, 20, 0.2)

scene_root = gr.node('root')

b1 = gr.nh_box('b1', {0,0,0}, 200)
scene_root:add_child(b1)
b1:translate(-250, -200, -100)
b1:scale(2.5, 0.1, 2)
b1:set_material(mat2)

s2 = gr.nh_sphere('s2', {0, 0, 0}, 80)
scene_root:add_child(s2)
s2:translate(120, -100, 210)
s2:set_material(mat1)

b2 = gr.nh_box('b2', {0,0,0}, 100)
scene_root:add_child(b2)
b2:translate(-230, -200, 150)
b2:set_material(mat1)

blue_light = gr.light({-100.0, 150.0, 400.0}, {0.3, 0.3, 0.9}, {1, 0, 0})
orange_light = gr.light({400.0, 100.0, 150.0}, {0.7, 0.0, 0.7}, {1, 0, 0})
white_light = gr.light({-200, 90.0, 250.0}, {0.9, 0.9, 0.9}, {1, 0, 0}, {1,-2,-1}, 2, 0.9)

gr.render(scene_root, '../img/conelight_test.png', 1024, 1024,
	  {0, 0, 800}, {0, 0, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {blue_light,white_light})