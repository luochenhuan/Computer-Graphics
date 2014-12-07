-- A simple scene with five spheres

mat1 = gr.material({0.7, 1.0, 0.7}, {0.5, 0.7, 0.5}, 25)
mat2 = gr.material({0.5, 0.5, 0.5}, {0.5, 0.7, 0.5}, 25)
mat3 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25)

scene_root = gr.node('root')


b1 = gr.nh_box('b1', {80, -300, -200}, 200)
scene_root:add_child(b1)
b1:set_material(mat2)


blue_light = gr.light({-100.0, 150.0, 400.0}, {0.3, 0.3, 0.9}, {1, 0, 0})
orange_light = gr.light({400.0, 100.0, 150.0}, {0.7, 0.0, 0.7}, {1, 0, 0})
white_light = gr.conelight({0, 90.0, 80.0}, {0.9, 0.9, 0.9}, {1, 0, 0}, {1,-1,-1}, 2, 0.9)

gr.render(scene_root, 'conelight_test.png', 256, 256,
	  {0, 0, 800}, {0, 0, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {orange_light}, {white_light})
