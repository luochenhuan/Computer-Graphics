mat1 = gr.material({0.7, 1.0, 0.7}, {0.5, 0.7, 0.5}, 25, 0)
mat2 = gr.material({0.5, 0.5, 0.5}, {0.5, 0.7, 0.5}, 25, 0)
mat3 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25, 0)


scene_root = gr.node('root')

s1 = gr.nh_sphere('s1', {-100, 0, 0}, 100)
scene_root:add_child(s1)
s1:set_material(mat3)
--s1:translate(-100,0,0)
s1:rotate('X', 90)

s2 = gr.nh_sphere('s2', {150, 0, -100}, 150)
scene_root:add_child(s2)
s2:set_material(mat2)

c1 = gr.nh_cylinder('cyl1', {0, -100, -200}, {0, 1, 0}, 200, 200)
scene_root:add_child(c1)
c1:set_material(mat1)

blue_light = gr.light({-200.0, 150.0, 400.0}, {0.3, 0.3, 0.9}, {1, 0, 0})
orange_light = gr.light({400.0, 100.0, 300.0}, {0.5, 0.0, 0.5}, {1, 0, 0})
white_light = gr.light({50.0, -300.0, 300.0}, {0.5, 0.5, 0.5}, {1, 0, 0})

gr.render(scene_root, '../img/hier_bbox_4.png', 256, 256,
	  {0, 0, 800}, {0, 0, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {blue_light, orange_light, white_light})
