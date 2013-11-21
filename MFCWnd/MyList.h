#pragma once


#include <vector>

class CColumnStyle;

class CMyList : public CListCtrl
{
	DECLARE_DYNAMIC(CMyList)

public:
    enum ColumnType
    {
        COLUMN_TYPE_CHECKBOX = 0,
        COLUMN_TYPE_TEXT,
        COLUMN_TYPE_PROGRESS,
        COLUMN_TYPE_MAX
    };

	CMyList();
	virtual ~CMyList();
    
    BOOL Create(CWnd* pParent, UINT nID);
    void AddColumn(ColumnType type, int index, const CString& str, int format, int width);
    void SetColumnFont(int index, int nPointSize, LPCTSTR lpszFaceName);

    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

private:
    static const DWORD ms_dwListStyle;
    static const DWORD ms_dwListStyleEx;
    
    typedef std::vector<CColumnStyle*> ColumnStyleList;
    ColumnStyleList m_columnDrawers;

    CImageList m_imgList;

	DECLARE_MESSAGE_MAP()

    afx_msg INT OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg VOID OnSelectionChange(NMHDR *pNMHDR, LRESULT *pResult);

};


