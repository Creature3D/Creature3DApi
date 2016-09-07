/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2006 Robert Osfield 
 *
 * This library is open source and may be redistributed and/or modified under  
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or 
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * OpenSceneGraph Public License for more details.
*/
#include <CRCore/crNotify.h>
#include <CRParticle/crModularProgram.h>
#include <CRParticle/crBounceOperator.h>

using namespace CRParticle;

void crBounceOperator::handleTriangle( const Domain& domain, crParticle* P, double dt )
{
    CRCore::crVector3 nextpos = P->getPosition() + P->getVelocity() * dt;
    float distance = domain.plane.distance( P->getPosition() );
    if ( distance*domain.plane.distance(nextpos)>=0 ) return;
    
    CRCore::crVector3 normal = domain.plane.getNormal();
    float nv = normal * P->getVelocity();
    CRCore::crVector3 hitPoint = P->getPosition() - P->getVelocity() * (distance / nv);
    
    float upos = (hitPoint - domain.v1) * domain.s1;
    float vpos = (hitPoint - domain.v1) * domain.s2;
    if ( upos<0.0f || vpos<0.0f || (upos + vpos)>1.0f ) return;
    
    // Compute tangential and normal components of velocity
    CRCore::crVector3 vn = normal * nv;
    CRCore::crVector3 vt = P->getVelocity() - vn;
    
    // Compute new velocity
    if ( vt.length2()<=m_cutoff ) P->setVelocity( vt - vn*m_resilience );
    else P->setVelocity( vt*(1.0f-m_friction) - vn*m_resilience );
}

void crBounceOperator::handleRectangle( const Domain& domain, crParticle* P, double dt )
{
    CRCore::crVector3 nextpos = P->getPosition() + P->getVelocity() * dt;
    float distance = domain.plane.distance( P->getPosition() );
    if ( distance*domain.plane.distance(nextpos)>=0 ) return;
    
    CRCore::crVector3 normal = domain.plane.getNormal();
    float nv = normal * P->getVelocity();
    CRCore::crVector3 hitPoint = P->getPosition() - P->getVelocity() * (distance / nv);
    
    float upos = (hitPoint - domain.v1) * domain.s1;
    float vpos = (hitPoint - domain.v1) * domain.s2;
    if ( upos<0.0f || upos>1.0f || vpos<0.0f || vpos>1.0f ) return;
    
    // Compute tangential and normal components of velocity
    CRCore::crVector3 vn = normal * nv;
    CRCore::crVector3 vt = P->getVelocity() - vn;
    
    // Compute new velocity
    if ( vt.length2()<=m_cutoff ) P->setVelocity( vt - vn*m_resilience );
    else P->setVelocity( vt*(1.0f-m_friction) - vn*m_resilience );
}

void crBounceOperator::handlePlane( const Domain& domain, crParticle* P, double dt )
{
    CRCore::crVector3 nextpos = P->getPosition() + P->getVelocity() * dt;
    float distance = domain.plane.distance( P->getPosition() );
    if ( distance*domain.plane.distance(nextpos)>=0 ) return;
    
    CRCore::crVector3 normal = domain.plane.getNormal();
    float nv = normal * P->getVelocity();
    
    // Compute tangential and normal components of velocity
    CRCore::crVector3 vn = normal * nv;
    CRCore::crVector3 vt = P->getVelocity() - vn;
    
    // Compute new velocity
    if ( vt.length2()<=m_cutoff ) P->setVelocity( vt - vn*m_resilience );
    else P->setVelocity( vt*(1.0f-m_friction) - vn*m_resilience );
}

void crBounceOperator::handleSphere( const Domain& domain, crParticle* P, double dt )
{
    CRCore::crVector3 nextpos = P->getPosition() + P->getVelocity() * dt;
    float distance1 = (P->getPosition() - domain.v1).length();
    if ( distance1<=domain.r1 )  // Within the sphere
    {
        float distance2 = (nextpos - domain.v1).length();
        if ( distance2<=domain.r1 ) return;
        
        // Bounce back in if going outside
        CRCore::crVector3 normal = domain.v1 - P->getPosition(); normal.normalize();
        float nmag = P->getVelocity() * normal;
        
        // Compute tangential and normal components of velocity
        CRCore::crVector3 vn = normal * nmag;
        CRCore::crVector3 vt = P->getVelocity() - vn;
        if ( nmag<0 ) vn = -vn;
        
        // Compute new velocity
        float tanscale = (vt.length2()<=m_cutoff) ? 1.0f : (1.0f - m_friction);
        P->setVelocity( vt * tanscale + vn * m_resilience );
        
        // Make sure the particle is fixed to stay inside
        nextpos = P->getPosition() + P->getVelocity() * dt;
        distance2 = (nextpos - domain.v1).length();
        if ( distance2>domain.r1 )
        {
            normal = domain.v1 - nextpos; normal.normalize();
            
            CRCore::crVector3 wishPoint = domain.v1 - normal * (0.999f * domain.r1);
            P->setVelocity( (wishPoint - P->getPosition()) / dt );
        }
    }
    else  // Outside the sphere
    {
        float distance2 = (nextpos - domain.v1).length();
        if ( distance2>domain.r1 ) return;
        
        // Bounce back out if going inside
        CRCore::crVector3 normal = P->getPosition() - domain.v1; normal.normalize();
        float nmag = P->getVelocity() * normal;
        
        // Compute tangential and normal components of velocity
        CRCore::crVector3 vn = normal * nmag;
        CRCore::crVector3 vt = P->getVelocity() - vn;
        if ( nmag<0 ) vn = -vn;
        
        // Compute new velocity
        float tanscale = (vt.length2()<=m_cutoff) ? 1.0f : (1.0f - m_friction);
        P->setVelocity( vt * tanscale + vn * m_resilience );
    }
}

void crBounceOperator::handleDisk( const Domain& domain, crParticle* P, double dt )
{
    CRCore::crVector3 nextpos = P->getPosition() + P->getVelocity() * dt;
    float distance = domain.plane.distance( P->getPosition() );
    if ( distance*domain.plane.distance(nextpos)>=0 ) return;
    
    CRCore::crVector3 normal = domain.plane.getNormal();
    float nv = normal * P->getVelocity();
    CRCore::crVector3 hitPoint = P->getPosition() - P->getVelocity() * (distance / nv);
    
    float radius = (hitPoint - domain.v1).length();
    if ( radius>domain.r1 || radius<domain.r2 ) return;
    
    // Compute tangential and normal components of velocity
    CRCore::crVector3 vn = normal * nv;
    CRCore::crVector3 vt = P->getVelocity() - vn;
    
    // Compute new velocity
    if ( vt.length2()<=m_cutoff ) P->setVelocity( vt - vn*m_resilience );
    else P->setVelocity( vt*(1.0f-m_friction) - vn*m_resilience );
}
