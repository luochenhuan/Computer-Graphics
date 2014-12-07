-- A simple scene with five spheres

mat1 = gr.material({0.7, 1.0, 0.7}, {0.5, 0.7, 0.5}, 25)
mat2 = gr.material({0.5, 0.5, 0.5}, {0.5, 0.7, 0.5}, 25)
mat3 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25)

gold = gr.material({0.9, 0.8, 0.4}, {0.8, 0.8, 0.4}, 25)
grass = gr.material({0.1, 0.7, 0.1}, {0.0, 0.0, 0.0}, 0)
blue = gr.material({0.7, 0.6, 1}, {0.5, 0.4, 0.8}, 25)
red = gr.material({1, 0.6, 0.6}, {0.5, 0.4, 0.8}, 25)
white = gr.material({1, 1, 1}, {0.5, 0.4, 0.8}, 25)
brown = gr.material({101.0/255, 69.0/255, 34.0/255}, {0.8, 0.8, 0.2}, 2)

root = gr.node('root')


house = gr.node('house')
root:add_child(house)
house:translate(-8,-5,-10)
house:rotate('Y',-20)
house:scale(4,4,4)

h1 = gr.cube('h1')
house:add_child(h1)
h1:set_material(brown)
--h1:translate(-5,-2,0)
-- h1:translate(0, 0, 0)
-- h1:rotate('Y',-20)
-- h1:scale(1, 1, 2)

-- pyramid
require('pyramid')
house:add_child(pyramid)
pyramid:set_material(brown)
pyramid:translate(-0.5,1,1.5)
-- pyramid:rotate('Y',-40)
pyramid:scale(2, 4, 2)

mm = gr.node('mm')
root:add_child(mm)
mm:translate(3,0,0)
-- mm:rotate('Y',-90)


-- mickey head
require('mickey')
mickey:set_material(mat3)
mickey:rotate('Z', -90)
mickey:rotate('Y', -90)
mickey:scale (5.0, 5.0, 5.0)
mm:add_child(mickey)

-- mickey body
body = gr.sphere('body')
body:set_material(red)
mm:add_child(body)
body:translate(2.5,-0.8,2.5)
body:scale (1, 1.5, 1)

-- mickey limbs
lh = gr.sphere('lh')
lh:set_material(white)
mm:add_child(lh)
lh:translate(3.5,-0.2,2.5)
lh:rotate('Z', -45)
lh:scale (0.5, 1.5, 0.5)

rh = gr.sphere('rh')
rh:set_material(white)
mm:add_child(rh)
rh:translate(1.5,-0.2,2.5)
rh:rotate('Z', 45)
rh:scale (0.5, 1.5, 0.5)


-- fench
fench = gr.node('fench')
fench:rotate('Y', 20)
fench:translate(-11,-4, 5)
fench:scale(0.7,0.7,0.7)

f1 = gr.sphere('f1')
fench:add_child(f1)
f1:set_material(blue)
f1:scale(0.5, 3, 0.5)

-- cylinder
require('cylinder')
fench:add_child(cylinder)
cylinder:set_material(mat1)
cylinder:translate(-1.0, 0.2, 0.1)
cylinder:rotate('Z', -90)
cylinder:scale (.5, 2.0, 0.6)

for i = 1,6 do
   an_fench = gr.node('fench' .. tostring(i))
   an_fench:rotate('Y', (i-1) * 15)
   -- an_fench:translate((i-1) * 2, 0, 0)
   root:add_child(an_fench)
   an_fench:add_child(fench)
end

-- grass
plane = gr.mesh('plane', {
	{-1, 0, -1},
	{ 1, 0, -1},
	{1,  0, 1},
	{-1, 0, 1},
     }, {
	{3, 2, 1, 0}
     })
root:add_child(plane)
plane:set_material(grass)
plane:translate(0,-5,-80)
plane:scale(200, 200, 200)


sun = gr.light({-100.0, 100.0, 200.0}, {0.9, 0.9, 0.9}, {1, 0, 0})
-- sun = gr.light({400.0, 100.0, 150.0}, {0.95, 0.75, 0.60}, {1, 0, 0})

gr.render(root, 'self.png', 512, 512,
	  {0, 0,30}, {0, 0, -1}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {sun})

