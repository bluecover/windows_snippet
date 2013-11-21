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

    CString m_strName;            // 单词
    CString m_strSoundmark;       // 音标
    CString m_strExplanation;     // 解释
    float   m_fReviewProgress;    // 复习完成度
    CString m_strCollectTime;     // 收藏时间
    CString m_strCategory;        // 分类
    bool    m_bIsChecked;         // 是否被选中了
};