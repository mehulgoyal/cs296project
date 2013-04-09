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
      bs1.SetAsBox(3.8,0.2, b2Vec2(-1.0f,-1.5f), 0);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 110.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,1.4, b2Vec2(2.2f,0.f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 110.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,1.4, b2Vec2(-4.8f,0.f), 0);
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
      bd.position.Set(10.0f, 3.0f);
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
