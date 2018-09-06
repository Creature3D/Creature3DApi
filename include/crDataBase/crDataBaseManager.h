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
#ifndef CRDATABASE_CRDATABASEMANAGER_H
#define CRDATABASE_CRDATABASEMANAGER_H

#include <CRDataBase/crExport.h>
#include <CRCore/Referenced.h>
#include <CRCore/ref_ptr.h>
#include <CRCore/crDataManager.h>
#include <CRCore/crStreamBuf.h>
#include <CRCore/crTimer.h>
#include <CRCore/thread/crMutex.h>
#include <map>
namespace CRDataBase
{
class CRDATABASE_EXPORT crUpdateSql :  public CRCore::Referenced
{
public:
	crUpdateSql();
	void setUpdateSql(const std::string &sql);
	const std::string &getUpdateSql()const;
	void setUpdateSql(CRCore::crStreamBuf *sql);
	CRCore::crStreamBuf *getSqlStream();
	virtual void buildUpdateSql(){}
protected:
	std::string m_updateSql;
	CRCore::ref_ptr<CRCore::crStreamBuf> m_sqlstream;//ʹ��sqlstreamʱע��stream�ﲻ�ɺ�������([39]')
};
class CRDATABASE_EXPORT crQueryData :  public CRCore::crData
{
public:
	crQueryData();
	crQueryData(const crQueryData& data);
	DataClass(CRDataBase, Query)
	void setQuerySql(const std::string &sql);
	const std::string &getQuerySql()const;
	void setQuerySql(CRCore::crStreamBuf *sql);
	CRCore::crStreamBuf *getSqlStream();
	void setNumColumn(int numColumn);
	int getNumColumn();
    virtual void buildQuerySql(){}
	virtual void addParam(int i, char *buf, int length){}
protected:
    virtual void addParam(int i, const std::string& str){}
	virtual void getParam(int i, void*& param){}
	virtual void inputParam(int i, void *param){}
	std::string m_querySql;
	int m_numColumn;
	CRCore::ref_ptr<CRCore::crStreamBuf> m_sqlstream;
};

class CRDATABASE_EXPORT crDataBase :  public CRCore::Referenced
{
public:
	crDataBase();

    //void init(const std::string &updateIp,const std::string &queryIp,int dbport,const std::string &user,const std::string &password,const std::string &database);
	//��ѯ���ݿ�Ϊ�������ݿ�ı������ݿ�
	//���εĸ������ݿ�ѹ���ܴ�һ��һ̨�������ݿ��������֧��ͬʱ����2-3ǧ�ˣ�������Ҫ��ƶ������ݿ��������2̨һ�飬���¡���ѯ����
	//��Щ���ݱ�������ң���Ҫʵʱ���浽���ݿ⣬������ʱ���棬���������ͻ���¼��������ݶ�ʧ��
	//int openUpdateDataBase();
	//int openQueryDataBase();
	//void closeUpdateDataBase();
	//void closeQueryDataBase();
	void init(const std::string &dbIp,int dbport,const std::string &user,const std::string &password,const std::string &database);
	int openDataBase();
	void closeDataBase();

	int executeUpdate(const std::string &sql);//����ture��ʾ�ɹ�
	int executeUpdate(char *sql,int length);//����ture��ʾ�ɹ�
	int executeUpdate(crUpdateSql *sql);//����ture��ʾ�ɹ�
	int executeQuery(const std::string &sql);//����ture��ʾ�ɹ�
	int executeQuery(crQueryData *query);//����ture��ʾ�ɹ�
	void commit();
	void rollback();
	int getInsertID();
	typedef std::vector< CRCore::ref_ptr<crQueryData> > QueryResultVec;
	QueryResultVec &getQueryResult();
	void releaseQuery();

	unsigned long realEscapeString(char *to, const char *from, int from_length);

	crDataBase *beginSession();
	void endSession(crDataBase *session);
	void dbping();
	const char *getQueryError();
	const char *getUpdateError();
protected:
	virtual ~crDataBase();
	//void* m_updateDB;
	//void* m_queryDB;
	void* m_db;

	//std::string m_updateDBIP;
	//std::string m_queryDBIP;
	std::string m_dbip;
	unsigned int m_port;
	std::string m_userName;
	std::string m_password;
	std::string m_database;
	QueryResultVec m_queryResultVec;

	CRCore::crCriticalMutex m_sessionMutex;
};

class CRDATABASE_EXPORT crDataBaseManager :  public CRCore::Referenced
{
public:
	crDataBaseManager():m_pingTime(0L){}
	static crDataBaseManager *getInstance();
	void clear();

	void setAccountDB(crDataBase *db);
	crDataBase *getAccountDB();
	void setGlobalDB(crDataBase *db);
	crDataBase *getGlobalDB();

	typedef std::map< unsigned short,CRCore::ref_ptr<crDataBase> > DBMap;//dbid,U_QDBPair
	typedef std::vector<DBMap> DBMapVec;
	void initDBMapVec(int size);
	void insertDataBase(unsigned short enumid,unsigned short dbid, crDataBase *db);
    crDataBase *getDataBase(unsigned short enumid,unsigned short dbid);

	typedef std::vector< CRCore::ref_ptr<crDataBase> > DBVec;
	void initDBVec(int size);
	void insertDataBase(unsigned short enumid,crDataBase *db);
	crDataBase *getDataBase(unsigned short enumid);
	void dbping();
	void dbErrorRecord(const char *sql,int length,const char *error);
	unsigned long escapeString(char *to, const char *from, int from_length);
protected:
	virtual ~crDataBaseManager(){};
	static CRCore::ref_ptr<crDataBaseManager> m_instance;

	CRCore::ref_ptr<crDataBase> m_accountDB;//Account
	CRCore::ref_ptr<crDataBase> m_globalDB;//GlobalDB,��Ϸȫ�ַ�����
	DBMapVec m_dbMapVec;//���ݿ��飬һ��enumid��Ӧһ�����ݿ� GameDB:0
	DBVec m_dbVec;//ResDB=0,GameGlobalDB=1
	CRCore::Timer_t m_pingTime;
};

}

#endif
