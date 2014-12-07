-- need background set to simple background

cola_tex = gr.imgtex('../data/coca-cola2.png', {0.3, 0.3, 0.3}, {0.3, 0.3, 0.3}, 10, 0, 0)
alum = gr.material({1, 0.3, 0.3}, {0.7, 0.7, 0.7}, 25, 0, 0)
refractmat = gr.material({0.1, 0.1, 0.1}, {0.5, 0.7, 0.5}, 25, 0, 1.5)
wall = gr.imgtex('../data/white_wall.png', {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, 20, 0, 0)


scene_root = gr.node('root')

beads = gr.node('bead')
--scene_root:add_child(beads)
beads:translate(0,0,300)

cola = gr.node('cola')
scene_root:add_child(cola)
cola:translate(0,0,100)

cola_cyl = gr.nh_cylinder('cola_cyl', {0, 0, 0}, {0, 1, 0}, 100, 300)
cola:add_child(cola_cyl)
cola_cyl:translate(0,-200,0)
cola_cyl:rotate('Y',20)
cola_cyl:set_material(cola_tex)

c2 = gr.nh_cone('cone1', {0, 0,0}, 100, 200, 20)
cola:add_child(c2)
c2:translate(0,100,0)
c2:set_material(alum)

c1 = gr.nh_cone('cola_cone', {0,0,0}, 100, 200, 20)
cola:add_child(c1)
c1:translate(0,-200,0)
c1:rotate('Z',180)
c1:set_material(alum)

------------------------------  bead ------------------------------

s2 = gr.nh_sphere('s2', {0, 0, 0}, 10)
--scene_root:add_child(s2)
s2:translate(0, 0,0)
s2:scale(0.8,1,1)
s2:set_material(refractmat)

randx = {-7 ,0,-14, 55, 30, -38, 2,  4,40}
randy = {-70,20,53,-30,-53, -30,-20,-110,30}


for i = 1,9 do
	an_bead = gr.node('bead' .. tostring(i))
	an_bead:translate(randx[i], randy[i], 0)
	--an_bead:rotate('Y', (i-1) * 15)
	beads:add_child(an_bead)
	an_bead:add_child(s2)
end


------------------------------ background plane ------------------------------
p1 = gr.plane('planeback', {0,0,0},{1,0,0},{0,1,0}, 1000, 800)
scene_root:add_child(p1)
p1:translate(-500, -300, -400)
p1:set_material(wall)

p2 = gr.plane('planebottom', {0,0,0},{1,0,0},{0,0,1}, 1000, 1000)
scene_root:add_child(p2)
p2:translate(-500, -300, -400)
p2:set_material(wall)

-- p3 = gr.plane('planeleft', {0,0,0},{0,0,1},{0,1,0}, 800, 800)
-- scene_root:add_child(p3)
-- p3:translate(-500, -300, -400)
-- p3:set_material(wall)

green_light = gr.light({400.0, 100.0, 100.0}, {0.5, 0.7, 0.5}, {1, 0, 0})
white_light = gr.light({0.0, 100.0, 0.0}, {0.5, 0.5, 0.5}, {1, 0, 0})

gr.render(scene_root, '../img/cola_bb.png', 256, 256,
	  {0, 0, 800}, {0, 0, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {white_light, green_light})
