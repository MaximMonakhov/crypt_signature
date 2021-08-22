
#ifndef _CP_SCHANNEL_
#define _CP_SCHANNEL_

#define CPSSP_PACKAGE_CAPABILITIES	SECPKG_FLAG_INTEGRITY		|	\
					SECPKG_FLAG_PRIVACY		|	\
					SECPKG_FLAG_CONNECTION		|	\
					SECPKG_FLAG_MULTI_REQUIRED	|	\
					SECPKG_FLAG_EXTENDED_ERROR	|	\
					SECPKG_FLAG_IMPERSONATION	|	\
					SECPKG_FLAG_ACCEPT_WIN32_NAME   |	\
					SECPKG_FLAG_STREAM		|	\
					SECPKG_FLAG_MUTUAL_AUTH

#define CPSSP_PACKAGE_HEADER_SIZE	0x5U
#define CPSSP_PACKAGE_MAX_TOKEN		(0x4000-CPSSP_PACKAGE_HEADER_SIZE)
#define CPSSP_PACKAGE_MAX_MESSAGE	SSL3_RT_MAX_PLAIN_LENGTH

#define SSL3_RT_CHANGE_CIPHER_SPEC	20
#define SSL3_RT_ALERT			21
#define SSL3_RT_HANDSHAKE		22
#define SSL3_RT_APPLICATION_DATA	23

#define RNET_HANDLE 1
#define NOT_RNET_HANDLE 2
#define UNDEFINE_HANDLE 3 //RNET_HANDLE | NOT_RNET_HANDLE

typedef struct _PROTOCOL_VERSION_ {
	BYTE	Major;
	BYTE	Minor;
} PROTOCOL_VERSION, *PPROTOCOL_VERSION;

typedef struct _TLS1_RECORD_HEADER_ {
	BYTE				Type;
	PROTOCOL_VERSION		Version;
	BYTE				HiLength;
	BYTE				LoLength;
} TLS1_RECORD_HEADER, *PTLS1_RECORD_HEADER;

typedef struct _SECURITY_HANDLE_FLAGS_  {
	DWORD	dwFlags;
} SECURITY_HANDLE_FLAGS, *PSECURITY_HANDLE_FLAGS;

typedef struct _CPSSP_CTX_FLAGS_ {
    unsigned int Server:1;
    unsigned int MutualAuth:1;
    unsigned int UseSupplied:1;
    unsigned int ManualValidation:1;
    unsigned int FixedDH:1;
    unsigned int SplitByMessages:1;
    unsigned int SkipNextMAC:1;
    unsigned int ReadPacketNumOverflow:1;
    unsigned int WritePacketNumOverflow:1;
//флажки отвечающие за TLS extensions
//для клиента означают, что extension посылался, после получения hello от сервера - будет ли поддерживаться
//для сервера означают, что получен от клиента и будет поддерживаться
    unsigned int server_name:1;
    unsigned int renegotiation_info:1;
    unsigned int session_ticket:1;
    unsigned int hash_mac_select : 1; //клиент больше не посылает, сервер посылает, только если получит
    unsigned int hash_mac_matched_2001 : 1; // Проверяем match теперь сверху
    unsigned int next_protocol_negotiation : 1;
    unsigned int application_layer_protocol_negotiation : 1;
    unsigned int status_request:1;
    unsigned int hash_and_sign_cln_algs : 1;
    unsigned int extended_master_secret : 1;
    unsigned int session_reused : 1;
    unsigned int client_legacy_sent : 1;
    unsigned int elliptic_curves : 1;
    unsigned int ec_point_formats : 1;
    // Новые флаги добавлять строго в конец!
    unsigned int ServerKeyExchangeMsgExpected : 1;
    unsigned int SessionTicketAcquired : 1;
} CPSSP_CTX_FLAGS, *PCPSSP_CTX_FLAGS;

#ifdef KSP_LITE
#ifdef UNIX
typedef void * LSA_SEC_HANDLE;
#endif
typedef struct _SECURIY_HANDLE_{    
    //наш контекст
    LSA_SEC_HANDLE				CPSecHandle;
    //Контекст родного schannel
    LSA_SEC_HANDLE				PatchSecHandle;
    //Контекст LSA, который дернул KSP
    LSA_SEC_HANDLE				LsaContextId;
    ULONG_PTR					Id;
} SECURITY_HANDLE, *PSECURITY_HANDLE;
#else
typedef struct _SECURIY_HANDLE_{
    DWORD					dwHandleStatus;
    SecHandle					CPSecHandle;
} SECURITY_HANDLE, *PSECURITY_HANDLE;
#endif

// TODO: Включить SDK 8.1
// Детектируем отсутствие SDK по SECBUFFER_APPLICATION_PROTOCOLS
#ifndef SECBUFFER_APPLICATION_PROTOCOLS
#define SECBUFFER_APPLICATION_PROTOCOLS 18  // Lists of application protocol IDs, one per negotiation extension

typedef enum _SEC_APPLICATION_PROTOCOL_NEGOTIATION_EXT
{
    SecApplicationProtocolNegotiationExt_None,
    SecApplicationProtocolNegotiationExt_NPN,
    SecApplicationProtocolNegotiationExt_ALPN
} SEC_APPLICATION_PROTOCOL_NEGOTIATION_EXT, *PSEC_APPLICATION_PROTOCOL_NEGOTIATION_EXT;

// На Unix этого нет
#ifndef ANYSIZE_ARRAY
#define ANYSIZE_ARRAY 1
#endif

typedef struct _SEC_APPLICATION_PROTOCOL_LIST {
    SEC_APPLICATION_PROTOCOL_NEGOTIATION_EXT ProtoNegoExt; // Protocol negotiation extension type to use with this list of protocols
    unsigned short ProtocolListSize;                       // Size in bytes of the protocol ID list
    unsigned char ProtocolList[ANYSIZE_ARRAY];             // 8-bit length-prefixed application protocol IDs, most preferred first
} SEC_APPLICATION_PROTOCOL_LIST, *PSEC_APPLICATION_PROTOCOL_LIST;

typedef struct _SEC_APPLICATION_PROTOCOLS {
    unsigned long ProtocolListsSize;                            // Size in bytes of the protocol ID lists array
    SEC_APPLICATION_PROTOCOL_LIST ProtocolLists[ANYSIZE_ARRAY]; // Array of protocol ID lists
} SEC_APPLICATION_PROTOCOLS, *PSEC_APPLICATION_PROTOCOLS;

#define SECPKG_ATTR_APPLICATION_PROTOCOL 35

typedef enum _SEC_APPLICATION_PROTOCOL_NEGOTIATION_STATUS
{
    SecApplicationProtocolNegotiationStatus_None,
    SecApplicationProtocolNegotiationStatus_Success,
    SecApplicationProtocolNegotiationStatus_SelectedClientOnly
} SEC_APPLICATION_PROTOCOL_NEGOTIATION_STATUS, *PSEC_APPLICATION_PROTOCOL_NEGOTIATION_STATUS;

#define MAX_PROTOCOL_ID_SIZE 0xff

typedef struct _SecPkgContext_ApplicationProtocol
{
    SEC_APPLICATION_PROTOCOL_NEGOTIATION_STATUS ProtoNegoStatus; // Application  protocol negotiation status
    SEC_APPLICATION_PROTOCOL_NEGOTIATION_EXT ProtoNegoExt;       // Protocol negotiation extension type corresponding to this protocol ID
    unsigned char ProtocolIdSize;                                // Size in bytes of the application protocol ID
    unsigned char ProtocolId[MAX_PROTOCOL_ID_SIZE];              // Byte string representing the negotiated application protocol ID
} SecPkgContext_ApplicationProtocol, *PSecPkgContext_ApplicationProtocol;

#endif /*SECBUFFER_APPLICATION_PROTOCOLS*/

#endif /* _CP_SCHANNEL_ */
