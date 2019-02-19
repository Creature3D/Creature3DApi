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
#ifndef CRNETAPP_CRRABBITMQ_H
#define CRNETAPP_CRRABBITMQ_H 1

#include <CRNetApp/appExport.h>
#include <CRCore/ref_ptr.h>
#include <CRCore/Referenced.h>
#include "amqp_tcp_socket.h"
#include <vector>
#include <list>
#include <string>
#include <map>
namespace CRNetApp {

class CRNETAPP_EXPORT crRabbitmq : public CRCore::Referenced
{
public:
	crRabbitmq();
	static crRabbitmq *getInstance();
	virtual void clear();

	int connect(const std::string &strHostname, int iPort, const std::string &strUser, const std::string &strPasswd);
	int disconnect();
	/**
	*   @brief       ExchangeDeclare    ����exchange
	*	@param       [in]               strExchange
	*   @param       [in]               strType
	*   @return ����0ֵ����ɹ�����exchange��С��0�������
	*/
	int exchangeDeclare(const std::string &strExchange, const std::string &strType);

	/**
	*   @brief       QueueDeclare                     ������Ϣ����
	*	@param       [in]               strQueueName  ��Ϣ����ʵ��
	*   @param
	*   @return ����0ֵ����ɹ�����queue��С��0�������
	*/
	int queueDeclare(const std::string &strQueueName);

	/**
	*   @brief       QueueBind                        �����У��������Ͱ󶨹���������γ�һ��·�ɱ�
	*	@param       [in]               strQueueName  ��Ϣ����
	*	@param       [in]               strExchange   ����������
	*	@param       [in]               strBindKey    ·������  ��msg.#�� ��msg.weather.**��
	*   @return ����0ֵ����ɹ��󶨣�С��0�������
	*/
	int queueBind(const std::string &strQueueName, const std::string &strExchange, const std::string &strBindKey);

	/**
	*   @brief       QueueUnbind                      �����У��������Ͱ󶨹���󶨽��
	*	@param       [in]               strQueueName  ��Ϣ����
	*	@param       [in]               strExchange   ����������
	*	@param       [in]               strBindKey    ·������  ��msg.#�� ��msg.weather.**��
	*   @return ����0ֵ����ɹ��󶨣�С��0�������
	*/
	int queueUnbind(const std::string &strQueueName, const std::string &strExchange, const std::string &strBindKey);

	/**
	*   @brief       QueueDelete                      ɾ����Ϣ���С�
	*	@param       [in]               strQueueName  ��Ϣ��������
	*	@param       [in]               iIfUnused     ��Ϣ�����Ƿ����ã�1 �����Ƿ����ö�ɾ��
	*   @return ����0ֵ����ɹ�ɾ��queue��С��0�������
	*/
	int queueDelete(const std::string &strQueueName, int iIfUnused);

	/**
	* @brief Publish  ������Ϣ
	* @param [in] strMessage        ��Ϣʵ��
	* @param [in] strExchange       ������
	* @param [in] strRoutekey       ·�ɹ���
	*   1.Direct Exchange �C ����·�ɼ�����Ҫ��һ�����а󶨵��������ϣ�Ҫ�����Ϣ��һ���ض���·�ɼ���ȫƥ�䡣
	*   2.Fanout Exchange �C ������·�ɼ��������а󶨵��������ϡ�һ�����͵�����������Ϣ���ᱻת������ý������󶨵����ж����ϡ�
	*   3.Topic Exchange �C ��·�ɼ���ĳģʽ����ƥ�䡣��ʱ������Ҫ��Ҫһ��ģʽ�ϡ����š�#��ƥ��һ�������ʣ����š�*��ƥ�䲻�಻��һ���ʡ�
	*      ��ˡ�audit.#���ܹ�ƥ�䵽��audit.irs.corporate�������ǡ�audit.*�� ֻ��ƥ�䵽��audit.irs��
	* @return ����0ֵ����ɹ�������Ϣʵ�壬С��0�����ʹ���
	*/
	int publish(const std::string &strMessage, const std::string &strExchange, const std::string &strRoutekey);

	/**
	* @brief consumer  ������Ϣ
	* @param [in]  strQueueName         ��������
	* @param [out] message				��ȡ����Ϣʵ��
	* @param [int] timeout              ȡ�õ���Ϣ���ӳ٣���ΪNULL����ʾ����ȡ�����ӳ٣�����״̬
	* @return ����0ֵ����ɹ���С��0������󣬴�����Ϣ��ErrorReturn����
	*/
	int consumer(const std::string &strQueueName, std::string &message, struct timeval *timeout = NULL);


protected:
	virtual ~crRabbitmq();
	static CRCore::ref_ptr<crRabbitmq> m_instance;

	int errorMsg(amqp_rpc_reply_t x, char const *context);

	std::string                 m_strHostname;      // amqp����
	int                         m_iPort;            // amqp�˿�
	std::string					m_strUser;
	std::string					m_strPasswd;
	int                         m_iChannel;

	amqp_socket_t               *m_pSock;
	amqp_connection_state_t     m_pConn;
};

}
#endif