/*****************************************************************************/
/* SCommon.h                              Copyright (c) Ladislav Zezula 2003 */
/*---------------------------------------------------------------------------*/
/* Common functions for encryption/decryption from Storm.dll. Included by    */
/* SFile*** functions, do not include and do not use this file directly      */
/*---------------------------------------------------------------------------*/
/*   Date    Ver   Who  Comment                                              */
/* --------  ----  ---  -------                                              */
/* 24.03.03  1.00  Lad  The first version of SFileCommon.h                   */
/* 12.06.04  1.00  Lad  Renamed to SCommon.h                                 */
/*****************************************************************************/

#ifndef __SCOMMON_H__
#define __SCOMMON_H__

//-----------------------------------------------------------------------------
// StormLib private defines

#define SFILE_TYPE_DATA  0              // Process the file as data file
#define SFILE_TYPE_WAVE  1              // Process the file as WAVe file

#define LISTFILE_ENTRY_DELETED   (DWORD_PTR)(-2)
#define LISTFILE_ENTRY_FREE      (DWORD_PTR)(-1)

// Prevent problems with CRT "min" and "max" functions,
// as they are not defined on all platforms
#define STORMLIB_MIN(a, b) ((a < b) ? a : b)
#define STORMLIB_MAX(a, b) ((a > b) ? a : b)

//-----------------------------------------------------------------------------
// External variables

extern TMPQArchive * pFirstOpen;
extern LCID          lcLocale;

//-----------------------------------------------------------------------------
// Encryption and decryption functions

int   PrepareStormBuffer();

void  EncryptHashTable(DWORD * pdwTable, BYTE * pbKey, DWORD dwLength);
void  DecryptHashTable(DWORD * pdwTable, BYTE * pbKey, DWORD dwLength);
TMPQHash * FindFreeHashEntry(TMPQArchive * ha, const char * szFileName);

void  EncryptBlockTable(DWORD * pdwTable, BYTE * pbKey, DWORD dwLength);
void  DecryptBlockTable(DWORD * pdwTable, BYTE * pbKey, DWORD dwLength);

DWORD DetectFileSeed(DWORD * block, DWORD decrypted);
DWORD DetectFileSeed2(DWORD * block, UINT nDwords, ...);
void  EncryptMPQBlock(DWORD * pdwBlock, DWORD dwLength, DWORD dwSeed1);
void  DecryptMPQBlock(DWORD * pdwBlock, DWORD dwLength, DWORD dwSeed1);

DWORD DecryptHashIndex(TMPQArchive * ha, const char * szFileName);
DWORD DecryptName1    (const char * szFileName);
DWORD DecryptName2    (const char * szFileName);
DWORD DecryptFileSeed (const char * szFileName);

TMPQHash * GetHashEntry  (TMPQArchive * ha, const char * szFileName);
TMPQHash * GetHashEntryEx(TMPQArchive * ha, const char * szFileName, LCID lcLocale);

//-----------------------------------------------------------------------------
// Compression and decompression functions

int Compress_pklib  (char * pbOutBuffer, int * pdwOutLength, char * pbInBuffer, int dwInLength, int * pCmpType, int nCmpLevel);
int Decompress_pklib(char * pbOutBuffer, int * pdwOutLength, char * pbInBuffer, int dwInLength);

//-----------------------------------------------------------------------------
// Checking functions

BOOL IsValidMpqHandle(TMPQArchive * ha);
BOOL IsValidFileHandle(TMPQFile * hf);

//-----------------------------------------------------------------------------
// Other functions

BOOL SFileOpenArchiveEx(const char * szMpqName, DWORD dwPriority, DWORD dwFlags, HANDLE * phMPQ, DWORD dwAccessMode = GENERIC_READ);
int  AddInternalFile(TMPQArchive * ha, const char * szFileName);
int  AddFileToArchive(TMPQArchive * ha, HANDLE hFile, const char * szArchivedName, DWORD dwFlags, DWORD dwQuality, int nFileType, BOOL * pbReplaced);
int  SetDataCompression(int nDataCompression);
int  SaveMPQTables(TMPQArchive * ha);
void FreeMPQArchive(TMPQArchive *& ha);
void FreeMPQFile(TMPQFile *& hf);

BOOL CheckWildCard(const char * szString, const char * szWildCard);

//-----------------------------------------------------------------------------
// Attributes support

int  SAttrFileCreate(TMPQArchive * ha);
int  SAttrFileLoad(TMPQArchive * ha);
int  SAttrFileSaveToMpq(TMPQArchive * ha);
void FreeMPQAttributes(TMPQAttr * pAttr);

//-----------------------------------------------------------------------------
// Listfile functions

int  SListFileCreateListFile(TMPQArchive * ha);
int  SListFileCreateNode(TMPQArchive * ha, const char * szFileName, LCID lcLocale);
int  SListFileRemoveNode(TMPQArchive * ha, const char * szFileName, LCID lcLocale);
void SListFileFreeListFile(TMPQArchive * ha);

int  SListFileSaveToMpq(TMPQArchive * ha);

#endif // __SCOMMON_H__

