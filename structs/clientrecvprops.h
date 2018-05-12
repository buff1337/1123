#pragma once

struct RecvProp;

class DVariant
{
public:
	union
	{
		float	m_Float;
		long	m_Int;
		char	*m_pString;
		void	*m_pData;
		Vector m_Vector;
		//float	m_Vector[3];
	};
};

class CRecvProxyData
{
public:
	const RecvProp	*m_pRecvProp;
	char _pad[4];//csgo ( for l4d keep it commented out :) )
	DVariant		m_Value;
	int				m_iElement;
	int				m_ObjectID;
};

typedef void(*RecvVarProxyFn)(const CRecvProxyData *pData, void *pStruct, void *pOut);

/*struct RecvTable
{
	RecvProp		*m_pProps;
	int				m_nProps;
	void			*m_pDecoder;
	char			*m_pNetTableName;
	bool			m_bInitialized;
	bool			m_bInMainList;
};*/
struct RecvTable
{
	RecvProp		*m_pProps;
	int				m_nProps;
	void			*m_pDecoder;
	char			*m_pNetTableName;
	bool			m_bInitialized;
	bool			m_bInMainList;
};

struct RecvProp
{
	char					*m_pVarName;
	int						m_RecvType;
	int						m_Flags;
	int						m_StringBufferSize;
	bool					m_bInsideArray;
	const void				*m_pExtraData;
	RecvProp				*m_pArrayProp;
	void*					m_ArrayLengthProxy;
	void*					m_ProxyFn;
	void*					m_DataTableProxyFn;
	RecvTable				*m_pDataTable;
	int						m_Offset;
	int						m_ElementStride;
	int						m_nElements;
	const char				*m_pParentArrayPropName;
};

/*HAVE TO PLACE IT HERE*/
class ClientClass
{
	typedef IClientNetworkable*   (*CreateClientClassFn)(int entnum, int serialNum);
	typedef IClientNetworkable*   (*CreateEventFn)();

public:
	CreateClientClassFn			m_pCreateFn;
	CreateEventFn  			m_pCreateEventFn;
	char			*m_pNetworkName;
	RecvTable		*m_pRecvTable;
	ClientClass		*m_pNext;
	int				m_ClassID;
};