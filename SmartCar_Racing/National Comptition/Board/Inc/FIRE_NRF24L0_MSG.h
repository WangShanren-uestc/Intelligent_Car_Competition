/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,Ұ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�Ұ���ѧ��̳ http://www.chuxue123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����Ұ��Ƽ����У�δ������������������ҵ��;��
 *     �޸�����ʱ���뱣��Ұ��Ƽ��İ�Ȩ������
 *
 * @file       FIRE_NRF24L0_MSG.h
 * @brief      ���ߵ��� ��Ϣ���� ����
 * @author     Ұ��Ƽ�
 * @version    v5.0
 * @date       2014-01-04
 */


#ifndef _FIRE_NRF24L0_MSG_H_
#define _FIRE_NRF24L0_MSG_H_

#include "fire_ui_var.h"
#include "FIRE_NRF24L0.h"



#define COM_LEN     2   //com����ռ�õ��ֽ�



//��������COMִ�к������ؽ��
//COM�����Ҫִ�ж�Ӧ�ĺ���
//MSG��Ϣ�����ͷ�����֪ͨ������Ҫִ���κκ���
typedef enum
{
    NRF_RESULT_FALSE = 0,                   //�١�ʧ�ܡ��¼�û����
    NRF_RESULT_TRUE = 1,                    //�桢�ɹ����¼�������
    NRF_RESULT_QUIT,                    //�˳�

    NRF_RESULT_NULL,                    //�������κδ���

    //��������
    NRF_RESULT_RX_NO,                   //û���յ�����
    NRF_RESULT_RX_VALID,                //������Ч����
    NRF_RESULT_RX_NOVALID,              //���յ����ݣ�����Ч


    /*** EVENT �¼� ***/
    //  NRF_RESULT_EVENT_FALSE,             //û�¼������������¼���������
    //  NRF_RESULT_EVENT_FINIST,            //�¼��������
    //  NRF_RESULT_EVENT_CONTINUE,          //�¼��������䣨����¼������ˣ���Ҫ�������䣩

} nrf_result_e;

//����������Ϣ����
typedef enum
{
    ////////////////// COM���� /////////////////////
    //��ҪУ����յ������Ƿ���ȷ
    //���͵����ݣ� XXX_COM ��~XXX_COM    �������������Ҫ���͵���Ϣ���ɶ�Ӧ��ִ�к������д���

    //ͼ����
    COM_IMG,

    //����CCD
    COM_CCD,

    //�����������
    COM_VAR,

    COM_RETRAN,//��λ���䣬����֮ǰ���յ�������

    /*  ��Ҫ���ӹ��ܣ�������λ��  */
	COM_MY,


    COM_MAX     ,       //������������Ŀ                                                  ********************************

} com_e;

extern void             nrf_msg_init();                                //��ʼ����Ϣ����(��û�г�ʼ�� nrf ģ��)
extern nrf_result_e     nrf_msg_tx(com_e   com, uint8 *sendbuf);       //�������ݣ����ͳ�����com����
extern nrf_result_e     nrf_msg_rx(com_e  *com, uint8 *rebuf);         //��������,�����д���








#endif  //_FIRE_NRF24L0_MSG_H_