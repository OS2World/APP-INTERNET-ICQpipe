/*
 * ICQPipe.C	pwICQ plugin to send messages to a Pipe
 *		(Designed for use with SysBar/2)
 *
 */

 #define INCL_WIN

 #ifdef _NCLIB_
    #include <nclib.h>
 #else
    #include <os2.h>
 #endif

 #include <stdio.h>
 #include <pwicq.h>

/*----------------------------------------------------------------------------*/

static void 		writePipe(const char *);
static void 		loadConfig(HWND, DLGINFO *);
static void 		saveConfig(HWND, DLGINFO *);

MRESULT EXPENTRY 	icqPipeCfg(HWND, ULONG, MPARAM, MPARAM);

/*----------------------------------------------------------------------------*/

 static char 	pipeName[0x0100]	="\\PIPE\\pwICQ";
 static ULONG   flags			= 0x00003;
 static	HMODULE	module			= NULLHANDLE;

/*----------------------------------------------------------------------------*/

 int EXPENTRY ICQPConfigure(HICQ icq, HMODULE mod)
 {
    /*
     *
     * PLUGIN configuration routine, the first called by pwICQ, if returns
     * nonzero the plugin is unloaded
     *
     */
    module = mod;

    ICQLoadString(icq, "icqPipe:Name", 0x0100, pipeName, pipeName);
    flags = ICQLoadLong(icq, "icqPipe:Flags", flags);

    return 0;
 }

 void EXPENTRY ICQPInitialize(HICQ icq,HWND hwnd)
 {
    if(flags&1)
       writePipe("Starting");
 }

 void EXPENTRY ICQPTerminate(HICQ icq)
 {
    if(flags&1)
       writePipe("Stopped");
 }

 void EXPENTRY ICQPSystemEvent(HICQ icq,short eventCode)
 {
    /*
     * Called in every system event
     *
     * Event codes in pwICQ.H (#define EVT_*)
     *
     */
    if(!(flags&1))
    {
       if(eventCode == EVT_OFFLINE)
	  writePipe("");
       return;
    }

    switch(eventCode)
    {
    case EVT_OFFLINE:
       writePipe("Disconnected");
       break;

    case EVT_CONNECT:
       writePipe("Connecting");
       break;

    }

 }

 void EXPENTRY ICQPUserEvent(HICQ icq, HUSER usr, short eventCode)
 {
    /*
     * Called in every user event
     *
     * Event codes in pwICQ.H (#define EVT_*)
     *
     */
    char 	text[0x0100];

    if(!(flags&2))
       return;

    if(eventCode == EVT_ONLINE)
    {
       sprintf(text,"%s online",ICQQueryUserNick(usr));
       writePipe(text);
    }
 }

 void EXPENTRY ICQPMessageChanged(HICQ ctl, ULONG uin, USRMSG *msg)
 {
    /*
     * Called when the first message changes
     */
   char 	title[0x0100];
   HUSER	usr;

   if(!(flags&4))
      return;

   if(msg)
   {
      usr = ICQQueryUser(ctl,uin);

      if(usr)
	 ICQQueryMsgTitle(ctl, msg, ICQQueryUserNick(usr), 0x00FF, title);
      else
	 ICQQueryMsgTitle(ctl, msg, "System", 0x00FF, title);
   }
   else
   {
      *title = 0;
   }
   writePipe(title);
 }


 static void writePipe(const char *text)
 {
    FILE *f = fopen(pipeName,"wt");

    if(f)
    {
       fprintf(f,"%s\n",text);
       fclose(f);
    }
 }

 void EXPENTRY ICQPAddConfigPage(HICQ icq, HWND ntbk)
 {
    /*
     * Add one page to the pwICQ's main configuration notebook
     */
    ICQMntDialog( ntbk, BKA_MAJOR, icqPipeCfg, module, 1000, 1000);
 }

 MRESULT EXPENTRY icqPipeCfg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
 {
    /* Dialog procedure */

    switch(msg)
    {
    case WMICQD_HANDLE:
       loadConfig(hwnd,PVOIDFROMMP(mp1));
       break;

    case WMICQ_SAVE:
       saveConfig(hwnd, WinQueryWindowPtr(hwnd,QWL_USER));
       break;

    case WMICQ_CANCEL:
       break;

    default:
       return WinDefDlgProc(hwnd,msg,mp1,mp2);
    }
    return 0;

 }

 static void loadConfig(HWND hwnd, DLGINFO *dlg)
 {
    ULONG flg;

    WinSetWindowPtr(hwnd,QWL_USER,dlg);

    ICQLoadDlgText(dlg, hwnd, 105, "icqPipe:Name");

    flg = ICQLoadLong(dlg->ctl, "icqPipe:Flags", 0x07);

    if(flg & 1)
       WinSendDlgItemMsg(hwnd,101,BM_SETCHECK,MPFROMSHORT(TRUE),(MPARAM)NULL);
    else
       WinSendDlgItemMsg(hwnd,101,BM_SETCHECK,MPFROMSHORT(FALSE),(MPARAM)NULL);

    if(flg & 2)
       WinSendDlgItemMsg(hwnd,102,BM_SETCHECK,MPFROMSHORT(TRUE),(MPARAM)NULL);
    else
       WinSendDlgItemMsg(hwnd,102,BM_SETCHECK,MPFROMSHORT(FALSE),(MPARAM)NULL);

    if(flg & 4)
       WinSendDlgItemMsg(hwnd,106,BM_SETCHECK,MPFROMSHORT(TRUE),(MPARAM)NULL);
    else
       WinSendDlgItemMsg(hwnd,106,BM_SETCHECK,MPFROMSHORT(FALSE),(MPARAM)NULL);

 }

 static void saveConfig(HWND hwnd, DLGINFO *dlg)
 {
    WinQueryDlgItemText( hwnd, 105, 0x0100, pipeName);
    ICQSaveString(dlg->ctl,"icqPipe:Name",pipeName);

    flags  = (WinQueryButtonCheckstate(hwnd,101) ? 1 : 0)
	     | (WinQueryButtonCheckstate(hwnd,102) ? 2 : 0)
	     | (WinQueryButtonCheckstate(hwnd,106) ? 4 : 0);

    ICQSaveLong(dlg->ctl, "icqPipe:Flags", flags);

 }

