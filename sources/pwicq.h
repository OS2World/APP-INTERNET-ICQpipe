/*
 * PWICQ.H - Prototipos da parte publica do PWICQ
 */

//---[ Definicoes ]-------------------------------------------------------------

#ifndef _PWICQ_DEF_

 #define _PWICQ_DEF_

 #define _VERSION_ 	"0.29"
 #define _REVISION_	0x0002

 #define GUI_STACK 	32768
 #define MSG_TYPES	15

 #define SEPARATOR 	0xFE
 #define FIELDMRK  	0xFE

 #define STRINGSPT 	"þ"

 #ifndef HICQ
    #define HICQ void *
 #endif

 #ifndef HUSER
    #define HUSER USER *
 #endif

 #ifndef ICQFILE
    #define ICQFILE void *
 #endif

 #define TCP_PKTSIZE	2048
 #define MSG_MAXLEN	 512

 #define ICQLoadButton(h,i,c,s,d) WinSendDlgItemMsg(h,i,BM_SETCHECK,MPFROMSHORT(ICQLoadLong(c,s,d)),(MPARAM)NULL)
 #define ICQSaveButton(h,i,c,s) ICQSaveLong(c,s,(ULONG)WinSendDlgItemMsg(h,i,BM_QUERYCHECK,0,0) == 0 ? 0 : 1);

 typedef struct addmenu 		// Used by plugin manager to add options
 {
    HPOINTER 	ptr;
    USHORT 	id;
    USHORT 	option;
    char   	text[80];
 } ADDMENU;

 typedef struct user
 {
    ULONG       	uin;            // UIN
    ULONG               mode;           // Status (Online, away, etc)
    long                ip[2];          // IP Adresses (reporteds from user and from server)
    int                 port;           // TCP port to connect
    ULONG               flags;          // Options/Flags
    ULONG               group;          // Reserved
    short               btmCode;        // Reserved
 } USER;

 typedef struct icqdate
 {
    unsigned short      year;
    char                month;
    char                day;
    char                hour;
    char                minute;
    char                seconds;
 } ICQDATE;

 typedef struct usrmsg                  // Message on the user's queue
 {
    USHORT              type;           // Message type
    USHORT		tcpFlags;	// TCP Message Flags
    /* TCP Message Command Types */
    #define TCP_MSG_AUTO         0x0000  /* TCP message ACK and Auto-Reply 		*/
    #define TCP_MSG_REAL         0x0010  /* TCP message 				*/
    #define TCP_MSG_LIST         0x0020  /* TCP message sent to the contact list 	*/
    #define TCP_MSG_URGENT       0x0040  /* TCP message sent urgently 			*/

    /* The following are flags and are OR'd with the above Command Types */
    #define TCP_MSGF_S_INVISIBLE 0x0080  /* The message sender is Invisible 		*/
    #define TCP_MSGF_S_AWAY      0x0100  /* The message sender is Away 			*/
    #define TCP_MSGF_S_OCCUPIED  0x0200  /* The message sender is Occupied 		*/
    #define TCP_MSGF_S_NA        0x0800  /* The message sender is Not Available 	*/
    #define TCP_MSGF_S_DND       0x1000  /* The message sender is Do Not Disturb 	*/

    ICQDATE             date;           // Date/Time of the message
    long		seq;		// Sequence number (direct TCP messages only)
    HWND                hwnd;           // Message Window

 } USRMSG;

 typedef struct sysmsg                  // Message on the system's queue
 {
    long                uin;            // The sender
    USRMSG              msg;            // The message
 } SYSMSG;

 typedef struct dlginfo			// Dialog helper
 {
    HWND	hwnd;			// Window's handle
    HICQ	ctl;			// ICQ handle
    long	uin;			// Owner's of the dialog UIN
    HUSER 	usr;			// Owner's of the dialog handle
    HINI	ini;			// Handle of the pwICQ INI file
    char	id[11];			// Window's Identification
    HPOINTER	icon;			// Window's Icon
    USHORT	type;			// Dialog's type

    // Work areas for the Dialog's message processor
    long	flags;			// Generic flags
    long	lValue;			// Generic Value
    char	temp[0x0100];		// Temporary buffer

 } DLGINFO;

 typedef struct chatinfo
 {
    char	status;			// Situacao (0 = Em handshake, 1 = Ativo, >1 Erro/Terminando)
    ULONG	flag;			// Flags usadas pela janela de chat
    int		idle;			// Tempo sem processar pacote

    HICQ 	ctl;			// Handle do core
    HUSER	usr;			// Handle do usuario
    long	uin;			// UIN do usuario

    HWND	hwnd;			// Handle da janela de chat
    HWND	frame;			// Frame da janela de chat
    USHORT	cx;
    USHORT	cy;			// Tamanho da janela

    char	uFont[20];		// Fonte do usuario
    ULONG	uFore;			// Cor de frente do usuario
    ULONG	uBack;			// Cor de fundo do usuario

    ULONG	ufSize;			// Font-Size do usuario
    ULONG	ufFace;			// Font-Face do usuario

    ULONG	lFore;			// Minha cor de frente
    ULONG	lBack;			// Minha cor de fundo

    ULONG	lfSize;			// Minha Font-Size
    ULONG	lfFace;			// Minha Font-Face

    int		Sock;			// Socket TCP que administra o chat
    int		Thread;			// Thread de comunicacao
    int		wThread;		// Thread de janela

    USHORT	hello;			// Codigo da mensagem de hello

    char	cursor;			// Posicao do cursor
    char	text[0x0100];		// Buffer de linha recebida
    HWND	dialog[2];		// Dialogos

 } CHATINFO;

//---[ Queue commands ]---------------------------------------------------------

 #define ICQCMD_RESTART		0x0001
 #define ICQCMD_SHOW		0x0002
 #define ICQCMD_QUIT		0x0003
 #define ICQCMD_SETMODE		0x0004

//---[ Popup menu's control flags ]---------------------------------------------

 #define OPT_ALL    		0x0001
 #define OPT_WAITING    	0x0002
 #define OPT_USERON		0x0004
 #define OPT_TEXTSCRIPT 	0x0008
 #define OPT_WEBENABLED 	0x0010
 #define OPT_DIRECT     	0x0020
 #define OPT_SYSTEMON   	0x0040

//---[ System/User event codes ]------------------------------------------------

 #define EVT_ONLINE     0x00000001      // Usuario/sistema on-line
 #define EVT_OFFLINE    0x00000002      // Usuario/sistema off-line
 #define EVT_STATUS     0x00000003      // Mudanca de status
 #define EVT_CONNECT    0x00000004      // Iniciou processo de conexao
 #define EVT_RECV       0x00000005      // Pacote recebido
 #define EVT_SENT       0x00000006      // Pacote enviado
 #define EVT_CONNCT	0x00000007	// Conexao recebida
 #define EVT_DISCONNCT  0x00000008	// Conexao encerrada
 #define EVT_LOGONOK    0x00000009	// Processo de logon completo
 #define EVT_STARTUP    0x0000000A	// Sistema iniciando
 #define EVT_CONTACT    0x0000000B	// Contact-list confirmada
 #define EVT_GOAWAY	0x0000000C	// Servidor pediu p'ra sair
 #define EVT_RETRY	0x0000000D	// Servidor pediu p'ra tentar de novo
 #define EVT_NOTFOUND	0x0000000E	// Usuario nao encontrado
 #define EVT_FOUND	0x0000000F	// Informacao de usuario recebida
 #define EVT_ENDMSG	0x00000010	// Fim das mensagems armazenadas
 #define EVT_ENDSEARCH	0x00000011	// Pesquisa terminada
 #define EVT_USERFOUND	0x00000012	// Usuario encontrado (Pesquisa)
 #define EVT_REJECTED	0x00000013	// Rejeitado pelo servidor
 #define EVT_CONTACTED  0x00000014	// Servidor foi contactado
 #define EVT_NETFAIL	0x00000015	// Falha na rede
 #define EVT_TCPREJECT  0x00000016	// Conexao TCP rejeitada
 #define EVT_BEEP	0x00000017	// Beep
 #define EVT_PARM	0x00000018	// Parametro foi mudado
 #define EVT_MESSAGE	0x00000019	// Mensagem recebida

//---[ Menu IDs ]---------------------------------------------------------------

 #define MNU_SETMODE	0x00		// Menu de modos
 #define MNU_USER   	0x01		// Menu de usuario
 #define MNU_SYSTEM	0x02		// Menu de sistema
 #define MNU_SCRIPT	0x03		// Menu de scripts

 #define MNU_QUANT	0x04

 #define MNU_MSGBUTTON  99		// Botao na caixa de mensagem

//---[ Tipos de janela de confirmacao (ICQDlgOpenQueryWindow) ]-----------------

 #define QRY_REQUEST	0x00		// Pedido de autoriza‡„o
 #define QRY_REASK	0x01		// Pedido de autoriza‡„o (de novo)
 #define QRY_REFUSE	0x02		// Autorizacao negada
 #define QRY_REJECTCHAT 0x03		// Chat rejeitado
 #define QRY_REJECTFILE 0x04		// Arquivo rejeitado

//---[ Message types ]----------------------------------------------------------

 #define MSG_NORMAL     0x0001  // Normal
 #define MSG_CHAT	0x0002  // Pedido de chat
 #define MSG_FILE	0x0003  // Pedido de transferencia de arquivo
 #define MSG_URL        0x0004  // Descricao 0xFE URL
 #define MSG_REQ        0x0006  // Pedido de autorizacao
 #define MSG_REFUSED    0x0007  // Autorizacao negada
 #define MSG_AUTHORIZE  0x0008  // Usuario foi autorizado
 #define MSG_ADD        0x000C  // "You were added" Nick 0xFE Primeiro nome 0xFE ultimo nome 0xFE e-mail 0xFE flag ('1'/'0')
 #define MSG_PAGER	0x000D	// ICQ-Pager message
 #define MSG_MAIL	0x000E  // Mail Express
 #define MSG_CONTACT    0x0013  // Contact-list message

 #define MSG_MASS	0x8000  // Mass message

 // Internal
 #define MSG_REPLY      0xFE01  // Reply a uma mensagem
 #define MSG_ACCEPTED	0xFE03  // Arquivo aceito
 #define MSG_NEWMSG     0xFF01  // Nova mensagem de texto
 #define MSG_NEWURL     0xFF04  // Nova mensagem de URL
 #define MSG_NEWCHAT	0xFF02  // Pedido de CHAT
 #define MSG_NEWFILE	0xFF03	// Enviar arquivo

//---[ User flags ]-------------------------------------------------------------

 #define USR_INLIST     0x00000001      // Usuario esta na lista?
 #define USR_BLINK      0x00000002      // Usuario esta piscando?
 #define USR_PENDENT    0x00000004      // Usuario tem eventos pendentes??
 #define USR_WAITING    0x00000008      // Aguardando autorizacao
 #define USR_PWICQ      0x00000010      // Usuario utiliza o pwICQ, posso usar funcoes extras
 #define USR_REFUSED    0x00000020      // Usuario recusou a anexacao
 #define USR_DELETED    0x00000040      // Usuario foi deletado
 #define USR_IGNORE     0x00000080      // Ignorar mensagems do usuario
 #define USR_AUTOOPEN   0x00000100      // Abre mensagems do usuario automaticamente
 #define USR_REFRESH    0x00000200      // Atualizar dados do usuario
 #define USR_AUTHORIZE  0x00000400      // Usuario tem que autorizar anexacao
 #define USR_NOINFO     0x00000800      // Nao foi possivel pesquisar o usuario
 #define USR_LOGMSG     0x00001000      // Gravar log de todas as mensagems do usuario
 #define USR_ACT        0x00002000      // Houve atividade no usuario
 #define USR_INVISIBLE  0x00004000      // Usuario esta na minha 'invisible list'
 #define USR_VISIBLE    0x00008000      // Usuario esta na minha 'visible list'
 #define USR_REXX	0x00010000	// Habilita scripts Rexx para o usuario
 #define USR_SEARCH	0x00020000	// Existe uma pesquisa ativa para o usuario
 #define USR_NOAWAY	0x00040000	// Ignora mensagems de AWAY do usuario
 #define USR_NOSNDAWAY  0x00080000	// Nao envia mensagems de AWAY ao usuario
 #define USR_HISTORY	0x00100000	// Usuario usa arquivo de historico
 #define USR_ACCEPT	0x00200000	// Always accept files
 #define USR_AUTORESUME 0x00400000	// Always resume
 #define USR_DIRECT	0x00800000	// Direct connected (Offline)

 #define USR_HIDE       0x40000000      // Nao mostra na contact-list
/* #define USR_KILL       0x80000000      // Reservado para o |Shake-Boom| Uin 27193227 */

//---[ Modos ]------------------------------------------------------------------

 // Especiais
 #define ICQ_STATUS    		0x000001FF       // Mascara para separar online/offline status das flags
 #define ICQ_WEBPRESENCE	0x00010000	 // Ativa WebPresence
 #define ICQ_HIDEIP    		0x00020000
 #define ICQ_PHONEBUSY 		0x00040000
 #define ICQ_BIRTHDAY  		0x00080000
 #define ICQ_SOCKS     		0x00100000	// Conexao via SOCKS
 #define ICQ_WEBSERVER		0x00200000	// Webserver ativo

 #define ICQ_KNOWMODES		0x803F01FF	// Modos que eu ja conheco

 // UDP
 #define ICQ_OFFLINE   0xFFFFFFFF       // Offline
 #define ICQ_ONLINE    0x00000000       // Online
 #define ICQ_AWAY      0x00000001       // Away
 #define ICQ_NA        0x00000005       // N/A (Extended away)
 #define ICQ_NA99A     0x00000004
 #define ICQ_BUSY      0x00000010       // Occupied (Mac)
 #define ICQ_OCCUPIED  0x00000011       // Occupied (Urgent MSGs only)
 #define ICQ_DND       0x00000013       // Do not Disturb
 #define ICQ_DND2      0x00000002	// Do not Disturb (LICQ)
 #define ICQ_FREECHAT  0x00000020       // Available for chat
 #define ICQ_PRIVACY   0x00000100       // Privacy (Invisible)

// #define ICQ_DIRECT    0x80000100	// Direct connected (Invisible)

//---[ Filtros para a user-list ]-----------------------------------------------

 #define UFLT_ALL       0xFFFF         // Apresenta todos os usuarios
 #define UFLT_ONLINE    0x000B	       // Apresenta offline com evento e online

//---[ Mensagems de janela ]----------------------------------------------------

 #ifdef WM_USER

   /* Eventos */
   #define WMICQ_START     WM_USER+1101 // Starting (MP1 = HICQ, MP2 = uin)
   #define WMICQ_NETWORK   WM_USER+1102 // Evento de rede (MP1 = Evento, MP2 = size)
   #define WMICQ_SYSTEM    WM_USER+1103 // Evento de sistema (MP1 = Evento, MP2 = OnlineStatus)
   #define WMICQ_USER      WM_USER+1104 // Evento de usuario (MP1 = Evento, MP2 = HUSER)
   #define WMICQ_CONFIG    WM_USER+1105 // Carregar configuracao (MP1 = HICQ, MP2 = INI)
   #define WMICQ_UPDATE	   WM_USER+1106 // Vai redesenhar lista de usuarios (MP1=Inicio/final,MP2=Filtro)
   #define WMICQ_CHAT 	   WM_USER+1107 // Evento de chat (MP1=Evento, MP2=CHATINFO *)
   #define WMICQ_FILE	   WM_USER+1108 // Evento de arquivo (MP1=Evento, MP2=ICQFILE)

   #define WMICQ_WARNING   WM_USER+1110 // Alerta (MP1=Numero/Pos, MP2=ID)
   #define WMICQ_ERROR     WM_USER+1111 // Erro (MP1=Numero/Pos, MP2=ID)
   #define WMICQ_SOCKET	   WM_USER+1112 // Socket error (MP1 = Numero/Pos MP2=sock_errno())
   #define WMICQ_FATAL	   WM_USER+1113 // Erro fatal, apresentar e abortar (MP1=Numero/Pos, MP2=ID)
   #define WMICQ_MMERROR   WM_USER+1113 // Erro de multimidia (MP1=NUM MP2=Play/Stop)
   #define WMICQ_MMMSG	   WM_USER+1114 // Mensagem de erro de multimedia

   /* Mensagems/chat */
   #define WMICQ_SYSMSG    WM_USER+1151 // Mensagem de sistema (MP1 = SYSMSG *)
   #define WMICQ_USRMSG    WM_USER+1152 // Mensagem de usuario (MP1 = HUSER, MP2 = USRMSG *)
   #define WMICQ_CHATLINE  WM_USER+1153 // Linha de chat recebida (MP1=string,MP2=CHATINFO *)
   #define WMICQ_INIT	   WM_USER+1154 // Inicializa a janela (MP1=HICQ)
   #define WMICQ_OFFLINE   WM_USER+1155 // Usuario do outro lado saiu
   #define WMICQ_CHAR	   WM_USER+1156 // Chegou uma tecla (MP1=tecla, MP2 = CHATINFO *);
   #define WMICQ_PARM	   WM_USER+1157 // Mudanca de parametros (MP1=id, MP2= CHATINFO *)
   #define WMICQ_HCHAT	   WM_USER+1158 // Define handle do chat (MP1=void *, MP2=ctl)
   #define WMICQ_SETICON   WM_USER+1159 // Seta o icone de uma janela de mensagem (MP1=hFRAME, MP2=Tipo/Pos)
   #define WMICQ_PLUGIN	   WM_USER+1160 // Plugin envia um texto (MP1=char *)
   #define WMICQ_EVTMSG	   WM_USER+1161 // Message event (MP1=UIN,MP2=HUSER)

   /* Janela principal */
   #define WMICQ_USRADD    WM_USER+1201 // Anexa usuario (MP1 = HUSER, MP2 = NICK)
   #define WMICQ_USRSEP    WM_USER+1202 // Anexa separador (MP1 = Tipo)
   #define WMICQ_REFRESH   WM_USER+1203 // Redesenha usuarios
   #define WMICQ_USERINFO  WM_USER+1204 // Chegou atualizacao de usuario (MP1=HUSER, MP2=SEQ)

   /* Diversos */
   #define WMICQ_CONCT     WM_USER+1250 // Animacao do botao de connect (MP1=POS)
   #define WMICQ_NEXT      WM_USER+1251 // Situacao do botao de Read-Next (MP1=TRUE/FALSE)
   #define WMICQ_SYSMODE   WM_USER+1252 // Modo do sistema (MP1= TRUE/FALSE MP2=System online mode)
   #define WMICQ_USRMODE   WM_USER+1253 // Modo do usuario (MP1= TRUE/FALSE MP2=User online mode)
   #define WMICQ_SETHANDLE WM_USER+1254 // Configura o handle da conexao (MP1=HICQ, MP2=HUSER)
   #define WMICQ_SYSBLINK  WM_USER+1255 // Pisca botao do sistema (MP1=Codigo,MP2=POS)
   #define WMICQ_TITLE     WM_USER+1256 // Configura o titulo da janela (MP1=STRING, MP2=TYPE/POS)
   #define WMICQ_STATUS	   WM_USER+1257 // Mensagem de status (MP1=Codigo, MP2=Info (char *))
   #define WMICQ_CHANGED   WM_USER+1258 // Dados do usuario corrente foram trocados
   #define WMICQ_SAVE	   WM_USER+1259 // Salvar configuracao/dados do usuario
   #define WMICQ_CANCEL	   WM_USER+1260 // Cancelar alteracoes
   #define WMICQ_SHOW	   WM_USER+1261 // Mostra a janela
   #define WMICQ_SOUND	   WM_USER+1262 // Mensagem de audio (MP1=Iniciando/terminando)
   #define WMICQ_TCP	   WM_USER+1263 // Recebida conexao TCP de usuario (MP1=UIN,MP2=HUSER)
   #define WMICQ_IDLE	   WM_USER+1264 // 1 tick por minuto para a janela de chat (MP1=tempo IDLE)
   #define WMICQ_FSTATUS   WM_USER+1265 // Situacao de transferencia de arquivo (MP1=tempo IDLE, MP2= REQUEST *)
   #define WMICQ_READY	   WM_USER+1266 // Sistema pronto (MP1=BOOL)
   #define WMICQ_FILEERR   WM_USER+1267 // Erro no acesso a arquivo (MP1=valor)
   #define WMICQ_MINUTE	   WM_USER+1268 // One by minute to all windows (MP1=HICQ, MP2=DATETIME *)
   #define WMICQ_ADDMENU   WM_USER+1269 // Used by plugin manager (MP1=ADDMENU *)
   #define WMICQ_USRINFO   WM_USER+1270 // User info received (MP1=UIN, MP2=query_type,response_type)
   #define WMICQ_EXTSEARCH WM_USER+1271 // Extended info request status (MP1=uin, MP2=bool)

   /* Pesquisa */
   #define WMICQS_START    WM_USER+1300 // Pesquisa foi iniciada (MP1=Id)
   #define WMICQS_END	   WM_USER+1301 // Pesquisa foi terminada (MP1=Id, MP2=More)
   #define WMICQS_FOUND	   WM_USER+1302 // Usuario encontrado(MP1=Id, MP2=Buffer[Limpar apos copiar])
   #define WMICQS_CLOSE	   WM_USER+1303 // Pesquisa foi fechada (MP1=Id)
   #define WMICQS_TIMEOUT  WM_USER+1304 // Timeout na pesquisa (MP1=Id)

   /* Janela de edi‡ao/visualizacao de mensagems */
   #define WMICQM_SETMSG   WM_USER+1257 // Configura mensagem (MP1=UIN, MP2=USRMSG *)
   #define WMICQM_SET	   WM_USER+1350	// Seta um campo na janela (MP1=ID, MP2= (char *) )
   #define WMICQM_ENABLE   WM_USER+1351 // Liga/desliga botao na janela (MP1=ID, MP2= BOOL)
   #define WMICQM_ADDNEW   WM_USER+1352 // Liga desliga botoes de request/add (MP1=BOOL)
   #define WMICQM_READY	   WM_USER+1353 // Janela preenchida, pode mostrar
   #define WMICQM_RECONFIG WM_USER+1354 // Reconfigura janela (MP1=Novo tipo)

   /* Dialogs only */
   #define WMICQD_HANDLE   WM_USER+1400 // Configura dialogo (MP1=DLGINFO *)
   #define WMICQD_START	   WM_USER+1401 // Starting

 #endif

//---[ PWICQDLL.DLL ]-----------------------------------------------------------

 HICQ           EXPENTRY ICQStart(long, const char *, HINI);
 int            EXPENTRY ICQStop(HICQ);
 BOOL           EXPENTRY ICQRegister(HICQ, HWND,  HWND EXPENTRY (*)(HWND, USHORT) );
 BOOL           EXPENTRY ICQDeRegister(HICQ, HWND);
 void 		EXPENTRY ICQCreateObject(HICQ);
 BOOL		EXPENTRY ICQMMLoaded(HICQ);

 void 		EXPENTRY ICQEnableAutoAway(HWND);

 void           EXPENTRY ICQSetMode(HICQ, long);
 BOOL           EXPENTRY ICQAutoOpen(HICQ);
 void		EXPENTRY ICQDisconnect(HICQ);
 void		EXPENTRY ICQRecconect(HICQ);
 void 		EXPENTRY ICQGoOffline(HICQ);
 void 		EXPENTRY ICQSaveUserInfo(HICQ, const char *, const char *, const char *last, const char *, BOOL);

 HUSER          EXPENTRY ICQAddUser(HICQ,long,const char *, const char *, const char *, const char *, const char *, long);
 HUSER          EXPENTRY ICQAddNewUser(HICQ,long,const char *, const char *, const char *, const char *);
 int            EXPENTRY ICQRequestAut(HICQ, HWND, long, const char *, const char *, const char *, const char *);
 int		EXPENTRY ICQReAskAut(HICQ, HWND, HUSER);

 HUSER		EXPENTRY ICQQueryUser(HICQ,ULONG);
 const char *	EXPENTRY ICQQueryNick(HICQ,HUSER);
 const char *   EXPENTRY ICQQueryUserNick(HUSER);
 const char *   EXPENTRY ICQQueryUserEmail(HUSER);
 const char *   EXPENTRY ICQQueryUserFirstName(HUSER);
 const char *   EXPENTRY ICQQueryUserLastName(HUSER);
 const char *	EXPENTRY ICQQueryUserSound(HUSER);
 void           EXPENTRY ICQRedrawUsers(HICQ);
 HUSER          EXPENTRY ICQRefreshUser(HUSER, const char *, const char *, const char *, const char *, const char *);
 void           EXPENTRY ICQSaveContactList(HICQ);
 void           EXPENTRY ICQDeleteUser(HUSER);
 HICQ		EXPENTRY ICQQueryUserConnct(HUSER);
 void		EXPENTRY ICQSetUserFlags(HUSER, ULONG);
 long		EXPENTRY ICQQueryUserIP(HUSER);

 BOOL 		EXPENTRY ICQOpenSearch(HICQ, HUSER, HWND, const char *, HWND (*callback)(HICQ, HWND, void *),void *);
 int            EXPENTRY ICQRequestBasicInfo(HICQ, HWND, ULONG);
 int		EXPENTRY ICQRequestExtendedInfo(HICQ, HWND, ULONG);
 short		EXPENTRY ICQSearchByUin(HICQ,HWND,long);
 short		EXPENTRY ICQSearchUser(HICQ,HWND,const char *, const char *, const char *, const char *);
 void		EXPENTRY ICQCloseSearch(HICQ,short);
 void		EXPENTRY ICQSetSearchWindow(HICQ,HWND);

 short          EXPENTRY ICQQueryModeBitmap(long);
 USHORT         EXPENTRY ICQQueryMsgType(HICQ, HUSER);
 ULONG		EXPENTRY ICQQueryUin(HICQ);

 void           EXPENTRY ICQSetHandle(HICQ, HWND);

 void           EXPENTRY ICQWinBroadcast(HICQ, ULONG, MPARAM, MPARAM);
 void           EXPENTRY ICQUserBroadcast(HUSER, ULONG, MPARAM, MPARAM);
 void		EXPENTRY ICQPostMessage(HICQ, ULONG, MPARAM, MPARAM);
 const char *	EXPENTRY ICQQueryString(HICQ, short, short, char *);
 void		EXPENTRY ICQOpenConfigDlg(HICQ);

 void           EXPENTRY ICQStoreWindowPos(HICQ,HWND,const char *);
 void           EXPENTRY ICQRestoreWindowPos(HICQ,HWND,const char *, short, short);
 BOOL		EXPENTRY ICQOpenWindow(HICQ, HUSER, HWND, const char *, HWND (*)(HICQ, HWND, void *),void *);
 void		EXPENTRY ICQDeRegisterDialog(HICQ, HWND);
 void		EXPENTRY ICQRegisterDialog(HICQ, int, HWND);
 void		EXPENTRY ICQUserDialog(HICQ,HUSER,int,HWND);
 void		EXPENTRY ICQConfigureWindow(HICQ, HUSER, long, HWND);

 void           EXPENTRY ICQUserClick(HUSER,BOOL);
 void           EXPENTRY ICQSystemClick(HICQ);
 void           EXPENTRY ICQEditMsg(HICQ, long, USHORT);
 void           EXPENTRY ICQReadNext(HICQ, HUSER, HWND);
 void 		EXPENTRY ICQMessage(HICQ,long,const char *,const char *,const char *,const char *, BOOL);
 BOOL		EXPENTRY ICQQueryLogMode(HICQ);


 #define ICQSendMsg(c, h, u, t, m, w) ICQMsgServer(c, h, u, t, m, w)
 BOOL           EXPENTRY ICQMsgServer(HICQ, HWND, long, short, char *, char *, USHORT);

 BOOL		EXPENTRY ICQMsgDirect(HICQ, HWND, long, short, char *, char *, USHORT);
 BOOL		EXPENTRY ICQRequestChat(HICQ,HWND,long,char *);
 BOOL           EXPENTRY ICQAuthorize(HICQ, HWND, long);
 BOOL           EXPENTRY ICQRefuse(HICQ, HWND, long, char *);
 void           EXPENTRY ICQSetFilter(HICQ, USHORT);

 BOOL		EXPENTRY ICQRequestFile(HICQ,HWND,long,char *, char *);

 void		EXPENTRY ICQChkKbrd(HICQ, HWND, USHORT);
// void		EXPENTRY ICQFormatScript(HICQ, HUSER, const char *, int, char *, short);
 BOOL 		EXPENTRY ICQExecuteScript(HWND, HICQ, HUSER, short, const char *, int, char *);

 long		EXPENTRY ICQQueryReserved(HICQ,const char *);
 HINI		EXPENTRY ICQQueryInifile(HICQ);
 HWND		EXPENTRY ICQQueryMainWindow(HICQ);
 void		EXPENTRY ICQWriteSysLog(HICQ,const char *);
 int		EXPENTRY ICQPlaySound(HICQ, const char *, BOOL);
 MRESULT	EXPENTRY ICQProcessSound(HICQ, HWND, ULONG, MPARAM, MPARAM);
 BOOL 		EXPENTRY ICQSendChatLine(CHATINFO *, char *);

 char *   	EXPENTRY ICQLoadMsg(HAB, short, short, char *);
 void 		EXPENTRY ICQSetWindowTitle(HWND, HICQ, USRMSG *, const char *);
 USHORT		EXPENTRY ICQQueryMsgTitle(HICQ, const USRMSG *, const char *, int sz, char *);
 void		EXPENTRY ICQSetFont(HWND, HICQ, USHORT);

 BOOL           EXPENTRY MouseOver(HWND, short);
 BOOL 		EXPENTRY ICQCanConnect(HICQ, HUSER);

 BOOL	 	EXPENTRY ICQRejectRequest(HUSER, USRMSG *, char *);
 BOOL		EXPENTRY ICQAcceptRequest(HUSER, USRMSG *);

 BOOL 		EXPENTRY ICQDeleteMessage(HICQ, HUSER, HWND, USRMSG *, USHORT);

 void *		EXPENTRY ICQAllocMemory(HICQ,USHORT);
 void		EXPENTRY ICQFreeMemory(HICQ,void *);

 #ifdef __NCLIB__
 MEMMGR *	EXPENTRY ICQQueryMemoryManager(HICQ);
 #endif

 void		EXPENTRY ICQExecPluginOption(HICQ, HUSER, USHORT, USHORT, HWND);
 void		EXPENTRY ICQConvertCpg(HICQ,char *,BOOL);

 BOOL		EXPENTRY ICQCanRequestUserInfo(HICQ);

//---[ ICQTOOLS.DLL ]-----------------------------------------------------------

 const char *   EXPENTRY ICQLoadString(HICQ, const char *, int, char *, const char *);
 const char *   EXPENTRY ICQSaveString(HICQ, const char *, const char *);
 ULONG      	EXPENTRY ICQLoadLong(HICQ,const char *, ULONG);
 ULONG      	EXPENTRY ICQSaveLong(HICQ,const char *, ULONG);
 void 		EXPENTRY ICQSaveDlgText(DLGINFO *, HWND, short, const char *);
 void 		EXPENTRY ICQLoadDlgText(DLGINFO *, HWND, short, const char *);

 void 		EXPENTRY ICQMntDialog(HWND, USHORT, PFNWP, HMODULE, ULONG, int);
 ULONG 		EXPENTRY ICQMessageBox(HICQ, HWND, HMODULE, USHORT, ULONG);

 void 		EXPENTRY ICQLoadModeFlags(HWND, USHORT, USHORT, const char *, ULONG, DLGINFO *);
 void 		EXPENTRY ICQSaveModeFlags(HWND, USHORT, USHORT, const char *, DLGINFO *);
 BOOL 		EXPENTRY ICQQueryModeFlag(HICQ, ULONG);
 USHORT		EXPENTRY ICQQueryModeName(HICQ, int, char *);

 int 		EXPENTRY ICQQueryLocalCodepage(HICQ);

 int		EXPENTRY ICQSendHTTPRequest(HICQ, const char *, const char *, long *);
 int 		EXPENTRY ICQhttpRecv(HICQ, int, char *, int);

 void		EXPENTRY ICQOpenURL(HICQ,const char *);
 void		EXPENTRY ICQCreateURLObject(HICQ,const char *, const char *);

 ULONG 		EXPENTRY ICQSaveRadioButton(DLGINFO *, HWND, SHORT, const char *, const short *);
 void 		EXPENTRY ICQLoadRadioButton(DLGINFO *, HWND, SHORT, const char *, int, const short *);

 const ULONG *	EXPENTRY ICQQueryModes(void);
 char * 	EXPENTRY ICQModeDescr(HICQ, ULONG, char *);

 const char *   EXPENTRY ICQLoadUserDB(HICQ, HUSER, const char *, int, char *);
 const char *   EXPENTRY ICQSaveUserDB(HICQ, HUSER, const char *, const char *);

 void   	EXPENTRY ICQDlgLoadUserDB(DLGINFO *, HWND, short, const char *, int, char *);
 void   	EXPENTRY ICQDlgSaveUserDB(DLGINFO *, HWND, short, const char *, int, char *);
 void 		EXPENTRY ICQDlgLoadUserCountry(DLGINFO *, HWND, short, const char *);
 void 		EXPENTRY ICQDlgSaveUserCountry(DLGINFO *, HWND, short, const char *);

 const char * 	EXPENTRY ICQQueryProfileString(HICQ, const char *, const char *, const char *, char *, int);
 const char *   EXPENTRY ICQQueryPrfString(HINI, const char *, const char *, const char *, char *, int);

 BOOL		EXPENTRY ICQLoadCtryList(HICQ, ULONG, HWND, USHORT);

//---[ PWICQDLG.DLL ]-----------------------------------------------------------

 HMODULE	EXPENTRY ICQDlgInitialize(HICQ, HAB);
 void		EXPENTRY ICQDlgTerminate(HMODULE);
 void 		EXPENTRY ICQConfigureDialogManager(HICQ, HWND);
 void		EXPENTRY ICQDlgOpenSearch(HICQ);
 void		EXPENTRY ICQDlgOpenUserInfo(HICQ, HUSER, HWND);
 void 		EXPENTRY ICQDlgOpenUserFlags(HICQ, HUSER, HWND);
 void		EXPENTRY ICQDlgOpenCurrentUser(HICQ, HWND);
 BOOL		EXPENTRY ICQDlgOpenQueryWindow(HICQ, long, HWND, int, const char *, int, char *);
 void		EXPENTRY ICQAwayMsg(HICQ, HUSER, HWND, USHORT, const char *);
 void 		EXPENTRY ICQSelectFile(HWND,USHORT,DLGINFO *,const char *,const char *);
 void		EXPENTRY ICQSelectColor(HWND,HICQ,ULONG);
 void 		EXPENTRY ICQProcessDialog(HICQ, HUSER, char *, USHORT, HMODULE, PFNWP, void *);

//---[ PQICQCHT.DLL ]-----------------------------------------------------------

 int            EXPENTRY ICQChatInitialize(HAB);
 HWND		EXPENTRY ICQOpenChatWin(CHATINFO *);
 void *		EXPENTRY ICQChatStart(HICQ, HWND);
 void		EXPENTRY ICQChatStop(HICQ, void *);
 void 		EXPENTRY ICQConfigureChatSystem(HICQ, HWND);

//---[ PWICQGUI.DLL ]-----------------------------------------------------------

 #define ICQ_MAIN       "pwICQ1"        // Dialogo principal
 #define ICQ_MSG        "pwICQ2"        // Dialogo de mensagem
 #define ICQ_MENU       "pwICQ3"        // Menus
 #define ICQ_CHAT       "pwICQ4"        // Janela de chat
 #define ICQ_CHAT2	"pwICQ5"	// Area de texto da janela de chat
 #define ICQ_BUTTON	"pwICQ6"	// Botoes de controle

 int            EXPENTRY ICQRegisterClasses(HAB);
 HWND           EXPENTRY ICQCreateMainWindow(HICQ, HINI);
 HWND 		EXPENTRY ICQCreateMsgWindow(HWND,USHORT);
 HUSER          EXPENTRY ICQQuerySelected(HWND);
 void		EXPENTRY ICQConfigureSkinManager(HICQ, HWND);
 void		EXPENTRY ICQSkinManagerOptions(HICQ, HWND);
 void           EXPENTRY DrawICQBitmap(HPS,HBITMAP,short,PPOINTL);
 BOOL		EXPENTRY ICQDefMsgProc(HICQ,HWND,ULONG,MPARAM,MPARAM);

//---[ ICQPLAY.DLL ]------------------------------------------------------------

 int 		EXPENTRY ICQPlayWav(HICQ, const char *);
 MRESULT 	EXPENTRY ICQMMMsg(HICQ, HWND, ULONG, MPARAM, MPARAM);
 void		EXPENTRY ICQPlayInitialize(HICQ);
 void		EXPENTRY ICQPlayTerminate(HICQ);
 void		EXPENTRY ICQKeySound(HICQ,char);

//---[ ICQNET.DLL ]-------------------------------------------------------------

 int 		EXPENTRY ICQOpenUDP(void);
 int 		EXPENTRY ICQOpenTCP(void);
 int 		EXPENTRY ICQBindSocket(int, int);
 int		EXPENTRY ICQCloseSocket(int);
 long		EXPENTRY ICQGetHostID(void);
 long		EXPENTRY ICQGetHostByName(char *);
 int		EXPENTRY ICQGetPort(int);
 int		EXPENTRY ICQSendTo(int,long,int,void *, int);
 int		EXPENTRY ICQGetSockError(void);
 int 		EXPENTRY ICQRecvFrom(int, long *, int *, void *, int);
 int 		EXPENTRY ICQCancelSocket(int);
 int		EXPENTRY ICQAcceptConnct(int, long *, int *);
 int		EXPENTRY ICQListen(int);
 int 		EXPENTRY ICQSetTCPOpt(int);
 int		EXPENTRY ICQRecv(int,void *, int);
 int		EXPENTRY ICQSend(int,void *, int);
 int 		EXPENTRY ICQConnect(int, long, int);
 BOOL		EXPENTRY chkForNat(HICQ, long);
 void 		EXPENTRY ICQConfigureNetwork(HICQ, HWND);
 int 		EXPENTRY ICQSetSockTimeout(int, HICQ, const char *, int);
 BOOL		EXPENTRY ICQCheckVersion(HICQ);
 int 		EXPENTRY ICQVerifySocket(HICQ, int);

//---[ History/Plugins ]--------------------------------------------------------

 enum HST_TYPES
 {
    HST_RECEIVED,			// Received
    HST_SERVER,				// Sent thru server
    HST_DIRECT,				// Sent directly to user


    HST_MAX
 };

 int 		EXPENTRY ICQPConfigure(HICQ, HMODULE);
 void		EXPENTRY ICQPInitialize(HICQ,HWND);
 void		EXPENTRY ICQPTerminate(HICQ);
 void		EXPENTRY ICQPAddConfigPage(HICQ, HWND);
 void		EXPENTRY ICQPAddUserPage(HICQ, HUSER, HWND);
 void		EXPENTRY ICQPOpen(HICQ, HUSER, HWND);
 BOOL		EXPENTRY ICQPMessageReceived(HICQ, long, USRMSG *);
 void		EXPENTRY ICQPMessageChanged(HICQ, ULONG, USRMSG *);
 void		EXPENTRY ICQPSystemEvent(HICQ,short);
 void		EXPENTRY ICQPUserEvent(HICQ,HUSER,short);
 void 		EXPENTRY ICQPMenu(HICQ,HUSER,USHORT,HWND);
 int 		EXPENTRY ICQPAddMsgButtons(HICQ,HWND,int);


#endif




