/* Creature3D - Online Game Engine, Copyright (C) 2005 Wucaihua(26756325@qq.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
*/
#ifndef CRIOMANAGER_CRPREREMOVENODEVISITOR_H
#define CRIOMANAGER_CRPREREMOVENODEVISITOR_H 1

#include <CRCore/crNodeVisitor.h>
#include <CRCore/crNode.h>
namespace CRIOManager {
class crPreRemoveNodeVisitor : public CRCore::crNodeVisitor
{
public:
	crPreRemoveNodeVisitor(); 
	static crPreRemoveNodeVisitor *getInstance();
	virtual void apply(CRCore::crNode& node);
protected:
	virtual ~crPreRemoveNodeVisitor(); 
};
}

#endif

