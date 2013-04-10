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
    
    //right platform with heavy ball, the slants
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

{
      b2BodyDef *bd1 = new b2BodyDef;
      bd1->type = b2_dynamicBody;
      bd1->position.Set(7.3,5);
      bd1->fixedRotation = true;
      
      //The open box
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
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(6.5, 5); // Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody2(20, 10); // Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(6.5, 15); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(20, 15); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    }
    
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

{
      b2PolygonShape shape;
      shape.SetAsBox(0.25f,1.0f);
      
      b2FixtureDef surface;
      surface.shape = &shape;
      surface.density = 0.0f;
      surface.friction = 0.0f;
      surface.restitution = 1.0f;
	
      b2BodyDef bd;
      bd.position.Set(11.7f, 3.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&surface);
    }
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
