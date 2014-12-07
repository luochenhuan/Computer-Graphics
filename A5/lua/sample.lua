-- -- A simple scene with five spheres

mat1 = gr.material({0.4, 0.5, 0.4}, {0.5, 0.7, 0.5}, 25, 0)
mat2 = gr.material({0.5, 0.5, 0.5}, {0.5, 0.7, 0.5}, 25, 0)
mat3 = gr.material({0.3, 0.3, 0.3}, {0.5, 0.7, 0.5}, 20, 0.2)

turb1 = gr.turbulence({0.3, 0.3, 0.3}, {0.5, 0.7, 0.5}, 20, 0, 0, 50, 5)
turb2 = gr.turbulence({0.3, 0.3, 0.3}, {0.5, 0.7, 0.5}, 20, 0, 0, 50, 5)
chboard = gr.checker({0.3, 0.3, 0.3}, {0.5, 0.7, 0.5}, 25, 0, 0,{1,1,1},{0,0,0})
chboard_pl = gr.checker({0.3, 0.3, 0.3}, {0.1, 0.3, 0.1}, 5, 0, 0,{1,1,1},{0,0,0},'pNormalMap', 10000, 5)


wall = gr.imgtex('../data/brick.png', {0.1, 0.1, 0.1}, {0.5, 0.7, 0.5}, 20, 0, 0)
wall_pl = gr.imgtex('../data/brick.png', {0.1, 0.1, 0.1}, {0.5, 0.7, 0.5}, 20, 0, 0, 'pNormalMap', 1000, 2)
brick_nm = gr.imgtex('../data/brick.png', {0,0,0}, {0.5, 0.5, 0.5}, 20, 0.0, 0,'imgNormalMap', '../data/brick_nm.png')

scene_root = gr.node('root')
col_1 = gr.node('col_1')
scene_root:add_child(col_1)
col_1:translate(-100, 0, 0)


s3 = gr.nh_sphere('s3', {0, 0, 0}, 50)
col_1:add_child(s3)
s3:translate(-50, -40, 100)
s3:set_material(chboard_pl)


p1 = gr.plane('planeback', {0,0,0},{1,0,0},{0,1,0}, 1000, 800)
scene_root:add_child(p1)
p1:translate(-500, -300, -400)
p1:set_material(wall)


blue_light = gr.light({-100.0, 150.0, 400.0}, {0.3, 0.3, 0.9}, {1, 0, 0})
orange_light = gr.light({400.0, 100.0, 150.0}, {0.7, 0.0, 0.7}, {1, 0, 0})
white_light = gr.light({-200, 90.0, 250.0}, {0.9, 0.9, 0.9}, {1, 0, 0}, {1,-2,-1}, 2, 0.9)

gr.render(scene_root, '../img/non_perlin_show_aa.png', 256, 256,
	  {0, 0, 800}, {0, 0, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {blue_light,white_light})
