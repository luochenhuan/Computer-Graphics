require('readobj')

-- purple = gr.material({0.9, 0.1, 0.9}, {0.0, 0.0, 0.0}, 0, 0)
cellwood = gr.material({102.0/255, 51.0/255, 0.1}, {0.0, 0.0, 0.0}, 0, 0)

root = gr.node('root')

cello = gr.mesh('cello', readobj('../obj/cello.obj'))
root:add_child(cello)
cello:set_material(cellwood)
--cello:rotate('Y',90)
cello:translate(40, 100, 20)
cello:scale(50, 50, 50)

blue_light = gr.light({-100.0, 150.0, 400.0}, {0.3, 0.3, 0.9}, {1, 0, 0})
orange_light = gr.light({400.0, 100.0, 300.0}, {0.7, 0.0, 0.7}, {1, 0, 0})
-- white_light = gr.light({-300, 600.0, 200.0}, {0.9, 0.9, 0.9}, {1, 0, 0})
-- white_conelight = gr.light({0, 40.0, 0.0}, {1.0, 1.0, 1.0}, {1, 0, 0}, {0,-1,0}, 5, 0.95)
white_light = gr.light({-300, 400.0, -380.0}, {0.9, 0.9, 0.9}, {1, 0, 0})

gr.render(root, '../img/cello_Test.png', 256, 256,
	  {0, 0, 800}, {0, 0, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {white_light})
