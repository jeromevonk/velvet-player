#define NO_SEEKING_ALLOWED 0xFFFFFFFF

class CMCI_interface
{
public:
   CMCI_interface(char* szAlias = NULL);
   ~CMCI_interface();

   DWORD Open(char* szFile, bool bCanSeek);
   DWORD Close();
   DWORD Play();
   DWORD Pause();
   DWORD Resume();
   DWORD Stop();
   DWORD SetVolume(int iVolume);
   char* GetCurrentSong();
   DWORD GetSongLength(int* iMinutes, int* iSeconds);
   DWORD GetSongLength(int* iMiliSeconds);
   DWORD GetCurrentPosition(int* iMinutes, int* iSeconds);
   DWORD GetCurrentPosition(int* iMiliSeconds);
   DWORD isPlaying();
   DWORD Seek(int iMiliSeconds);

public:
   int m_iCurrentSongMinLen;
   int m_iCurrentSongSecLen;

private:
   char m_szAlias[30];
   char m_szCurrentSong[220];
   bool m_bCanSeek;
};