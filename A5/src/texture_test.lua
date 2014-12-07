
mat1 = gr.material({0.7, 1.0, 0.7}, {0.5, 0.7, 0.5}, 25, 0)
mat2 = gr.material({0.8, 0.4, 0.1}, {0.5, 0.7, 0.5}, 25, 0.5, 0, 'imgNormalMap', '../brickwork.png')
mat3 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25, 0.5)
mat4 = gr.material({0.0, 0.0, 0.0}, {0.5, 0.7, 0.5}, 25, 0, 1.33)
brick = gr.imgtex('../brick.png', {0.1, 0.1, 0.1}, {0.5, 0.7, 0.5}, 20, 0.1, 0, 'pNormalMap', 10, 2)
wall = gr.imgtex('../window2.png', {0.1, 0.1, 0.1}, {0.1, 0.1, 0.1}, 10, 0.1, 0)


scene_root = gr.node('root')

-- the floor
p1 = gr.plane('plane', {-350, -150, 50},{1,0,0},{0,1,0}, 300, 300)
scene_root:add_child(p1)
p1:translate(100, 50, -50)
--p1:rotate('Y',-45)
p1:scale(1,.5,1)
p1:set_material(wall)

white_light = gr.light({-300, 1000.0, 200.0}, {0.9, 0.9, 0.9}, {1, 0, 0})

gr.render(scene_root, 'texture_test.png', 256, 256,
	  {0, 0, 800}, {0, 0, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {white_light})
