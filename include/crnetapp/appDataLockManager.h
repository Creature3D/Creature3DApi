/* Creature3D - Online Game Engine, Copyright (C) 2005 ��ƻ�(26756325@qq.com)
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
/**********************************************************************
*����Ӧ�ÿ���dll����ڼ���Ӧ�ò�dll�Ƿ�ʹ���˶�����
*Ϊ����Ǳ�ڵĽ��������գ�Ӧ�ò����Ӧ������ʹ�ö�����				
**********************************************************************/
#ifndef CRNETAPP_DATALOCKMANAGER_H
#define CRNETAPP_DATALOCKMANAGER_H 1

#include <CRNetApp/appExport.h>
#include <CRCore/crDataManager.h>
#include <CRCore/thread/crMutex.h>
#include <CRCore/thread/crScopedLock.h>
#include  <CRCore/thread/crCriticalMutex.h>
#include <map>

namespace CRNetApp{
//���÷���ʾ����CRNetApp::crDataLock scopedLock(data);
class CRNETAPP_EXPORT crDataLock
{
public:
	crDataLock(CRCore::crData *data);
	~crDataLock();
	void unlock();//������Ҫ��ǰ�ͷŵĵط�
private:
	CRCore::ref_ptr<CRCore::crData> m_lockedData;
};
class CRNETAPP_EXPORT crDataLockManager : public CRCore::Referenced
{
public:
	crDataLockManager();
	static crDataLockManager *getInstance();
	void clear();

	void lockData(CRCore::crData *data);
	void unlockData(CRCore::crData *data);
	typedef std::map<int,CRCore::ref_ptr<CRCore::crData> > ThreadLockDataMap;
protected:
	virtual ~crDataLockManager(){}
	static CRCore::ref_ptr<crDataLockManager> m_instance;
	CRCore::crCriticalMutex m_mutex;
	ThreadLockDataMap m_threadLockDataMap;
};
}
#endif