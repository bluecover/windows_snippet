/********************************************************************
	filename: 	Word.h	
	created:	2012/03/05
	author:		ZhaoHao
	purpose:	Define Word class.
*********************************************************************/
#pragma once

class CWord
{
public:
    CWord(const CString& name, 
        const CString& soundmark,
        const CString& explanation,
        float progress,
        const CString& cloectTime,
        const CString& category)
        : m_strName(name),
          m_strSoundmark(soundmark),
          m_strExplanation(explanation),
          m_fReviewProgress(progress),
          m_strCollectTime(cloectTime),
          m_strCategory(category),
          m_bIsChecked(false)
    {

    }

    CString m_strName;            // ����
    CString m_strSoundmark;       // ����
    CString m_strExplanation;     // ����
    float   m_fReviewProgress;    // ��ϰ��ɶ�
    CString m_strCollectTime;     // �ղ�ʱ��
    CString m_strCategory;        // ����
    bool    m_bIsChecked;         // �Ƿ�ѡ����
};