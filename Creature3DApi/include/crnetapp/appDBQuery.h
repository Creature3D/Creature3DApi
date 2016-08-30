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
#ifndef CRNETAPP_DBQUERY_H
#define CRNETAPP_DBQUERY_H 1

#include <CRNetApp/appExport.h>
#include <CRDataBase/crDataBaseManager.h>
#include <CRCore/crStreamBuf.h>
#include <string>

namespace CRNetApp{

///////GlobalDB
class CRNETAPP_EXPORT crLoginQueryData : public CRDataBase::crQueryData
{//����userName��ѯaccount������
public:
	crLoginQueryData();
	crLoginQueryData(const crLoginQueryData& data);
	DataClass(CRNetApp, LoginQuery)
	virtual void addParam(int i, char *buf, int length);
	void buildQuerySql(const std::string& name,const std::string& pwd);
	int getPlayerID();

	//unsigned short getChatDBID();
	//const std::string &getNickName() const;
	//const std::string &getRelName() const;
	//char getSex();
 //   const std::string &getAddress() const;
	//const std::string &getBirthday() const;
	//const std::string &getIdiograph() const;
 //   char getBloodtype();
	//char getWork();
 //   const std::string &getSchool() const;
 //   const std::string &getEmail() const;
 //   const std::string &getBlog() const;
 //   const std::string &getTel() const;
 //   const std::string &getMobile() const;
 //   const std::string &getNote() const;
	//char getBeFriendValid();
	//const std::string& getLogindate() const;
	int getLastServerID();
	unsigned char getLocked();
protected:
	int m_id;

	//std::string m_nickname;
	//std::string m_relname;
	//unsigned short m_chatdbid;

	//char m_sex;//�Ա�0ΪŮ��1Ϊ��
	//std::string m_address;
	//std::string m_birthday;
	//std::string m_idiograph;
	//char m_bloodtype;
	//char m_work;
	//std::string m_school;
	//std::string m_email;
	//std::string m_blog;
	//std::string m_tel;
	//std::string m_mobile;
	//std::string m_note;
	//char m_beFriendValid;
	//std::string m_logindate;
	int m_lastserverid;
	unsigned char m_locked;
};

class CRNETAPP_EXPORT crLoginChatQueryData : public CRDataBase::crQueryData
{//����playerid��ѯaccount������
public:
	crLoginChatQueryData();
	crLoginChatQueryData(const crLoginChatQueryData& data);
	DataClass(CRNetApp, LoginChatQuery)
	virtual void addParam(int i, char *buf, int length);
	void buildQuerySql(int playerid);
	unsigned short getChatDBID();
	const std::string &getNickName() const;
	const std::string& getKey() const;
protected:
	unsigned short m_chatdbid;
	std::string m_nickname;
	std::string m_key;
};

class CRNETAPP_EXPORT crChatStateQueryData : public CRDataBase::crQueryData
{//����playerid��ѯaccount������
public:
	crChatStateQueryData();
	crChatStateQueryData(const crChatStateQueryData& data);
	DataClass(CRNetApp, ChatStateQuery)
	virtual void addParam(int i, char *buf, int length);
	void buildQuerySql(int playerid);
	char getChatState();
protected:
	char m_chatstate;
};

class CRNETAPP_EXPORT crChatStateNickNameQueryData : public CRDataBase::crQueryData
{//����playerid��ѯaccount������
public:
	crChatStateNickNameQueryData();
	crChatStateNickNameQueryData(const crChatStateNickNameQueryData& data);
	DataClass(CRNetApp, ChatStateNickNameQuery)
	virtual void addParam(int i, char *buf, int length);
	void buildQuerySql(int playerid);
	char getChatState();
	const std::string &getNickName() const;
protected:
	char m_chatstate;
	std::string m_nickname;
};

class CRNETAPP_EXPORT crJoinGroupQueryData : public CRDataBase::crQueryData
{//����playerid��ѯaccount������
public:
	crJoinGroupQueryData();
	crJoinGroupQueryData(const crJoinGroupQueryData& data);
	DataClass(CRNetApp, JoinGroupQuery)
	virtual void addParam(int i, char *buf, int length);
	void buildQuerySql(int playerid);
	char getChatState();
	unsigned short getChatDBID();
	const std::string &getNickName() const;
protected:
	char m_chatstate;
	unsigned short m_chatdbid;
	std::string m_nickname;
};

class CRNETAPP_EXPORT crPlayerFriendTableQueryData : public CRDataBase::crQueryData
{//����playerid��ѯplayerfriend������
public:
	crPlayerFriendTableQueryData();
	crPlayerFriendTableQueryData(const crPlayerFriendTableQueryData& data);
	DataClass(CRNetApp, PlayerFriendTableQuery)
	virtual void addParam(int i, char *buf, int length);
	void buildQuerySql(int myid);
	int getID();
	int getFriendID();
	const std::string& getColumnName() const;
	const std::string& getRemark() const;
protected:
	int m_id;
	int m_friendid;
	std::string m_columnname;
	std::string m_remark;
};

class CRNETAPP_EXPORT crPlayerFriendLeavewordQueryData : public CRDataBase::crQueryData
{//����playerfriendid��ѯplayerfriendrec������
public:
	crPlayerFriendLeavewordQueryData();
	crPlayerFriendLeavewordQueryData(const crPlayerFriendLeavewordQueryData& data);
	DataClass(CRNetApp, PlayerFriendLeavewordQuery)
	virtual void addParam(int i, char *buf, int length);
	void buildQuerySql(int playerfriendid);
	const CRCore::crStreamBuf *getLeaveword() const;
protected:
	CRCore::ref_ptr<CRCore::crStreamBuf> m_leaveword;
};

class CRNETAPP_EXPORT crPlayerGroupTableQueryData : public CRDataBase::crQueryData
{//����playerid��ѯplayergroup������
public:
	crPlayerGroupTableQueryData();
	crPlayerGroupTableQueryData(const crPlayerGroupTableQueryData& data);
	DataClass(CRNetApp, PlayerGroupTableQuery)
	virtual void addParam(int i, char *buf, int length);
	void buildQuerySql(int myid);
	int getID();
	const std::string& getRemark() const;
	int getGroupID();
protected:
	int m_id;
	int m_groupid;
	std::string m_remark;
};

class CRNETAPP_EXPORT crChatGroupTableQueryData : public CRDataBase::crQueryData
{//����groupname��ѯchatgroup������
public:
	crChatGroupTableQueryData();
	crChatGroupTableQueryData(const crChatGroupTableQueryData& data);
	DataClass(CRNetApp, ChatGroupTableQuery)
	virtual void addParam(int i, char *buf, int length);
	void buildQuerySql(const std::string& groupname);
	int getID();
	int getCreator();
	int getManager1();
	int getManager2();
	int getManager3();
protected:
	int m_id;
	int m_creator;
	int m_manager1;
	int m_manager2;
	int m_manager3;
};

class CRNETAPP_EXPORT crChatGroupTableByIDQueryData : public CRDataBase::crQueryData
{//����id��ѯGroup������
public:
	crChatGroupTableByIDQueryData();
	crChatGroupTableByIDQueryData(const crChatGroupTableByIDQueryData& data);
	DataClass(CRNetApp, ChatGroupTableByIDQuery)
	virtual void addParam(int i, char *buf, int length);
	void buildQuerySql(int id);
	const std::string& getGroupName() const;
	int getCreator();
	int getManager1();
	int getManager2();
	int getManager3();
protected:
	std::string m_groupname;
	int m_creator;
	int m_manager1;
	int m_manager2;
	int m_manager3;
};

class CRNETAPP_EXPORT crGroupMemberTableQueryData : public CRDataBase::crQueryData
{//����groupid��ѯgroupmember������
public:
	crGroupMemberTableQueryData();
	crGroupMemberTableQueryData(const crGroupMemberTableQueryData& data);
	DataClass(CRNetApp, GroupMemberTableQuery)
	virtual void addParam(int i, char *buf, int length);
	void buildQuerySql(int groupid);
	int getID();
	int getPlayerID();
	const std::string& getMemberName() const;
	const std::string& getMemberRemark() const;
protected:
	int m_id;
	int m_playerid;
	std::string m_membername;
	std::string m_memberremark;
};

class CRNETAPP_EXPORT crPlayerGroupLeavewordQueryData : public CRDataBase::crQueryData
{//����playergroupid��ѯplayergrouprec������
public:
	crPlayerGroupLeavewordQueryData();
	crPlayerGroupLeavewordQueryData(const crPlayerGroupLeavewordQueryData& data);
	DataClass(CRNetApp, PlayerGroupLeavewordQuery)
	virtual void addParam(int i, char *buf, int length);
	void buildQuerySql(int playergroupid);
	const CRCore::crStreamBuf *getLeaveword() const;
protected:
	CRCore::ref_ptr<CRCore::crStreamBuf> m_leaveword;
};

class CRNETAPP_EXPORT crBeFriendValidQueryData : public CRDataBase::crQueryData
{//����playerid��ѯaccount������
public:
	crBeFriendValidQueryData();
	crBeFriendValidQueryData(const crBeFriendValidQueryData& data);
	DataClass(CRNetApp, BeFriendValidQuery)
	virtual void addParam(int i, char *buf, int length);
	void buildQuerySql(int playerid);
	unsigned char getBeFriendValid();
    const std::string &getNickName() const;
	char getChatState();
protected:
	unsigned char m_beFriendValid;
	std::string m_nickname;
	char m_chatstate;
};

class CRNETAPP_EXPORT crChatDBIDQueryData : public CRDataBase::crQueryData
{//����playerid��ѯaccount������
public:
	crChatDBIDQueryData();
	crChatDBIDQueryData(const crChatDBIDQueryData& data);
	DataClass(CRNetApp, ChatDBIDQuery)
	virtual void addParam(int i, char *buf, int length);
	void buildQuerySql(int playerid);
	unsigned short getChatDBID(); 
protected:
	unsigned short m_chatdbid;
};

class CRNETAPP_EXPORT crPlayerFriendIDQueryData : public CRDataBase::crQueryData
{//����playerid,friendid��ѯplayerfriend������
public:
	crPlayerFriendIDQueryData();
	crPlayerFriendIDQueryData(const crPlayerFriendIDQueryData& data);
	DataClass(CRNetApp, PlayerFriendIDQuery)
	virtual void addParam(int i, char *buf, int length);
	void buildQuerySql(int playerid,int friendid);
	int getID(); 
protected:
	int m_id;
};

class CRNETAPP_EXPORT crPlayerGroupIDQueryData : public CRDataBase::crQueryData
{//����playerid,groupid��ѯplayergroup������
public:
	crPlayerGroupIDQueryData();
	crPlayerGroupIDQueryData(const crPlayerGroupIDQueryData& data);
	DataClass(CRNetApp, PlayerGroupIDQuery)
	virtual void addParam(int i, char *buf, int length);
	void buildQuerySql(int playerid,int groupid);
	int getID(); 
protected:
	int m_id;
};

class CRNETAPP_EXPORT crOnchatAccountLimitQueryData : public CRDataBase::crQueryData
{//��ѯaccount������
public:
	crOnchatAccountLimitQueryData();
	crOnchatAccountLimitQueryData(const crOnchatAccountLimitQueryData& data);
	DataClass(CRNetApp, OnchatAccountLimitQuery)
	virtual void addParam(int i, char *buf, int length);
	void buildQuerySql(int rows,int offset,int exceptid = 0);
	int getID();
	const std::string& getNickName() const;
	const std::string& getAddress() const;
protected:
	int m_id;
	std::string m_nickname;
	std::string m_address;
};

class CRNETAPP_EXPORT crChatGroupLimitQueryData : public CRDataBase::crQueryData
{//��ѯGroup������
public:
	crChatGroupLimitQueryData();
	crChatGroupLimitQueryData(const crChatGroupLimitQueryData& data);
	DataClass(CRNetApp, ChatGroupLimitQuery)
	virtual void addParam(int i, char *buf, int length);
	void buildQuerySql(int rows,int offset);
	int getID();
	const std::string& getGroupName() const;
	int getCreator();
protected:
	int m_id;
	std::string m_groupname;
	int m_creator;
};
}
#endif