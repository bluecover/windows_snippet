

class CNoTrackObject
{
public:
	void* __stdcall operator new(size_t nSize);
	void __stdcall operator delete(void*);
    virtual ~CNoTrackObject() {};
};


class CProcessLocalObject
{
public:
    CNoTrackObject* GetData(CNoTrackObject* (__stdcall* pfnCreateObject)())
    {
        if (m_pObject == NULL)
        {
            AfxLockGlobals(CRIT_PROCESSLOCAL);
            TRY
            {
                if (m_pObject == NULL)
                    m_pObject = (*pfnCreateObject)();
            }
            CATCH_ALL(e)
            {
                AfxUnlockGlobals(CRIT_PROCESSLOCAL);
                THROW_LAST();
            }
            END_CATCH_ALL
                AfxUnlockGlobals(CRIT_PROCESSLOCAL);
        }
        return m_pObject;
    }

    ~CProcessLocalObject();
    {
        if (m_pObject != NULL)
            delete m_pObject;
    }

    CNoTrackObject* volatile m_pObject;
};

template<class TYPE>
class CProcessLocal : public CProcessLocalObject
{
    // Attributes
public:
    inline TYPE* GetData()
    {
        TYPE* pData = (TYPE*)CProcessLocalObject::GetData(&CreateObject);
        ENSURE(pData != NULL);
        return pData;
    }
    inline TYPE* GetDataNA() { return (TYPE*)m_pObject; }
    inline operator TYPE*()  { return GetData(); }
    inline TYPE* operator->() { return GetData(); }

    static CNoTrackObject* __stdcall CreateObject()
    {
        return new TYPE; 
    }
};