require('readobj')
chair = gr.mesh('cello', readobj('../obj/dchair_obj.obj'))
chair:translate(0,-100,500)
chair:rotate('Y',-30)

-- stone = gr.material({0.8, 0.7, 0.7}, {0.0, 0.0, 0.0}, 0, 0)
-- grass = gr.material({0.1, 0.7, 0.1}, {0.0, 0.0, 0.0}, 0, 0)
-- hide = gr.material({0.84, 0.6, 0.53}, {0.3, 0.3, 0.3}, 20, 0)

-- root = gr.node('root')

-- chair = gr.mesh('cello', readobj('../obj/dchair_obj.obj'))
-- root:add_child(chair)
-- chair:set_material(stone)
-- chair:translate(0,-100,500)
-- chair:rotate('Y',-30)

-- blue_light = gr.light({-200.0, 150.0, 400.0}, {0.3, 0.3, 0.9}, {1, 0, 0})
-- orange_light = gr.light({400.0, 100.0, 300.0}, {0.5, 0.0, 0.5}, {1, 0, 0})
-- white_light = gr.light({50.0, -300.0, -800.0}, {0.5, 0.5, 0.5}, {1, 0, 0})

-- gr.render(root, 'chair_Test.png', 256, 256,
-- 	  {0, 0, 800}, {0, 0, -800}, {0, 1, 0}, 50,
-- 	  {0.3, 0.3, 0.3}, {white_light})
