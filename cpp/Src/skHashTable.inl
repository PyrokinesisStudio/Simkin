/*
Copyright 1996-2001
Simon Whiteside

$Id: skHashTable.inl,v 1.6 2001/03/05 16:46:28 sdw Exp $
*/

//---------------------------------------------------
inline skHashTable::skHashTable(USize size) 
     //---------------------------------------------------
    : m_Size(size),m_NumEntries(0)
{
    m_Slots=new skHashEntryList[size];
}
//---------------------------------------------------
inline skHashTable::~skHashTable() 
     //---------------------------------------------------
{
    clear();
    delete [] m_Slots;
}
//---------------------------------------------------
inline skHashTable::skHashTable(const skHashTable&)
     //---------------------------------------------------
{
}
//---------------------------------------------------
inline skHashTable::skHashTable()
     //---------------------------------------------------
{
}
//---------------------------------------------------
inline skHashTable& skHashTable::operator=(const skHashTable&)
     //---------------------------------------------------
{
    return *this;
}
//---------------------------------------------------
inline skHashTableIterator::skHashTableIterator(const skHashTable& t)
     //---------------------------------------------------
    : m_Table(t), m_Slot(0),m_ListIterator(0)
{
}
//---------------------------------------------------
inline skHashTableIterator::~skHashTableIterator()
     //---------------------------------------------------
{
    delete m_ListIterator;
}
//---------------------------------------------------
inline skHashEntry * skHashTable::findEntry(void * key, USize & slot) const
     //---------------------------------------------------
{
    assert(key);
    slot=hashKey(key)%m_Size;
    skHashEntryListIterator iter(m_Slots[slot]);
    skHashEntry * pentry=0;
    while ((pentry=iter())!=0)
	if (compareKeys(pentry->m_Key,key))
	    break;
    return pentry;
}
// Version which doesn't return slot.
//---------------------------------------------------
inline skHashEntry * skHashTable::findEntry(void * key) const
     //---------------------------------------------------
{
    assert(key);
    skHashEntryListIterator iter(m_Slots[hashKey(key)%m_Size]);
    skHashEntry * pentry=0;
    while ((pentry=iter())!=0)
	if (compareKeys(pentry->m_Key,key))
	    break;
    return pentry;
}
//---------------------------------------------------
inline void * skHashTable::value(void * key)  const
     //---------------------------------------------------
{
    assert(key);
    skHashEntry * pentry=findEntry(key);
    if (pentry)
	return pentry->m_Value;
    else
	return 0;
}
//---------------------------------------------------
inline skHashTableIterator& skHashTableIterator::operator=(const skHashTableIterator&)
     //---------------------------------------------------
{
    return *this;
}
//---------------------------------------------------
inline void * skHashTableIterator::key() const
     //---------------------------------------------------
{
    return m_Key;
}
//---------------------------------------------------
inline void * skHashTableIterator::value() const
     //---------------------------------------------------
{
    return m_Value;
}
//---------------------------------------------------
inline USize skHashTable::entries() const
     //---------------------------------------------------
{
    return m_NumEntries;
}

#define TTH_PREFIX template<class TKey,class TValue> 

//---------------------------------------------------
TTH_PREFIX inline skTHashTable<TKey,TValue>::skTHashTable(USize  size)
     //---------------------------------------------------
    : skHashTable(size)
{
}
//---------------------------------------------------
TTH_PREFIX inline skTHashTable<TKey,TValue>::skTHashTable()
     //---------------------------------------------------
    : skHashTable(DEFAULT_skHashTable_SIZE)
{
}
//---------------------------------------------------
TTH_PREFIX inline skTHashTable<TKey,TValue>::~skTHashTable()
     //---------------------------------------------------
{
    clearAndDestroy();
}

//---------------------------------------------------
TTH_PREFIX inline void skTHashTable<TKey,TValue>::insertKeyAndValue(TKey * key, TValue * value)
     //---------------------------------------------------
{
    skHashTable::insertKeyAndValue(key,value);
}
//---------------------------------------------------
TTH_PREFIX inline TValue * skTHashTable<TKey,TValue>::value(const TKey * key)
     //---------------------------------------------------
{
    return (TValue*)skHashTable::value((void *)key);
}
//---------------------------------------------------
TTH_PREFIX inline void skTHashTable<TKey,TValue>::del(const TKey * key)
     //---------------------------------------------------
{
    skHashTable::del((void *)key);
}
//---------------------------------------------------
TTH_PREFIX inline void skTHashTable<TKey,TValue>::delKeyNotValue(const TKey * key)
     //---------------------------------------------------
{
    skHashTable::delKeyNotValue(key);
}
//---------------------------------------------------
TTH_PREFIX inline void skTHashTable<TKey,TValue>::remove(const TKey * key)
     //---------------------------------------------------
{
    skHashTable::remove(key);
}
//---------------------------------------------------
TTH_PREFIX inline int skTHashTable<TKey,TValue>::compareKeys(void * key1, void * key2) const
     //---------------------------------------------------
{
    return (*(TKey *)key1==*(TKey *)key2);
}
//---------------------------------------------------
TTH_PREFIX inline void skTHashTable<TKey,TValue>::deleteKey(void * key)
     //---------------------------------------------------
{
    delete (TKey *)key;
}
//---------------------------------------------------
TTH_PREFIX inline void skTHashTable<TKey,TValue>::deleteValue(void * value)
     //---------------------------------------------------
{
    delete (TValue *)value;
}
//---------------------------------------------------
TTH_PREFIX inline USize skTHashTable<TKey,TValue>::hashKey(void * key) const
     //---------------------------------------------------
{
    return ::hashKey((TKey *)key);
}
//---------------------------------------------------
TTH_PREFIX inline skTHashTableIterator<TKey,TValue>::skTHashTableIterator(const skTHashTable<TKey,TValue>& l)
     //---------------------------------------------------
    : skHashTableIterator(l)
{
}
//---------------------------------------------------
TTH_PREFIX inline TKey * skTHashTableIterator<TKey,TValue>::key() const
     //---------------------------------------------------
{
    return (TKey*)skHashTableIterator::key();
}
//---------------------------------------------------
TTH_PREFIX inline TValue * skTHashTableIterator<TKey,TValue>::value() const
     //---------------------------------------------------
{
    return (TValue*)skHashTableIterator::value();
}










