--
-- CS488 -- Introduction to Computer Graphics
-- 
-- a3mark.lua
--
-- A very simple scene creating a trivial puppet.  The TAs will be
-- using this scene as part of marking your assignment.  You'll
-- probably want to make sure you get reasonable results with it!

rootnode = gr.node('root')


red =    gr.material({255, 0.0, 0.0},    { 25,  25,  25}, 10)
blue =   gr.material({0.0, 0.0, 255},    { 25,  25,  25}, 10)
green =  gr.material({0.0, 255, 0.0},    { 25,  25,  25}, 10)
white =  gr.material({255, 255, 255},    { 25,  25,  25}, 10)
yellow = gr.material({255, 255, 0.0},    { 25,  25,  25}, 10)
black =  gr.material({0.0, 0.0, 0.0},    { 25,  25,  25}, 30)

torso = gr.node('torso')
torso:translate(0.0,2.0,0.0)
	torsoS = gr.sphere('torsoS')
	torsoS:set_material(white)
	torsoS:scale(2.25, 3.0, 1.0)

torso:add_child(torsoS)
rootnode:add_child(torso)

head = gr.node('head')
head:translate(0.0, .75, 0.0)
	headS = gr.sphere('headS')
	headS:set_material(white)
	headS:scale(1.5, 1.5, 1.5)

	nose = gr.sphere('gr')
	nose:set_material(red)

	nose:translate(0.0, -0.5, 1.5)
	nose:scale(0.25, 0.25, 0.25)
head:add_child(headS)
head:add_child(nose)

neck = gr.node('neck')
neck:translate(0.0, 0.25, 0.0)
	neckS = gr.sphere('neckS')
	neckS:set_material(blue)
	neckS:scale(0.5, 0.75, 0.5)
neck:add_child(neckS)

shoulder =gr.node("shoulder")
shoulder:translate(0.0, 2.75, 0.0)
	shoulderS = gr.sphere('shoulderS')
	shoulderS:scale(3.5, 0.5, 1.0)
	shoulderS:set_material(green)
shoulder:add_child(shoulderS)

torso:add_child(shoulder)


-- Joint Points --
torsoJoint = gr.joint('torsoJoint', {-15.0, 0.0, 15.0}, {0.0,0.0,0.0})
torsoJoint:translate(0.0, 0.75, 0.0)
shoulder:add_child(torsoJoint)

neckJoint = gr.joint('neckJoint', {-20.0, 0.0, 20.0}, {-90.0, 0.0, 90.0})
neckJoint:translate(0.0, .75, 0.0)
neck:add_child(neckJoint)

shoulderLJoint = gr.joint('shoulderLJoint', {-90.0, 0.0, 90.0}, {-5.0, 0.0, 5.0})
shoulderLJoint:translate(-2.75, 0.0, 0.0)
shoulder:add_child(shoulderLJoint)

torsoJoint:add_child(neck)
neckJoint:add_child(head)

-----------[[         LEFT ARM           ]]---------
upperArmL = gr.node('upperArmL')
upperArmL:translate(-0.5, -2.0, 0.0)
	upperArmLS = gr.sphere('upperArmLS')
	upperArmLS:set_material(white)
	upperArmLS:scale(0.4, 2.25, 1.0)
upperArmL:add_child(upperArmLS)

shoulderLJoint:add_child(upperArmL)

elbowL = gr.joint('elbowL', {0.0, 0.0, 90.0}, {-5.0, 0.0, 5.0})
elbowL:translate(0.0, -1.125, 0.0)
upperArmL:add_child(elbowL)

foreArmL = gr.node('foreArmL')
foreArmL:translate(0.0, -1.125, 0.0)
	foreArmLS = gr.sphere('foreArmLS')
	foreArmLS:set_material(yellow)
	foreArmLS:scale(0.4, 2.25, 1.0)
foreArmL:add_child(foreArmLS)
elbowL:add_child(foreArmL)

wristL =gr.joint('wristL', {-30.0,0.0,30.0}, {-5.0, 0.0, 5.0})
wristL:translate(0.0, -2.25, 0.0)
foreArmL:add_child(wristL)

handL = gr.node('handL')
handL:translate(0.0, -0.625, 0.0)
	handLS = gr.sphere('handLS')
	handLS:set_material(white)
	handLS:scale(0.4,1.25,0.75)
handL:add_child(handLS)
wristL:add_child(handL)

-----------[[         RIGHT ARM           ]]---------
shoulderRJoint = gr.joint('shoulderRJoint', {-90.0, 0.0, 90.0}, {-5.0, 0.0, 5.0})
shoulderRJoint:translate(2.75, 0.0, 0.0)
shoulder:add_child(shoulderRJoint)

upperArmR = gr.node('upperArmR')
upperArmR:translate(0.5, -2.0, 0.0)
	upperArmRS = gr.sphere('upperArmRS')
	upperArmRS:set_material(white)
	upperArmRS:scale(0.4, 2.25, 1.0)
upperArmR:add_child(upperArmRS)
shoulderRJoint:add_child(upperArmR)

elbowR = gr.joint('elbowR', {0.0, 0.0, 90.0}, {-5.0, 0.0, 5.0})
elbowR:translate(0.0, -1.125, 0.0)
upperArmR:add_child(elbowR)

foreArmR = gr.node('foreArmR')
foreArmR:translate(0.0, -1.125, 0.0)
	foreArmRS = gr.sphere('foreArmRS')
	foreArmRS:set_material(yellow)
	foreArmRS:scale(0.4, 2.25, 1.0)
foreArmR:add_child(foreArmRS)
elbowR:add_child(foreArmR)

wristR =gr.joint('wristR', {-30.0,0.0,30.0}, {-5.0, 0.0, 5.0})
wristR:translate(0.0, -2.25, 0.0)
foreArmR:add_child(wristR)

handR = gr.node('handR')
handR:translate(0.0, -0.625, 0.0)
	handRS = gr.sphere('handRS')
	handRS:set_material(white)
	handRS:scale(0.4,1.25,0.75)
handR:add_child(handRS)
wristR:add_child(handR)

-----------[[         HIP           ]]---------
hip = gr.node('hip')
hip:translate(0.0, -2.0, 0.0)
	hipS = gr.sphere('hipS')
	hipS:set_material(green)
	hipS:scale(2.5, 1.0, 1.2)
hip:add_child(hipS)
torso:add_child(hip)

-----------[[         LEFT LEG           ]]---------
hipJointL = gr.joint('hipJointL', {-5.0, 0.0, 90.0}, {0.0,0.0,90.0})
hipJointL:translate(-1.75, 0.0,0.0)
hip:add_child(hipJointL)

thighL = gr.node('thighL')
thighL:translate(0.0, -2.0, 0.0)
	thighLS = gr.sphere('thighLS')
	thighLS:set_material(white)
	thighLS:scale(0.75, 2.25, 1.0)
thighL:add_child(thighLS)
hipJointL:add_child(thighL)

kneeJointL = gr.joint('kneeJointL', {0.0, 0.0, 90.0}, {-5.0, 0.0, 5.0})
kneeJointL:translate(0.0, -1.125, 0.0)
thighL:add_child(kneeJointL)

calfL = gr.node('calfL')
calfL:translate(0.0, -2.125, 0.0)
	calfLS = gr.sphere('calfLS')
	calfLS:set_material(yellow)
	calfLS:scale(0.75, 2.25, 1.0)
calfL:add_child(calfLS)
kneeJointL:add_child(calfL)

ankleJointL =gr.joint('ankleJointL', {-30.0,0.0,30.0}, {-5.0, 0.0, 5.0})
ankleJointL:translate(0.0, -2.25, 0.0)
calfL:add_child(ankleJointL)

footL = gr.node('footL')
footL:rotate('x', 90.0)
footL:rotate('y', 30.0)
footL:translate(-0.6, -0.2, 0.0)
	footLS = gr.sphere('footLS')
	footLS:set_material(green)
	footLS:scale(1.3,0.5,0.5)
footL:add_child(footLS)
ankleJointL:add_child(footL)

-----------[[         RIGHT LEG           ]]---------
hipJointR = gr.joint('hipJointR', {-5.0, 0.0, 90.0}, {0.0,0.0,90.0})
hipJointR:translate(1.75, 0.0,0.0)
hip:add_child(hipJointR)

thighR = gr.node('thighR')
thighR:translate(0.0, -2.0, 0.0)
	thighRS = gr.sphere('thighRS')
	thighRS:set_material(white)
	thighRS:scale(0.75, 2.25, 1.0)
thighR:add_child(thighRS)
hipJointR:add_child(thighR)

kneeJointR = gr.joint('kneeJointR', {0.0, 0.0, 90.0}, {-5.0, 0.0, 5.0})
kneeJointR:translate(0.0, -1.125, 0.0)
thighR:add_child(kneeJointR)

calfR = gr.node('calfR')
calfR:translate(0.0, -2.125, 0.0)
	calfRS = gr.sphere('calfRS')
	calfRS:set_material(yellow)
	calfRS:scale(0.75, 2.25, 1.0)
calfR:add_child(calfRS)
kneeJointR:add_child(calfR)

ankleJointR =gr.joint('ankleJointR', {-30.0,0.0,30.0}, {-5.0, 0.0, 5.0})
ankleJointR:translate(0.0, -2.25, 0.0)
calfR:add_child(ankleJointR)

footR = gr.node('footR')
footR:rotate('x', 90.0)
footR:rotate('y', -30.0)
footR:translate(0.6, -0.2, 0.0)
	footRS = gr.sphere('footRS')
	footRS:set_material(green)
	footRS:scale(1.3,0.5,0.5)
footR:add_child(footRS)
ankleJointR:add_child(footR)

return rootnode
