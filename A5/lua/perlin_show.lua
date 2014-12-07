-- -- A simple scene with five spheres

mat1 = gr.material({0.4, 0.5, 0.4}, {0.5, 0.7, 0.5}, 25, 0)
mat2 = gr.material({0.5, 0.5, 0.5}, {0.5, 0.7, 0.5}, 25, 0)
mat3 = gr.material({0.3, 0.3, 0.3}, {0.5, 0.7, 0.5}, 20, 0.2)

turb1 = gr.turbulence({0.3, 0.3, 0.3}, {0.5, 0.7, 0.5}, 20, 0, 0, 100, 5, {1,1,1},{0.7,0.5,0})
turb2 = gr.turbulence({0.3, 0.3, 0.3}, {0.5, 0.7, 0.5}, 20, 0, 0, 50, 5, {1,1,1}, {0,0,1})

turb3 = gr.turbulence({0.3, 0.3, 0.3}, {0.5, 0.7, 0.5}, 20, 0, 0, 100, 10, {1,1,1},{0.1,0.6,0.8})
turb4 = gr.turbulence({0.3, 0.3, 0.3}, {0.5, 0.7, 0.5}, 20, 0, 0, 150, 5, {1,1,1}, {0.4,0,0.5})

chboard = gr.checker({0.3, 0.3, 0.3}, {0.5, 0.7, 0.5}, 25, 0, 0,{1,1,1},{0,0,0})
chboard_pl = gr.checker({0.3, 0.3, 0.3}, {0.1, 0.3, 0.1}, 5, 0, 0,{1,1,1},{0,0,0},'pNormalMap', 10000, 5)


wall = gr.imgtex('../data/brick.png', {0.1, 0.1, 0.1}, {0.5, 0.7, 0.5}, 20, 0, 0)
wall_pl = gr.imgtex('../data/brick.png', {0.1, 0.1, 0.1}, {0.5, 0.7, 0.5}, 20, 0, 0, 'pNormalMap', 1000, 2)
brick_nm = gr.imgtex('../data/brick.png', {0,0,0}, {0.5, 0.5, 0.5}, 20, 0.0, 0,'imgNormalMap', '../data/brick_nm.png')

scene_root = gr.node('root')
col_1 = gr.node('col_1')
scene_root:add_child(col_1)
col_1:translate(-100, 0, 0)

col_2 = gr.node('col_2')
scene_root:add_child(col_2)
col_2:translate(100, 0, 100)

s2 = gr.nh_sphere('s2', {0, 0, 0}, 50)
col_1:add_child(s2)
s2:translate(-50, 100, 100)
s2:set_material(turb3)

s3 = gr.nh_sphere('s3', {0, 0, 0}, 50)
col_1:add_child(s3)
s3:translate(-50, -40, 100)
s3:set_material(turb4)


c2 = gr.nh_cylinder('cyl2', {0, 0, 0}, {0, 1, 0}, 100, 120)
col_2:add_child(c2)
c2:translate(10,70,0)
c2:rotate('X',-20)
--c2:rotate('Z',20)
c2:scale(0.5,0.5,0.5)
c2:set_material(turb1)

c3 = gr.nh_cylinder('cyl3', {0, 0, 0}, {0, 1, 0}, 100, 120)
col_2:add_child(c3)
c3:translate(0,-70,0)
c3:rotate('X',30)
c3:scale(0.5,0.5,0.5)
c3:set_material(turb2)



p1 = gr.plane('planeback', {0,0,0},{1,0,0},{0,1,0}, 1000, 800)
scene_root:add_child(p1)
p1:translate(-500, -300, -400)
p1:set_material(wall_pl)

-- p2 = gr.plane('planeback2', {0,0,1},{1,0,0},{0,1,0}, 1000, 800)
-- scene_root:add_child(p2)
-- p2:translate(10, -300, -400)
-- p2:set_material(wall)


blue_light = gr.light({-100.0, 150.0, 400.0}, {0.3, 0.3, 0.9}, {1, 0, 0})
orange_light = gr.light({400.0, 100.0, 150.0}, {0.7, 0.0, 0.7}, {1, 0, 0})
white_light = gr.light({-200, 90.0, 250.0}, {0.9, 0.9, 0.9}, {1, 0, 0}, {1,-2,-1}, 2, 0.9)

gr.render(scene_root, '../img/perlin_show.png', 512, 512,
      {0, 0, 800}, {0, 0, -800}, {0, 1, 0}, 50,
      {0.3, 0.3, 0.3}, {blue_light,white_light})






-- scene_root = gr.node('root')
-- col_1 = gr.node('col_1')
-- scene_root:add_child(col_1)
-- col_1:translate(-100, 0, 0)

-- col_2 = gr.node('col_2')
-- scene_root:add_child(col_2)
-- col_2:translate(100, 0, 100)

-- s2 = gr.nh_sphere('s2', {0, 0, 0}, 50)
-- col_1:add_child(s2)
-- s2:translate(-50, 100, 100)
-- s2:set_material(chboard_pl)

-- s3 = gr.nh_sphere('s3', {0, 0, 0}, 50)
-- col_1:add_child(s3)
-- s3:translate(-50, -40, 100)
-- s3:set_material(chboard)

-- c1 = gr.nh_cylinder('cyl1', {0, 0, 0}, {0, 1, 0}, 100, 120)
-- col_2:add_child(c1)
-- c1:translate(0,210,0)
-- --c1:rotate('X',-10)
-- c1:scale(0.5,0.5,0.5)
-- c1:set_material(chboard)

-- c2 = gr.nh_cylinder('cyl2', {0, 0, 0}, {0, 1, 0}, 100, 120)
-- col_2:add_child(c2)
-- c2:translate(10,70,0)
-- c2:rotate('X',20)
-- c2:rotate('Z',20)
-- c2:scale(0.5,0.5,0.5)
-- c2:set_material(turb1)

-- c3 = gr.nh_cylinder('cyl3', {0, 0, 0}, {0, 1, 0}, 100, 120)
-- col_2:add_child(c3)
-- c3:translate(0,-70,0)
-- -- c3:rotate('X',30)
-- c3:scale(0.5,0.5,0.5)
-- c3:set_material(turb2)

-- c4 = gr.nh_cylinder('cyl4', {0, 0, 0}, {0, 1, 0}, 100, 120)
-- col_2:add_child(c4)
-- c4:translate(0,-210,0)
-- --c4:rotate('Y',30)
-- c4:scale(0.5,0.5,0.5)
-- c4:set_material(square_nm)


-- p1 = gr.plane('planeback', {0,0,0},{1,0,0},{0,1,0}, 1000, 800)
-- scene_root:add_child(p1)
-- p1:translate(-500, -300, -400)
-- p1:set_material(wall_pl)

-- p2 = gr.plane('planeback2', {0,0,1},{1,0,0},{0,1,0}, 1000, 800)
-- scene_root:add_child(p2)
-- p2:translate(10, -300, -400)
-- p2:set_material(wall)


-- blue_light = gr.light({-100.0, 150.0, 400.0}, {0.3, 0.3, 0.9}, {1, 0, 0})
-- orange_light = gr.light({400.0, 100.0, 150.0}, {0.7, 0.0, 0.7}, {1, 0, 0})
-- white_light = gr.light({-200, 90.0, 250.0}, {0.9, 0.9, 0.9}, {1, 0, 0}, {1,-2,-1}, 2, 0.9)

-- gr.render(scene_root, '../img/perlin_show_2.png', 1024, 1024,
-- 	  {0, 0, 800}, {0, 0, -800}, {0, 1, 0}, 50,
-- 	  {0.3, 0.3, 0.3}, {blue_light,white_light})