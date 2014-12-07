-- need background set to simple background

mat1 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25, 0)
mat1_nm = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25, 0.3, 0, 'imgNormalMap', '../data/stone_normalmap.png')
mat3 = gr.material({.8, 0.5, 0.1}, {0.5, 0.7, 0.5}, 25, 0)
refractmat = gr.material({0.1, 0.1, 0.1}, {0.5, 0.7, 0.5}, 25, 0, 1.5)
chboard = gr.checker({0.3, 0.3, 0.3}, {0.5, 0.7, 0.5}, 25, 0, 0,{1,1,1},{0,0,0})
turb = gr.turbulence({0.3, 0.3, 0.3}, {0.5, 0.7, 0.5}, 20, 0, 0, 50, 5)

noise = gr.imgtex('../data/white_wall.png', {0.1, 0.1, 0.1}, {0.5, 0.7, 0.5}, 20, 0, 0, 'pNormalMap', 10, 2)
earth = gr.imgtex('../data/earth2.png', {0.0, 0.0, 0.0}, {0.5, 0.5, 0.5}, 20, 0, 0)

stone = gr.imgtex('../data/172.png', {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, 20, 0, 0)
stone_nm = gr.imgtex('../data/172.png', {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, 20, 0, 0,'imgNormalMap', '../data/172_norm.png')

poly = gr.imgtex('../data/poly.png', {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, 20, 0, 0)
poly_nm = gr.imgtex('../data/poly.png', {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, 20, 0, 0,'imgNormalMap', '../data/poly_norm.png')

brick = gr.imgtex('../data/brick.png', {0,0,0}, {0.5, 0.5, 0.5}, 20, 0.0, 0)
brick_nm = gr.imgtex('../data/brick.png', {0,0,0}, {0.5, 0.5, 0.5}, 20, 0.0, 0,'imgNormalMap', '../data/brick_nm.png')

wall_nm = gr.imgtex('../data/whitewall.png', {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, 20, 0, 0, 'imgNormalMap', '../data/stone_normalmap.png')
whitewall = gr.imgtex('../data/whitewall.png', {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, 20, 0, 0)

marble = gr.imgtex('../data/marble1.png', {0.0, 0.0, 0.0}, {0.3, 0.3, 0.3}, 10, 0, 0)
square_nm = gr.material({1, 0, 191.0/255}, {0.5, 0.7, 0.5}, 25, 0, 0,'imgNormalMap', '../data/brick_nm.png')


scene_root = gr.node('root')

col_1 = gr.node('col_1')
scene_root:add_child(col_1)
col_1:translate(-100, 0, 0)

col_2 = gr.node('col_2')
scene_root:add_child(col_2)
col_2:translate(100, 0, 100)

col_3 = gr.node('col_3')
--scene_root:add_child(col_3)
col_3:translate(100, 0, 100)

s1 = gr.nh_sphere('s1', {0, 0, 0}, 50)
col_1:add_child(s1)
s1:translate(-50, 240, 100)
s1:rotate('Y', 150)
s1:set_material(earth)

s2 = gr.nh_sphere('s2', {0, 0, 0}, 50)
col_1:add_child(s2)
s2:translate(-50, 100, 100)
s2:set_material(chboard)

s3 = gr.nh_sphere('s3', {0, 0, 0}, 500)
col_1:add_child(s3)
s3:translate(-50, -40, 100)
s3:scale(0.1,0.1,0.1)
s3:set_material(mat1)


s31 = gr.nh_sphere('s31', {0, 0, 0}, 500)
col_1:add_child(s31)
s31:translate(-50, -180, 100)
s31:scale(0.1,0.1,0.1)
s31:set_material(mat1_nm)


c1 = gr.nh_cylinder('cyl1', {0, 0, 0}, {0, 1, 0}, 100, 120)
col_2:add_child(c1)
c1:translate(0,210,0)
--c1:rotate('X',-10)
c1:scale(0.5,0.5,0.5)
c1:set_material(chboard)

c2 = gr.nh_cylinder('cyl2', {0, 0, 0}, {0, 1, 0}, 100, 120)
col_2:add_child(c2)
c2:translate(10,70,0)
c2:rotate('X',20)
c2:rotate('Z',20)
c2:scale(0.5,0.5,0.5)
c2:set_material(marble)

c3 = gr.nh_cylinder('cyl3', {0, 0, 0}, {0, 1, 0}, 100, 120)
col_2:add_child(c3)
c3:translate(0,-70,0)
-- c3:rotate('X',30)
c3:scale(0.5,0.5,0.5)
c3:set_material(turb)

c4 = gr.nh_cylinder('cyl4', {0, 0, 0}, {0, 1, 0}, 100, 120)
col_2:add_child(c4)
c4:translate(0,-210,0)
--c4:rotate('Y',30)
c4:scale(0.5,0.5,0.5)
c4:set_material(square_nm)


cone1 = gr.nh_cone('cone1', {0,0,0}, 50, 40, 40)
col_3:add_child(cone1)
cone1:translate(0,200,40)
cone1:rotate('X',-10)
cone1:set_material(marble)

cone2 = gr.nh_cone('cone2', {0,0,0}, 50, 40, 40)
col_3:add_child(cone2)
cone2:translate(0,70,0)
cone2:rotate('X',30)
cone2:set_material(marble)

cone3 = gr.nh_cone('cone3', {0,0,0}, 50, 40, 40)
col_3:add_child(cone3)
cone2:translate(0,-60,0)
-- c3:rotate('X',30)
cone3:set_material(turb)

cone4 = gr.nh_cone('cone4', {0,0,0}, 50, 40, 40)
col_3:add_child(cone4)
cone4:translate(0,-210,0)
--c4:rotate('Y',30)
cone3:set_material(square_nm)

------------------------------ background plane ------------------------------
p1 = gr.plane('planeback', {0,0,0},{1,0,0},{0,1,0}, 1000, 800)
scene_root:add_child(p1)
p1:translate(-500, -300, -400)
p1:set_material(brick_nm)

p2 = gr.plane('planebottom', {0,0,0},{1,0,0},{0,0,1}, 1000, 1000)
scene_root:add_child(p2)
p2:translate(-500, -300, -400)
p2:set_material(noise)

-- p3 = gr.plane('planeleft', {0,0,0},{0,0,1},{0,1,0}, 800, 800)
-- scene_root:add_child(p3)
-- p3:translate(-400, -300, -400)
-- p3:set_material(stone_nm)

green_light = gr.light({400.0, 100.0, 300.0}, {0.5, 0.7, 0.5}, {1, 0, 0})
orange_light = gr.light({-400.0, 100.0, 300.0}, {0.5, 0.0, 0.5}, {1, 0, 0})
white_light = gr.light({0.0, 100.0, 200.0}, {0.5, 0.5, 0.5}, {1, 0, 0})

gr.render(scene_root, '../img/texture_show_2.png', 1024, 1024,
	  {0, 0, 800}, {0, 0, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {white_light, green_light, orange_light})
