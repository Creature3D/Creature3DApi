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
#ifndef CRNETAPP_NETCHATDATA_H
#define CRNETAPP_NETCHATDATA_H 1

#include <CRNetApp/appExport.h>
//#include <creature3d.h>
#include <CRNet/crNetDataManager.h>
#include <CRCore/crWchMsg.h>
#include <CRCore/thread/crMutex.h>
#include <CRCore/thread/crScopedLock.h>
#include <map>
#include <vector>
#include <deque>

namespace CRNetApp {

class CRNETAPP_EXPORT crNetChatData :  public CRCore::Referenced
{
public:
	crNetChatData();

	enum ChatState
	{
		OffLine,//����
		OnLine,//����
		Hide,//����
		Leave,//�뿪
		Busy,//æµ
		Quiet,//����
		UserDefine//�Զ���
	};

	class CRNETAPP_EXPORT crChatFriend : public CRCore::Referenced
	{
	public:
		crChatFriend();
		void setID(int id);
		int getID();
		void setPlayerID(int playerid);
		int getPlayerID();
		void setColumnName(const std::string &columnName);
		const std::string &getColumnName() const;
		void setRemark(const std::string &remark);
		const std::string &getRemark() const;
		void setFriendChatState(char chatstate);
		char getFriendChatState();

		void setNickName(const std::string &nickName);
		const std::string &getNickName() const;
		void recChat(const std::string &str);
		void getChatRec(std::vector<std::string> &recArray);
		void loadChatRec(std::vector<std::string> &recArray);
		void setHasNewMsg(bool newmsg);
		bool getHasNewMsg();
	protected:
		virtual ~crChatFriend();
		int m_id;
		int m_playerid;
		char m_friendChatState;
		std::string m_columnName;//������
		std::string m_remark;//��ע	
	protected://AccountDB
		std::string m_nickName;
		CRCore::ref_ptr<CRCore::crStreamBuf> m_chatRec;
		GNE::Mutex m_recMutex;
		bool m_hasNewMsg;
	};
	class CRNETAPP_EXPORT crChatGroupMember : public CRCore::Referenced
	{
	public:
		crChatGroupMember();
		void setMemberID(int memberid);
		int getMemberID();
		void setPlayerID(int playerid);
		int getPlayerID();
		void setMemberName(const std::string &memberName);
		const std::string &getMemberName() const;
		void setMemberRemark(const std::string &remark);
		const std::string &getMemberRemark() const;
		void setMemberChatState(char chatstate);
		char getMemberChatState();

		void setNickName(const std::string &nickName);
		const std::string &getNickName() const;
	protected:
		int m_memberid;
		int m_playerid;
		char m_memberidChatState;
		std::string m_memberName;//Ⱥ��Ա��Ƭ
		std::string m_memberRemark;//Ⱥ��Ա��ע

	protected://AccountDB
		std::string m_nickName;
	};
	class CRNETAPP_EXPORT crChatGroup : public CRCore::Referenced
	{
	public:
		crChatGroup();
		void setID(int id);
		int getID();
		void setGroupID(int groupid);
		int getGroupID();
		void setGroupName(const std::string &groupName);
		const std::string &getGroupName() const;
		void setGroupRemark(const std::string &remark);
		const std::string &getGroupRemark() const;
        void setCreator(int creator);
		int getCreator();
		void setManager1(int manager);
		int getManager1();
		void setManager2(int manager);
		int getManager2();
		void setManager3(int manager);
		int getManager3();
		typedef std::map<int, CRCore::ref_ptr<crChatGroupMember> > ChatMemberMap;//playerid,��Ա
		void insertMember(crChatGroupMember *data);
		void removeMember(int playerid);
		void clearMemberMap();
		crChatGroupMember *getMember(int playerid);
		void lockMemberMap();
		ChatMemberMap &getMemberMap();
		void unlockMemberMap();
		void recChat(const std::string &str);
		void getChatRec(std::vector<std::string> &recArray);
		void loadChatRec(std::vector<std::string> &recArray);
		void setHasNewMsg(bool newmsg);
		bool getHasNewMsg();
	protected:
		virtual ~crChatGroup();
		int m_id;
		int m_groupid;
		std::string m_groupName;//Ⱥ��
		std::string m_remark;//Ⱥ��ע
		int m_creator;//
		int m_manager1;
		int m_manager2;
		int m_manager3;
		ChatMemberMap m_chatMemberMap;//Ⱥ��Ա
	    CRCore::crMutex m_memberMutex;
		CRCore::ref_ptr<CRCore::crStreamBuf> m_chatRec;
		GNE::Mutex m_recMutex;
		bool m_hasNewMsg;
	};

	typedef std::map<int, CRCore::ref_ptr<crChatFriend> > FriendMap;//playerid������
	void insertFriend(crChatFriend *data);
	void removeFriend(int playerid);
	void clearFriendMap();
	crChatFriend *getFriend(int playerid);
	bool isFriend(int playerid);
	void lockFriendMap();
	FriendMap &getFriendMap();
	void unlockFriendMap();

	typedef std::map<int, CRCore::ref_ptr<crChatGroup> > ChatGroupMap;//id,crChatGroup Ⱥ
	void insertChatGroup(crChatGroup *chatGroup);
	crChatGroup *getChatGroup(int playergroupid);
	crChatGroup *findChatGroup(int groupid);
	crChatGroup *findChatGroup(const std::string &groupname);
	void removeChatGroup(int playergroupid);
	void clearGroupMap();
	int getNumChatGroup();
	void lockGroupMap();
	ChatGroupMap &getChatGroupMap();
	void unlockGroupMap();

	void setMyChatState(ChatState chatState);
	ChatState getMyChatState();

	enum ChatTargetType
	{
		ChatFriend,
		chatgroup,
	};
	void setChatTarget(unsigned char targetType, Referenced *target);
	unsigned char getChatTargetType();
    Referenced *getChatTarget();
protected:
	ChatState m_myChatState;
	FriendMap m_friendMap;
	ChatGroupMap m_chatGroupMap;
	CRCore::crMutex m_friendMutex;
	CRCore::crMutex m_groupMutex;

    unsigned char m_chatTargetType;
	CRCore::ref_ptr<Referenced> m_chatTarget;//��ǰ�������
};

}

#endif
