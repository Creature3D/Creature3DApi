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
#ifndef CRNETAPP_CRDATACLASS_H
#define CRNETAPP_CRDATACLASS_H 1

#include <CRNetApp/appExport.h>
#include <CRNetApp/appDataParam.h>
#include <CRCore/crStreamBuf.h>
#include <CRCore/crHandleManager.h>
#include <CRCore/crDataManager.h>
#include <CRGUI/crImageStage.h>
#include <CRCore/thread/crMutex.h>
#include <CRCore/thread/crScopedLock.h>
#include <CRNetApp/appNetChatData.h>
#include <CREncapsulation/crTableIO.h>
#include <CRCore/crArgumentParser.h>
#include <CRCore/crWidgetNode.h>
#include <gnelib.h>
#include <vector>
#include <list>
#include <string>
#include <map>
namespace CRNetApp{
class crInstanceItem;
class crGameTask;
class crWaypoint;
struct ItemUseParam;
typedef std::map< int,CRCore::ref_ptr<CREncapsulation::crTableIO> >TableIOMap;
typedef std::map< int,std::string >TableFileMap;
typedef std::map< int, unsigned char > GMMap;//playerid,Ȩ��
typedef std::map< int, float > WordValueMap;//�ֵ��
class CRNETAPP_EXPORT crGlobalData : public CRCore::crData
{
public:
	crGlobalData();
	crGlobalData(const crGlobalData& data);
	DataClass(CRNetApp, Global)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);

	inline std::string& gClientCfg() { return g_clientfile; }//��������������
	inline std::string& gStartDate() { return g_startDate; }//��������������
	inline float gUnitScale() { return g_unitScale; }
	inline unsigned char gMaxLapover() { return g_maxLapover; }
	inline float gSalerate() { return g_salerate; }
	inline float gRemoveOutRangeTime() { return g_removeOutRangeTime; }
	inline float gRecycleIDTime() { return g_recycleIDTime; }
	inline float gRecycleStreamIDTime_in() { return g_recycleStreamIDTime_in; }
	inline float gRecycleStreamIDTime_out() { return g_recycleStreamIDTime_out; }
	inline unsigned char gMaxgroupmember() { return g_maxgroupmember; }
	inline unsigned char gMaxSkillLevelLearn() { return g_maxSkillLevelLearn; }
	inline float gMinFollowDistance() { return g_minFollowDistance; }
	inline float gMinItemUseRange() { return g_minItemUseRange; }
	inline unsigned char gItemVisiableDelay() { return g_itemVisiableDelay; }
	inline int gMaxRecBufSize() { return g_maxRecBufSize; }
	inline std::string gGameChatRecFile() { return g_gameChatRecFile; }
	inline std::string gChatMsgRecFile() { return g_chatMsgRecFile; }
	inline int gNumGameChatShow() { return g_numGameChatShow; }
	inline int gNumGameChatClear() { return g_numGameChatClear; }
	inline unsigned short gMaxInRangePlayer() { return g_maxInRangePlayer; }
	inline unsigned short gMaxInRangeItem() { return g_maxInRangeItem; }
	inline float gStreamCacheMaxTime() { return g_streamCacheMaxTime; }
	inline unsigned char gMaxDisplayTaskTrace() { return g_maxDisplayTaskTrace; }
	inline float gRemoveItemChildTime() { return g_removeItemChildTime; }
	inline float gControllerTime() { return g_controllerTime; }
	inline float gLayerHeight() { return g_layerHeight; }
	inline float gWalkHeight() { return g_walkHeight; }
	inline unsigned char gMaxRoleCanJoin() { return g_maxRoleCanJoin; }
	inline short gFirstGameSceneID() { return g_firstGameSceneID; }
	inline int gGameID() { return g_gameid; }
	inline int gMainRoleAItemID() { return g_mainRoleAItemID; }
	inline int gMainRoleAMetierID() { return g_mainRoleAMetierID; }
	inline unsigned char gLoginConnectCount() { return g_loginConnectCount; }
	inline const std::string& gDynamicDownloadTabName() { return g_dynamicDownloadTabName; }
	inline CRCore::ref_ptr<CREncapsulation::crTableIO> gGameGlobalTable() { return g_gameGlobalTable.get(); }
	inline CRCore::ref_ptr<CREncapsulation::crTableIO> gNewDynamicDownloadTable() { return g_newDynamicDownloadTable.get(); }
	//inline CRCore::ref_ptr<CREncapsulation::crTableIO> gGMTable() { return g_gmTable.get(); }
	inline CRCore::ref_ptr<CREncapsulation::crTableIO> gGlobalTable(int id)
	{ TableIOMap::iterator itr = g_globalTables.find(id); return itr != g_globalTables.end()?itr->second.get():NULL; }
	inline std::string gGlobalTableFile(int id)
	{
		TableFileMap::iterator itr = g_globalTableFileMap.find(id); return itr != g_globalTableFileMap.end() ? itr->second : "";
	}
	inline std::string gGameGlobalValue(int id,int viplv = 0)
	{
		CREncapsulation::crTableIO::StrVec record;
		if(g_gameGlobalTable->queryOneRecord(0,CRCore::crArgumentParser::appItoa(id),record)>=0)
		{
			if(viplv+1<record.size())
			{
				if(record[viplv+1].empty())
					return record[1];
				else
					return record[viplv+1];
			}
		}
		return "NULL";
	}
	inline float gWorldValue(int id)
	{
		WordValueMap::iterator itr = g_wordValueMap.find(id);
		return itr != g_wordValueMap.end() ? itr->second : 0.0f;
	}
	void UpdateWorldValue(int id, float value);
	inline bool gShowDebugInfo() { return g_showDebugInfo; }
	inline bool gEnableRobotTest() { return g_enableRobotTest; }
	inline float gSightRange() { return g_sightRange; }
	inline short gEyePointRange() { return g_eyePointRange; }
	inline short gEyePointHeight() { return g_eyePointHeight; }
	inline float gItemAdjustAngular() { return g_itemAdjustAngular; }
	inline float gFollowDelta() { return g_followDelta; }
	inline float gPortScopeSqr() { return g_portScopeSqr; }
	inline float gItemVisiableInterval() { return g_itemVisiableInterval; }
	inline float gDynamicTryWait() { return g_dynamicTryWait; }
	//void reloadGMTable(const std::string &filename);
	void reloadGameGlobalTable(const std::string &filename);
	void reloadGlobalTable(int id);
	void reloadGlobalTable(int id,const std::string &filename);
	void lockGMMap();
	GMMap &getGMMap();
	short getGMAuthority(int playerid);//-1��ʾ��GM
	void unlockGMMap();
protected:
	////����������ʱ��ע������0,0,0��Ϊ����վ���㡣
	std::string g_clientfile;//client.cfg�ļ���
	std::string g_startDate;//����������ʱ��
	float g_unitScale;
	unsigned char g_maxLapover;
	float g_salerate;
	float g_removeOutRangeTime;//100s
	float g_recycleIDTime;//110s
	float g_recycleStreamIDTime_in;//��������(��������)����ʱ��
	float g_recycleStreamIDTime_out;//��������ʱ��
	unsigned char g_maxgroupmember;
	unsigned char g_maxSkillLevelLearn;//��ѧ������߼��ܵȼ�
	float g_minFollowDistance;
	float g_minItemUseRange;//��������С��������
	float g_followDelta;
	unsigned char g_itemVisiableDelay;//ms
	int g_maxRecBufSize;//0.5MB
	std::string g_gameChatRecFile;
	std::string g_chatMsgRecFile; 
	int g_numGameChatShow;
	int g_numGameChatClear;
	unsigned short g_maxInRangePlayer;//32;
	unsigned short g_maxInRangeItem;
	float g_streamCacheMaxTime;
	unsigned char g_maxDisplayTaskTrace;
	float g_removeItemChildTime;//20s
	float g_controllerTime;//0.5s
	float g_layerHeight;//2.5��
	float g_walkHeight;//0.8
	unsigned char  g_maxRoleCanJoin;//���Բ�ս������ɫ����
	short g_firstGameSceneID;
	int g_gameid;
	int g_mainRoleAItemID;
	int g_mainRoleAMetierID;
	unsigned char g_loginConnectCount;//��¼�������������
	std::string g_dynamicDownloadTabName;
	CRCore::ref_ptr<CREncapsulation::crTableIO> g_gameGlobalTable;
	CRCore::ref_ptr<CREncapsulation::crTableIO> g_newDynamicDownloadTable;
	//CRCore::ref_ptr<CREncapsulation::crTableIO> g_gmTable;
	TableIOMap g_globalTables;
	TableFileMap g_globalTableFileMap;
	////////DebugInfo
	bool g_showDebugInfo;
	bool g_enableRobotTest;
	float g_sightRange;
	short g_eyePointRange;//
	short g_eyePointHeight;
	float g_itemAdjustAngular;
	float g_portScopeSqr;
	float g_itemVisiableInterval;
	float g_dynamicTryWait;//item��̬��ײѰ·���Եȴ�ʱ��
	CRCore::ref_ptr<CREncapsulation::crTableIO> g_wordValueTable;
	WordValueMap g_wordValueMap;//���ٻ���
	GNE::Mutex m_gmMapMutex;
	GMMap m_gmMap;
};
class crRecvFileStream;
class CRNETAPP_EXPORT crGameClientData : public crGlobalData
{
public:
	crGameClientData();
	crGameClientData(const crGameClientData& data);
    DataClass(CRNetApp, GameClient)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);

	typedef std::map< CRCore::ref_ptr<CRGUI::crImageStage>,  CRCore::ref_ptr<crNetChatData::crChatFriend> > FriendChatMap;
	void insertFriendChatMap(CRGUI::crImageStage *stage, crNetChatData::crChatFriend *chatFriend);
	crNetChatData::crChatFriend *getChatFriend(CRGUI::crImageStage *stage);
	CRGUI::crImageStage *getChatFriendStage(crNetChatData::crChatFriend *chatFriend);
	//DownloadServer��̬����
	typedef std::deque<std::string> DownloadFileDeque;//filename�������ļ�����
	typedef std::map<int,DownloadFileDeque> DownloadFileTaskMap;//������ɺ�Ҫ��������Ϣ
	bool insertDownloadFile(int msgparam, const std::string &file);//����false��ʾ���ļ��Ѿ����������ض���
	void startDownloadFile(int msgparam, short netType);
	void recvedFileStream(crRecvFileStream *fileStream);//�������
	void fileNotExist(unsigned short downloadFlg,const std::string &file,short netType);//�ļ�������

	//HttpDown ��̬����
	//void lockHttpDownload();
	//void unlockHttpDownload();
	void insertHttpDownloadFile(int msgparam, const std::string &file);//����false��ʾ���ļ��Ѿ����������ض���
	void startHttpDownloadTask(int msgparam);
	void downloadUpdate();
protected:
	FriendChatMap m_friendChatMap;
    CRCore::crMutex m_friendChatMapMutex;

	DownloadFileTaskMap m_downloadFileTaskMap;
	GNE::Mutex m_downloadFileMutex;

	//HttpDown ��̬����
	DownloadFileTaskMap m_perhttpDownloadTaskMap;
	DownloadFileTaskMap m_httpDownloadTaskMap;
	GNE::Mutex m_perhttpDownloadMutex;
	GNE::Mutex m_httpDownloadMutex;
};
//crRole Data
typedef std::vector<int> IntVec;//����ʵ��ID�����ܵȼ�����ڼ���Data��
//typedef std::vector<int> EquipVec;//װ������ʵ��ID 
//typedef std::vector<int> ThingVec;//��Ʒ����ʵ��ID����Ʒ�����������ƷData��
//typedef std::vector<int> EquipOnVec;//װ�������ϵģ�ʵ��ID
//typedef std::vector<int> QuickVec;//�������ʵ��ID���ɴ�ż��ܻ��ʹ�õ���Ʒ
//typedef std::vector<int> Storage;//�ֿ⣬ʵ��ID
typedef std::set<int> GroupMemberSet;//���ѵ�playerid, ����Ҫ����
//typedef std::vector<int> FriendVec;//����playerid
typedef std::set<int> MetierSkillASet;//ְҵ���ܳ���ID

typedef std::map<int,int> AttackMap;//��ͨ��������ID��ʵ��ID�����ܵȼ�����ڼ���Data��
typedef std::map<int,int> SkillMap;//���ܳ���ID��ʵ��ID�����ܵȼ�����ڼ���Data��
typedef std::vector<CRCore::crVector2f> PatrolPointVec;//��Ϊ��λ
//typedef std::map<_crInt64,float> PlayerEnmityMap;//playerid,roleid,��޶�
//typedef std::map<int,float> NpcEnmityMap;//itemid,��޶�
typedef std::multimap< CRCore::ref_ptr<crInstanceItem>,int > EnmityMap;//item,enmity
typedef std::multimap< float, CRCore::ref_ptr<crInstanceItem>, std::less<float> > InPatrolEnemyMap;//dist(��Ϊ��λ),item
typedef std::map<int,float> ItemDropMap;//item abstractid,������ װ�����䱻���ʰȡ��crCreateItemChildPacket
typedef std::map<int, CRCore::ref_ptr<crGameTask> >GameTaskMap;//taskid
typedef std::multimap<int,int> BackPackMap;//����ID,ʵ��ID
typedef std::multimap<int,int> StorageMap;//�ֿ� ����ID,ʵ��ID
typedef std::multimap<int,int> EquipOnMap;//����ID,ʵ��ID
//typedef std::map<int,int> QuickMap;//����ID,ʵ��ID
typedef std::list< std::pair<int,int> > QuickList;//����ID,ʵ��ID
typedef std::multimap<int,unsigned char> ItemCountMap;//����ID,count
//typedef std::map<int,int> NpcSaleItemMap;//����ID,ʵ��ID
//Npc����������Ʒ��������������ϵͳͶ����Ʒ������������-1��ʾ���0��ʾû�п�档ϵͳÿ��һ��ʱ��λ���������ʽΪNPC������
//typedef std::pair<short,int> CountPricePair;//����,�ۼ� �ۼ�0��ʾ�۸��itemdata��ȡ
//typedef std::pair<int,CountPricePair> SaleItemPair;//ʵ��ID,����,�ۼ�
typedef std::multimap<int,CRCore::crVector3i> SaleItemMap;//����ID,ʵ��ID,����,�ۼ�
typedef std::set<int> ExchangePlayerSet;//playerid
typedef std::list< std::pair<char,int> > QuickKeyVec;//key,����ID
typedef std::vector<int> EquipComposeRequestVec;//abstractid
typedef std::map<unsigned short,std::string> ActStateMap;//״̬ID,������  ��ɫ�����⶯��ģʽ �Ի�״̬�����ŵ�״̬�����⽻��״̬�ȣ��������������ֶ�����
class CRNETAPP_EXPORT crRoleData : public CRCore::crData
{
public:
	crRoleData();
	crRoleData(const crRoleData& data);
	DataClass(CRNetApp, Role)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(_crInt64 msg);
protected:
	void serverCheckData(crInstanceItem *item, _crInt64 completeMsg/*int& count*/);
	void checkItemChild(CRNet::crNetConductor *netConductor,crInstanceItem *item,int first,int &second,std::set<int>&AbstractIDSet,int &count);
	void checkItemChildMultiMap(CRNet::crNetConductor *netConductor,crInstanceItem *item,int first,int &second,std::set<int>&TemporaryAbstractIDSet,int &count);
	void clientCheckData(crInstanceItem *item);
	void clientCheckItemChild(crInstanceItem *item,int first,int &second);
	void clientCheckItemChildMultiMap(crInstanceItem *item,int first,int &second,std::set<int>&TemporaryItemIDSet);
	void gameServerCheckData(crInstanceItem *item);
	void gameServerCheckItemChild(crInstanceItem *item,int first,int &second,unsigned short gamedbid);
	void gameServerCheckItemChildMultiMap(crInstanceItem *item,int first,int &second);
	
	unsigned char m_maxattack;
	unsigned char m_maxskill;
	unsigned char m_maxbackpack;//�������������
	unsigned char m_maxstorage;
	unsigned char m_maxequipon;//�ӽű���ȡ�����ü�¼�����ݿ�
	unsigned char m_maxquick;//�ӽű���ȡ�����ü�¼�����ݿ�

	AttackMap m_attackMap;//
	SkillMap m_skillMap;//��ѧ���ļ���
	//BackPackMap m_backPackMap;
	//StorageMap m_storageMap;//�ֿ����NPC/ITEM�����������������
	//ItemCountMap m_storageCountMap;
	EquipOnMap m_equipOnMap;
	//QuickList   m_quickList;
	//QuickKeyVec m_quickKeyVec;//��ݼ�����
	//ItemCountMap m_itemCountMap;

	//ItemDropMap m_itemDropMap;
	//SaleItemMap m_saleItemMap;//��Ҫ���紫��
	//4 m_exchangePlayerSet;//����ʱ�̲��������ݣ�ֻ�ڷ�����������Ҫͬ�����ͻ��ˣ���m_saleItemMap�б仯ʱ��ͬ������������

	short m_sightRange;//��Ұ �ӽű���ȡ�����ü�¼�����ݿ�
	short m_guardRange;//����뾶
	short m_eyeHeight;//�۾��߶� �ӽű���ȡ�����ü�¼�����ݿ�
	int m_hp;
	int m_mp;
	int m_attack;
	int m_defend;
	short m_magicDefend;//����
	short m_speed;//�ƶ��ٶ�
	short m_stealth;//������룬�Է�����Ұ-�������
	short m_stealthspy;//��������
	short m_hitratio;//������
	//float m_attackSpeed;//����
	short m_attackSpeed;//�����ٶ�����ǧ�ֱ�
	short m_skillSpeed;//ʩ���ٶ�����ǧ�ֱ�
	unsigned char m_armourType;//��������
	//����ʱ������
	unsigned char m_targetType;
	//CRCore::ref_ptr<CRCore::crNode> m_targetNode;
	int m_targetID;
	int m_targetRoleID;//m_targetType=roleʱ��Ч
	CRCore::crVector3 m_targetPosition;
	CRCore::crVector3 m_moveToPosition;//IS_MoveToPos IS_MoveToUseSkill IS_AttackToPos
	unsigned char m_itemState;
	unsigned char m_itemState_rec;
	unsigned int m_guiseState;//����״̬
	unsigned char m_camp;//��Ӫ//0���������ɹ���,�۲��ߣ� 1��ս�������˶����Զ��乥���� 2���ID����2��ʼ���涼�����ID����ͬ��Ӽ���Թ�����
	unsigned char m_fightmode;//ս��ģʽ
	float m_followDistance;//����Ŀ�꣬��Ŀ�걣�ֵľ���
	CRNetApp::PatrolPointVec m_patrolPointVec;//Ѳ�ߵ�����
	char m_patrolIndex;//��ǰѲ������
	unsigned char m_patrolLoopMode;//0:��ѭ�� 1:LOOP 2:SWING
	//int m_baseEnmity;//������޶�
	//CRNetApp::PlayerEnmityMap m_playerEnmityMap;//����ҵĳ�޶�
	//CRNetApp::NpcEnmityMap m_npcEnmityMap;//��NPC�ĳ�޶�
	EnmityMap m_enmityMap;
	InPatrolEnemyMap m_inpatrolEnemyMap;

	float m_rthp;
	float m_rtmp;
	//float m_currentUseItemProtectTime;//��ǰ�ļ��ܱ���ʱ��
	int m_currentAttackID;//��ǰѡ�����ͨ����itemid
	int m_aboutToUseItemID;//��Ҫʹ�õ�itemid�����缴��Ҫʩ�ż��ܣ�ʹ�ù�֮������Ϊ0
	//����״̬�����Ե�Ӱ��ֵ������ͬ���Եĸ���Ӱ�죬���߻Ḳ��ǰ��
	short m_extrahp;
	short m_extrahp_rd;//read
	short m_extramp;
	short m_extramp_rd;
	short m_extraAttack;
	short m_extraAttack_rd;
	short m_extraDefend;//����״̬�Է������Ե�Ӱ��ֵ
	short m_extraDefend_rd;
	//short m_extraSpeed;
	//short m_extraSpeed_rd;
	short m_extraStealth;
	short m_extraStealth_rd;
	short m_extraStealthSpy;
	short m_extraStealthSpy_rd;
	short m_extraHitratioPercent;//�����ʰٷֱ�
	short m_extraHitratioPercent_rd;
	short m_extraAttackSpeed;//�����ٶ������ٷֱ�
	short m_extraAttackSpeed_rd;
	short m_extraSkillSpeed;//ʩ���ٶ������ٷֱ�
	short m_extraSkillSpeed_rd;
	unsigned int m_extraGuise;//����״̬
	unsigned int m_extraGuise_rd;
	short m_extraRadius;//��ײ�뾶�ٷֱ�
	short m_extraRadius_rd;
	short m_extraIgnoreDefend;//��͸�����׺��Ӱٷֱ�
	short m_extraIgnoreDefend_rd;
	short m_extraIgnoreMagicDefend;//������͸�����׺��Ӱٷֱ�
	short m_extraIgnoreMagicDefend_rd;
	short m_extraSightRange;
	short m_extraSightRange_rd;

	short m_crit;//����
	short m_parry;//��
	short m_dodge;//����
	short m_extraCrit;
	short m_extraCrit_rd;
	short m_extraParry;
	short m_extraParry_rd;
	short m_extraDodge;
	short m_extraDodge_rd;
	bool m_isCrit;//
	bool m_isParry;
	bool m_isDodge;//
	bool m_isMiss;//�Ƿ�δ����

	short m_extraAttackPercent;
	short m_extraAttackPercent_rd;
	short m_extraSpeedPercent;
	short m_extraSpeedPercent_rd;
	short m_extraDefendPercent;
	short m_extraDefendPercent_rd;
	short m_extraMagicDefendPercent;//����״̬�Է������Ե�Ӱ��ֵ
	short m_extraMagicDefendPercent_rd;
	short m_extraBuildAttackPercent;
	short m_extraBuildAttackPercent_rd;
	short m_extraCritPercent;
	short m_extraCritPercent_rd;
	short m_extraParryPercent;
	short m_extraParryPercent_rd;
	short m_extraDodgePercent;
	short m_extraDodgePercent_rd;
	short m_extraAttackDist;//����
	short m_extraAttackDist_rd;//����
	short m_extraAttackAbsorbHP;
	short m_extraAttackAbsorbHP_rd;
	short m_extraSkillAbsorbHP;
	short m_extraSkillAbsorbHP_rd;
	short m_extraAttackDamageBack;
	short m_extraAttackDamageBack_rd;
	short m_extraSkillDamageBack;
	short m_extraSkillDamageBack_rd;
	float m_extraRTHP;
	float m_extraRTHP_rd;

	short m_inbornHPPercent;
	short m_inbornMPPercent;
	short m_inbornAttackPercent;
	short m_inbornDefendPercent;
	short m_inbornMagicDefendPercent;
	short m_inbornBuildAttackPercent;
	short m_inbornSpeed;
	short m_inbornAttackSpeedPercent;
	short m_inbornSkillSpeedPercent;
	short m_inbornSightRange;
	short m_inbornAttackDist;//����
	///
	short m_inbornStealth;
	short m_inbornStealthSpy;
	short m_inbornCrit;
	short m_inbornParry;
	short m_inbornDodge;
	short m_inbornIgnoreDefend;
	short m_inbornIgnoreMagicDefend;

	unsigned char m_inbornIgnoreDodge;//����Ŀ������ ���ɵ���
	short m_inbornAttackDamageBack;//�����˺�����
	short m_inbornSkillDamageBack;//�����˺�����
	short m_inbornAttackAbsorbHP;//������Ѫ
	short m_inbornSkillAbsorbHP;//������Ѫ
	short m_inbornCritPower;//������ ���ɵ��ӣ�����ɱ������200%��Ϊ250%��->��������,�ٷֱ�
	_crInt32 m_inbornSputtering;//�����˺�������뾶(unsigned short)���˺��ٷֱȣ�unsigned short����

	short m_inbornAttackDamage;//�����˺������˺�����
	short m_inbornSkillDamage;
	short m_extraAttackDamage;
	short m_extraAttackDamage_rd;
	short m_extraSkillDamage;
	short m_extraSkillDamage_rd;

	short m_inbornSkillDamageIncrease;//���˼ӳ�
	short m_extraSkillDamageIncrease;//���˼ӳ�
	short m_extraSkillDamageIncrease_rd;//���˼ӳ�
	short m_inbornAttackDamageIncrease;//���˼ӳ�
	short m_extraAttackDamageIncrease;//���˼ӳ�
	short m_extraAttackDamageIncrease_rd;//���˼ӳ�

	unsigned char m_extraIgnoreDodge;
	unsigned char m_extraIgnoreDodge_rd;
	short m_extraCritPower;
	short m_extraCritPower_rd;
	_crInt32 m_extraSputtering;//�����˺�������뾶(unsigned short)���˺��ٷֱȣ�unsigned short����
	_crInt32 m_extraSputtering_rd;//�����˺�������뾶(unsigned short)���˺��ٷֱȣ�unsigned short����

	short m_inbornHitratioPercent;//�����ʰٷֱ�

	//short m_cureEffectPercent;//�ظ�Ч���ٷֱ�
	short m_extraCureEffectPercent;//�ظ�Ч���ٷֱ�
	short m_extraCureEffectPercent_rd;
	short m_inbornCureEffectPercent;

	CRNetApp::ActStateMap m_actStateMap;
	unsigned short m_currentActState;//0��ʾδ��������״̬ �ͻ��˸����¼���ı��ָ������Ҫ����ͬ��
	float m_currentActDuration;//�ͻ��˸����¼���ı��ֵ������Ҫ����ͬ��
	//CRCore::crVector2 m_halfLengths;//itemcollidesize,�ӽű���ȡ���������ݿ⣬����Ҫ����ͬ��,��ײ�뾶�������뾶
	CRCore::crVector3 m_halfPhysicsBox;//itemcollidesize,�ӽű���ȡ���������ݿ⣬����Ҫ����ͬ��,��ײ�뾶�������뾶
	CRCore::ref_ptr<ItemUseParam> m_itemUseParam;//�����ͷ�
	CRCore::ref_ptr<ItemUseParam> m_attackUseParam;//��ͨ����
	/////////////////////////////////////
	//����״̬��Ϣ
	CRCore::ref_ptr<CRCore::crData> m_extraDataClass;//����״̬��ͬ������
	//ʹ�ü���ʱ�ĸ���״ֻ̬��ʹ��ʱ��ͬ�����������
	//װ���ĸ���״̬�������������á�
	////////////////////////

	//CRCore::ref_ptr<CRCore::crStreamBuf> m_dataStream;//==crRole::m_stream
	GNE::Mutex m_dataMutex;
	static GNE::Mutex m_saveMutex;
};
class CRNETAPP_EXPORT crRpgGameRoleData : public crRoleData
{
public:
	crRpgGameRoleData();
	crRpgGameRoleData(const crRpgGameRoleData& data);
	DataClass(CRNetApp, RpgGameRole)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(_crInt64 msg);
protected:
	//void serverCheckData(crInstanceItem *item, int &count);
	//void checkItemChild(CRNet::crNetConductor *netConductor,crInstanceItem *item,int first,int &second,int &count);
	//void checkItemChildMultiMap(CRNet::crNetConductor *netConductor,crInstanceItem *item,int first,int &second,std::set<int>&TemporaryAbstractIDSet,int &count);
	//void clientCheckItemChild(crInstanceItem *item,int first,int &second);
	//void clientCheckItemChildMultiMap(crInstanceItem *item,int first,int &second,std::set<int>&TemporaryItemIDSet);
	//short m_sightRange;//��Ұ �ӽű���ȡ�����ü�¼�����ݿ�
	//int m_hp;
	//int m_mp;
	//short m_attack;
	//short m_defend;
	//short m_speed;
	//float m_attackSpeed;//����

	//Tank����
	short m_currentSpeed;//��ǰ�ٶȣ�m_speed = ����ٶ�
	short m_acceleration;//���ٶ�
	short m_damp;//���� ���� = m_currentSpeed * m_damp;
	float m_currentAngular;//��ǰ���ٶ�,��λ�ǻ���
	short m_angularAccel;//�Ǽ��ٶȣ���λ�ǽǶ�/s
	short m_angularDamp;//���ٶ�˥������λ�ǽǶ�/s
	short m_maxAngular;//�����ٶȣ���λ�ǽǶ�/s

	unsigned char m_level;
	int m_experience;
	int m_gold;
	short m_strength;
	short m_agility;
    short m_intellect;
	//unsigned char m_camp;

	//unsigned char m_maxattack;
	//unsigned char m_maxskill;
	//unsigned char m_maxbackpack;//�������������
	//unsigned char m_maxstorage;
	//unsigned char m_maxequipon;//�ӽű���ȡ�����ü�¼�����ݿ�
	//unsigned char m_maxquick;//�ӽű���ȡ�����ü�¼�����ݿ�

	//AttackMap m_attackMap;//
	//SkillMap m_skillMap;//��ѧ���ļ���
	//BackPackMap m_backPackMap;
 //   StorageMap m_storageMap;//�ֿ����NPC/ITEM�����������������
	//ItemCountMap m_storageCountMap;
 //   EquipOnMap m_equipOnMap;
 //   QuickList   m_quickList;
	//QuickKeyVec m_quickKeyVec;//��ݼ�����
	//ItemCountMap m_itemCountMap;

	//�������ݴӽű���ȡ�������¼�����ݿ�
	std::string m_itemIcon;//ͼ��
	//PatrolPointVec m_patrolPointVec;//Ѳ�ߵ�����
	short m_expToKiller;
	short m_goldToKiller;
 //   ItemDropMap m_itemDropMap;
	//SaleItemMap m_saleItemMap;//��Ҫ���紫��
	//ExchangePlayerSet m_exchangePlayerSet;//����ʱ�̲��������ݣ�ֻ�ڷ�����������Ҫͬ�����ͻ��ˣ���m_saleItemMap�б仯ʱ��ͬ������������

    unsigned short m_attrPoint;//δ��������Ե�,ÿ��1�����5�㣬ע������������
	unsigned short m_skillPoint;//δʹ�õļ��ܵ�,ÿ��1�����2�㣬ע������������

	//����Ϊ����ʱ�̲��������ݣ�����¼��datastream
	//mouse pick packet
	//��Ҫ����ͬ�������� NetControl Data
	//unsigned char m_targetType;
	//CRCore::ref_ptr<CRCore::crNode> m_targetNode;
	//int m_targetID;
	//int m_targetRoleID;//m_targetType=roleʱ��Ч
	//CRCore::crVector3 m_targetPosition;
	//unsigned char m_itemState;
	//unsigned char m_guiseState;//����״̬
	//float m_followDistance;//����Ŀ�꣬��Ŀ�걣�ֵľ���
    //����ʱ������
	//float m_rthp;
	//float m_rtmp;
	short m_kill;//��ǰս��ɱ����
	short m_dead;//��ǰս����������
 //   /////////////////////////////////////
	////����״̬��Ϣ
	//CRCore::ref_ptr<CRCore::crData> m_extraDataClass;//����״̬��ͬ������
	////ʹ�ü���ʱ�ĸ���״ֻ̬��ʹ��ʱ��ͬ�����������
	////װ���ĸ���״̬�������������á�
	//////////////////////////
	//float m_currentUseItemProtectTime;//��ǰ�ļ��ܱ���ʱ��

    /////����������
	//int m_currentAttackID;//��ǰѡ�����ͨ����itemid
	//int m_aboutToUseItemID;//��Ҫʹ�õ�itemid�����缴��Ҫʩ�ż��ܣ�ʹ�ù�֮������Ϊ0
	//unsigned char m_fightmode;//ս��ģʽ
	GroupMemberSet m_groupMemberSet;
	//unsigned char m_patrolIndex;//��ǰѲ������
	//PlayerEnmityMap m_playerEnmityMap;//����ҵĳ�޶�
	//NpcEnmityMap m_npcEnmityMap;//��NPC�ĳ�޶�
	//����״̬�����Ե�Ӱ��ֵ������ͬ���Եĸ���Ӱ�죬���߻Ḳ��ǰ��
	//short m_extrahp;
	//short m_extramp;
	//short m_extraAttack;
	//short m_extraDefend;//����״̬�Է������Ե�Ӱ��ֵ
	//short m_extraSpeed;
	//float m_extraAttackSpeed;
    char m_extraLevel;
    short m_extraStrength;
    short m_extraAgility;
	short m_extraIntellect;

	//SpecialActStateMap m_specialActStateMap;
	//unsigned short m_currentSpecialActState;//0��ʾδ��������״̬ �ͻ��˸����¼���ı��ָ������Ҫ����ͬ��
	//float m_currentActDuration;//�ͻ��˸����¼���ı��ָ������Ҫ����ͬ��
	unsigned char m_controllerFlg;//0:stopmove, 1:moveup, 2:movedown, 3:moveleft, 4:moveright
	float m_controllerTime;//���Ƶ���Чʱ��
};
//crRole MetierData
class CRNETAPP_EXPORT crRpgGameMetierData : public CRCore::crData
{
public:
	crRpgGameMetierData();
	crRpgGameMetierData(const crRpgGameMetierData& data);
	DataClass(CRNetApp, RpgGameMetier)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(_crInt64 msg);
protected:
	virtual ~crRpgGameMetierData();
	MetierSkillASet m_metierSkillASet;//ְҵ���ܳ���ID�б�,�ӽű���ȡ�����ô洢�����ݿ�
	GameTaskMap m_gameTaskMap;
	//CRCore::ref_ptr<crGameTask> m_addTask;//loadʱ���õ�
	//CRCore::ref_ptr<CRCore::crStreamBuf> m_dataStream;//==crRole::m_metierStream
	GNE::Mutex m_dataMutex;
	int m_currentTaskID;
	static GNE::Mutex m_saveMutex;
};
//crViewMatterObject Data
class CRNETAPP_EXPORT crRpgGameBotData : public CRCore::crNodeData
{
public:
	crRpgGameBotData();
	crRpgGameBotData(const crRpgGameBotData& data);
	DataClass(CRNetApp, RpgGameBot)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
protected:
	GNE::Mutex m_dataMutex;
	CRCore::ref_ptr<crInstanceItem> m_item;
    
	float m_viewHeight;
	float m_walkableHeight;
	float m_turnToIdleTime;
	std::string m_botEffectStr;
    //���ǲ���
	//float m_cameraBorrowTime;//������ʱ��
	//float m_cameraBorrowInterval;//�������ʱ����
};
//crInstanceItem Data
class CRNETAPP_EXPORT crRpgGameItemData : public CRCore::crData
{
public:
	crRpgGameItemData();
	crRpgGameItemData(const crRpgGameItemData& data);
	DataClass(CRNetApp, RpgGameItem)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(_crInt64 msg);
protected:
	unsigned char m_dataType;
	unsigned char m_itemState;
	unsigned int m_guiseState;//����״̬
	unsigned short m_touchDistance;
	short m_zoffset;
	int m_belongPlayerID;
	int m_itemPrice;
	float m_rthp;
	float m_useItemProtectTime;//ʹ�ñ���ʱ��
	std::string m_itemIcon;
	//EquipComposeRequestVec m_equipComposeRequestVec;
	//int m_composeEquipID;//����id
	//SaleItemMap m_saleItemMap;
	//ExchangePlayerSet m_exchangePlayerSet;//����ʱ�̲��������ݣ�ֻ�ڷ�����������Ҫͬ�����ͻ��ˣ���m_saleItemMap�б仯ʱ��ͬ������������
	GNE::Mutex m_dataMutex;
	//CRCore::ref_ptr<CRCore::crStreamBuf> m_dataStream;

	//Equip
	std::string m_meshFileName;//��Ƥfilename
	//Skill or Thing
	std::string m_animFileName;//����filename
	///ֻ��Ҫ�ͻ��˴���
	std::string m_itemTalk;
	std::string m_itemOption;
	std::string m_itemInfoText;
	//CRCore::crVector2 m_halfLengths;//itemcollidesize,�ӽű���ȡ���������ݿ⣬����Ҫ����ͬ��
	CRCore::crVector3 m_halfPhysicsBox;
	char m_defaultkey;
};
//crNode Data
class CRNETAPP_EXPORT crRpgGameNodeData : public CRCore::crNodeData
{
public:
	crRpgGameNodeData();
	crRpgGameNodeData(const crRpgGameNodeData& data);
	DataClass(CRNetApp, RpgGameNode)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
protected:
	CRCore::ref_ptr<crInstanceItem> m_item;
};

class CRNETAPP_EXPORT crRpgGameWeaponData : public CRCore::crNodeData
{
public:
	crRpgGameWeaponData();
	crRpgGameWeaponData(const crRpgGameWeaponData& data);
	DataClass(CRNetApp, RpgGameWeapon)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
protected:
	CRCore::ref_ptr<crInstanceItem> m_item;
	std::string m_weaponActStr;
	float m_weaponSpeedScale;
};

class CRNETAPP_EXPORT crRpgGameSkillData : public CRCore::crData
{
public:
	crRpgGameSkillData();
	crRpgGameSkillData(const crRpgGameSkillData& data);
	DataClass(CRNetApp, RpgGameSkill)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(_crInt64 msg);
protected:
	unsigned char m_dataType;
	unsigned char m_skilllevel;
	float m_cdtime;
	char m_skilltype;//��������,�������ܻ򱻶�����

	unsigned short m_itemUseRange;//ʹ�÷�Χ
	short m_itemUseScope;//���÷�Χ
	CRCore::crVector2s m_physicsDM;
	CRCore::crVector2s m_magicDM;
	unsigned short m_needMP;
	unsigned short m_needHP;
	int m_targetExtraID;
	int m_userExtraID;
	unsigned char m_targetType;//ʹ�ö�������
	int m_belongPlayerID;//�¼�
	int m_itemPrice;//1���ļ۸������۸� �� skilllevel * itemPrice
	std::string m_itemIcon;

	float m_useItemProtectTime;//ʹ�ñ���ʱ��
	float m_duration;//����ʱ��
	//CRCore::ref_ptr<CRCore::crStreamBuf> m_dataStream;
	GNE::Mutex m_dataMutex;
	///ֻ��Ҫ�ͻ��˴���
	std::string m_meshFileName;//��Ƥfilename �¼�
	std::string m_animFileName;//����filename �¼�
	std::string m_itemInfoText;
	short m_aimid;
	CRCore::crVector2 m_uiAimRange;
	float m_attackAim;
	static GNE::Mutex m_saveMutex;
	char m_defaultkey;
	//����ʱ������
	_crInt64 m_lastUseTime;//��һ��ʹ��ʱ��
};
typedef std::map<short,short> ExtraIDMap;//id,(���Ӵ���,���ȼ�)
class CRNETAPP_EXPORT crRpgGameExtraData : public CRCore::crData
{
public:
	crRpgGameExtraData();
	crRpgGameExtraData(const crRpgGameExtraData& data);
	DataClass(CRNetApp, RpgGameExtra)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(_crInt64 msg);
	virtual void clear();
protected:
    ExtraIDMap m_extraIDMap;
	GNE::Mutex m_dataMutex;
};

//VR_ICBC
class CRNETAPP_EXPORT crTalkChooseUIData : public CRCore::crUIData
{
public:
	crTalkChooseUIData();
	crTalkChooseUIData(const crTalkChooseUIData& data);
	DataClass(CRNetApp, TalkChooseUI)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(_crInt64 msg);
protected:
	unsigned short m_buttonid;
	unsigned short m_textid;
};

class CRNETAPP_EXPORT crBrainData : public CRCore::crData
{
public:
	crBrainData();
	crBrainData(const crBrainData& data);
	DataClass(CRNetApp, Brain)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(_crInt64 msg);
protected:
	CRCore::crNode* m_currentFocusNode;
	CRCore::ref_ptr<CREncapsulation::crTableIO> m_createRoleTab;
	int m_currentRoleTabIndex;
	CRCore::crNode* m_roleAttachToNode;
	std::string m_attachBoneName;
	CRCore::crVector3 m_attachOffset;
	CRCore::crVector3 m_attachScale;
	float m_attachRotAngle;
    CRCore::crNode* m_loadedNode;
};
class crRole;
typedef std::vector< CRCore::ref_ptr<crRole> > SelectMyRoleVec    ;
typedef std::map< CRCore::ref_ptr<CRCore::crMatrixTransform>, CRCore::ref_ptr<CRNetApp::crWaypoint> > WaypointNodeMap;
class CRNETAPP_EXPORT crCameraData : public CRCore::crNodeData
{
public:
	crCameraData();
	crCameraData(const crCameraData& data);
	DataClass(CRNetApp, Camera)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(_crInt64 msg);
	enum CameraMove
	{
		None = 0x0,
		MoveLeft = 0x1,
		MoveRight = 0x2,
		MoveUp = 0x4,
		MoveDown = 0x8,
	};
	enum CameraRot
	{
		RotLeft = 0x1,
		RotRight = 0x2,
	};
protected:
	virtual ~crCameraData();
	unsigned char m_cameraMove;
	unsigned char m_cameraRot;
	unsigned char m_targetType;
	double m_cameraBorrowTime;//������ʱ��
	float m_cameraBorrowInterval;//�������ʱ����
	CRCore::ref_ptr<CRCore::crNode> m_targetNode;
	CRCore::ref_ptr<CRNetApp::crInstanceItem> m_targetItem;
	CRCore::crVector3 m_targetPosition;
	CRCore::crVector3i m_mousePosRec;//x,y, z=0��ʾ��Ч��1��ʾ��Ч
	SelectMyRoleVec m_selectMyRoles;
	CRCore::ref_ptr<CRNetApp::crInstanceItem> m_selectItem;
	
	CRCore::ref_ptr<CRNetApp::crWaypoint> m_waypointroot;//Editor��
	WaypointNodeMap m_waypointNodeMap;//Editor
	GNE::Mutex m_dataMutex;
};
class crPlayerGameData;
class crCommandDlgData : public CRCore::crUIData
{
public:
	crCommandDlgData();
	crCommandDlgData(const crCommandDlgData& data);
	DataClass(CRCore, CommandDlg)
	virtual void inputParam(int i, void *param);
	virtual void excHandle(_crInt64 msg);
protected:
	int m_parentType;
	void *m_parent;
	//CRCore::ref_ptr<CRCore::crWidgetNode> m_commandDlgWidget;
	//CRCore::ref_ptr<crPlayerGameData> m_commandDlgPlayerGameData;
};
typedef std::map<CRCore::ref_ptr<crInstanceItem>,float> HitMap;//hit,rate
class CRNETAPP_EXPORT crUseItemRecord : public CRCore::Referenced
{
public:
	crUseItemRecord():m_duration(0.0f),m_damageCount(1){}
	void setItem(crInstanceItem *item) { m_item = item; }
	crInstanceItem *getItem() { return m_item.get(); }
	void setUser(crInstanceItem *user) { m_user = user; }
	crInstanceItem *getUser() { return m_user.get(); }
	void setTarget(crInstanceItem *target) { m_target = target; }
	crInstanceItem *getTarget() { return m_target.get(); }
	void setDuration(float duration) { m_duration = duration; }
	float& duration(){ return m_duration; }
	HitMap &getHitMap(){ return m_hitMap; }
	void setDamageCount(char count){ m_damageCount = count; }
	char getDamageCount(){ return m_damageCount; }
	bool getHitValid(crInstanceItem *hititem, bool npcfire);
protected:
	CRCore::ref_ptr<crInstanceItem> m_item;//bulletitem
	CRCore::ref_ptr<crInstanceItem> m_user;
	CRCore::ref_ptr<crInstanceItem> m_target;
	HitMap m_hitMap;//�����߼�¼����ֹ�ظ�����
	float m_duration;
	char m_damageCount;
};
typedef std::multimap< CRCore::ref_ptr<crInstanceItem>,CRCore::ref_ptr<crUseItemRecord> > UseItemRecordMap;//user,record
typedef std::multimap< float,CRCore::ref_ptr<crUseItemRecord>,std::less<float> > HitTestMap;//duration,record
class CRNETAPP_EXPORT crSceneServerData : public CRCore::crData
{
public:
	crSceneServerData();
	crSceneServerData(const crSceneServerData& data);
	DataClass(CRNetApp, SceneServer)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(_crInt64 msg);
protected:
	UseItemRecordMap m_useItemRecordMap;
	GNE::Mutex m_dataMutex;
};
class CRNETAPP_EXPORT crRoomData : public CRCore::crData
{
public:
	crRoomData();
	crRoomData(const crRoomData& data);
	DataClass(CRNetApp, Room)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(_crInt64 msg);
protected:
	short m_progress;
	GNE::Mutex m_dataMutex;
};
}
#endif