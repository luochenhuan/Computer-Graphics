-- need background set to simple background
laptopalum = gr.material({0.8, 0.8, 0.8}, {0.7, 0.7, 0.7}, 25, 0, 0)
topmac = gr.imgtex('../data/mac_screen2.png', {0.1, 0.1, 0.1}, {0.5, 0.5, 0.5}, 10, 0, 0)
lowmac = gr.imgtex('../data/mbp_keyboard2.png', {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, 10, 0, 0)


laptop = gr.node('laptop')
laptop:rotate('Y',-30)

lap = gr.cuboid('lap', {0, 0, 0}, 80, 2, 60)
laptop:add_child(lap)
lap:set_material(laptopalum)

lap_plane = gr.plane('low_plane', {0,3,0},{1,0,0},{0,0,1}, 80, 60)
laptop:add_child(lap_plane)
lap_plane:set_material(lowmac)


top_all = gr.node('top_all')
laptop:add_child(top_all)
top_all:translate(0,2,0)
top_all:rotate('X',-30)

top = gr.cuboid('top', {0, 0, 0}, 80, 60, 2)
top_all:add_child(top)
top:set_material(laptopalum)

top_plane = gr.plane('top_plane', {0,0,3},{1,0,0},{0,1,0}, 80, 60)
top_all:add_child(top_plane)
top_plane:set_material(topmac)

-- green_light = gr.light({400.0, 100.0, 400.0}, {0.5, 0.7, 0.5}, {1, 0, 0})
-- white_light = gr.light({0.0, 300.0, 400.0}, {0.5, 0.5, 0.5}, {1, 0, 0})

-- gr.render(scene_root, 'laptop.png', 1024, 1024,
-- 	  {0, 0, 800}, {0, 0, -800}, {0, 1, 0}, 50,
-- 	  {0.3, 0.3, 0.3}, {green_light, white_light})
