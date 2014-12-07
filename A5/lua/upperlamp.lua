
upperlamptex = gr.material({1, 251.0/255, 240.0/255}, {0.7, 0.7, 0.7}, 25, 0, 0)
alum = gr.material({0.3, 0.3, 0.3}, {0.7, 0.7, 0.7}, 25, 0, 0)
white = gr.imgtex('../data/white_wall.png', {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, 20, 0, 0, 'imgNormalMap', '../data/concrete_nm.png')
-- scene_root = gr.node('root')


------------------------------ background plane ------------------------------
-- room_cube = gr.node('room_cube')
-- scene_root:add_child(room_cube)
-- room_cube:translate(-400, -300, -400)


-- p1 = gr.plane('planeback', {0,0,0},{1,0,0},{0,1,0}, 2000, 1000)
-- room_cube:add_child(p1)
-- p1:set_material(whitewall)


-- p2 = gr.plane('planebottom', {0,0,0},{1,0,0},{0,0,1}, 2000, 1000)
-- room_cube:add_child(p2)
-- p2:set_material(floorwood)

-- p3 = gr.plane('planeleft', {0,0,0},{0,0,1},{0,1,0}, 1000, 1000)
-- room_cube:add_child(p3)
-- p3:set_material(brick_nm)

-- p4 = gr.plane('planeup', {0,0,0},{1,0,0},{0,0,1}, 2000, 1000)
-- room_cube:add_child(p4)
-- p4:translate(0, 800, 0)
-- p4:set_material(wall)


upperlamp = gr.node('upperlamp')
-- upperlamp:translate(300,600,100)

string = gr.nh_cylinder('string', {0, 0, 0}, {0, 1, 0}, 5, 200)
upperlamp:add_child(string)
string:translate(0,0,0)
-- string:rotate('Y',20)
string:set_material(alum)

---------------------------  lamp -------------------------------------
conelamp = gr.nh_cone('conelamp', {0,0,0}, 100, 100, 60)
upperlamp:add_child(conelamp)
conelamp:translate(0, 0, 0)
conelamp:set_material(upperlamptex)

ball = gr.nh_sphere('ball', {0, 0, 0}, 20)
upperlamp:add_child(ball)
ball:translate(0, 2, 0)
ball:set_material(white)

--------------------------- lights -------------------------------------
-- blue_light = gr.light({-100.0, 150.0, 400.0}, {0.3, 0.3, 0.9}, {1, 0, 0})
-- orange_light = gr.light({600.0, 100.0, 300.0}, {0.6, 0.3, 0.6}, {1, 0, 0})
-- -- white_light = gr.light({-300, 600.0, 200.0}, {0.9, 0.9, 0.9}, {1, 0, 0})
-- -- white_conelight = gr.light({0, 40.0, 0.0}, {1.0, 1.0, 1.0}, {1, 0, 0}, {0,-1,0}, 5, 0.95)
-- white_light = gr.light({-300, 400.0, -380.0}, {0.9, 0.9, 0.9}, {1, 0, 0})


-- gr.render(scene_root, '../img/upperlamp.png', 256, 256,
-- 	  {0, 0, 800}, {0, 0, -800}, {0, 1, 0}, 50,
-- 	  {0.3, 0.3, 0.3}, {white_light,orange_light}) 
