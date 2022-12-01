#include "StdAfx.h"
#include "MCI_interface.h"

#define MCI_BUFFER_LEN 256

CMCI_interface::CMCI_interface(char* szAlias)
: m_bCanSeek(false),
  m_iCurrentSongMinLen(0),
  m_iCurrentSongSecLen(0)
{
   if ( NULL != szAlias && strlen(szAlias) < 30 )
   {
      strcpy_s(m_szAlias, sizeof(m_szAlias), szAlias);
   }
   else
   {
      sprintf_s(m_szAlias, sizeof(m_szAlias), "MCI_App");
   }
}

CMCI_interface::~CMCI_interface()
{

}

DWORD CMCI_interface::Open(char* szFile, bool bCanSeek)
{
   DWORD dwRet = 0;
   char szCmd[MCI_BUFFER_LEN];

   // Open
   sprintf_s( szCmd, sizeof(szCmd), "open \"%s\" alias %s", szFile, m_szAlias );
   mciSendString( szCmd, NULL, 0, NULL );
   if ( dwRet != 0)
   {
      return dwRet;
   }

   // Set time format
   sprintf_s( szCmd, sizeof(szCmd), "set %s time format to milliseconds", m_szAlias );
   mciSendString( szCmd, NULL, 0, NULL );
   if ( dwRet != 0)
   {
      return dwRet;
   }

   // Set seek
   sprintf_s( szCmd, sizeof(szCmd), "set %s seek exactly on", m_szAlias );
   mciSendString( szCmd, NULL, 0, NULL );
   if ( dwRet != 0)
   {
      return dwRet;
   }

   // Set as current song
   strcpy_s(m_szCurrentSong, sizeof(m_szCurrentSong), szFile);

   // In these variable, store if the user can seek through  the song
   m_bCanSeek = bCanSeek;

   // Call GetSongLength to update class variables (m_iCurrentSongMinLen and m_iCurrentSongSecLen)
   GetSongLength(NULL);

   return 0;
}

DWORD CMCI_interface::Close(void)
{
   char szCmd[MCI_BUFFER_LEN];
   sprintf_s( szCmd, sizeof(szCmd), "close %s", m_szAlias  );

   // Erase current song
   strcpy_s(m_szCurrentSong, sizeof(m_szCurrentSong), "\0");

   return mciSendString( szCmd, NULL, 0, NULL );
}

DWORD CMCI_interface::Play(void)
{
   char szCmd[MCI_BUFFER_LEN];
   sprintf_s( szCmd, sizeof(szCmd), "play %s", m_szAlias );
   return mciSendString( szCmd, NULL, 0, NULL );
}

DWORD CMCI_interface::Pause(void)
{
   char szCmd[MCI_BUFFER_LEN];
   sprintf_s( szCmd, sizeof(szCmd), "pause %s", m_szAlias );
   return mciSendString( szCmd, NULL, 0, NULL );
}

DWORD CMCI_interface::Resume(void)
{
   char szCmd[MCI_BUFFER_LEN];
   sprintf_s( szCmd, sizeof(szCmd), "resume %s", m_szAlias );
   return mciSendString( szCmd, NULL, 0, NULL );
}

DWORD CMCI_interface::Stop(void)
{
   char szCmd[MCI_BUFFER_LEN];
   sprintf_s( szCmd, sizeof(szCmd), "stop %s", m_szAlias );
   return mciSendString( szCmd, NULL, 0, NULL );
}

DWORD CMCI_interface::SetVolume(int iVolume)
{
   char szCmd[MCI_BUFFER_LEN];
   sprintf_s( szCmd, sizeof(szCmd), "setaudio %s volume to %u", m_szAlias, iVolume);
   return mciSendString( szCmd, NULL, 0, NULL );
}

DWORD CMCI_interface::isPlaying()
{
   DWORD dwRet = 0;
   char szCmd[MCI_BUFFER_LEN]      = {0};
   char szResponse[MCI_BUFFER_LEN] = {0};
   sprintf_s( szCmd, sizeof(szCmd), "status %s mode", m_szAlias );
   dwRet =  mciSendString( szCmd, szResponse, sizeof(szResponse), NULL );

   if ( 0 == memcmp(szResponse, "playing", 7) )
   {
      return 1;
   }
   else
   {
      return 0;
   }
}

DWORD CMCI_interface::GetCurrentPosition(int* iMinutes, int* iSeconds)
{
   DWORD dwRet = 0;
   char szCmd[MCI_BUFFER_LEN]      = {0};
   char szResponse[MCI_BUFFER_LEN] = {0};
   sprintf_s( szCmd, sizeof(szCmd), "status %s position", m_szAlias );

   dwRet = mciSendString( szCmd, szResponse, sizeof(szResponse), NULL );

   int iMiliSeconds = atoi(szResponse);

   if ( 0 == dwRet )
   {
      *iSeconds = (iMiliSeconds / 1000) % 60;
      *iMinutes = (iMiliSeconds / 1000) / 60;
   }

   return dwRet;
}

DWORD CMCI_interface::GetCurrentPosition(int* iMiliSeconds)
{
   DWORD dwRet = 0;
   char szCmd[MCI_BUFFER_LEN]      = {0};
   char szResponse[MCI_BUFFER_LEN] = {0};
   sprintf_s( szCmd, sizeof(szCmd), "status %s position", m_szAlias );

   dwRet =  mciSendString( szCmd, szResponse, sizeof(szResponse), NULL );
   *iMiliSeconds = atoi(szResponse);

   return dwRet;
}

DWORD CMCI_interface::Seek(int iMiliSeconds)
{
   char szCmd[MCI_BUFFER_LEN] = {0};

   if ( false == m_bCanSeek )
   {
      return NO_SEEKING_ALLOWED;
   }

   if ( 1 == isPlaying() )
   {
      sprintf_s( szCmd, sizeof(szCmd), "play %s from %d", m_szAlias, iMiliSeconds);
   }
   else
   {
      sprintf_s( szCmd, sizeof(szCmd), "seek %s to %d", m_szAlias, iMiliSeconds);
   }

   return mciSendString( szCmd, NULL, 0, NULL );
}

char* CMCI_interface::GetCurrentSong(void)
{
   if ( !isPlaying() )
   {
      return NULL;
   }

   return m_szCurrentSong;
}

DWORD CMCI_interface::GetSongLength(int* iSeconds)
{
   // ***************************************************************************************************************
   // This MCI function may return the wrong length if the mp3 encoded with VBR (variable bit rate)
   // See http://forums.codeguru.com/showthread.php?456663-mciSendString%28-quot-status-ALIAS-length-quot-%29-returns-wrong-value
   // and https://en.wikipedia.org/wiki/Variable_bitrate
   // ***************************************************************************************************************

   // ***************************************************************************************************************

   if ( strlen(m_szCurrentSong) == 0 )
   {
      return 2;
   }

   // Instead, we are going to use id3lib
   DWORD dwRet = 0;
   int iSecondsAux = 0;

   ID3_Tag myTag(m_szCurrentSong);
   const Mp3_Headerinfo* mp3info;
   if ((mp3info = myTag.GetMp3HeaderInfo()) != NULL)
   {

      // If we have the information from ID3 lib, use it
      if ( 0 != mp3info->time )
      {
         iSecondsAux = mp3info->time;
      }
      else
      {
         // Error with the ID3 tag, so let's use MCI
         char szCmd[MCI_BUFFER_LEN]      = {0};
         char szResponse[MCI_BUFFER_LEN] = {0};
         sprintf_s( szCmd, sizeof(szCmd), "status %s length", m_szAlias);
         dwRet = mciSendString( szCmd, szResponse, sizeof(szResponse), NULL );

         int iMiliSeconds = atoi(szResponse);
         iSecondsAux      = (iMiliSeconds / 1000) + 1; // add 1, no harm done in rounding up
      }

      m_iCurrentSongMinLen = iSecondsAux / 60;
      m_iCurrentSongSecLen = iSecondsAux % 60;

      if ( NULL != iSeconds )
      {
         *iSeconds = iSecondsAux;
      }
   }
   else
   {
      dwRet = 1;
   }

   return dwRet;
}
