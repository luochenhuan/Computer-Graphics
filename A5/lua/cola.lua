-- need background set to simple background

cola_tex = gr.imgtex('../data/cola_zero1.png', {0.3, 0.3, 0.3}, {0.3, 0.3, 0.3}, 10, 0, 0)
alum = gr.material({0.3, 0.3, 0.3}, {0.7, 0.7, 0.7}, 25, 0, 0)
--refractmat = gr.material({0.1, 0.1, 0.1}, {0.5, 0.7, 0.5}, 25, 0, 1.5)
--wall = gr.imgtex('../data/white_wall.png', {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, 20, 0, 0)


--scene_root = gr.node('root')

cola = gr.node('cola')
-- scene_root:add_child(cola)
--cola:translate(0,0,100)

cola_cyl = gr.nh_cylinder('cola_cyl', {0, 0, 0}, {0, 1, 0}, 100, 300)
cola:add_child(cola_cyl)
cola_cyl:translate(0,-150,0)
cola_cyl:rotate('Y',-1)
cola_cyl:set_material(cola_tex)

c2 = gr.nh_cone('cone1', {0, 0,0}, 100, 200, 20)
cola:add_child(c2)
c2:translate(0,150,0)
c2:set_material(alum)

c1 = gr.nh_cone('cola_cone', {0,0,0}, 100, 200, 20)
cola:add_child(c1)
c1:translate(0,-150,0)
c1:rotate('Z',180)
c1:set_material(alum)

-- green_light = gr.light({400.0, 100.0, 100.0}, {0.5, 0.7, 0.5}, {1, 0, 0})
-- white_light = gr.light({0.0, 100.0, 0.0}, {0.5, 0.5, 0.5}, {1, 0, 0})

-- gr.render(scene_root, 'cola.png', 256, 256,
-- 	  {0, 0, 800}, {0, 0, -800}, {0, 1, 0}, 50,
-- 	  {0.3, 0.3, 0.3}, {white_light})
