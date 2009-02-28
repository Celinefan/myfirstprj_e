// IMGFUC.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(SCU_III_IMGFUC_INCLUDED_)
#define SCU_III_IMGFUC_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <scuu.h>
#include <afxtempl.h>
#include <fstream.h>

typedef CArray<CRect,CRect> ObjRectArray;

void ReverseColor( CImage* pPic );
void ReverseColor( CDIBitmap* pPic );
BOOL Norm_Image( IMAGE ImgOrg, IMAGE ImgNorm, CRect rcProc );
void Scaleimage( CImage* pPic, float fPercent );
void Scaleimage( CDIBitmap* pPic, float fPercent );
void DrawRect( CImage* pPic, CRect rect, int r, int g, int b );
void DrawRect( CDIBitmap* pPic, CRect rect, int r, int g, int b );
void DrawObjRectArray( CImage* pPic, ObjRectArray &rectArray, int r, int g, int b );
void DrawObjRectArray( CDIBitmap* pPic, ObjRectArray &rectArray, int r, int g, int b );
void FillImage(CImage* pPic, CRect rc, int r, int g, int b);
void DrawObjRectArray(IMAGE imgDis, ObjRectArray &RectArray );
void SaveIMGPart( CImage *pPic, CRect rcSave, int nChannel, CString strFilePath );
void SavePICPart( CImage *pPic, CRect rcSave, CString strFilePath );
void SavePICPart( CDIBitmap *pPic, CRect rcSave, CString strFilePath );
BOOL ImageSave( IMAGE img, CString strSavePath );

void SortRect(ObjRectArray &rect_array);
void SortRect_B2T(ObjRectArray &rect_array);//Sort From bottom to top;
void SortRectByLength(ObjRectArray &rect_array);//Sort by the width;
void SortRectByArea( ObjRectArray &rect_array );//Sort by the area;

void TransferRectFromL2W( CRect& rc, CRect rcLocal );//Transfer Rect from Local to Whole
void TransferRcArrayFromL2W( ObjRectArray& rcArray, CRect rcLocal);

void SplitFilePath( CString& filePath, CString& fileName);
int GetPicturePathList( CString strDir, CStringList &strPathList);
int GetPicturePathList( CString strDir, CStringList &strPathList, CStringList &strSubDirList );

void ReduceFrames( CImage* pPic );
void InsertFrames( CImage* pPic );

CRect MergeRects( CRect r1 , CRect r2 );
void SortRectFromTtoB(ObjRectArray &rect_array);
void SortRectFromBtoT(ObjRectArray &rect_array);

BOOL GetImageRectPart(IMAGE &bigImg, IMAGE &partImg, CRect &rect);
BOOL GetPicRectPart( CImage* pPic, CImage *pPartPic, CRect &rect );
BOOL GetPicRectPart( CDIBitmap* pPic, CDIBitmap *pPartPic, CRect &rect );

float randNum();

BOOL RegulateRect( CRect &rc, int l, int t, int r, int b );
BOOL WriteRect2Txt( fstream &fInfo, CRect rcCur );
BOOL WriteRcArray2Txt( fstream &fInfo, ObjRectArray& rcArray );

#endif // !defined(SCU_III_IMGFUC_INCLUDED_)