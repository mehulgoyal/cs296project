/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
 * Base code for CS 296 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */


#include "cs296_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs296
{
  dominos_t::dominos_t()
  {
    //Ground
    //!<B>1. Ground </B>
    /*! For the ground we keep a variable of type b2Body, and retain a pointer "b1" to it. 
    The variable "shape" with type <B>b2EdgeShape</B>, used as a fixture to a body, ground. It basically used to create edges.
    The type <B>b2Vec2</B> defines a vertex and the "ground" is defined as an edge with start-vertex:(-90m,0m) and end-vertex:(90m,0m).
    The variable "bd" of type <B>b2BodyDef</B> is created and attaches the ground object to the world object.
    */
    b2Body* b1;
    {
      b2EdgeShape shape;
      shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f));
	
      b2BodyDef bd;
      b2FixtureDef fixdef;
      fixdef.shape=&shape;
      fixdef.friction=1.0;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&fixdef);
    }
      
    //Top horizontal shelf
    //!<B>2. Top horizontal shelf</B>
    /*!
    Variable "shape", type b2PolygonShape is defined, to set the fixtures to the shelf.
    Variable "bd", type b2BodyDef is used to define the shelf object so that the shelf could be created by passing to world object
    The shelf is a aligned box assigned center (-31m,30m) using position.Set, and dimensions 12m x 0.5m using SetAsBox.
    "ground" points to the shelf object of type b2Body, which is created by passing to the world object. 
    The density of the self is 0, so mass of the object is 0.\
    */
    {
      b2PolygonShape shapebox;
      shapebox.SetAsBox(10.0f, 0.25f);
	
	  b2FixtureDef fd;
      fd.shape = &shapebox;
      fd.density = 0.0f;
      fd.friction = 1.0f;
	
      b2BodyDef bd;
      bd.position.Set(-30.0f, 40.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&fd);
    }

    //Dominos
    //!<B>3. Dominos </B>
    /*!
    10 Dominos are kept on the top shelf which are knocked off by a pendulum.
    Variable "shape", type b2PolygonShape is used to define rectangular domino shape with dimensions 0.2mx2m.
    Variable "fd", type b2PolygonShape for fixtures of a domino. It is here we set its density=20 and friction coeff=0.1
    Then we pass the domino object to the world object as variable "bd", type b2BodyDef to create the domino.
    This process is repeated 10 times (in the <I>for</I> loop) to create 10 dominos.
    */
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.06f, 1.0f);
	
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 40.0f;
      fd.friction = 1.0f;
		
      for (int i = -1; i < 9; ++i)
	{
	  b2BodyDef bd;
	  bd.type = b2_dynamicBody;
	  bd.position.Set(-36.5f + 1.8f *i, 41.25f);
	  b2Body* body = m_world->CreateBody(&bd);
	  body->CreateFixture(&fd);
	}
    }
    
    
    //The two spheres- ek aur ghusana hai left mein
    /*!
      Two spheres are kept on the horizontal platform, which are knocked by the top-left pivoted-platform.
      Variable of type <b>b2Body</b> defines the object "spherebody".
      The fixtures "ballfd" and "ballfd2", shape="circle" and radius="0.5" are attached to "spherebody".
      Attributes of fixture "ballfd" are : density=250, friction=0.9, restitution=0.8, position=(-39.0,30.9).
      Attributes of fixture "ballfd2" are : density=595, friction=0.9, restitution=0.8, position=(-26.0,30.9).
    */
	{
      b2Body* spherebody;
	
      b2CircleShape circle;
      circle.m_radius = 0.5;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 250.0f;
      ballfd.friction = 0.9f;
      ballfd.restitution = 0.8f;
      
      b2FixtureDef ballfd2;
      ballfd2.shape = &circle;
      ballfd2.density = 595.0f;
      ballfd2.friction = 0.9f;
      ballfd2.restitution = 0.8f;
      
   /*   b2FixtureDef ballfd3;
      ballfd3.shape = &circle;
      ballfd3.density = 200.0f;
      ballfd3.friction = 0.2f;
      ballfd3.restitution = 0.1f;
	*/
      
	
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(-39.0, 30.9f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	  
      b2BodyDef ballbd2;
	  ballbd2.type = b2_dynamicBody;
	  ballbd2.position.Set(-30.5f + 4.0, 30.9f);
	  spherebody = m_world->CreateBody(&ballbd2);
	  spherebody->CreateFixture(&ballfd2);
	  
	/*  b2BodyDef ballbd1;
	  ballbd1.type = b2_dynamicBody;
	  ballbd1.position.Set(-33.5f + 9.0, 30.9f);
	  spherebody = m_world->CreateBody(&ballbd1);
	  spherebody->CreateFixture(&ballfd3);
	*/
    }
    //vertical frictionless hinge
    /*!
      Variable "bd" is a dyanamic <b>b2BodyDef</b> object, with type <b>b2_dynamicBody</b>.
      Position of "bd" is (-40.6,33.9), and its used to create a <b>b2Body</b> object, where body1 is the pointer.
      A fixture "fd" is defined using <b>b2FixtureDef</b> with attributes : shape=<b>b2PolygonShape</b>, density=150.0.
      Fixture "fd" is attached to "body1" defined above.
      A fixture "ballfd" is defined using <b>b2FixtureDef</b>  with attributes : shape="circleshape"(type=<b>b2CircleShape</b>,radius=0.2),
           density=1000.0, friction=0.0, restitution=1.0.
      Fixture "ballfd" is attached to body pointed by "body2", created by passing body "bd2"(type=<b>b2BodyDef</b>) to "CreateBody()" function.
      The position of object corresponding to "body2" is (-40.6,38.0).
      Finally, both bodies corresponding to "body1" and "body2" are connected by a revolute joint "jointDef"(type=<b>b2RevoluteJointDef</b>) 
          with corresponding anchors at (0.0,-2.9) and (0.0) .
    */
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.2f, 4.35f);
      b2BodyDef bd;
      bd.position.Set(-40.6f, 33.9f);
      bd.type = b2_dynamicBody;
      b2Body* body1 = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 150.0f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body1->CreateFixture(fd);
      
      b2CircleShape circleShape;
	  circleShape.m_radius = 0.2;  
      b2BodyDef bd2;
      bd2.position.Set(-40.6f, 38.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);
      b2FixtureDef ballfd;
      ballfd.shape = &circleShape;
      ballfd.density = 1000.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 1.0f;
      body2->CreateFixture(&ballfd);

      b2RevoluteJointDef jointDef;
      
      jointDef.bodyA = body1;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0.0f,-2.9f);
      jointDef.localAnchorB.Set(0,0);
      //jointDef.maxMotorTorque = 100.0f;
      //jointDef.motorSpeed = 23.0f;
      //jointDef.enableMotor = true;
      jointDef.collideConnected = false;
      //default was false
      m_world->CreateJoint(&jointDef);
    
    }
    //platform for the spheres
    /*!
      The platform for the spheres is created by passing the body "bd"(defined using <b>b2BodyDef</b>) object to the <b>m_world->CreateBody()</b> function, 
          which attaches it to the ground object pointed by "ground"(type=<b>b2Body</b>).
      A Fixture "surface" is created which is a box(<b>b2PolygonShape</b> pbject shape) of dimensions (9.5,0.25) {formed using "SetAsBox" function},
          density=0.0,friction=0.0,restitution=1.0 .
      Fixture "surface" is fixed to the body object pointed by "ground" .
    */
    {
      b2PolygonShape shape;
      shape.SetAsBox(9.5f, 0.25f);
      
      b2FixtureDef surface;
      surface.shape = &shape;
      surface.density = 0.0f;
      surface.friction = 0.0f;
      surface.restitution = 1.0f;
	
      b2BodyDef bd;
      bd.position.Set(-30.0f, 30.4f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&surface);
    }    
    //reflector for ball
    /*!
      For reflection the balls, a fixed object is created by passing the <b>b2BodyDef</b> object "bd" to the ground object pointed by "ground".
      The position of "bd" is (-13.7,27.4) .
      Also the fixture "reflect" is defined using <b>b2FixtureDef</b> with attributes: shape {<b>b2PolygonShape</b> object, dimensions= (0.3,4.25) using <b>SetAsBox()</b> function},
          density=0.0, friction=0.0, restitution=1.0  .
      The fixture "reflect" is then attached to the ground object pointed using "ground" .
    */
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.3f, 4.25f);
      
      b2FixtureDef reflect;
      reflect.shape = &shape;
      reflect.density = 0.0f;
      reflect.friction = 0.0f;
      reflect.restitution = 1.0f;
	
      b2BodyDef bd;
      bd.position.Set(-13.7f, 27.4f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&reflect);
    }
     //side slant platform1
    /*!
      Here we create the curved surface by using multiple platform object with proper dimensions and alignments. 
      Basically, we create the curved surfaces using small lines spaced closely {using a "for" loop}so that the curves are approximated to curves made from points.
      Firstly, we define a body using <b>b2Body</b> pointed by "basecurve1", then we define a shape using curveEdgeShape {type <b>b2EdgeShape</b>}.
      The object curveDef, type <b>b2BodyDef</b> is used to create a body object in the world by passing to "basecurve1".
      The fixture "lowrest" is defined ,using <b>b2FixtureDef</b>, locally in each iteration with attributes : 
          shape="curveEdgeShape" {whose parameters are modified each iteration governed by (x,y) values in that iteration} , friction=0.0, 
          restitution=0.0  {restitution=0.0 helps to make a smooth movement of ball across the curve} .
    */
      {
      b2Body* basecurve1;
      
      float32 x = -30.3f;
      float32 y = 28.0f;
      for(int i = 0 ; i < 10 ; i++){
		  b2EdgeShape curveEdgeShape;
		  b2BodyDef curveDef;
        curveEdgeShape.Set(b2Vec2(x,y) , b2Vec2(x+(i+2)*0.28 , y-(9-i)*0.621024));
        x = x+(i+2)*0.28;
        y = y-(9-i)*0.621024;
        b2FixtureDef lowrest;
        lowrest.shape= &curveEdgeShape;
        lowrest.density= 0.0f;
        lowrest.friction= 0.0f;
        lowrest.restitution= 0.0f;
        basecurve1 = m_world->CreateBody(&curveDef);
        basecurve1->CreateFixture(&lowrest);
      }
    }
    
    //motor to set in motion
    /*!
      Here we create the top motor-driven platform which initializes the simulation.
      The object "bd", defined using <b>b2BodyDef</b> with position (-18.99,41.9) is passed to the world and the body object, pointed by "body1", is formed .
      Then, a fixture is created with pointer "fd" and attributes : shape=<b>b2PolygonShape</b> object created using <b>SetAsBox()</b> dimensions=(0.2,3.15), 
          density=455.0 .
      The fixture "fd" is attached to "body1" .
      Another body with pointer "body2" is created by passing object "bd2" {defined using <b>b2BodyDef</b>}, position = (-18.99,41.9) .
      The Fixture "ballfd" is defined using <b>b2FixtureDef</b> and attributes : shape="circleShape" {type=<b>b2CircleShape</b>, radius=0.2}, 
          density=38.0, friction= 0.0, restitution=1.0 .
      The Fixture "ballfd" is then is attached to the body referenced by "body2".
      Finally a revolute joint, type=<b>b2RevoluteJointDef</b> is created with its attributes as : {first body}bodyA="body1", {second body}bodyB="body2", 
          {anchor for body1} localAnchorA=(0.0,0.0), {anchor for body2} localAnchorA=(0,0), {maximum torque of the attached motor} maxMotorTorque=10000.0,
          {maximum motor speed} motorSpeed=-236.0, {enabler of the motor, motor starts as soon as its set to true} enableMotor=true, 
          {whether the two bodies connected by the revolute joint are allowed to collide} collideConnected=false .
      Finally the joint is created by passing it to the "m_world" . 
    */
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.2f, 3.15f);
      b2BodyDef bd;
      bd.position.Set(-18.99f, 41.9f);
      bd.type = b2_dynamicBody;
      b2Body* body1 = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 455.0f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body1->CreateFixture(fd);
      
      b2CircleShape circleShape;
	  circleShape.m_radius = 0.2;  
      b2BodyDef bd2;
      //bd2.type = b2_dynamicBody;
      bd2.position.Set(-18.99f, 41.9f);
      b2Body* body2 = m_world->CreateBody(&bd2);
      b2FixtureDef ballfd;
      ballfd.shape = &circleShape;
      ballfd.density = 38.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 1.0f;
      body2->CreateFixture(&ballfd);

      b2RevoluteJointDef jointDef;
      
      jointDef.bodyA = body1;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0.0f, 0.0f);
      jointDef.localAnchorB.Set(0,0);
      jointDef.maxMotorTorque = 10000.0f;
      jointDef.motorSpeed = -236.0f;
      jointDef.enableMotor = true;
      jointDef.collideConnected = false;
      //default was false
      m_world->CreateJoint(&jointDef);
    
    }
    
    //right platform with heavy ball, the slants . 
    /*!<h3>Right platform with the heavy ball. </h3>
      <p>Firstly a Fixture "surface", type <b>b2FixtureDef</b> is defined, its attributes are : shape = <b>b2PolygonShape</b> object 
          <b>shape</b> which is formed using SetAsBox() with dimensions=(3.5,0.25), density = 0.0, friction=0.0, restitution=1.0 .<br>
      Then a <b>b2BodyDef</b> object is passed to the ground object, pointed by "ground" . Its dimensions are (-12.2,39.4) .<br>
      The fixture "surface" is also attached to the ground object .<br>
      A body with pointer "spherebody", type <b>b2Body</b> is defined and after that a <b>b2CircleShape</b> object defines a shape object "circle" with radius=0.7 .
      A Fixture "ballfd", type <b>b2FixtureDef</b> is defined and passed the following attributes : shape = "circle", density=250.0, friction=0.2, restitution=0.835 .
      Then the body object represented by "spherebody" is assigned a body object "ballbd", type <b>b2BodyDef</b> with type=<b>b2_dynamicBody</b> {dynamic body type},
          position=(-15.7,41.1) .
      Also the fixture "ballfd" is assigned to the body-object represented by "spherebody" .
      After that body object represented by "slant", type <b>b2Body</b> is defined, then an edge "slantShape", type <b>b2EdgeShape</b> is defined,
           with end points : (-8.7,39.4) and (23,35.4) {where points are represented by "b2Vec"} .
      This <b>b2EdgeShape</b> object "slantShape" is used while defining the Fixture "slantfric", type <b>b2FixtureDef</b> and attributes : shape="slantShape", 
          density = "0.0", friction="0.3", restitution=0.5 .
      This Fixture is attached to the body object "slant" .
      Then the body object represented by "slant2", type <b>b2Body</b> is defined, then an edge "slantShape2", type <b>b2EdgeShape</b> is defined,
           with end points : (32,39.4) and (26.8,25.4) {where points are represented by "b2Vec"} .
      This <b>b2EdgeShape</b> object "slantShape2" is used while defining the Fixture "slantfric2", type <b>b2FixtureDef</b> and attributes : shape="slantShape2", 
          density = "0.0", friction="0.3", restitution=0.5 .
      This Fixture is attached to the body object "slant2" .</p>
    */
    {
      b2PolygonShape shape;
      shape.SetAsBox(3.5f, 0.25f);
      
      b2FixtureDef surface;
      surface.shape = &shape;
      surface.density = 0.0f;
      surface.friction = 0.0f;
      surface.restitution = 1.0f;
	
      b2BodyDef bd;
      bd.position.Set(-12.2f, 39.4f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&surface);
      
      b2Body* spherebody;
      b2CircleShape circle;
      circle.m_radius = 0.7f;
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 250.0f;
      ballfd.friction = 0.2f;
      ballfd.restitution = 0.835f; 
      b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(-15.7, 39.4 + 0.7f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	  
	  b2Body* slant;
	  b2EdgeShape slantShape;
	  slantShape.Set(b2Vec2(-8.7,39.4) , b2Vec2(23,35.4));
	  b2BodyDef curveDef;
	  b2FixtureDef slantfric;
      slantfric.shape = &slantShape;
      slantfric.density = 0.0f;
      slantfric.friction = 0.3f;
      slantfric.restitution = 0.5f; 
	  slant = m_world->CreateBody(&curveDef);
	  slant->CreateFixture(&slantfric);
	  
	  b2Body* slant2;
	  b2EdgeShape slantShape2;
	  slantShape2.Set(b2Vec2(32,39.4) , b2Vec2(26.8,25.4));
	  b2BodyDef curveDef2;
	  b2FixtureDef slantfric2;
      slantfric2.shape = &slantShape2;
      slantfric2.density = 0.0f;
      slantfric2.friction = 1.0f;
      slantfric2.restitution = 0.3f; 
	  slant2 = m_world->CreateBody(&curveDef2);
	  slant2->CreateFixture(&slantfric2);
    }  
    
    //platform holding train of spheres to be triggered, and the train of spheres
    /*!<h3>Platform holding train of spheres to be triggered, and the train of spheres</h3>
      Here we create a train of 10 spheres kept on the platform .<br>
      The object "ballbd" defines the body for a sphere and is passed to the world to create body.<br>
      The object "ballfd" is a fixture for a sphere with body definition given by "ballbd".<br> 
      Here is a description of objects defined for this system :
          "shape" {type=<b>b2PolygonShape</b>, <b>SetAsBox()</b> used to set dimensions to (9.0,0.25) . <br>
          "bd" :type=<b>b2BodyDef</b>, defines a body-object with position(9.0,27.9) . <br>
          "spherebody" :pointer of type <b>b2Body</b> defines the main body object. <br>
          "circle" : type <b>b2CircleShape</b>, defines a shape type circle and radius=0.5 <br>
          "ballfd" : type <b>b2FixtureDef</b>, defines a fixture with attributes : shape="circle", density=150.0, friction=0.0, restitution=0.0 .<br>
          "ballbd" : type <b>b2BodyDef</b>, type <b>b2_dynamicBody</b>, used to define a dynamic body locally for each iteration .<br>
      The body object "bd" is assigned to "ground" and also a fixture is fixed to "ground" with shape : "shape" .<br>
      Also "ballbd" is used to assign a ball to the body object "spherebody", each time the iteration is run, and at the same time 
          fixture "ballfd" is also attached to it.<br>
    */
    {
		b2PolygonShape shape;
      shape.SetAsBox(9.0f, 0.25f);
      
      b2BodyDef bd;
      bd.position.Set(9.0, 27.9f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
      
      
      b2Body* spherebody;
	
      b2CircleShape circle;
      circle.m_radius = 0.5;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 150.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
	
      for (int i = 4; i < 14; ++i)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(5.0f + i*1.0f-0.5, 28.4f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	}
    
	}
	
	//high-torque motor to force the balls in the bucket
  /*!<h3> High Torque motor driven revolving plank for guiding the train of spheres .</h3> 
    <p>This is a system consisiting of a motor driven platform which directs the train of balls, coming down the curve, to the bucket or the left open box .<br>
    The platfrom "body1" is hinged with a small circle "body2", and the motor appplies torque which increases its speed upto its maxspeed .<br> 
    Here is a description of objects defined for this system 
          "shape" : type <b>b2PolygonShape</b>, <b>SetAsBox()</b> used to set dimensions to (0.2,3.99) .</br>
          "bd" : type <b>b2BodyDef</b>, type=<b>b2_dynamicBody</b>, defines a body-object with position(-5.5, 14.0) .</br>
          "body1" : pointer of type=<b>b2Body</b> , assigned the body created by passing "bd" to <b>m_world->CreateBody()</b> .</br>
          "fd" {type <b>b2FixtureDef</b>, defines a fixture with attributes : shape="shape", density=500.0 .</br>
          "circleShape" : type <b>b2CircleShape</b>, defines a shape type circle and radius="0.2" .</br>
          "bd2" : type <b>b2BodyDef</b>, type=<b>b2_dynamicBody</b>, defines a body-object with position(-5.5, 16.0) .</br>
          "body2" : pointer of type <b>b2Body</b> , assigned the body created by passing "bd2" to <b>m_world->CreateBody()</b> </br>
          "ballfd" : type <b>b2FixtureDef</b>, defines a fixture with attributes : shape="circleShape", density=38.0, friction=0.0, restitution=1.0 </br>
          "jointDef" : type <b>b2RevoluteJointDef</b>, its a revolute joint with attributesa as : bodyA="body1", bodyB="body2" .</br>
              anchor for body1 : localAnchorA=(0.0f, 0.0f) , anchor for body2 : localAnchorB=(0.0, 0.0) , max torque allowed for motor : maxMotorTorque=10000.0 .</br>
              max motor speed :  motorSpeed=300.0, collision allowing flag : collisionConnected=false, motor enabler starts motor when enabled: motorenable=true .</br>
    The Fixture "fd" is attached to "body1" and the Fixture "ballfd" is attached to "body2".</br>
    Finally the motor-driven system with revolute-joint  is created by passing "jointDef" to m_world->CreateJoint() .</br></p>
  */
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.2f, 3.99f);
      b2BodyDef bd;
      bd.position.Set(-5.5f, 14.0f);
      bd.type = b2_dynamicBody;
      b2Body* body1 = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 500.0f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body1->CreateFixture(fd);
      
      b2CircleShape circleShape;
	  circleShape.m_radius = 0.2;  
      b2BodyDef bd2;
      //bd2.type = b2_dynamicBody;
      bd2.position.Set(-5.5f, 16.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);
      b2FixtureDef ballfd;
      ballfd.shape = &circleShape;
      ballfd.density = 38.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 1.0f;
      body2->CreateFixture(&ballfd);

      b2RevoluteJointDef jointDef;
      
      jointDef.bodyA = body1;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0.0f, 0.0f);
      jointDef.localAnchorB.Set(0,0);
      jointDef.maxMotorTorque = 10000.0f;
      jointDef.motorSpeed = 300.0f;
      jointDef.enableMotor = true;
      jointDef.collideConnected = false;
      //default was false
      m_world->CreateJoint(&jointDef);
    
    }
    //pulley guide 1
    /*!<h3>Curved guiding surface, below the "plank+train of spheres system"</h3>
    <p>The falling train of spheres are guided towards another curved surface .</br>
      The curve is constructed using multiple small edges/lines to give a approximted curve with restitution=0 so that the direction change is uniform.</br> 
      Here is a description of objects defined for this system : 
          "curveEdgeshape" : type=<b>b2EdgeShape</b>, "Set()" used to set end-points in each iteration according to the curve .</br> 
          "curveDef" : type=<b>b2BodyDef</b>, type=<b>b2_dynamicBody</b>, defines a body-object . </br>
          "basecurve1" : pointer of type=<b>b2Body</b> , assigned a body each iteration, created by passing "curveDef" to <b>m_world->CreateBody()</b> .</br>
          "lowrest" : type=<b>b2FixtureDef</b>, its a fixture defined each iteration, assigned : shape = "curveEdgeShape", density=0, friction=3, restitution=-0.8 .</br>
      Here the end points of the edge "curveEdgeShape" are set every iteration and (x,y) are updated each iteration so that a smooth curve is obtained .</br>
      The body-object "curveDef" and fixture "lowrest" are assigned to the body "basecurve1" each iteration, basically adding a small line,
           with slightly different slope and length with end points:(x,y) and [x-(i+2)*0.1 , y-(9-i)*0.3], so that a smooth curve is obtained .</br>
      The curve is formed using 10 lines.</br>
    */
    {
      b2Body* basecurve1;
      
      float32 x = 8.4f;
      float32 y = 23.0f;
      for(int i = 0 ; i < 10 ; i++){
		  b2EdgeShape curveEdgeShape;
		  b2BodyDef curveDef;
        curveEdgeShape.Set(b2Vec2(x,y) , b2Vec2(x-(i+2)*0.1 , y-(9-i)*0.3));
        x = x-(i+2)*0.1;
        y = y-(9-i)*0.3;
        b2FixtureDef lowrest;
        lowrest.shape= &curveEdgeShape;
        lowrest.density= 0.0f;
        lowrest.friction= 3.0f;
        lowrest.restitution= -0.8f;
        basecurve1 = m_world->CreateBody(&curveDef);
        basecurve1->CreateFixture(&lowrest);
      }
    } 
    //pulley guide 2
    /*!<h3>Curved guiding surface, below the first guiding surface</h3>
    <p>The falling train of spheres are guided towards open box1 where they are collected one by one .</br>
      The curve is constructed using multiple small edges/lines to give a approximted curve with restitution=0 so that the direction change is uniform.</br> 
      Here is a description of objects defined for this system :
          "curveEdgeshape" : type <b>b2EdgeShape</b>, "Set()" used to set end-points in each iteration according to the curve .<br>
          "curveDef" : type <b>b2BodyDef</b>, type=<b>b2_dynamicBody</b>, defines a body-object .<br> 
          "basecurve1" : pointer of type <b>b2Body</b> , assigned a body each iteration, created by passing "curveDef" to <b>m_world->CreateBody()</b> .<br>
          "lowrest"  : type <b>b2FixtureDef</b>, its a fixture defined each iteration, assigned : shape = "curveEdgeShape", density=0, friction=3, restitution=-0.8 .<br>
      Here the end points of the edge "curveEdgeShape" are set every iteration and (x,y) are updated each iteration so that a smooth curve is obtained .<br>
      The body-object "curveDef" and fixture "lowrest" are assigned to the body "basecurve1" each iteration, basically adding a small line,
           with slightly different slope and length with end points:(x,y) and [x+(i+2)*0.3 , y-(9-i)*0.1], so that a smooth curve is obtained .<br>
      The curve is formed using 11 lines. <br></p>
    */
    
    {
      b2Body* basecurve1;
      
      float32 x = -18.0f;
      float32 y = 13.4f;
      for(int i = 0 ; i < 11 ; i++){
		  b2EdgeShape curveEdgeShape;
		  b2BodyDef curveDef;
        curveEdgeShape.Set(b2Vec2(x,y) , b2Vec2(x+(i+2)*0.3 , y-(9-i)*0.1));
        x = x+(i+2)*0.3;
        y = y-(10-i)*0.1;
        b2FixtureDef lowrest;
        lowrest.shape= &curveEdgeShape;
        lowrest.density= 0.0f;
        lowrest.friction= 3.0f;
        lowrest.restitution= 0.0f;
        basecurve1 = m_world->CreateBody(&curveDef);
        basecurve1->CreateFixture(&lowrest);
      }
    }
    
      //platform to hold the heavy ball
      /*!<h3> Heavy vertical Platform plus Heavy horizontal plank system , lying to the right </h3>
    <p>
      The heavy vertical platform is hinged with a small circle above it, about which it can move. <br>
      Both are joined using a revolute joint .<br>
      Teh heavy horizontal plank is fixed and lies just below the vertical plank.<br> 
      Here is a description of objects defined for this system :
          "shape" : type <b>b2PolygonShape</b>, <b>SetAsBox()</b> used to set dimensions to (4.4,0.35) .<br>
          "surface" : type <b>b2FixtureDef</b>, defines a fixture with attributes : shape="shape", density=0.0, friction=0.2, restitution=-1.0 .<br>        
          "bd" : type <b>b2BodyDef</b>, defines a body-object with position(27.6, 14.4) .<br>
          "shape2" : type <b>b2PolygonShape</b>, <b>SetAsBox()</b> used to set dimensions to (0.4,2.90) .<br> 
          "heavyplank" : type <b>b2FixtureDef</b>, defines a fixture with attributes : shape="shape2", density=500.0, friction=100.0, restitution=0.0 .<br>
          "bd2" : type <b>b2BodyDef</b>, type=<b>b2_dynamicBody</b>, defines a body-object with position(27.6, 22.4) .<br>          
          "hplank" : pointer of type <b>b2Body</b> , assigned the body created by passing "bd2" to <b>m_world->CreateBody()</b> .<br>
          "circleShape" : type <b>b2CircleShape</b>, defines a shape of type circle and radius="0.2" .<br>
          "bd3" : type <b>b2BodyDef</b>, type=<b>b2_dynamicBody</b>, defines a body-object with position(27.6, 22.4) .<br>  
          "body2" : pointer of type <b>b2Body</b> , assigned the body created by passing "bd3" to <b>m_world->CreateBody()</b> .<br>
          "ballfd" : type <b>b2FixtureDef</b>, defines a fixture with attributes : shape="circleShape", density=38.0, friction=0.0, restitution=1.0 .<br>
          "jointDef" : type <b>b2RevoluteJointDef</b>, its a revolute joint with attributesa as : bodyA="hplank", bodyB="body2" .<br>
              {for hplank}localAnchorA=(0.0, 4.5) , {for body2}localAnchorB=(0.0, 0.0) , {collision between connected bodies allowing flag} collisionConnected=false .<br>
      The body defined by "bd" is passed to the "m_world->CreateBody" whose result is assigned to <b>b2Body</b> type object "ground" .<br>
      Next, the fixture "surface" is also fixed to the "ground" body.<br>
      The Fixture "heavyplank" is attached to the body "hplank" object and the Fixture "ballfd" is attached to the body "body2" .<br>
      Finally the motor-driven system with revolute-joint  is created by passing "jointDef" to m_world->CreateJoint() .<br>
      </p>
    */
    {
	  b2PolygonShape shape;
      shape.SetAsBox(4.4, 0.35f);
      
      b2FixtureDef surface;
      surface.shape = &shape;
      surface.density = 0.0f;
      surface.friction = 0.2f;
      surface.restitution = -1.0f;
	
      b2BodyDef bd;
      bd.position.Set(27.6f, 14.4f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&surface);
      
      b2PolygonShape shape2;
      shape2.SetAsBox(0.4f, 2.90f);
      
      b2FixtureDef heavyplank;
      heavyplank.shape = &shape2;
      heavyplank.density = 500.0f;
      heavyplank.friction = 100.0f;
      heavyplank.restitution = 0.0f;
	
      b2BodyDef bd2;
      bd2.type= b2_dynamicBody;
      bd2.position.Set(27.6f, 22.4f);
      b2Body* hplank = m_world->CreateBody(&bd2);
      hplank->CreateFixture(&heavyplank);
      
      b2CircleShape circleShape;
	    circleShape.m_radius = 0.2;  
      b2BodyDef bd3;
      bd3.position.Set(27.6f, 22.4f);
      b2Body* body2 = m_world->CreateBody(&bd3);
      b2FixtureDef ballfd;
      ballfd.shape = &circleShape;
      ballfd.density = 38.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      body2->CreateFixture(&ballfd);

      b2RevoluteJointDef jointDef;
      
      jointDef.bodyA = hplank;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0.0f,4.5f);
      jointDef.localAnchorB.Set(0,0);
      //jointDef.maxMotorTorque = 100.0f;
      //jointDef.motorSpeed = 23.0f;
      //jointDef.enableMotor = true;
      jointDef.collideConnected = false;
      //default was false
      m_world->CreateJoint(&jointDef);
      
      
    }
    //heavy ball guide to its resting place
    /*<h3>Curved surface , above the right open box of pulley .</h3>
    <p>
      This curved surface is a guide to the heavy sphere which starts from the top. <br>
      It guides the sphere to the heavy vertical plank in front of its lower end .</br> 
      Here is a description of objects defined for this system :
          "curveEdgeshape" : type <b>b2EdgeShape</b>, "Set()" used to set end-points in each iteration according to the curve . <br>
          "curveDef" : type <b>b2BodyDef</b>, type=<b>b2_dynamicBody</b>, defines a body-object . <br>
          "heavyguide" : pointer of type <b>b2Body</b> , assigned a body each iteration, created by passing "curveDef" to <b>m_world->CreateBody()</b> .<br>
          "lowrest" : type <b>b2FixtureDef</b>, its a fixture defined each iteration, assigned : shape = "curveEdgeShape", density=700, friction=3, restitution=-0.0 .<br>
      Here the end points of the edge "curveEdgeShape" are set every iteration and (x,y) are updated each iteration so that a smooth curve is obtained .<br>
      The body-object "curveDef" and fixture "lowrest" are assigned to the body "heavyguide" each iteration, basically adding a small line,
           with slightly different slope and length with end points:(x,y) and [x+(i+2)*0.12 , y-(9-i)*0.1], so that a smooth curve is obtained .<br>
      The curve is formed using 10 lines.<br>
      </p>
    */
    {
      b2Body* heavyguide;
      
      float32 x = 15.7f;
      float32 y = 22.4f;
      for(int i = 0 ; i < 10 ; i++){
		  b2EdgeShape curveEdgeShape;
		  b2BodyDef curveDef;
        curveEdgeShape.Set(b2Vec2(x,y) , b2Vec2(x+(i+2)*0.12 , y-(9-i)*0.1));
        x = x+(i+2)*0.12;
        y = y-(9-i)*0.1;
        b2FixtureDef lowrest;
        lowrest.shape= &curveEdgeShape;
        lowrest.density= 700.0f;
        lowrest.friction= 3.0f;
        lowrest.restitution= 0.0f;
        heavyguide = m_world->CreateBody(&curveDef);
        heavyguide->CreateFixture(&lowrest);
      }
    }
    
    //
    /*!sabse right mein jo hinged plank hai
    <h3> Rightmost plank, hinged at its centre .</h3>
    <p>
    This system consists of a vertical plank hinged with a small circle at its centre, thus it can rotate about its centre .<br>
    The plank is disturbed when a small sphere the train of spheres hits its lower end and it in turn hits the biggest sphere .<br>
      Here is a description of objects defined for this system :
          "shape" : type <b>b2PolygonShape</b>, <b>SetAsBox()</b> used to set dimensions to (0.2,8.5) .<br>        
          "bd" : type <b>b2BodyDef</b>, defines a body-object with position(33.0, 9.0) .<br>
          "fd" : type <b>b2FixtureDef</b>, defines a fixture with attributes : shape="shape", density=10.0 .<br>
          "body1" : pointer of type <b>b2Body</b> , its assigned the body, created by passing "bd" to <b>m_world->CreateBody()</b> .<br>
          "circleShape" : type <b>b2CircleShape</b>, defines a shape type circle and radius="0.2" .<br>
          "bd2" : type <b>b2BodyDef</b>, type=<b>b2_dynamicBody</b>, defines a body-object with position(33.0, 9.0) .<br>
          "body2" : pointer of type <b>b2Body</b> , assigned the body created by passing "bd2" to <b>m_world->CreateBody()</b>  . <br>
          "ballfd" : type <b>b2FixtureDef</b>, defines a fixture with attributes : shape="circleShape", density=38.0, friction=0.0, restitution=1.0 .<br>
          "jointDef" : type <b>b2RevoluteJointDef</b>, its a revolute joint with attributesa as : bodyA="body1", bodyB="body2" .<br>
              anchor for body1 : localAnchorA=(0.0, 0.0) , anchor for body2 : localAnchorB=(0.0, 0.0) , collision flag : collisionConnected=false .<br>
      The fixture "fd" is attached to the body corresponding to "body1" and the Fixture "ballfd" is attached to the body corresponding to "body2" .<br>
      Finally the motor-driven system with revolute-joint  is created by passing "jointDef" to m_world->CreateJoint() .<br>
      </p>
    */

	{
      b2PolygonShape shape;
      shape.SetAsBox(0.2f, 8.5f);
      b2BodyDef bd;
      bd.position.Set(33.0f, 9.0f);
      bd.type = b2_dynamicBody;
      b2Body* body1 = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 10.0f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body1->CreateFixture(fd);
      
      b2CircleShape circleShape;
	  circleShape.m_radius = 0.2;  
      b2BodyDef bd2;
      bd2.position.Set(33.0f, 9.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);
      b2FixtureDef ballfd;
      ballfd.shape = &circleShape;
      ballfd.density = 38.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 1.0f;
      body2->CreateFixture(&ballfd);

      b2RevoluteJointDef jointDef;
      
      jointDef.bodyA = body1;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0.0f,0.0f);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    
  }

	//
  /*! Jo sphere sabse right mein sabse bada hai 
  <h3> Largest sphere on the Horizontal-Plank plus Hinged Vertical-Plank system </h3>
    Here is a description of objects defined for this system : 
          "circle" {type=<b>b2CircleShape</b>, defines a shape of type circle and radius="1.3"},          
          "ballbd" {type=<b>b2BodyDef</b>, defines a body-object with position(31.0, 19.0)}, 
          "ballfd" {type=<b>b2FixtureDef</b>, defines a fixture with attributes : shape="shape", density=10.0},
          "spherebody" {pointer of type=<b>b2Body</b>,body-type=<b>b2_dynamicBody</b> , its assigned the dynamic body, created by passing "ballbd" to <b>m_world->CreateBody()</b>}
    The Fixture "ballfd" is attached to the body corresponding to "spherebody" .
    
  */

  {
      b2Body* spherebody;
      b2CircleShape circle;
      circle.m_radius = 1.3f;
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 300.0f;
      ballfd.friction = 0.2f;
      ballfd.restitution = 0.835f; 
      b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(31.0f, 19.0f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	
	}

  ///
  /*!
    Variable "bd1", type b2BodyDef is to pass both the box and the bar (on opposite sides of pulley) to the world object.
    The position of the open box is set to (7.3, 5).
    The fixedRotation variable is set to true for restricting the rotation of the open box and bar.
  */

{
      b2BodyDef *bd1 = new b2BodyDef;
      bd1->type = b2_dynamicBody;
      bd1->position.Set(7.3,5);
      bd1->fixedRotation = true;
      
      //The open box
    /*!

      Here is a description of objects defined for this system :
          "bs1" {type=<b>b2PolygonShape</b>, <b>SetAsBox()</b> used to set dimensions to (0.2,8.5), centre : (-0.2,-1.5), tilt angle : 0 },   
          "fd1d" {type=<b>b2FixtureDef</b>, defines a fixture with attributes : shape="bs1", density=110.0, friction=0.5,restitution=0},
          "bs2" {type=<b>b2PolygonShape</b>, <b>SetAsBox()</b> used to set dimensions to (0.2,1.4), centre : (4.5,0), tilt angle : 0 },
          "fd2" {type=<b>b2FixtureDef</b>, defines a fixture with attributes : shape="bs1", density=110.0, friction=0.5,restitution=0},          
          "bs3" {type=<b>b2PolygonShape</b>, <b>SetAsBox()</b> used to set dimensions to (0.2,1.4), centre : (-4.9,0), tilt angle : 0 },
          "fd3" {type=<b>b2FixtureDef</b>, defines a fixture with attributes : shape="bs1", density=110.0, friction=0.5,restitution=0},          
          "box1" {pointer of type=<b>b2Body</b> , its assigned the body, created by passing "bd1"(defined above) to <b>m_world->CreateBody()</b>}
      All the three Fixtures "fd1"(horizontal wall), "fd2"(vertical wall) and "fd3"(vertical wall),
           representing the three walls of the first box are attached to the body object "box1" .

    */

      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 110.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(4.9,0.2, b2Vec2(-0.2f,-1.5f), 0);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 110.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,1.4, b2Vec2(4.5f,0.f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 110.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,1.4, b2Vec2(-4.9f,0.f), 0);
      fd3->shape = &bs3;
       
      b2Body* box1 = m_world->CreateBody(bd1);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);

      //The box2
    /*!
       Variable "bd2", type b2BodyDef is to pass both the boxes (on opposite sides of pulley) to the world object.
      The position of the open box is set to (20, 10).
      The fixedRotation variable is set to true for restricting the rotation of the open box and bar.

      Here is a description of objects defined for this system :
          "bs4" {type=<b>b2PolygonShape</b>, <b>SetAsBox()</b> used to set dimensions to (2,0.2), centre : (0,-1.9), tilt angle : 0 },   
          "fd4" {type=<b>b2FixtureDef</b>, defines a fixture with attributes : shape="bs1", density=110.0, friction=0.5,restitution=0},
          "bs5" {type=<b>b2PolygonShape</b>, <b>SetAsBox()</b> used to set dimensions to (0.2,2), centre : (2.0,0), tilt angle : 0 },
          "fd5" {type=<b>b2FixtureDef</b>, defines a fixture with attributes : shape="bs1", density=110.0, friction=0.5,restitution=0},          
          "bs6" {type=<b>b2PolygonShape</b>, <b>SetAsBox()</b> used to set dimensions to (0.2,2), centre : (-2.0,0), tilt angle : 0 },
          "fd6" {type=<b>b2FixtureDef</b>, defines a fixture with attributes : shape="bs1", density=110.0, friction=0.5,restitution=0},          
          "box2" {pointer of type=<b>b2Body</b> , its assigned the body, created by passing "bd1"(defined above) to <b>m_world->CreateBody()</b>}
      All the three Fixtures "fd4"(horizontal wall), "fd5"(vertical wall) and "fd6"(vertical wall),
           representing the three walls of the first box are attached to the body object "box2" .

     */

      b2BodyDef *bd2 = new b2BodyDef;
      bd2->type = b2_dynamicBody;
      bd2->position.Set(20,10);
      bd2->fixedRotation = true;
      
      b2FixtureDef *fd4 = new b2FixtureDef;
      fd4->density = 100.0;
      fd4->friction = 0.5;
      fd4->restitution = 0.f;
      fd4->shape = new b2PolygonShape;
      b2PolygonShape bs4;
      bs4.SetAsBox(2,0.2, b2Vec2(0.f,-1.9f), 0);
      fd4->shape = &bs4;
      b2FixtureDef *fd5 = new b2FixtureDef;
      fd5->density = 100.0;
      fd5->friction = 0.5;
      fd5->restitution = 0.f;
      fd5->shape = new b2PolygonShape;
      b2PolygonShape bs5;
      bs5.SetAsBox(0.2,2, b2Vec2(2.0f,0.f), 0);
      fd5->shape = &bs5;
      b2FixtureDef *fd6 = new b2FixtureDef;
      fd6->density = 100.0;
      fd6->friction = 0.5;
      fd6->restitution = 0.f;
      fd6->shape = new b2PolygonShape;
      b2PolygonShape bs6;
      bs6.SetAsBox(0.2,2, b2Vec2(-2.0f,0.f), 0);
      fd6->shape = &bs6;
      
      //Vertical plank holds the second box from swinging .

      /*! right waali pulley ko left mein jaane se rokne ke liye
        Here is a description of objects defined for this system : 
          "holder" {type=<b>b2PolygonShape</b>, <b>SetAsBox()</b> used to set dimensions to (0.2,1.6) },  
          "bdxy" {type=<b>b2BodyDef</b>, defines a body-object with position(17.5, 8.6)}, 
          "holderbox" {pointer of type=<b>b2Body</b> , its assigned the body, created by passing "bdxy" to <b>m_world->CreateBody()</b>}

          "fd4" {type=<b>b2FixtureDef</b>, defines a fixture with attributes : shape="bs1", density=110.0, friction=0.5,restitution=0},        
      */
      b2PolygonShape holder;
      holder.SetAsBox(0.2f, 1.6f);
      b2BodyDef bdxy;
      bdxy.position.Set(17.5f, 8.6f);
      b2Body* holderbox = m_world->CreateBody(&bdxy);
      holderbox->CreateFixture(&holder, 0.0);
      
      b2Body* box2 = m_world->CreateBody(bd2);
      box2->CreateFixture(fd4);	
      box2->CreateFixture(fd5);
      box2->CreateFixture(fd6);
	
      // The pulley joint
      // The pulley joint
      /*!
      <p>3) Pulley Joint: <br/>
      Variable "myjoint" points to the object, type b2PulleyJointDef, and joins the open box1 and the open box2 using two anchors situated at (6.5, 15) and (20, 15), which are the two pegs for the pulley rope to pass on.</p>
      */

      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(6.5, 5); // Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody2(20, 10); // Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(6.5, 15); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(20, 15); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    }

    ///left waley pulley box ko girne se bachaane ke liye
    
{
      b2PolygonShape shape;
      shape.SetAsBox(2.0f, 0.25f);
      
      b2FixtureDef surface;
      surface.shape = &shape;
      surface.density = 0.0f;
      surface.friction = 0.0f;
      surface.restitution = 1.0f;
	
      b2BodyDef bd;
      bd.position.Set(7.0f, 2.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&surface);
}

    // left waali pulley ko right jaane se bachaane ke liye

{
      b2PolygonShape shape;
      shape.SetAsBox(0.25f,1.0f);
      
      b2FixtureDef surface;
      surface.shape = &shape;
      surface.density = 0.0f;
      surface.friction = 0.0f;
      surface.restitution = 1.0f;
	
      b2BodyDef bd;
      bd.position.Set(10.0f, 3.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&surface);
}

    //

   /*! guided path for the ball from left
    Here is a description of objects defined for this system :
          "curveEdgeshape" {type=<b>b2EdgeShape</b>, "Set()" used to set end-points in each iteration according to the curve}, 
          "curveDef" {type=<b>b2BodyDef</b>, type=<b>b2_dynamicBody</b>, defines a body-object}, 
          "basecurve1" {pointer of type=<b>b2Body</b> , assigned a body each iteration, created by passing "curveDef" to <b>m_world->CreateBody()</b>} 
          "lowrest" {type=<b>b2FixtureDef</b>, its a fixture defined each iteration, assigned : shape = "curveEdgeShape", density=0, friction=3, restitution=-0.8}
      Here the end points of the edge "curveEdgeShape" are set every iteration and (x,y) are updated each iteration so that a smooth curve is obtained .
      The body-object "curveDef" and fixture "lowrest" are assigned to the body "basecurve1" each iteration, basically adding a small line,
           with slightly different slope and length with end points:(x,y) and [x+(i+2)*0.3 , y-(9-i)*0.1], so that a smooth curve is obtained 
      The curve is formed using 11 lines.
    */
{
      b2Body* basecurve1;
      
      float32 x = -18.0f;
      float32 y = 7.0f;
      for(int i = 0 ; i < 11 ; i++){
		  b2EdgeShape curveEdgeShape;
		  b2BodyDef curveDef;
        curveEdgeShape.Set(b2Vec2(x,y) , b2Vec2(x+(i+2)*0.3 , y-(9-i)*0.1));
        x = x+(i+2)*0.3;
        y = y-(10-i)*0.1;
        b2FixtureDef lowrest;
        lowrest.shape= &curveEdgeShape;
        lowrest.density= 0.0f;
        lowrest.friction= 0.0f;
        lowrest.restitution= 1.0f;
        basecurve1 = m_world->CreateBody(&curveDef);
        basecurve1->CreateFixture(&lowrest);
      }
}

    //
    /*! Finally jo ball right waaley box ke andar gir rahi hai aur uska chota sa plank
      Here is a description of objects defined for this system :
          "shape" {type=<b>b2PolygonShape</b>, <b>SetAsBox()</b> used to set dimensions to (1.0,0.35) },
          "surface" {type=<b>b2FixtureDef</b>, defines a fixture with attributes : shape="shape", density=0.0, friction=0.2, restitution=0.1},
          "bd" {type=<b>b2BodyDef</b>, defines a body-object with position(21.7, 13.4)},
          "spherebody" {pointer of type=<b>b2Body</b> , its assigned the body, created by passing "bd" to <b>m_world->CreateBody()</b>}
          "circle" {type=<b>b2CircleShape</b>, defines a shape type circle and radius="1.0"},
          "ballfd" {type=<b>b2FixtureDef</b>, defines a fixture with attributes : shape="circleShape", density=2000.0, friction=0.2, restitution=0.835}
          "ballbd" {type=<b>b2BodyDef</b>, type=<b>b2_dynamicBody</b>, defines a body-object with position(21.7, 13.9)},
      The body-object represented by "ground" is assigned object returned when object "bd" is passed to <b>m_world->CreateBody()</b> .
      After that, the Fixture "surface" is also attached to the object represented by "ground" .
      Finally the Fixture "ballfd" is attached to the body represented by "spherebody" .

    */
{
      b2PolygonShape shape;
      shape.SetAsBox(1.0, 0.35f);
      
      b2FixtureDef surface;
      surface.shape = &shape;
      surface.density = 0.0f;
      surface.friction = 0.2f;
      surface.restitution = 0.1f;
	
      b2BodyDef bd;
      bd.position.Set(21.7f, 13.4f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&surface);
      
      b2Body* spherebody;
      b2CircleShape circle;
      circle.m_radius = 1.0f;
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 2000.0f;
      ballfd.friction = 0.2f;
      ballfd.restitution = 0.835f;
      b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(21.7f, 13.9f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	
	}
}
  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
