/********************************************************************
	filename: 	WordListController.h	
	created:	2012/03/05
	author:		ZhaoHao
	purpose:	Define WordListController class.
*********************************************************************/
#pragma once

#include "Word.h"
#include "ColumnStyle.h"
#include <vector>

class CWordIndexCmpPre
{
public:
    CWordIndexCmpPre(std::vector<CWord>& wordList)
        : m_WordListRef(wordList)
    {}

    bool operator()(size_t a, size_t b)
    {
        return m_WordListRef[a].m_strName < m_WordListRef[b].m_strName;
    }

private:
    std::vector<CWord>& m_WordListRef;
};


class CWordListController : public CListCtrl
{
public:
    enum Column
    {
        COLUMN_NUMBER = 0,
        COLUMN_NAME,
        COLUMN_SOUNDMARK,
        COLUMN_EXPLANATION,
        COLUMN_PROGRESS,
        COLUMN_COLLECT_TIME,
        COLUMN_CATEGORY,
        COLUMN_MAX
    };

    DECLARE_DYNAMIC(CWordListController)
    DECLARE_MESSAGE_MAP()

public:
    CWordListController(); 
    ~CWordListController();
        
    BOOL CreateListCtrl(CWnd* pParent, int nID);

    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

    void AddWord(const CWord& newWord);
    CWord* GetWordByIndex(size_t index);

    void Sort();

private:
    typedef std::vector<CWord> WordList;
    typedef std::vector<CColumnStyle*> ColumnStyleList;
    typedef std::vector<size_t> IndexList;

    static const int   ms_iIdListCtrl;
    static const DWORD ms_dwListStyle;
    static const DWORD ms_dwListStyleEx;

    WordList& GetDisplayList();

    WordList m_vecWordListAll;
    IndexList m_vecIndexList;
    ColumnStyleList m_vecColumnStyles;
    CImageList m_imgList;

    afx_msg VOID GetDisplayInfo(NMHDR* pNMHDR, LRESULT* pResult);  
    afx_msg VOID OnSelectionChange(NMHDR *pNMHDR, LRESULT *pResult);
};